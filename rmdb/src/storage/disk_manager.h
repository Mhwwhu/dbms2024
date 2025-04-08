/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#pragma once

#include <fcntl.h>     
#include <sys/stat.h>  
#include <unistd.h>    

#include <atomic>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

#include "common/config.h"
#include "errors.h"  
#include "common/rc.h"

/**
 * @description: DiskManager的作用主要是根据上层的需要对磁盘文件进行操作
 */
class DiskManager {
   public:
    explicit DiskManager();

    ~DiskManager() = default;

    RC write_page(int fd, page_id_t page_no, const char *offset, int num_bytes);

    RC read_page(int fd, page_id_t page_no, char *offset, int num_bytes);

    page_id_t allocate_page(int fd);

    RC deallocate_page(page_id_t page_id);

    /*目录操作*/
    bool is_dir(const std::string &path);

    RC create_dir(const std::string &path);

    RC destroy_dir(const std::string &path);

    /*文件操作*/
    bool is_file(const std::string &path);

    RC create_file(const std::string &path);

    RC destroy_file(const std::string &path);

    RC open_file(const std::string &path, int& fd);

    RC close_file(int fd);

    RC get_file_size(const std::string &file_name, int& size);

    RC get_file_name(int fd, std::string& name);

    RC get_file_fd(const std::string &file_name, int& fd);

    /*日志操作*/
    RC read_log(char *log_data, int size, int offset, int& read_size);

    RC write_log(char *log_data, int size);

    void SetLogFd(int log_fd) { log_fd_ = log_fd; }

    int GetLogFd() { return log_fd_; }

    /**
     * @description: 设置文件已经分配的页面个数
     * @param {int} fd 文件对应的文件句柄
     * @param {int} start_page_no 已经分配的页面个数，即文件接下来从start_page_no开始分配页面编号
     */
    void set_fd2pageno(int fd, int start_page_no) { fd2pageno_[fd] = start_page_no; }

    /**
     * @description: 获得文件目前已分配的页面个数，即如果文件要分配一个新页面，需要从fd2pagenp_[fd]开始分配
     * @return {page_id_t} 已分配的页面个数 
     * @param {int} fd 文件对应的句柄
     */
    page_id_t get_fd2pageno(int fd) { return fd2pageno_[fd]; }

    static constexpr int MAX_FD = 8192;

   private:
    // 文件打开列表，用于记录文件是否被打开
    std::unordered_map<std::string, int> path2fd_;  //<Page文件磁盘路径,Page fd>哈希表
    std::unordered_map<int, std::string> fd2path_;  //<Page fd,Page文件磁盘路径>哈希表

    int log_fd_ = -1;                             // WAL日志文件的文件句柄，默认为-1，代表未打开日志文件
    std::atomic<page_id_t> fd2pageno_[MAX_FD]{};  // 文件中已经分配的页面个数，初始值为0
};