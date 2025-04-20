/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include <netinet/in.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>
#include <atomic>

#include "errors.h"
#include "optimizer/optimizer.h"
#include "recovery/log_recovery.h"
#include "plan/plan.h"
#include "plan/planner.h"
#include "portal.h"
#include "analyze/analyze.h"
#include "operator/operator_generator.h"
#include "printer/printer.h"

#include "logger/logger.h"

#define SOCK_PORT 8765
#define MAX_CONN_LIMIT 8

static bool should_exit = false;

// 构建全局所需的管理器对象
auto printer_factory = std::make_unique<PrinterFactory>();
auto disk_manager = std::make_unique<DiskManager>();
auto buffer_pool_manager = std::make_unique<BufferPoolManager>(BUFFER_POOL_SIZE, disk_manager.get());
auto rm_manager = std::make_unique<RmManager>(disk_manager.get(), buffer_pool_manager.get());
auto ix_manager = std::make_unique<IxManager>(disk_manager.get(), buffer_pool_manager.get());
auto sm_manager = std::make_unique<SmManager>(disk_manager.get(), buffer_pool_manager.get(), rm_manager.get(), ix_manager.get());
auto lock_manager = std::make_unique<LockManager>();
auto txn_manager = std::make_unique<TransactionManager>(lock_manager.get(), sm_manager.get());
auto planner = std::make_unique<Planner>(sm_manager.get());
auto operator_generator = std::make_unique<OperatorGenerator>();
auto optimizer = std::make_unique<Optimizer>(sm_manager.get(), planner.get(), operator_generator.get());
auto log_manager = std::make_unique<LogManager>(disk_manager.get());
auto recovery = std::make_unique<RecoveryManager>(disk_manager.get(), buffer_pool_manager.get(), sm_manager.get());
auto portal = std::make_unique<Portal>(sm_manager.get());
auto analyze = std::make_unique<Analyze>(sm_manager.get());
auto parser = std::make_unique<Parser>();
pthread_mutex_t *buffer_mutex;
pthread_mutex_t *sockfd_mutex;

static jmp_buf jmpbuf;
void sigint_handler(int signo) {
    should_exit = true;
    log_manager->flush_log_to_disk();
    std::cout << "The Server receive Crtl+C, will been closed\n";
    longjmp(jmpbuf, 1);
}

// 判断当前正在执行的是显式事务还是单条SQL语句的事务，并更新事务ID
void SetTransaction(txn_id_t *txn_id, Context *context) {
    context->txn_ = txn_manager->get_transaction(*txn_id);
    if(context->txn_ == nullptr || context->txn_->get_state() == TransactionState::COMMITTED ||
        context->txn_->get_state() == TransactionState::ABORTED) {
        context->txn_ = txn_manager->begin(nullptr, context->log_mgr_);
        *txn_id = context->txn_->get_transaction_id();
        context->txn_->set_txn_mode(false);
    }
}

RC handle_sql(Context *context) {
    RC rc = RC::SUCCESS;

    // 语法解析
    rc = parser->handle_request(context);
    if(RM_FAIL(rc)) {
        LOG_ERROR("Failed to do parse");
        context->sql_result.set_return_code(rc);
        return rc;
    }

    // 语义分析
    rc = analyze->handle_request(context);
    if(RM_FAIL(rc)) {
        LOG_ERROR("Failed to do analyze");
        context->sql_result.set_return_code(rc);
        return rc;
    }

    // 优化器
    rc = optimizer->handle_request(context);
    if(RM_FAIL(rc)) {
        LOG_ERROR("Failed to do optimize");
        context->sql_result.set_return_code(rc);
        return rc;
    }

    // 执行器
    rc = portal->handle_request(context);
    if(RM_FAIL(rc)) {
        LOG_ERROR("Failed to do execute");
        context->sql_result.set_return_code(rc);
        return rc;
    }

    return rc;
}

