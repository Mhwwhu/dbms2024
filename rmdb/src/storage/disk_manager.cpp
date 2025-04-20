/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "storage/disk_manager.h"

#include <assert.h>    // for assert
#include <string.h>    // for memset
#include <sys/stat.h>  // for stat
#include <unistd.h>    // for lseek

using namespace std;

DiskManager::DiskManager() { memset(fd2pageno_, 0, MAX_FD * (sizeof(std::atomic<page_id_t>) / sizeof(char))); }

/**
 * @description: 将数据写入文件的指定磁盘页面中
 * @param {int} fd 磁盘文件的文件句柄
 * @param {page_id_t} page_no 写入目标页面的page_id
 * @param {char} *offset 要写入磁盘的数据
 * @param {int} num_bytes 要写入磁盘的数据大小
 */
RC DiskManager::write_page(int fd, page_id_t page_no, const char *offset, int num_bytes) {
    // Todo:
    // 1.lseek()定位到文件头，通过(fd,page_no)可以定位指定页面及其在磁盘文件中的偏移量
    // 2.调用write()函数
    // 注意write返回值与num_bytes不等时 throw InternalError("DiskManager::write_page Error");
    if(lseek(fd, page_no * PAGE_SIZE, SEEK_SET) == -1) return RC::IOERR_SEEK;
    ssize_t size = write(fd, offset, num_bytes);
    if(size != num_bytes) {
        return RC::IOERR_WRITE;
    }

    return RC::SUCCESS;
}

/**
 * @description: 读取文件中指定编号的页面中的部分数据到内存中
 * @param {int} fd 磁盘文件的文件句柄
 * @param {page_id_t} page_no 指定的页面编号
 * @param {char} *offset 读取的内容写入到offset中
 * @param {int} num_bytes 读取的数据量大小
 */
RC DiskManager::read_page(int fd, page_id_t page_no, char *offset, int num_bytes) {
    // Todo:
    // 1.lseek()定位到文件头，通过(fd,page_no)可以定位指定页面及其在磁盘文件中的偏移量
    // 2.调用read()函数
    // 注意read返回值与num_bytes不等时，throw InternalError("DiskManager::read_page Error");
    if(lseek(fd, page_no * PAGE_SIZE, SEEK_SET) == -1) return RC::IOERR_SEEK;
    ssize_t size = read(fd, offset, num_bytes);
    if(size != num_bytes) {
        return RC::IOERR_READ;
    }
    return RC::SUCCESS;
}

/**
 * @description: 分配一个新的页号
 * @return {page_id_t} 分配的新页号
 * @param {int} fd 指定文件的文件句柄
 */
page_id_t DiskManager::allocate_page(int fd) {
    // 简单的自增分配策略，指定文件的页面编号加1
    assert(fd >= 0 && fd < MAX_FD);
    return fd2pageno_[fd]++;
}

RC DiskManager::deallocate_page(__attribute__((unused)) page_id_t page_id) { return RC::SUCCESS; }

bool DiskManager::is_dir(const std::string& path) {
    struct stat st;
    return stat(path.c_str(), &st) == 0 && S_ISDIR(st.st_mode);
}

RC DiskManager::create_dir(const std::string &path) {
    // Create a subdirectory
    std::string cmd = "mkdir " + path;
    if (system(cmd.c_str()) < 0) {  // 创建一个名为path的目录
        return RC::UNIX_ERROR;
    }
}

RC DiskManager::destroy_dir(const std::string &path) {
    std::string cmd = "rm -r " + path;
    if (system(cmd.c_str()) < 0) {
        return RC::UNIX_ERROR;
    }
}

/**
 * @description: 判断指定路径文件是否存在
 * @return {bool} 若指定路径文件存在则返回true 
 * @param {string} &path 指定路径文件
 */
bool DiskManager::is_file(const std::string &path) {
    // 用struct stat获取文件信息
    struct stat st;
    return stat(path.c_str(), &st) == 0 && S_ISREG(st.st_mode);
}

/**
 * @description: 用于创建指定路径文件
 * @return {*}
 * @param {string} &path
 */
RC DiskManager::create_file(const std::string &path) {
    // Todo:
    // 调用open()函数，使用O_CREAT模式
    // 注意不能重复创建相同文件
    if(is_file(path)) {
        return RC::FILE_EXIST;
    }
    int result = open(path.c_str(), O_CREAT | O_RDWR, 0666);

    if(result < 0) return RC::IOERR_OPEN;

    return RC::SUCCESS;
}

/**
 * @description: 删除指定路径的文件
 * @param {string} &path 文件所在路径
 */
