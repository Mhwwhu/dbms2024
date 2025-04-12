#pragma once

#include "plan.h"

class ProjectPlan : public Plan {
public:
    ProjectPlan(const std::vector<std::shared_ptr<Expression>>& exprs) : exprs_(exprs) {}

    PlanTag type() const override { return PlanTag::PROJECT_PLAN; }

    const std::vector<std::shared_ptr<Expression>>& exprs() const { return exprs_; }

private:
    std::vector<std::shared_ptr<Expression>> exprs_;
};