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

#include <memory>

#include "bitmap.h"
#include "rm_defs.h"
#include "common/rc.h"
#include "tuple/tuple.h"

class RmManager;
class Context;

/* 对表数据文件中的页面进行封装 */
struct RmPageHandle {
    const RmFileHdr *file_hdr = nullptr;  // 当前页面所在文件的文件头指针
    Page *page = nullptr;                 // 页面的实际数据，包括页面存储的数据、元信息等
    RmPageHdr *page_hdr = nullptr;        // page->data的第一部分，存储页面元信息，指针指向首地址，长度为sizeof(RmPageHdr)
    char *bitmap = nullptr;               // page->data的第二部分，存储页面的bitmap，指针指向首地址，长度为file_hdr->bitmap_size
    char *slots = nullptr;                // page->data的第三部分，存储表的记录，指针指向首地址，每个slot的长度为file_hdr->record_size

    RmPageHandle(const RmFileHdr *fhdr_, Page *page_) : file_hdr(fhdr_), page(page_) {
        page_hdr = reinterpret_cast<RmPageHdr *>(page->get_data() + page->OFFSET_PAGE_HDR);
        bitmap = page->get_data() + sizeof(RmPageHdr) + page->OFFSET_PAGE_HDR;
        slots = bitmap + file_hdr->bitmap_size;
    }
    RmPageHandle() = default;

    // 返回指定slot_no的slot存储收地址
    char* get_slot(int slot_no) const {
        return slots + slot_no * file_hdr->record_size;  // slots的首地址 + slot个数 * 每个slot的大小(每个record的大小)
    }
};

/* 每个RmFileHandle对应一个表的数据文件，里面有多个page，每个page的数据封装在RmPageHandle中 */
class RmFileHandle {      
    friend class RecScan;    
    friend class RmManager;

private:
    DiskManager *disk_manager_;
    BufferPoolManager *buffer_pool_manager_;
    int fd_;        // 打开文件后产生的文件句柄
    RmFileHdr file_hdr_;    // 文件头，维护当前表文件的元数据

public:
    RmFileHandle(DiskManager *disk_manager, BufferPoolManager *buffer_pool_manager, int fd)
        : disk_manager_(disk_manager), buffer_pool_manager_(buffer_pool_manager), fd_(fd) {
        // 注意：这里从磁盘中读出文件描述符为fd的文件的file_hdr，读到内存中
        // 这里实际就是初始化file_hdr，只不过是从磁盘中读出进行初始化
        // init file_hdr_
        disk_manager_->read_page(fd, RM_FILE_HDR_PAGE, (char *)&file_hdr_, sizeof(file_hdr_));
        // disk_manager管理的fd对应的文件中，设置从file_hdr_.num_pages开始分配page_no
        disk_manager_->set_fd2pageno(fd, file_hdr_.num_pages);
    }

    RmFileHdr get_file_hdr() { return file_hdr_; }
    int GetFd() { return fd_; }

    /* 判断指定位置上是否已经存在一条记录，通过Bitmap来判断 */
    bool is_record(const Rid &rid) const {
        RmPageHandle page_handle(&file_hdr_, nullptr);
        RC rc = fetch_page_handle(rid.page_no, page_handle);
        if(RM_FAIL(rc)) return false;
        return Bitmap::is_set(page_handle.bitmap, rid.slot_no);  // page的slot_no位置上是否有record
    }

    RC get_record(const Rid &rid, Context *context, std::shared_ptr<RmRecord>& record) const;

    RC insert_record(char *buf, Rid& rid, Context *context);

    RC insert_record(const Rid &rid, char *buf);

    RC delete_record(const Rid &rid, Context *context);

    RC update_record(const Rid &rid, char *buf, Context *context);

    RC create_new_page_handle(RmPageHandle& handle);

    RC fetch_page_handle(page_id_t page_no, RmPageHandle& handle) const;

private:
    RC fetch_free_page_handle(RmPageHandle& handle);

};