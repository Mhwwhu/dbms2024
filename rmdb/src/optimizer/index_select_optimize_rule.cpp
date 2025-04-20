#include "index_select_optimize_rule.h"

RC IndexSelectOptimizeRule::apply(std::shared_ptr<Plan>& plan, std::shared_ptr<OptimizeContext> opt_context) const
{
    return RC::SUCCESS;
}