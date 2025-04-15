/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "rm_file_handle.h"

using namespace std;

/**
 * @description: 获取当前表中记录号为rid的记录
 * @param {Rid&} rid 记录号，指定记录的位置
 * @param {Context*} context
 * @return {unique_ptr<RmRecord>} rid对应的记录对象指针
 */
RC RmFileHandle::get_record(const Rid& rid, Context* context, shared_ptr<RmRecord>& record) const {
    // Todo:
    // 1. 获取指定记录所在的page handle
    // 2. 初始化一个指向RmRecord的指针（赋值其内部的data和size）

    RmPageHandle page_handle;
    RC rc = fetch_page_handle(rid.page_no, page_handle);
    if (RM_FAIL(rc)) {
        return rc;
    }

    // 检查指定位置是否有记录
    if (!Bitmap::is_set(page_handle.bitmap, rid.slot_no)) {
        return RC::NOT_EXIST;
    }

    // 初始化 RmRecord
    record = make_shared<RmRecord>();
    record->size = file_hdr_.record_size;
    record->data = new char[record->size];
    //record->rid = rid;
    memcpy(record->data, page_handle.get_slot(rid.slot_no), record->size);

    buffer_pool_manager_->unpin_page(page_handle.page->get_page_id(), false);
    return RC::SUCCESS;

}

/**
 * @description: 在当前表中插入一条记录，不指定插入位置
 * @param {char*} buf 要插入的记录的数据
 * @param {Context*} context
 * @return {Rid} 插入的记录的记录号（位置）
 */
RC RmFileHandle::insert_record(char *buf, Rid& rid, Context *context) {
    // Todo:
    // 1. 获取当前未满的page handle
    // 2. 在page handle中找到空闲slot位置
    // 3. 将buf复制到空闲slot位置
    // 4. 更新page_handle.page_hdr中的数据结
    // 注意考虑插入一条记录后页面已满的情况，需要更新file_hdr_.first_free_page_no

    RmPageHandle handle;
    RC rc = fetch_free_page_handle(handle);
    if(RM_FAIL(rc)) return rc;

    auto bitmap = handle.bitmap;
    auto bitmap_size = file_hdr_.bitmap_size;
    int slot_no = Bitmap::first_bit(false, bitmap, bitmap_size);
    char* slot = handle.get_slot(slot_no);

    memcpy(slot, buf, file_hdr_.record_size);
    handle.page_hdr->num_records++;
    Bitmap::set(bitmap, slot_no);
    
    // 如果插入之后页面已满，则需要更新file_hdr_
    if(Bitmap::first_bit(false, bitmap, bitmap_size) == bitmap_size) {
        file_hdr_.first_free_page_no = handle.page_hdr->next_free_page_no;
    }

    buffer_pool_manager_->unpin_page(handle.page->get_page_id(), true);

    return RC::SUCCESS;
}

/**
 * @description: 在当前表中的指定位置插入一条记录
 * @param {Rid&} rid 要插入记录的位置
 * @param {char*} buf 要插入记录的数据
 */
RC RmFileHandle::insert_record(const Rid &rid, char *buf) {

    RmPageHandle page_handle;
    RC rc = fetch_page_handle(rid.page_no, page_handle);
    if (RM_FAIL(rc)) {
        return rc;
    }
    // 检查指定位置是否已经有记录
    if (Bitmap::is_set(page_handle.bitmap, rid.slot_no)) {
        buffer_pool_manager_->unpin_page(page_handle.page->get_page_id(), false);
        return RC::EXIST;
    }

    // 将数据复制到指定位置
    char* slot = page_handle.get_slot(rid.slot_no);
    memcpy(slot, buf, file_hdr_.record_size);

    // 更新位图和页面头信息
    Bitmap::set(page_handle.bitmap, rid.slot_no);
    page_handle.page_hdr->num_records++;

    // 检查页面是否已满
    if (Bitmap::first_bit(false, page_handle.bitmap, file_hdr_.bitmap_size) == file_hdr_.bitmap_size) {
      
        file_hdr_.first_free_page_no = page_handle.page_hdr->next_free_page_no;
    }


    buffer_pool_manager_->unpin_page(page_handle.page->get_page_id(), true);

    return RC::SUCCESS;

}

/**
 * @description: 删除记录文件中记录号为rid的记录
 * @param {Rid&} rid 要删除的记录的记录号（位置）
 * @param {Context*} context
 */
