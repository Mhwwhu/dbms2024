#include "optimizer.h"

RC Optimizer::handle_request(Context* context)
{
    auto stmt = context->stmt;
    std::shared_ptr<Plan> plan;
    RC rc = RC::SUCCESS;
    if(!IStmt::is_dml(stmt->type())) return rc;
    
    rc = planner_->do_planner(stmt, context, plan);
    if(RM_FAIL(rc)) return rc;
    rc = rewrite(plan);
    if(RM_FAIL(rc)) return rc;
    rc = optimize(plan);
    if(RM_FAIL(rc)) return rc;
    
    context->plan = plan;
    
    std::shared_ptr<Operator> oper;
    rc = operator_generator_->generate(plan, oper);
    if(RM_FAIL(rc)) return rc;
    context->oper = oper;

    return rc;
}

RC Optimizer::rewrite(std::shared_ptr<Plan>& plan)
{
    return RC::SUCCESS;
}

RC Optimizer::optimize(std::shared_ptr<Plan>& plan)
{
    for (const auto& rule : optimize_rules_) {
        auto ctx = std::make_shared<OptimizeContext>();
        RC rc = rule->apply(plan, ctx);
        if (RM_FAIL(rc)) {
            LOG_ERROR("Failed to apply optimization rule");
            return rc;
        }
    }
    return RC::SUCCESS;
}