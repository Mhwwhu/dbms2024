#pragma once

#include "common/rc.h"
#include "system/sm_manager.h"
#include "parser/ast.h"
#include "expression/conjunction_expr.h"

class BinderContext;
class JointreeContext;

class FilterClause {
public:
    FilterClause(std::shared_ptr<ConjunctionExpr> conj) : conj_expr_(conj) {}
    ~FilterClause() = default;

    static RC create(SmManager* manager, std::shared_ptr<ast::ConjunctionNode> filter_node, std::shared_ptr<FilterClause>& filter_clause,
        std::shared_ptr<BinderContext> outer_context);

    static RC create(SmManager* manager, std::shared_ptr<ast::ConjunctionNode> filter_node, std::shared_ptr<FilterClause>& filter_clause,
        std::shared_ptr<JointreeContext> jointree_context);

    std::shared_ptr<ConjunctionExpr> conjunction_expr() const { return conj_expr_; }

private:
    static RC make_conjunction_expr(std::shared_ptr<ast::ConjunctionNode> conjunction, std::shared_ptr<ConjunctionExpr>& conj_expr,
        std::shared_ptr<BinderContext> outer_context);

    static RC make_condition_expr(std::shared_ptr<ast::ConditionNode> cond, std::shared_ptr<Expression>& comp_expr,
        std::shared_ptr<BinderContext> outer_context);

private:
    std::shared_ptr<ConjunctionExpr> conj_expr_;
};