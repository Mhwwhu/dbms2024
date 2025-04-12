#pragma once

#include "expression.h"

class ConjunctionExpr : public Expression {
public:
    ConjunctionExpr(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right, common::ConjunctionType type)
    : left_(left), right_(right), type_(type) {}
    ~ConjunctionExpr() override = default;

    ExprType type() const override { return ExprType::CONJUNCTION; }

    AttrType value_type() const override { return AttrType::BOOLEANS; }

    int value_length() const override { return sizeof(bool); }

    bool equal(const Expression& other) const override;

    RC get_value(const ITuple& tuple, Value& val) const override;

    RC try_get_value(Value& val) const override;

private:
    std::shared_ptr<Expression> left_;
    std::shared_ptr<Expression> right_;
    common::ConjunctionType type_;
};