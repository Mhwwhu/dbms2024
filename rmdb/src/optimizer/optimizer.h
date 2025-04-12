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

#include <map>

#include "errors.h"
#include "parser/parser.h"
#include "system/sm.h"
#include "common/context.h"
#include "transaction/transaction_manager.h"
#include "plan/planner.h"
#include "plan/plan.h"
#include "operator/operator_generator.h"

class Optimizer {
   private:
    SmManager *sm_manager_;
    Planner *planner_;
    OperatorGenerator* operator_generator_;

   public:
    Optimizer(SmManager *sm_manager,  Planner *planner, OperatorGenerator* operator_generator) 
        : sm_manager_(sm_manager),  planner_(planner), operator_generator_(operator_generator)
        {}
    
    std::shared_ptr<Plan> plan_query(std::shared_ptr<IStmt> stmt, Context *context) {
        // if (auto x = std::dynamic_pointer_cast<ast::Help>(stmt->parse)) {
        //     // help;
        //     return std::make_shared<OtherPlan>(T_Help, std::string());
        // } else if (auto x = std::dynamic_pointer_cast<ast::ShowTables>(stmt->parse)) {
        //     // show tables;
        //     return std::make_shared<OtherPlan>(T_ShowTable, std::string());
        // } else if (auto x = std::dynamic_pointer_cast<ast::DescTable>(stmt->parse)) {
        //     // desc table;
        //     return std::make_shared<OtherPlan>(T_DescTable, x->tab_name);
        // } else if (auto x = std::dynamic_pointer_cast<ast::TxnBegin>(stmt->parse)) {
        //     // begin;
        //     return std::make_shared<OtherPlan>(T_Transaction_begin, std::string());
        // } else if (auto x = std::dynamic_pointer_cast<ast::TxnAbort>(stmt->parse)) {
        //     // abort;
        //     return std::make_shared<OtherPlan>(T_Transaction_abort, std::string());
        // } else if (auto x = std::dynamic_pointer_cast<ast::TxnCommit>(stmt->parse)) {
        //     // commit;
        //     return std::make_shared<OtherPlan>(T_Transaction_commit, std::string());
        // } else if (auto x = std::dynamic_pointer_cast<ast::TxnRollback>(stmt->parse)) {
        //     // rollback;
        //     return std::make_shared<OtherPlan>(T_Transaction_rollback, std::string());
        // } else if (auto x = std::dynamic_pointer_cast<ast::SetNode>(stmt->parse)) {
        //     // Set Knob Plan
        //     return std::make_shared<SetKnobPlan>(x->set_knob_type_, x->bool_val_);
        // } else {
        //     return planner_->do_planner(stmt, context);
        // }
        return nullptr;
    }

    // TODO: 在该方法中完成plan和operator的生成，以及优化。plan和operator仅限于DML语句，其他语句则由下一个阶段的executor注入stmt执行。
    RC handle_request(Context* context);

};
