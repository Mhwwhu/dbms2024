#pragma once

#include "operator.h"
#include "system/sm_meta.h"

class Expression;

class UpdateOper : public Operator {
public:
    UpdateOper(const TabMeta &table, const std::map<ColMeta, std::shared_ptr<Expression>> &set_list)
    : table_(table), set_list_(set_list) {}

    OperatorType type() const override { return OperatorType::UPDATE_OPER; }

    RC open(Context* ctx) override;

    RC next() override { return RC::RECORD_EOF; }

    RC close() override { return RC::SUCCESS; }

    std::shared_ptr<ITuple> current_tuple() const { return nullptr; };

    virtual std::shared_ptr<TupleSchema> tuple_schema() const { return nullptr; }

    virtual bool has_tuple() const { return false; }

    const TabMeta& table_meta() const { return table_; }
    const std::map<ColMeta, std::shared_ptr<Expression>>& set_list() const { return set_list_; }

private:
    TabMeta table_;
    std::map<ColMeta, std::shared_ptr<Expression>> set_list_;
};