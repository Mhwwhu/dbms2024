#pragma once

#include "plan/plan.h"
#include "optimize_context.h"

class OptimizeRule {
public:
    virtual ~OptimizeRule() = default;
    virtual RC apply(std::shared_ptr<Plan>& plan, std::shared_ptr<OptimizeContext> opt_context) const = 0;
};