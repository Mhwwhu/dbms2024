#include "filter_oper.h"
#include "expression/conjunction_expr.h"

RC FilterOper::open(Context* context)
{
    if (children_.size() != 1) {
        return RC::INTERNAL;
    }
    return children_[0]->open(context);
}

RC FilterOper::next() 
{
    auto child = children_.front();
    RC rc = RC::SUCCESS;

    while(RM_SUCC(rc = child->next())) {
        auto tuple = child->current_tuple();
        if(tuple == nullptr) {
            return RC::INTERNAL;
        }
        
        Value val;
        rc = expr_->get_value(*tuple, val);
        if(RM_FAIL(rc)) return rc;
        if(val.get_boolean()) {
            return rc;
        }
    }

    return rc;
}

RC FilterOper::close()
{
    expr_ = nullptr;
    auto child = children_.front();
    return child->close();
}