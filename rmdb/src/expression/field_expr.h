#pragma once

#include "expression.h"
#include "system/sm_meta.h"
#include "tuple/expr_tuple_cell.h"

class FieldExpr : public Expression {
public:
    FieldExpr(const ColMeta& field, const TabMeta& table)
    : field_(field), table_(table) {}
    ~FieldExpr() override = default;

    bool equal(const Expression& other) const override;

    RC get_value(const ITuple& tuple, Value& value) const override
    {
        return tuple.find_cell(ExprTupleCellSpec(std::shared_ptr<const Expression>(this)), value);
    }

    RC try_get_value(Value& value) const override 
    {
         return RC::UNSUPPORTED;
    }

    ExprType type() const override { return ExprType::FIELD; }

    AttrType value_type() const override { return field_.type; }

    int value_length() const override { return field_.len; }

    const ColMeta& field_meta() const { return field_; }

    const TabMeta& table_meta() const { return table_; }

private:
    ColMeta field_;
    TabMeta table_;
};