RC DiskManager::destroy_file(const std::string &path) {
    // Todo:
    // 调用unlink()函数
    // 注意不能删除未关闭的文件
    if(!is_file(path)) {
        return RC::FILE_NOT_EXIST;
    }
    if(path2fd_.find(path) != path2fd_.end()) {
        return RC::FILE_NOT_CLOSED;
    }
    int result = unlink(path.c_str());

    if(result != 0) return RC::IOERR_UNLINK;

    return RC::SUCCESS;
}


/**
 * @description: 打开指定路径文件 
 * @return {int} 返回打开的文件的文件句柄
 * @param {string} &path 文件所在路径
 */
RC DiskManager::open_file(const std::string &path, int& fd) {
    // Todo:
    // 调用open()函数，使用O_RDWR模式
    // 注意不能重复打开相同文件，并且需要更新文件打开列表
    if(!is_file(path)) {
        return RC::FILE_NOT_EXIST;
    }
    if(path2fd_.find(path) != path2fd_.end()) {
        return RC::FILE_NOT_CLOSED;
    }
    fd = open(path.c_str(), O_RDWR);
    if(fd == -1) {
        return RC::IOERR_OPEN;
    }
    path2fd_[path] = fd;
    fd2path_[fd] = path;
    return RC::SUCCESS;
}

/**
 * @description:用于关闭指定路径文件 
 * @param {int} fd 打开的文件的文件句柄
 */
RC DiskManager::close_file(int fd) {
    // Todo:
    // 调用close()函数
    // 注意不能关闭未打开的文件，并且需要更新文件打开列表
    if(fd2path_.find(fd) == fd2path_.end()) {
        return RC::FILE_NOT_OPENED;
    }
    if(close(fd) != 0) return RC::IOERR_CLOSE;
    string path = fd2path_[fd];
    fd2path_.erase(fd);
    path2fd_.erase(path);
    fd2pageno_[fd] = 0;

    return RC::SUCCESS;
}


/**
 * @description: 获得文件的大小
 * @return {int} 文件的大小
 * @param {string} &file_name 文件名
 */
RC DiskManager::get_file_size(const std::string &file_name, int& size) {
    struct stat stat_buf;
    int result = stat(file_name.c_str(), &stat_buf);
    size =  result == 0 ? stat_buf.st_size : -1;
    if(result != 0) return RC::FILE_NOT_EXIST;
    return RC::SUCCESS;
}

/**
 * @description: 根据文件句柄获得文件名
 * @return {string} 文件句柄对应文件的文件名
 * @param {int} fd 文件句柄
 */
RC DiskManager::get_file_name(int fd, std::string& name) {
    if (!fd2path_.count(fd)) {
        return RC::FILE_NOT_OPENED;
    }
    name = fd2path_[fd];
    return RC::SUCCESS;
}

/**
 * @description:  获得文件名对应的文件句柄
 * @return {int} 文件句柄
 * @param {string} &file_name 文件名
 */
RC DiskManager::get_file_fd(const std::string &file_name, int& fd) {
    if (!path2fd_.count(file_name)) {
        return open_file(file_name, fd);
    }
    fd = path2fd_[file_name];
    return RC::SUCCESS;
}


/**
 * @description:  读取日志文件内容
 * @return {int} 返回读取的数据量，若为-1说明读取数据的起始位置超过了文件大小
 * @param {char} *log_data 读取内容到log_data中
 * @param {int} size 读取的数据量大小
 * @param {int} offset 读取的内容在文件中的位置
 */
RC DiskManager::read_log(char *log_data, int size, int offset, int& read_size) {
    RC rc = RC::SUCCESS;
    // read log file from the previous end
    if (log_fd_ == -1) {
        rc = open_file(LOG_FILE_NAME, log_fd_);
        if(RM_FAIL(rc)) return rc;
    }
    int file_size = -1;
    rc = get_file_size(LOG_FILE_NAME, file_size);
    if(RM_FAIL(rc)) return rc;

    if (offset > file_size) {
        return RC::OVERFLOW;
    }

    size = std::min(size, file_size - offset);
    if(size == 0) {
        read_size = 0;
        return RC::SUCCESS;
    }
    if(lseek(log_fd_, offset, SEEK_SET) < 0) return RC::IOERR_SEEK;
    read_size = read(log_fd_, log_data, size);
    assert(read_size == size);
    return RC::SUCCESS;
}


/**
 * @description: 写日志内容
 * @param {char} *log_data 要写入的日志内容
 * @param {int} size 要写入的内容大小
 */
RC DiskManager::write_log(char *log_data, int size) {
    RC rc = RC::SUCCESS;
    if (log_fd_ == -1) {
        rc = open_file(LOG_FILE_NAME, log_fd_);
        if(RM_FAIL(rc)) return rc;
    }

    // write from the file_end
    if(lseek(log_fd_, 0, SEEK_END) < 0) return RC::IOERR_SEEK;
    ssize_t bytes_write = write(log_fd_, log_data, size);
    if (bytes_write != size) {
        return RC::IOERR_WRITE;
    }

    return rc;
}