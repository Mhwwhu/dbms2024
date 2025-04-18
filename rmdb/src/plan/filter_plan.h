#pragma once

#include "plan.h"
#include "system/sm_meta.h"
#include "analyze/stmt/stmt.h"
#include "expression/expression.h"

class FilterPlan : public Plan {
public:
    FilterPlan(std::shared_ptr<Expression> filter): filter_(filter) {};

    PlanTag type() const override { return PlanTag::FLITER_PLAN; }

    std::shared_ptr<Expression> filter() const { return filter_; }
private:
    std::shared_ptr<Expression> filter_;
};