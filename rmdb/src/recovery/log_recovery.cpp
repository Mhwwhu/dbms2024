/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "log_recovery.h"

/**
 * @description: analyze阶段，需要获得脏页表（DPT）和未完成的事务列表（ATT）
 */
RC RecoveryManager::analyze() {
	return RC::UNIMPLEMENTED;
}

/**
 * @description: 重做所有未落盘的操作
 */
RC RecoveryManager::redo() {
	return RC::UNIMPLEMENTED;
}

/**
 * @description: 回滚未完成的事务
 */
RC RecoveryManager::undo() {
	return RC::UNIMPLEMENTED;
}