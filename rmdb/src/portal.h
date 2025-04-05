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

#include <cerrno>
#include <cstring>
#include <string>
#include "plan/plan.h"
#include "common/common.h"
#include "system/sm_manager.h"
#include "common/context.h"

typedef enum portalTag{
    PORTAL_Invalid_Query = 0,
    PORTAL_ONE_SELECT,
    PORTAL_DML_WITHOUT_SELECT,
    PORTAL_MULTI_QUERY, //DDL
    PORTAL_CMD_UTILITY //特殊的指令
} portalTag;


// struct PortalStmt {
//     portalTag tag;
    
//     std::vector<TabCol> sel_cols;
//     std::unique_ptr<AbstractExecutor> root;
//     std::shared_ptr<Plan> plan;
    
//     PortalStmt(portalTag tag_, std::vector<TabCol> sel_cols_, std::unique_ptr<AbstractExecutor> root_, std::shared_ptr<Plan> plan_) :
//             tag(tag_), sel_cols(std::move(sel_cols_)), root(std::move(root_)), plan(std::move(plan_)) {}
// };

class Portal
{
   private:
    SmManager *sm_manager_;
    

   public:
    Portal(SmManager *sm_manager) : sm_manager_(sm_manager){}
    ~Portal(){}

    RC handle_request(Context* context);

    // 将查询执行计划转换成对应的算子树
    // std::shared_ptr<PortalStmt> start(std::shared_ptr<Plan> plan, Context *context)
    // {
    //     // // 这里可以将select进行拆分，例如：一个select，带有return的select等
    //     // if (auto x = std::dynamic_pointer_cast<OtherPlan>(plan)) {
    //     //     return std::make_shared<PortalStmt>(PORTAL_CMD_UTILITY, std::vector<TabCol>(), std::unique_ptr<AbstractExecutor>(),plan);
    //     // } else if(auto x = std::dynamic_pointer_cast<SetKnobPlan>(plan)) {
    //     //     return std::make_shared<PortalStmt>(PORTAL_CMD_UTILITY, std::vector<TabCol>(), std::unique_ptr<AbstractExecutor>(), plan); 
    //     // } else if (auto x = std::dynamic_pointer_cast<DDLPlan>(plan)) {
    //     //     return std::make_shared<PortalStmt>(PORTAL_MULTI_QUERY, std::vector<TabCol>(), std::unique_ptr<AbstractExecutor>(),plan);
    //     // } else if (auto x = std::dynamic_pointer_cast<DMLPlan>(plan)) {
    //     //     switch(x->tag) {
    //     //         case T_select:
    //     //         {
    //     //             std::shared_ptr<ProjectionPlan> p = std::dynamic_pointer_cast<ProjectionPlan>(x->subplan_);
    //     //             std::unique_ptr<AbstractExecutor> root= convert_plan_executor(p, context);
    //     //             return std::make_shared<PortalStmt>(PORTAL_ONE_SELECT, std::move(p->sel_cols_), std::move(root), plan);
    //     //         }
                    
    //     //         case T_Update:
    //     //         {
    //     //             std::unique_ptr<AbstractExecutor> scan= convert_plan_executor(x->subplan_, context);
    //     //             std::vector<Rid> rids;
    //     //             for (scan->beginTuple(); !scan->is_end(); scan->nextTuple()) {
    //     //                 rids.push_back(scan->rid());
    //     //             }
    //     //             std::unique_ptr<AbstractExecutor> root =std::make_unique<UpdateExecutor>(sm_manager_, 
    //     //                                                     x->tab_name_, x->set_clauses_, x->conds_, rids, context);
    //     //             return std::make_shared<PortalStmt>(PORTAL_DML_WITHOUT_SELECT, std::vector<TabCol>(), std::move(root), plan);
    //     //         }
    //     //         case T_Delete:
    //     //         {
    //     //             std::unique_ptr<AbstractExecutor> scan= convert_plan_executor(x->subplan_, context);
    //     //             std::vector<Rid> rids;
    //     //             for (scan->beginTuple(); !scan->is_end(); scan->nextTuple()) {
    //     //                 rids.push_back(scan->rid());
    //     //             }

    //     //             std::unique_ptr<AbstractExecutor> root =
    //     //                 std::make_unique<DeleteExecutor>(sm_manager_, x->tab_name_, x->conds_, rids, context);

    //     //             return std::make_shared<PortalStmt>(PORTAL_DML_WITHOUT_SELECT, std::vector<TabCol>(), std::move(root), plan);
    //     //         }

    //     //         case T_Insert:
    //     //         {
    //     //             std::unique_ptr<AbstractExecutor> root =
    //     //                     std::make_unique<InsertExecutor>(sm_manager_, x->tab_name_, x->values_, context);
            
    //     //             return std::make_shared<PortalStmt>(PORTAL_DML_WITHOUT_SELECT, std::vector<TabCol>(), std::move(root), plan);
    //     //         }


    //     //         default:
    //     //             throw InternalError("Unexpected field type");
    //     //             break;
    //     //     }
    //     // } else {
    //     //     throw InternalError("Unexpected field type");
    //     // }
    //     return nullptr;
    // }

    // TODO: 根据context中的sql_result决定应该执行什么，具体参考miniob的PlainCommunicator::write_result_internal
    RC run(Context *context){
        auto sql_result = context->sql_result;
        if(sql_result.oper() == nullptr && sql_result.has_result()) {
            if(RM_SUCC(sql_result.return_code())) {

            }
            return sql_result.return_code();
        }

        return RC::INTERNAL;
    }

    // 清空资源
    void drop(){}


    // std::unique_ptr<AbstractExecutor> convert_plan_executor(std::shared_ptr<Plan> plan, Context *context)
    // {
    //     // if(auto x = std::dynamic_pointer_cast<ProjectionPlan>(plan)){
    //     //     return std::make_unique<ProjectionExecutor>(convert_plan_executor(x->subplan_, context), 
    //     //                                                 x->sel_cols_);
    //     // } else if(auto x = std::dynamic_pointer_cast<ScanPlan>(plan)) {
    //     //     if(x->tag == T_SeqScan) {
    //     //         return std::make_unique<SeqScanExecutor>(sm_manager_, x->tab_name_, x->conds_, context);
    //     //     }
    //     //     else {
    //     //         return std::make_unique<IndexScanExecutor>(sm_manager_, x->tab_name_, x->conds_, x->index_col_names_, context);
    //     //     } 
    //     // } else if(auto x = std::dynamic_pointer_cast<JoinPlan>(plan)) {
    //     //     std::unique_ptr<AbstractExecutor> left = convert_plan_executor(x->left_, context);
    //     //     std::unique_ptr<AbstractExecutor> right = convert_plan_executor(x->right_, context);
    //     //     std::unique_ptr<AbstractExecutor> join = std::make_unique<NestedLoopJoinExecutor>(
    //     //                         std::move(left), 
    //     //                         std::move(right), std::move(x->conds_));
    //     //     return join;
    //     // } else if(auto x = std::dynamic_pointer_cast<SortPlan>(plan)) {
    //     //     return std::make_unique<SortExecutor>(convert_plan_executor(x->subplan_, context), 
    //     //                                     x->sel_col_, x->is_desc_);
    //     // }
    //     return nullptr;
    // }

};