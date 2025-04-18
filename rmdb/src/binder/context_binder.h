#pragma once

#include "expression/expression.h"
#include "common/rc.h"

#include <set>

class BinderContext;

// 上下文绑定器，用于将表达式及其他可能需要绑定的对象绑定到对应上下文
class ContextBinder {
public:
    ContextBinder(std::shared_ptr<BinderContext> context) : context_(context) {}

    RC bind_expression(std::shared_ptr<Expression> expr, std::vector<std::shared_ptr<Expression>>& bound_exprs);

private:
    RC bind_unbound_field_expr(std::shared_ptr<Expression> expr, std::vector<std::shared_ptr<Expression>>& bound_exprs);
    RC bind_field_expr(std::shared_ptr<Expression> expr, std::vector<std::shared_ptr<Expression>>& bound_exprs);
    RC bind_value_expr(std::shared_ptr<Expression> expr, std::vector<std::shared_ptr<Expression>>& bound_exprs);
    RC bind_conjunction_expr(std::shared_ptr<Expression> expr, std::vector<std::shared_ptr<Expression>>& bound_exprs);
    RC bind_comp_expr(std::shared_ptr<Expression> expr, std::vector<std::shared_ptr<Expression>>& bound_exprs);
private:
    std::shared_ptr<const BinderContext> context_;
};