#include "expr_tuple.h"

RC ExprTuple::get_value(std::shared_ptr<const Expression> expression, Value& value) const
{
    RC rc = RC::SUCCESS;
    if (child_tuple_ != nullptr) {
        rc = expression->get_value(*child_tuple_, value);
    }
    else {
        rc = expression->try_get_value(value);
    }
    return rc;
}

RC ExprTuple::find_cell(const ITupleCellSpec& spec, Value& cell) const
{
    for(auto expr : exprs_) {
        if(spec.equals(ExprTupleCellSpec(expr))) {
            return get_value(expr, cell);
        }
    }
    return RC::NOTFOUND;
}