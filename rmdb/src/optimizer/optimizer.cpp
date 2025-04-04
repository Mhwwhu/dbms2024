#include "optimizer.h"

RC Optimizer::handle_request(Context* context)
{
    auto stmt = context->stmt;
    std::shared_ptr<Plan> plan;
    RC rc = RC::SUCCESS;
    if(!IStmt::is_dml(stmt->type())) return rc;
    
    rc = planner_->do_planner(stmt, context, plan);
    if(RM_FAIL(rc)) return rc;
    // TODO: 进行rewrite和optimize
    context->plan = plan;
    
    std::shared_ptr<Operator> oper;
    rc = operator_generator_->generate(plan, oper);
    if(RM_FAIL(rc)) return rc;
    context->oper = oper;

    return rc;
}