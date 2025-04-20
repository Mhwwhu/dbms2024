 #pragma once

 #include "optimize_rule.h"

class IndexSelectOptimizeRule : public OptimizeRule {
public:
    RC apply(std::shared_ptr<Plan>& plan, std::shared_ptr<OptimizeContext> opt_context) const override;
};