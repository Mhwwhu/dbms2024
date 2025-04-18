#pragma once

#include "common/rc.h"
#include "system/sm_manager.h"
#include "parser/ast.h"
#include "expression/expression.h"
#include "expression/conjunction_expr.h"

class BinderContext;
class JointreeContext;

class FilterClause {
public:
    FilterClause(std::shared_ptr<Expression> expr) : expr_(expr) {}
    ~FilterClause() = default;

    static RC create(SmManager* manager, std::shared_ptr<Expression> filter_node, std::shared_ptr<FilterClause>& filter_clause,
        std::shared_ptr<BinderContext> outer_context);

    static RC create(SmManager* manager, std::shared_ptr<Expression> filter_node, std::shared_ptr<FilterClause>& filter_clause,
        std::shared_ptr<JointreeContext> jointree_context);

    std::shared_ptr<Expression> expr() const { return expr_; }

private:
    std::shared_ptr<Expression> expr_;
};