void *client_handler(void *sock_fd) {
    int fd = *((int *)sock_fd);
    pthread_mutex_unlock(sockfd_mutex);

    int i_recvBytes;
    // 接收客户端发送的请求
    char data_recv[BUFFER_LENGTH];
    // 需要返回给客户端的结果
    char *data_send = new char[BUFFER_LENGTH];
    // 需要返回给客户端的结果的长度
    int offset = 0;
    // 记录客户端当前正在执行的事务ID
    txn_id_t txn_id = INVALID_TXN_ID;

    std::string output = "establish client connection, sockfd: " + std::to_string(fd) + "\n";
    std::cout << output;
    LOG_INFO("establish client connection, sockfd: {}", fd);

    auto client_printer = printer_factory->get_printer(PrinterType::UNSAFE_PRINTER);
    client_printer->init(fd);

    while (true) {
        std::cout << "Waiting for request..." << std::endl;
        memset(data_recv, 0, BUFFER_LENGTH);

        i_recvBytes = read(fd, data_recv, BUFFER_LENGTH);

        if (i_recvBytes == 0) {
            std::cout << "Maybe the client has closed" << std::endl;
            break;
        }
        if (i_recvBytes == -1) {
            LOG_ERROR("client read error, errorno: {}", errno);
            break;
        }
        
        printf("i_recvBytes: %d \n ", i_recvBytes);
        LOG_INFO("i_recvBytes: {}", i_recvBytes);

        if (strcmp(data_recv, "exit") == 0) {
            std::cout << "Client exit." << std::endl;
            break;
        }
        if (strcmp(data_recv, "crash") == 0) {
            std::cout << "Server crash" << std::endl;
            exit(1);
        }

        std::cout << "Read from client " << fd << ": " << data_recv << std::endl;
        LOG_INFO("Read from client {}: {}", fd, data_recv);

        memset(data_send, '\0', BUFFER_LENGTH);
        offset = 0;

        // 开启事务，初始化系统所需的上下文信息（包括事务对象指针、锁管理器指针、日志管理器指针、存放结果的buffer、记录结果长度的变量）
        Context *context = new Context(lock_manager.get(), log_manager.get(),  nullptr, sm_manager.get(), txn_manager.get(), data_send, &offset);
        SetTransaction(&txn_id, context);
        
        context->sql = data_recv;
        try {
            std::cout << "txn id: " << context->txn_->get_transaction_id() << std::endl;
            handle_sql(context);
            RC rc = client_printer->write_result(context);
            if(RM_FAIL(rc)) {
                LOG_ERROR("Getting result failed, rc = {}", strrc(rc));
            }

            // TODO 如果执行失败，那么事务也需要回滚
            
        } catch (TransactionAbortException &e) {
            // 事务需要回滚，需要把abort信息返回给客户端并写入output.txt文件中
            std::string str = "abort\n";
            memcpy(data_send, str.c_str(), str.length());
            data_send[str.length()] = '\0';
            offset = str.length();

            // 回滚事务
            txn_manager->abort(context->txn_, log_manager.get());
            std::cout << e.GetInfo() << std::endl;

            std::fstream outfile;
            outfile.open("output.txt", std::ios::out | std::ios::app);
            outfile << str;
            outfile.close();
        }

        // future TODO: 格式化 sql_handler.result, 传给客户端
        // send result with fixed format, use protobuf in the future
        // if (write(fd, data_send, offset + 1) == -1) {
        //     break;
        // }
        // 如果是单挑语句，需要按照一个完整的事务来执行，所以执行完当前语句后，自动提交事务
        if(context->txn_->get_txn_mode() == false)
        {
            txn_manager->commit(context->txn_, context->log_mgr_);
        }
    }

    // Clear
    std::cout << "Terminating current client_connection..." << std::endl;
    pthread_exit(NULL);  // terminate calling thread!
}

