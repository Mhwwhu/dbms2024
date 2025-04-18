#pragma once

#include "operator.h"
#include "system/sm_meta.h"

class Expression;

class DeleteOper : public Operator {
public:
    DeleteOper(const TabMeta& table_meta)
        : table_meta_(table_meta) {}

    OperatorType type() const override { return OperatorType::DELETE_OPER; }

    RC open(Context* context) override;

    RC next() override { return RC::RECORD_EOF; }

    RC close() override 
    {
        return RC::SUCCESS;
    }

    std::shared_ptr<ITuple> current_tuple() const override { return nullptr; }

    std::shared_ptr<TupleSchema> tuple_schema() const override { return nullptr; }

    bool has_tuple() const override { return false; }

private:
    TabMeta table_meta_;
};