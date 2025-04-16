#include "filter_clause.h"
#include "expression/comparison_expr.h"
#include "binder/binder_context.h"

using namespace ast;
using namespace std;
using namespace common;

RC FilterClause::make_conjunction_expr(std::shared_ptr<ConjunctionNode> conjunction, std::shared_ptr<ConjunctionExpr>& conj_expr,
    std::shared_ptr<BinderContext> outer_context)
{
    RC rc = RC::SUCCESS;
    if(conjunction->type == ConjunctionType::NONE) {
        shared_ptr<Expression> cond_expr;
        rc = make_condition_expr(conjunction->condition, cond_expr, outer_context);
        if(RM_FAIL(rc)) return rc;
        conj_expr = make_shared<ConjunctionExpr>(cond_expr, nullptr, ConjunctionType::NONE);
    }
    else {
        shared_ptr<ConjunctionExpr> left, right;
        rc = make_conjunction_expr(conjunction->left, left, outer_context);
        if(RM_FAIL(rc)) return rc;
        rc = make_conjunction_expr(conjunction->right, right, outer_context);
        if(RM_FAIL(rc)) return rc;
        conj_expr = make_shared<ConjunctionExpr>(left, right, conjunction->type);
    }
    return RC::SUCCESS;
}

RC FilterClause::make_condition_expr(std::shared_ptr<ConditionNode> cond, std::shared_ptr<Expression>& comp_expr,
    std::shared_ptr<BinderContext> outer_context)
{
    if(auto comp = dynamic_pointer_cast<CompareNode>(cond)) {
        comp_expr = make_shared<ComparisonExpr>(comp->left, comp->right, comp->comp);
        return RC::SUCCESS;
    }
    else if(true) {
        return RC::UNIMPLEMENTED;
    }
}

RC FilterClause::create(SmManager* manager, std::shared_ptr<ast::ConjunctionNode> filter_node, std::shared_ptr<FilterClause>& filter_clause,
    std::shared_ptr<BinderContext> outer_context)
{
    shared_ptr<ConjunctionExpr> conj_expr;
    RC rc = make_conjunction_expr(filter_node, conj_expr, outer_context);
    if(RM_FAIL(rc)) return rc;
    filter_clause = make_shared<FilterClause>(conj_expr);
    return RC::SUCCESS;
}

RC FilterClause::create(SmManager* manager, std::shared_ptr<ast::ConjunctionNode> filter_node, std::shared_ptr<FilterClause>& filter_clause,
    std::shared_ptr<JointreeContext> jointree_context)
{
    return RC::SUCCESS;
}