void start_server() {
    // init mutex
    buffer_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    sockfd_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(buffer_mutex, nullptr);
    pthread_mutex_init(sockfd_mutex, nullptr);

    int sockfd_server;
    int fd_temp;
    struct sockaddr_in s_addr_in {};

    // 初始化连接
    sockfd_server = socket(AF_INET, SOCK_STREAM, 0);  // ipv4,TCP
    assert(sockfd_server != -1);
    int val = 1;
    setsockopt(sockfd_server, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

    // before bind(), set the attr of structure sockaddr.
    memset(&s_addr_in, 0, sizeof(s_addr_in));
    s_addr_in.sin_family = AF_INET;
    s_addr_in.sin_addr.s_addr = htonl(INADDR_ANY);
    s_addr_in.sin_port = htons(SOCK_PORT);
    fd_temp = bind(sockfd_server, (struct sockaddr *)(&s_addr_in), sizeof(s_addr_in));
    if (fd_temp == -1) {
        LOG_CRITICAL("Bind error!");
        exit(1);
    }

    fd_temp = listen(sockfd_server, MAX_CONN_LIMIT);
    if (fd_temp == -1) {
        LOG_CRITICAL("Listen error!");
        exit(1);
    }

    while (!should_exit) {
        std::cout << "Waiting for new connection..." << std::endl;
        pthread_t thread_id;
        struct sockaddr_in s_addr_client {};
        int client_length = sizeof(s_addr_client);

        if (setjmp(jmpbuf)) {
            std::cout << "Break from Server Listen Loop\n";
            break;
        }

        // Block here. Until server accepts a new connection.
        pthread_mutex_lock(sockfd_mutex);
        int sockfd = accept(sockfd_server, (struct sockaddr *)(&s_addr_client), (socklen_t *)(&client_length));
        if (sockfd == -1) {
            LOG_CRITICAL("Accept error!");
            continue;  // ignore current socket ,continue while loop.
        }
        
        // 和客户端建立连接，并开启一个线程负责处理客户端请求
        if (pthread_create(&thread_id, nullptr, &client_handler, (void *)(&sockfd)) != 0) {
            LOG_CRITICAL("Create thread failed!");
            break;  // break while loop
        }

    }

    // Clear
    std::cout << " Try to close all client-connection.\n";
    int ret = shutdown(sockfd_server, SHUT_WR);  // shut down the all or part of a full-duplex connection.
    if(ret == -1) { printf("%s\n", strerror(errno)); }
//    assert(ret != -1);
    sm_manager->close_db();
    std::cout << " DB has been closed.\n";
    std::cout << "Server shuts down." << std::endl;
    LOG_INFO("DB has been closed.");
    LOG_INFO("Server shuts down.");
}

int main(int argc, char **argv) {
    if (argc != 2) {
        // 需要指定数据库名称
        std::cerr << "Usage: " << argv[0] << " <database>" << std::endl;
        exit(1);
    }

    signal(SIGINT, sigint_handler);
    setup_logger();
    try {
        std::cout << "\n"
                     "  _____  __  __ _____  ____  \n"
                     " |  __ \\|  \\/  |  __ \\|  _ \\ \n"
                     " | |__) | \\  / | |  | | |_) |\n"
                     " |  _  /| |\\/| | |  | |  _ < \n"
                     " | | \\ \\| |  | | |__| | |_) |\n"
                     " |_|  \\_\\_|  |_|_____/|____/ \n"
                     "\n"
                     "Welcome to RMDB!\n"
                     "Type 'help;' for help.\n"
                     "\n";
        // Database name is passed by args
        RC rc;
        std::string db_name = argv[1];
        if (!disk_manager->is_dir(db_name)) {
            LOG_INFO("Database {} is not found, create a new one", db_name);
            // Database not found, create a new one
            rc = sm_manager->create_db(db_name);
            if(RM_FAIL(rc)) {
                LOG_CRITICAL("Create database {} failed, rc = {}", db_name, strrc(rc));
                exit(1);
            }
        }
        // Open database
        rc = sm_manager->open_db(db_name);
        if(RM_FAIL(rc)) {
            LOG_CRITICAL("Open database {} failed, rc = {}", db_name, strrc(rc));
            exit(1);
        }

        LOG_INFO("Database {} opened", db_name);

        // recovery database
        recovery->analyze();
        recovery->redo();
        recovery->undo();
        
        // 开启服务端，开始接受客户端连接
        start_server();
    } catch (RMDBError &e) {
        LOG_CRITICAL("Fatal error: {}", e.what());
        exit(1);
    }
    spdlog::shutdown();
    return 0;
}
