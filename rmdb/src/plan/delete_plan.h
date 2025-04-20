#pragma once

#include "plan.h"
#include "system/sm_meta.h"

class DeletePlan : public Plan {
public:
    DeletePlan(const TabMeta& table_meta): table_meta_(table_meta){};

    PlanTag type() const override { return PlanTag::DELETE_PLAN; }

    const TabMeta& table_meta() const { return table_meta_; }

private:
    TabMeta table_meta_;
};