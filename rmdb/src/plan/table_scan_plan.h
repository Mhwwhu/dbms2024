#pragma once

#include "plan.h"
#include "system/sm_meta.h"
#include "analyze/stmt/stmt.h"

class ConjunctionExpr;

class TableScanPlan : public Plan {
public:
    TableScanPlan(const TabMeta& table, std::shared_ptr<ConjunctionExpr> filter) : table_(table), filter_(filter) {}

    PlanTag type() const { return PlanTag::TABLE_SCAN_PLAN; }

    void set_filter(std::shared_ptr<ConjunctionExpr> filter) { filter_ = filter; }

    std::shared_ptr<ConjunctionExpr> filter() const { return filter_; }

    const TabMeta& table_meta() const { return table_; }

private:
    TabMeta table_;
    std::shared_ptr<ConjunctionExpr> filter_;
};