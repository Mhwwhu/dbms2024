#include "conjunction_expr.h"

using namespace common;

bool ConjunctionExpr::equal(const Expression& other) const
{
    if(other.type() != ExprType::CONJUNCTION) return false;
    if(&other == this) return true;

    auto conj_expr = dynamic_cast<const ConjunctionExpr&>(other);
    return conj_expr.type_ == type_ && conj_expr.left_->equal(*left_) && conj_expr.right_->equal(*right_);
}

RC ConjunctionExpr::get_value(const ITuple& tuple, Value& val) const
{
    if(type_ == ConjunctionType::NONE) {
        return left_->get_value(tuple, val);
    }

    Value l_val, r_val;
    RC rc = left_->get_value(tuple, l_val);
    if(RM_FAIL(rc)) return rc;
    rc = right_->get_value(tuple, r_val);
    if(RM_FAIL(rc)) return rc;

    if(type_ == ConjunctionType::AND) {
        val = Value(l_val.get_boolean() && r_val.get_boolean());
    }
    else if(type_ == ConjunctionType::OR) {
        val = Value(l_val.get_boolean() || r_val.get_boolean());
    }
    else {
        return RC::INTERNAL;
    }
    return RC::SUCCESS;
}

RC ConjunctionExpr::try_get_value(Value& val) const
{
    if(type_ == ConjunctionType::NONE) {
        return left_->try_get_value(val);
    }

    Value l_val, r_val;
    RC rc = left_->try_get_value(l_val);
    if(RM_FAIL(rc)) return rc;
    rc = right_->try_get_value(r_val);
    if(RM_FAIL(rc)) return rc;

    if(type_ == ConjunctionType::AND) {
        val = Value(l_val.get_boolean() && r_val.get_boolean());
    }
    else if(type_ == ConjunctionType::OR) {
        val = Value(l_val.get_boolean() || r_val.get_boolean());
    }
    else {
        return RC::INTERNAL;
    }
    return RC::SUCCESS;
}