RC RmFileHandle::delete_record(const Rid &rid, Context *context) {
    // Todo:
    // 1. 获取指定记录所在的page handle
    // 2. 更新page_handle.page_hdr中的数据结构
    // 注意考虑删除一条记录后页面未满的情况，需要调用release_page_handle()


    RmPageHandle page_handle;
    RC rc = fetch_page_handle(rid.page_no, page_handle);
    if (RM_FAIL(rc)) {
        return rc;
    }

    // 检查指定位置是否有记录
    if (!Bitmap::is_set(page_handle.bitmap, rid.slot_no)) {
        buffer_pool_manager_->unpin_page(page_handle.page->get_page_id(), false);
        return RC::NOT_EXIST;
    }

    // 清除位图中的标记
    Bitmap::reset(page_handle.bitmap, rid.slot_no);
    page_handle.page_hdr->num_records--;

    // 检查页面是否从满变为未满
    if (Bitmap::first_bit(false, page_handle.bitmap, file_hdr_.bitmap_size) < file_hdr_.bitmap_size) {

        if (file_hdr_.first_free_page_no == -1 || file_hdr_.first_free_page_no > rid.page_no) {
            page_handle.page_hdr->next_free_page_no = file_hdr_.first_free_page_no;
            file_hdr_.first_free_page_no = rid.page_no;
        }
    }

    buffer_pool_manager_->unpin_page(page_handle.page->get_page_id(), true);
    return RC::SUCCESS;
}


/**
 * @description: 更新记录文件中记录号为rid的记录
 * @param {Rid&} rid 要更新的记录的记录号（位置）
 * @param {char*} buf 新记录的数据
 * @param {Context*} context
 */
RC RmFileHandle::update_record(const Rid &rid, char *buf, Context *context) {
    // Todo:
    // 1. 获取指定记录所在的page handle
    // 2. 更新记录
    
    RmPageHandle page_handle;
    RC rc = fetch_page_handle(rid.page_no, page_handle);
    if (RM_FAIL(rc)) {
        return rc;
    }

    // 检查指定位置是否有记录
    if (!Bitmap::is_set(page_handle.bitmap, rid.slot_no)) {
        buffer_pool_manager_->unpin_page(page_handle.page->get_page_id(), false);
        return RC::NOT_EXIST;
    }

    // 更新记录数据
    char* slot = page_handle.get_slot(rid.slot_no);
    memcpy(slot, buf, file_hdr_.record_size);

    buffer_pool_manager_->unpin_page(page_handle.page->get_page_id(), true);
    return RC::SUCCESS;

}

/**
 * 以下函数为辅助函数，仅提供参考，可以选择完成如下函数，也可以删除如下函数，在单元测试中不涉及如下函数接口的直接调用
*/
/**
 * @description: 获取指定页面的页面句柄
 * @param {int} page_no 页面号
 * @return {RmPageHandle} 指定页面的句柄
 */
RC RmFileHandle::fetch_page_handle(page_id_t page_no, RmPageHandle& handle) const {
    // Todo:
    // 使用缓冲池获取指定页面，并生成page_handle返回给上层
    // if page_no is invalid, throw PageNotExistError exception

    Page* page;
    PageId page_id {.fd = fd_, .page_no = page_no};
    RC rc = buffer_pool_manager_->fetch_page(page_id, page);
    if(RM_FAIL(rc)) return rc;
    handle = RmPageHandle(&file_hdr_, page);

    return RC::SUCCESS;
}

/**
 * @description: 创建一个新的page handle
 * @return {RmPageHandle} 新的PageHandle
 */
RC RmFileHandle::create_new_page_handle(RmPageHandle& handle) {
    // Todo:
    // 1.使用缓冲池来创建一个新page
    // 2.更新page handle中的相关信息
    // 3.更新file_hdr_

    PageId page_id {.fd = fd_};
    Page* page;
    RC rc = buffer_pool_manager_->new_page(&page_id, page);
    if(RM_FAIL(rc)) return rc;
    file_hdr_.num_pages++;
    if(file_hdr_.first_free_page_no == -1) file_hdr_.first_free_page_no = page_id.page_no;
    handle = RmPageHandle(&file_hdr_, page);

    // 更新page_hdr的信息
    handle.page_hdr->num_records = 0;
    handle.page_hdr->next_free_page_no = -1;

    return RC::SUCCESS;
}

/**
 * @brief 创建或获取一个空闲的page handle
 *
 * @note pin the page, remember to unpin it outside!
 */
RC RmFileHandle::fetch_free_page_handle(RmPageHandle& handle) {
    // Todo:
    // 1. 判断file_hdr_中是否还有空闲页
    //     1.1 没有空闲页：使用缓冲池来创建一个新page；可直接调用create_new_page_handle()
    //     1.2 有空闲页：直接获取第一个空闲页
    // 2. 生成page handle并返回给上层

    if(file_hdr_.first_free_page_no == -1) return create_new_page_handle(handle);
    return fetch_page_handle(file_hdr_.first_free_page_no, handle);
}