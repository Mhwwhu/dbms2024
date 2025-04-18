#pragma once

#include "plan.h"
#include "system/sm_meta.h"

class Expression;

class UpdatePlan : public Plan {
public:
    UpdatePlan(const TabMeta& table, const std::map<ColMeta, std::shared_ptr<Expression>>& set_list)
        : table_(table), set_list_(set_list) {}
    ~UpdatePlan() override = default;

    PlanTag type() const override { return PlanTag::UPDATE_PLAN; }

    const TabMeta& table_meta() const { return table_; }
    const std::map<ColMeta, std::shared_ptr<Expression>>& set_list() const { return set_list_; }

private:
    TabMeta table_;
    std::map<ColMeta, std::shared_ptr<Expression>> set_list_;
};