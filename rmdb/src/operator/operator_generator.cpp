#include "operator_generator.h"
#include "chunk_get_oper.h"
#include "insert_oper.h"
#include "project_oper.h"
#include "table_scan_oper.h"
#include "filter_oper.h"
#include "delete_oper.h"
#include "update_oper.h"
#include "tuple/expr_tuple.h"

using namespace std;

RC OperatorGenerator::generate(std::shared_ptr<Plan> plan, std::shared_ptr<Operator>& oper)
{
    switch(plan->type()) {
    case PlanTag::INSERT_PLAN:
        return create_operator(std::static_pointer_cast<InsertPlan>(plan), oper);
    case PlanTag::PROJECT_PLAN:
        return create_operator(std::static_pointer_cast<ProjectPlan>(plan), oper);
    case PlanTag::TABLE_SCAN_PLAN:
        return create_operator(std::static_pointer_cast<TableScanPlan>(plan), oper);
    case PlanTag::FLITER_PLAN: 
        return create_operator(std::static_pointer_cast<FilterPlan>(plan), oper);
    case PlanTag::DELETE_PLAN:
        return create_operator(std::static_pointer_cast<DeletePlan>(plan), oper);
    case PlanTag::UPDATE_PLAN:
        return create_operator(std::static_pointer_cast<UpdatePlan>(plan), oper);
    }
    
    return RC::INTERNAL;
}

RC OperatorGenerator::create_operator(std::shared_ptr<InsertPlan> plan, std::shared_ptr<Operator>& oper)
{
    // InsertPlan的child最多只能有一个，即ProjectPlan
    if(plan->children().size() == 1 && plan->children().front()->type() != PlanTag::PROJECT_PLAN) return RC::INTERNAL;
    if(plan->children().size() > 1) return RC::INTERNAL;
    auto child = plan->children().empty() ? nullptr : plan->children().front();

    if(!child) {
        std::vector<std::shared_ptr<ITuple>> chunk;
        auto rows = plan->opt_insert_rows();
        for(size_t i = 0; i < rows.size(); i++) {
            chunk.push_back(std::make_shared<ExprTuple>(rows[i]));
        }
        auto child_oper = std::make_shared<ChunkGetOper>(chunk, nullptr);

        oper = std::make_shared<InsertOper>(plan->table_meta(), plan->decl_cols());
        oper->add_child(child_oper);

        return RC::SUCCESS;
    }
    else if(child->type() == OperatorType::PROJECT_OPER) {
        // TODO
        return RC::UNIMPLEMENTED;
    }
    
    return RC::INTERNAL;
}

RC OperatorGenerator::create_operator(std::shared_ptr<ProjectPlan> plan, std::shared_ptr<Operator>& oper)
{
    RC rc = RC::SUCCESS;
    auto child_plans = plan->children();

    shared_ptr<Operator> child_oper;

    if(!child_plans.empty()) {
        auto child_plan = child_plans.front();
        rc = generate(child_plan, child_oper);
        if(RM_FAIL(rc)) return rc;
    }
    if(child_plans.size() > 1) return RC::INTERNAL;

    oper = make_shared<ProjectOper>(plan->exprs());
    if(child_oper) {
        oper->add_child(child_oper);
    }

    return RC::SUCCESS;
}

RC OperatorGenerator::create_operator(std::shared_ptr<TableScanPlan> plan, std::shared_ptr<Operator>& oper)
{
    RC rc = RC::SUCCESS;
    // table scan不允许有子节点
    if(!plan->children().empty()) return RC::INTERNAL;

    oper = make_shared<TableScanOper>(plan->table_meta(), plan->alias_name(), plan->filter());
    return RC::SUCCESS;
}

RC OperatorGenerator::create_operator(std::shared_ptr<FilterPlan> plan, std::shared_ptr<Operator>& oper)
{
    RC rc = RC::SUCCESS;
    if(plan->children().size() != 1) return RC::INTERNAL;

    auto child_plan = plan->children().front();
    shared_ptr<Operator> child_oper;
    rc = generate(child_plan, child_oper);
    if(RM_FAIL(rc)) return rc;

    oper = make_shared<FilterOper>(plan->filter());
    oper->add_child(std::move(child_oper));
    return RC::SUCCESS;
}

RC OperatorGenerator::create_operator(std::shared_ptr<DeletePlan> plan, std::shared_ptr<Operator>& oper)
{
    RC rc = RC::SUCCESS;
    if(plan->children().size() != 1) return RC::INTERNAL;

    auto child_plan = plan->children().front();
    shared_ptr<Operator> child_oper;
    rc = generate(child_plan, child_oper);
    if(RM_FAIL(rc)) return rc;

    oper = make_shared<DeleteOper>(plan->table_meta());
    oper->add_child(std::move(child_oper));
    return RC::SUCCESS;
}

RC OperatorGenerator::create_operator(std::shared_ptr<UpdatePlan> plan, std::shared_ptr<Operator>& oper)
{
    if(plan->children().size() != 1) return RC::INTERNAL;

    auto child_plan = plan->children().front();
    shared_ptr<Operator> child_oper;
    RC rc = generate(child_plan, child_oper);
    if(RM_FAIL(rc)) return rc;

    oper = make_shared<UpdateOper>(plan->table_meta(), plan->set_list());
    oper->add_child(std::move(child_oper));
    return RC::SUCCESS;
}