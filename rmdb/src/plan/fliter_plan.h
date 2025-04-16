#pragma once

#include "plan.h"
#include "system/sm_meta.h"
#include "analyze/stmt/stmt.h"
#include "filter_clause.h"

class FliterPlan : public Plan {
public:
    FliterPlan(std::shared_ptr<FilterClause> fliter,): fliter_(fliter) {};

    PlanTag type() const override { return PlanTag::FLITER_PLAN; }



private:
    std::shared_ptr<FilterClause> fliter_;
};