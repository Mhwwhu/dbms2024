#include "filter_clause.h"
#include "expression/comparison_expr.h"
#include "binder/binder_context.h"
#include "binder/context_binder.h"

using namespace ast;
using namespace std;
using namespace common;

RC FilterClause::create(SmManager* manager, std::shared_ptr<Expression> filter_node, std::shared_ptr<FilterClause>& filter_clause,
    std::shared_ptr<BinderContext> cur_context)
{
    ContextBinder binder(cur_context);
    vector<shared_ptr<Expression>> bound_exprs;
    RC rc = binder.bind_expression(filter_node, bound_exprs);
    if(RM_FAIL(rc)) return rc;
    filter_clause = make_shared<FilterClause>(std::move(bound_exprs.front()));
    return RC::SUCCESS;
}

RC FilterClause::create(SmManager* manager, std::shared_ptr<Expression> filter_node, std::shared_ptr<FilterClause>& filter_clause,
    std::shared_ptr<JointreeContext> jointree_context)
{
    return RC::SUCCESS;
}