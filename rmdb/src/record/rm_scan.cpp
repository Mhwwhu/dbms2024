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
 : file_handle_(file_handle), filter_(filter) {
    // Todo:
    // 初始化file_handle和rid（指向第一个存放了记录的位置）

}

RC RecScan::open() {

}

/**
 * @brief 找到文件中下一个存放了记录的位置
 */
RC RecScan::next() {
    // Todo:
    // 找到文件中下一个存放了记录的非空闲位置，用rid_来指向这个位置

}

/**
 * @brief RmScan内部存放的rid
 */
std::shared_ptr<RmRecord> RecScan::record() const {
    return nullptr;
}