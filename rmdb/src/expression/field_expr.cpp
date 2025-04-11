#include "field_expr.h"

bool FieldExpr::equal(const Expression& other) const
{
    if(this == &other) return true;
    if(other.type() != ExprType::FIELD) return false;

    auto other_field_expr = dynamic_cast<const FieldExpr&>(other);
    return field_.name == other_field_expr.field_.name
        && table_.name == other_field_expr.table_.name;
}