/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "rm_scan.h"
#include "rm_file_handle.h"

/**
 * @brief 初始化file_handle和rid
 * @param file_handle
 */
RecScan::RecScan(const RmFileHandle *file_handle, std::shared_ptr<ConjunctionExpr> filter)
 : file_handle_(file_handle), filter_(filter) {}

RC RecScan::open(Context* ctx) {
    context_ = ctx;
    record_ = std::make_shared<RmRecord>();
    record_->rid.page_no = INVALID_PAGE_ID;

    return RC::SUCCESS;
}

/**
 * @brief 找到文件中下一个存放了记录的位置
 */
RC RecScan::next() {
    // Todo:
    // 找到文件中下一个存放了记录的非空闲位置，用rid_来指向这个位置
    RC rc = RC::SUCCESS;

    auto& rid = record_->rid;

    if(rid.page_no == INVALID_PAGE_ID) {
        rid.page_no = 1;
        rid.slot_no = -1;
    }

    while(rid.page_no < file_handle_->file_hdr_.num_pages) {
        RmPageHandle page_handle;
        auto file_hdr = file_handle_->file_hdr_;
        rc = file_handle_->fetch_page_handle(rid.page_no, page_handle);
        if(RM_FAIL(rc)) return rc;
        int pos = Bitmap::next_bit(true, page_handle.bitmap, file_hdr.num_records_per_page, rid.slot_no);

        // 如果没有下一个记录了，则更新page_no
        if(pos == file_hdr.num_records_per_page) {
            rid.page_no++;
            rid.slot_no = -1;
        }
        else {
            rid.slot_no = pos;
            record_->data = new char[file_hdr.record_size];
            memcpy(record_->data, page_handle.get_slot(pos), file_hdr.record_size);
            record_->allocated_ = true;
            record_->size = file_hdr.record_size;
            return RC::SUCCESS;
        }
    }

    return RC::RECORD_EOF;
}

RC RecScan::close() {
    context_ = nullptr;
    record_ = nullptr;
}

/**
 * @brief RmScan内部存放的rid
 */
std::shared_ptr<RmRecord> RecScan::record() const {
    return record_;
}