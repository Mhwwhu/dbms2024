#include "field_expr.h"
#include "tuple/row_tuple_cell.h"

bool FieldExpr::equal(const Expression& other) const
{
    if(this == &other) return true;
    if(other.type() != ExprType::FIELD) return false;

    auto other_field_expr = dynamic_cast<const FieldExpr&>(other);
    return vfield_->type == other_field_expr.vfield_->type
        && vfield_->alias_name == other_field_expr.vfield_->alias_name
        && vtable_->type == other_field_expr.vtable_->type
        && vtable_->alias_name == other_field_expr.vtable_->alias_name;
}

RC FieldExpr::get_value(const ITuple& tuple, Value& value) const
{
    if(vtable_->type == common::VirtualTabType::TABLE) {
        return tuple.find_cell((RowTupleCellSpec(vtable_->alias_name, vfield_->alias_name)), value);
    }
}