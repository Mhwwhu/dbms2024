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

#include <assert.h>

#include "bitmap.h"
#include "rm_defs.h"
#include "rm_file_handle.h"
#include "common/rc.h"

/* 记录管理器，用于管理表的数据文件，进行文件的创建、打开、删除、关闭 */
class RmManager {
   private:
    DiskManager *disk_manager_;
    BufferPoolManager *buffer_pool_manager_;

   public:
    RmManager(DiskManager *disk_manager, BufferPoolManager *buffer_pool_manager)
        : disk_manager_(disk_manager), buffer_pool_manager_(buffer_pool_manager) {}

    /**
     * @description: 创建表的数据文件并初始化相关信息
     * @param {string&} filename 要创建的文件名称
     * @param {int} record_size 表中记录的大小
     */ 
    RC create_file(const std::string& filename, int record_size) {
        RC rc = RC::SUCCESS;
        if (record_size < 1 || record_size > RM_MAX_RECORD_SIZE) {
            return RC::INVALID_ARGUMENT;
        }
        disk_manager_->create_file(filename);

        int fd;
        if(RM_FAIL(rc = disk_manager_->open_file(filename, fd))) return rc;

        // 初始化file header
        RmFileHdr file_hdr{};
        file_hdr.record_size = record_size;
        file_hdr.num_pages = 1;
        file_hdr.first_free_page_no = RM_NO_PAGE;
        // We have: sizeof(hdr) + (n + 7) / 8 + n * record_size <= PAGE_SIZE
        file_hdr.num_records_per_page =
            (BITMAP_WIDTH * (PAGE_SIZE - 1 - (int)sizeof(RmFileHdr)) + 1) / (1 + record_size * BITMAP_WIDTH);
        file_hdr.bitmap_size = (file_hdr.num_records_per_page + BITMAP_WIDTH - 1) / BITMAP_WIDTH;

        // 将file header写入磁盘文件（名为file name，文件描述符为fd）中的第0页
        // head page直接写入磁盘，没有经过缓冲区的NewPage，那么也就不需要FlushPage
        if(RM_FAIL(rc = disk_manager_->write_page(fd, RM_FILE_HDR_PAGE, (char *)&file_hdr, sizeof(file_hdr)))) return rc;
        if(RM_FAIL(rc = disk_manager_->close_file(fd))) return rc;

        return RC::SUCCESS;
    }

    /**
     * @description: 删除表的数据文件
     * @param {string&} filename 要删除的文件名称
     */    
    RC destroy_file(const std::string& filename) { return disk_manager_->destroy_file(filename); }

    // 注意这里打开文件，创建并返回了record file handle的指针
    /**
     * @description: 打开表的数据文件，并返回文件句柄
     * @param {string&} filename 要打开的文件名称
     * @return {unique_ptr<RmFileHandle>} 文件句柄的指针
     */
    RC open_file(const std::string& filename, std::unique_ptr<RmFileHandle>& rm_file_handle) {
        int fd;
        RC rc;
        if(RM_FAIL(rc = disk_manager_->open_file(filename, fd))) return rc;
        rm_file_handle = std::make_unique<RmFileHandle>(disk_manager_, buffer_pool_manager_, fd);
        return RC::SUCCESS;
    }
    /**
     * @description: 关闭表的数据文件
     * @param {RmFileHandle*} file_handle 要关闭文件的句柄
     */
    RC close_file(const RmFileHandle* file_handle) {
        RC rc;
        if(RM_FAIL(rc = disk_manager_->write_page(file_handle->fd_, RM_FILE_HDR_PAGE, (char *)&file_handle->file_hdr_,
                                  sizeof(file_handle->file_hdr_))))
        {
            return rc;
        }
        // 缓冲区的所有页刷到磁盘，注意这句话必须写在close_file前面
        if(RM_FAIL(rc = buffer_pool_manager_->flush_all_pages(file_handle->fd_))) return rc;
        if(RM_FAIL(rc = disk_manager_->close_file(file_handle->fd_))) return rc;

        return RC::SUCCESS;
    }
};
