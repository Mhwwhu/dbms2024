#pragma once

#include "operator.h"
#include "system/sm_meta.h"
#include "record/rm_scan.h"

class ConjunctionExpr;
class RecScan;
class RowTuple;

class TableScanOper : public Operator {
public:
    TableScanOper(const TabMeta& table, const std::string& alias_name, std::shared_ptr<ConjunctionExpr> filter);

    OperatorType type() const override { return OperatorType::TABLE_SCAN_OPER; }

    RC open(Context* ctx) override;

    RC next() override;

    RC close() override;

    std::shared_ptr<ITuple> current_tuple() const override;

    std::shared_ptr<TupleSchema> tuple_schema() const override;

    bool has_tuple() const override { return true; }

    const TabMeta& table_meta() const { return table_; }

    const std::string& alias_name() const { return alias_name_; }

private:
    RC filter(std::shared_ptr<RowTuple> tuple, bool& result);

private:
    TabMeta table_;
    std::string alias_name_;
    std::shared_ptr<ConjunctionExpr> filter_;
    std::unique_ptr<RecScan> scanner_;
    std::shared_ptr<RowTuple> tuple_;
    std::shared_ptr<TupleSchema> tuple_schema_;
};