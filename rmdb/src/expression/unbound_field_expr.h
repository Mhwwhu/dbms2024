#pragma once

#include "expression.h"

class UnboundFieldExpr : public Expression {
public:
    UnboundFieldExpr(const std::string& table_name, const std::string& field_name)
    : table_name_(table_name), field_name_(field_name) {}
    ~UnboundFieldExpr() override = default;

    bool equal(const Expression& other) const override { return false; }
    
    RC get_value(const ITuple& tuple, Value& value) const override { return RC::UNSUPPORTED; }

    RC try_get_value(Value& value) const override { return RC::UNSUPPORTED; }

    ExprType type() const override { return ExprType::UNBOUND_FIELD; }

    AttrType value_type() const override { return AttrType::UNDEFINED; }

    int value_length() const override { return -1; }

    const std::string& field_name() const { return field_name_; }

    const std::string& table_name() const { return table_name_; }

private:
    std::string table_name_;
    std::string field_name_;
};