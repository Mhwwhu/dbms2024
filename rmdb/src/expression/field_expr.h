#pragma once

#include "expression.h"
#include "system/sm_meta.h"
#include "tuple/expr_tuple_cell.h"

class FieldExpr : public Expression {
public:
    FieldExpr(std::shared_ptr<VirtualFieldMeta> vfield, std::shared_ptr<VirtualTabMeta> vtable)
    : vfield_(vfield), vtable_(vtable) {}
    ~FieldExpr() override = default;

    bool equal(const Expression& other) const override;

    RC get_value(const ITuple& tuple, Value& value) const override;

    RC try_get_value(Value& value) const override 
    {
         return RC::UNSUPPORTED;
    }

    ExprType type() const override { return ExprType::FIELD; }

    AttrType value_type() const override { return vfield_->attr_type; }

    int value_length() const override { return vfield_->len; }

    std::shared_ptr<VirtualFieldMeta> vfield_meta() const { return vfield_; }

    std::shared_ptr<VirtualTabMeta> vtable_meta() const { return vtable_; }

private:
    std::shared_ptr<VirtualFieldMeta> vfield_;
    std::shared_ptr<VirtualTabMeta> vtable_;
};