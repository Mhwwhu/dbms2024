#include "context_binder.h"

RC ContextBinder::bind_expression(std::shared_ptr<Expression> expr, std::vector<std::shared_ptr<Expression>>& bound_exprs)
{
    switch(expr->type()) {
    case ExprType::UNBOUND_FIELD: {
        return bind_unbound_field_expr(expr, bound_exprs);
    }
    case ExprType::FIELD: {
        return bind_field_expr(expr, bound_exprs);
    }
    case ExprType::VALUE: {
        return bind_value_expr(expr, bound_exprs);
    }

    default: {
        return RC::INTERNAL;
    }
    }
}

RC ContextBinder::bind_unbound_field_expr(std::shared_ptr<Expression> expr, std::vector<std::shared_ptr<Expression>>& bound_exprs)
{

}

RC ContextBinder::bind_field_expr(std::shared_ptr<Expression> expr, std::vector<std::shared_ptr<Expression>>& bound_exprs)
{

}

RC ContextBinder::bind_value_expr(std::shared_ptr<Expression> expr, std::vector<std::shared_ptr<Expression>>& bound_exprs)
{
    bound_exprs.push_back(expr);
    return RC::SUCCESS;
}

RC ContextBinder::bind_conjunction_expr(std::shared_ptr<Expression> expr, std::vector<std::shared_ptr<Expression>>& bound_exprs)
{
    
}