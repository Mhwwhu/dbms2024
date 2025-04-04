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

#include <cassert>
#include <cstring>
#include <memory>
#include <string>
#include <vector>

#include "execution_defs.h"
#include "record/rm.h"
#include "system/sm.h"
#include "common/context.h"
#include "common/common.h"
#include "plan/plan.h"
#include "executor_abstract.h"
#include "transaction/transaction_manager.h"
#include "plan/planner.h"

class Planner;
/**
 * Query Language Manager
 * 是执行引擎中的“执行控制中心”，主要负责协调不同类型的 SQL 查询。
 * 它应该处于 查询计划完成后、执行器启动前 的阶段，负责把 Plan 计划交给合适的执行逻辑去跑。
 * by zxr
 */
class QlManager { 
   private:
    SmManager *sm_manager_;
    TransactionManager *txn_mgr_;
    Planner *planner_;

   public:
    QlManager(SmManager *sm_manager, TransactionManager *txn_mgr, Planner *planner) 
        : sm_manager_(sm_manager),  txn_mgr_(txn_mgr), planner_(planner) {}

    void run_mutli_query(std::shared_ptr<Plan> plan, Context *context);
    void run_cmd_utility(std::shared_ptr<Plan> plan, txn_id_t *txn_id, Context *context);
    void select_from(std::unique_ptr<AbstractExecutor> executorTreeRoot, std::vector<TabCol> sel_cols,
                        Context *context);

    void run_dml(std::unique_ptr<AbstractExecutor> exec);
};
