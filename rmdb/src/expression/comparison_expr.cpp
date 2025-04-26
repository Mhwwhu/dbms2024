#include "comparison_expr.h"

using namespace common;

bool ComparisonExpr::equal(const Expression& other) const
{
    if(other.type() != ExprType::COMPARISON) return false;
    if(&other == this) return true;

    auto conj_expr = dynamic_cast<const ComparisonExpr&>(other);
    return conj_expr.op_ == op_ && conj_expr.left_->equal(*left_) && conj_expr.right_->equal(*right_);
}

RC ComparisonExpr::get_value(const ITuple& tuple, Value& val) const
{
    Value l_val, r_val;
    RC rc = left_->get_value(tuple, l_val);
    if(RM_FAIL(rc)) return rc;
    rc = right_->get_value(tuple, r_val);
    if(RM_FAIL(rc)) return rc;

    int result = l_val.compare(r_val);
    if(result == INT32_MAX) {
        val = Value(false);
        return RC::SUCCESS;
    }

    switch(op_) {
    case EQ:
        val = Value(result == 0);
        break;
    case NE:
        val = Value(result != 0);
        break;
    case LT:
        val = Value(result < 0);
        break;
    case LE:
        val = Value(result <= 0);
        break;
    case GT:
        val = Value(result > 0);
        break;
    case GE:
        val = Value(result >= 0);
        break;
    default:
        return RC::INTERNAL;
    }
    return RC::SUCCESS;
}

RC ComparisonExpr::try_get_value(Value& val) const
{
    Value l_val, r_val;
    RC rc = left_->try_get_value(l_val);
    if(RM_FAIL(rc)) return rc;
    rc = right_->try_get_value(r_val);
    if(RM_FAIL(rc)) return rc;

    int result = l_val.compare(r_val);
    if(result == INT32_MAX) {
        val = Value(false);
        return RC::SUCCESS;
    }

    switch(op_) {
    case EQ:
        val = Value(result == 0);
        break;
    case NE:
        val = Value(result != 0);
        break;
    case LT:
        val = Value(result < 0);
        break;
    case LE:
        val = Value(result <= 0);
        break;
    case GT:
        val = Value(result > 0);
        break;
    case GE:
        val = Value(result > 0);
    default:
        return RC::INTERNAL;
    }
    return RC::SUCCESS;
}