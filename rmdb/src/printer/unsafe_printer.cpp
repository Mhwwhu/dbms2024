#include "unsafe_printer.h"
#include "common/context.h"

#include <unistd.h>

using namespace std;

UnsafePrinter::UnsafePrinter()
{
    send_message_delimiter_.assign(1, '\0');
}

UnsafePrinter::~UnsafePrinter()
{
    if(fd_ >= 0) {
        close(fd_);
        fd_ = -1;
    }
}

RC UnsafePrinter::init(int fd)
{
    fd_ = fd;
    writer_ = std::make_unique<BufferedWriter>(fd);
    return RC::SUCCESS;
}

RC UnsafePrinter::write_state(Context* ctx)
{
    auto sql_result = ctx->sql_result;

    if(!sql_result.has_result()) return RC::INTERNAL;

    string result = RM_SUCC(sql_result.return_code()) ? "SUCCESS" : "FAILURE";
    result += "\n";

    RC rc = writer_->writen(result.c_str(), result.size());

    if(RM_FAIL(rc)) return RC::IOERR_WRITE;

    return RC::SUCCESS;
}

RC UnsafePrinter::write_result_internal(Context* ctx)
{
    auto& sql_result = ctx->sql_result;

    // 如果没有oper，或者已经执行失败，则直接返回状态
    if((sql_result.has_result() && RM_FAIL(sql_result.return_code())) || !sql_result.oper()) {
        return write_state(ctx);
    }

    // 尝试打开oper，失败则返回状态
    auto oper = sql_result.oper();
    RC rc = oper->open(ctx);
    if(RM_FAIL(rc)) {
        oper->close();
        sql_result.set_return_code(rc);
        return write_state(ctx);
    }

    // 如果没有tuple，比如InsertOper, DeleteOper等，则也要输出rc的结果
    if(!oper->has_tuple()) {
        oper->close();
        sql_result.set_return_code(rc);
        return write_state(ctx);
    }

    // 对于有tuple的情况，需要打印tuple
    auto schema = oper->tuple_schema();
    if(!schema) {
        oper->close();
        return RC::INTERNAL;
    }
    int cell_num = schema->cell_num();
    const char* delim;
    for(int i = 0; i < cell_num; i++) {
        auto spec = schema->cell_at(i);
        string name = spec->name();
        if(i == 0) delim = "| ";
        else delim = " | ";
        rc = writer_->writen(delim, strlen(delim));
        if(RM_FAIL(rc)) {
            oper->close();
            return rc;
        }
        rc = writer_->writen(name.c_str(), name.size());
        if(RM_FAIL(rc)) {
            oper->close();
            return rc;
        }
    }
    delim = " |";
    rc = writer_->writen(delim, strlen(delim));
    if(RM_FAIL(rc)) {
        oper->close();
        return rc;
    }

    if(cell_num > 0) {
        rc = writer_->writen("\n", 1);
        if(RM_FAIL(rc)) {
            oper->close();
            return rc;
        }
    }

    rc = write_tuple_result(ctx);
    if(RM_FAIL(rc)) {
        RC rc_close = oper->close();
		if (RM_FAIL(rc_close)) rc = rc_close;
		sql_result.set_return_code(rc);
		write_state(ctx);
        return rc;
    }

    return RC::SUCCESS;
}

RC UnsafePrinter::write_tuple_result(Context* ctx)
{
    RC rc = RC::SUCCESS;
    auto& sql_result = ctx->sql_result;
    auto oper = sql_result.oper();
    shared_ptr<ITuple> tuple;
    while(RM_SUCC(rc = oper->next())) {
        tuple = oper->current_tuple();
        int cell_num = tuple->cell_num();

        const char* delim;
        for(int i = 0; i < cell_num; i++) {
            if(i == 0) delim = "| ";
            else delim = " | ";
            rc = writer_->writen(delim, strlen(delim));
            if(RM_FAIL(rc)) {
                oper->close();
                return rc;
            }

            Value val;
            rc = tuple->cell_at(i, val);
            if(RM_FAIL(rc)) {
                oper->close();
                return rc;
            }

            rc = writer_->writen(val.to_string().c_str(), val.to_string().size());
            if(RM_FAIL(rc)) {
                oper->close();
                return rc;
            }
        }
        delim = " |";
        rc = writer_->writen(delim, strlen(delim));
        if(RM_FAIL(rc)) {
            oper->close();
            return rc;
        }
        
        rc = writer_->writen("\n", 1);
        if(RM_FAIL(rc)) {
            oper->close();
            return rc;
        }
    }

    if(rc == RC::RECORD_EOF) rc = RC::SUCCESS;
    return rc;
}
//unsafe_printer.cpp:171
RC UnsafePrinter::write_result(Context* ctx)
{
    RC rc;
    rc = write_result_internal(ctx);
    if(RM_FAIL(rc)) return rc;

    rc = writer_->writen(send_message_delimiter_.data(), send_message_delimiter_.size());
    if(RM_FAIL(rc)) return rc;

    writer_->flush();

    return RC::SUCCESS;
}