#pragma once

#include "expression.h"

class ComparisonExpr : public Expression {
public:
    ComparisonExpr(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right, common::CompOp op)
    : left_(left), right_(right), op_(op) {}
    ~ComparisonExpr() = default;

    ExprType type() const override { return ExprType::COMPARISON; }

    AttrType value_type() const override { return AttrType::BOOLEANS; }

    int value_length() const override { return sizeof(bool); }

    bool equal(const Expression& other) const override;

    RC get_value(const ITuple& tuple, Value& val) const override;

    RC try_get_value(Value& val) const override;

    std::shared_ptr<Expression> left() const { return left_; }
    std::shared_ptr<Expression> right() const { return right_; }
    common::CompOp op() const { return op_; }

private:
    std::shared_ptr<Expression> left_;
    std::shared_ptr<Expression> right_;
    common::CompOp op_;
};