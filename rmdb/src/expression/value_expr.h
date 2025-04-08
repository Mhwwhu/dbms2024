#pragma once

#include "expression.h"

class ValueExpr : public Expression {
public:
    ValueExpr(const Value& val) {}
    ~ValueExpr() override = default;

    bool equal(const Expression& other) const override
    {
        if(this == &other) return true;
        if(other.type() != ExprType::VALUE) return false;

        return val_.compare(dynamic_cast<const ValueExpr&>(other).val_) == 0;
    }

    RC get_value(const ITuple& tuple, Value& value) const override
    {
        value = val_;
        return RC::SUCCESS;
    }

    RC try_get_value(Value& value) const override 
    {
         value = val_;
         return RC::SUCCESS;
    }

    ExprType type() const override { return ExprType::VALUE; }

    AttrType value_type() const override { return val_.attr_type(); }

    int value_length() const override { return val_.length(); }

private:
    Value val_;
};