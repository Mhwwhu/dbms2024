#pragma once

#include "operator.h"
#include "system/sm_meta.h"

class ConjunctionExpr;

class TableScanOper : public Operator {
public:
    TableScanOper(const TabMeta& table, std::shared_ptr<ConjunctionExpr> filter): table_(table), filter_(filter) {}

    OperatorType type() const override { return OperatorType::TABLE_SCAN_OPER; }

    RC open(Context* ctx) override;

    RC next() override;

    RC close() override;

    std::shared_ptr<ITuple> current_tuple() const override;

    std::shared_ptr<TupleSchema> tuple_schema() const override;

    bool has_tuple() const override { return true; }

    const TabMeta& table_meta() const { return table_; }

    std::shared_ptr<ConjunctionExpr> filter() const { return filter_; }

private:
    TabMeta table_;
    std::shared_ptr<ConjunctionExpr> filter_;
};