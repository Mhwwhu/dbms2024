#pragma once

#include "expression.h"

class StarExpr : public Expression
{
public:
	StarExpr() : table_name_() {}
	StarExpr(const std::string& table_name) : table_name_(table_name) {}
	virtual ~StarExpr() = default;

	ExprType type() const override { return ExprType::UNBOUND_STAR; }
	AttrType value_type() const override { return AttrType::UNDEFINED; }
	RC get_value(const ITuple& tuple, Value& value) const override { return RC::UNSUPPORTED; }
    RC try_get_value(Value& value) const override { return RC::UNSUPPORTED; }
    int value_length() const override { return -1; }

    bool equal(const Expression& other) const override 
    {
        if (other.type() != type()) {
            return false;
        }
        const StarExpr& other_star = static_cast<const StarExpr&>(other);
        return table_name_ == other_star.table_name_;
    }

	const std::string& table_name() const { return table_name_; }

private:
	std::string table_name_;
};