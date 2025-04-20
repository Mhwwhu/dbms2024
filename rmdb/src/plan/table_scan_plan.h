#pragma once

#include "plan.h"
#include "system/sm_meta.h"
#include "analyze/stmt/stmt.h"

class ConjunctionExpr;

class TableScanPlan : public Plan {
public:
    TableScanPlan(const TabMeta& table, const std::string& alias_name, std::shared_ptr<Expression> filter)
     : table_(table), alias_name_(alias_name), filter_(filter) {}

    PlanTag type() const { return PlanTag::TABLE_SCAN_PLAN; }

    void set_filter(std::shared_ptr<Expression> filter) { filter_ = filter; }

    std::shared_ptr<Expression> filter() const { return filter_; }

    const TabMeta& table_meta() const { return table_; }

    const std::string& alias_name() const { return alias_name_; }

private:
    TabMeta table_;
    std::string alias_name_;
    std::shared_ptr<Expression> filter_;
};