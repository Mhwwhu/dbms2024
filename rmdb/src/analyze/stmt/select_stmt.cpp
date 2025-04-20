#include "select_stmt.h"
#include "binder/context_binder.h"
#include "binder/binder_context.h"

using namespace std;

RC SelectStmt::create(SmManager* manager, std::shared_ptr<ast::SelectNode> select_node, std::shared_ptr<IStmt>& select_stmt,
    std::shared_ptr<BinderContext> outer_context)
{
    RC rc = RC::SUCCESS;
    if(manager == nullptr || select_node == nullptr) return RC::INVALID_ARGUMENT;

    std::shared_ptr<JoinClause> join_tree = nullptr;
    std::shared_ptr<FilterClause> where_clause = nullptr;
    std::shared_ptr<FilterClause> having_clause = nullptr;
    std::shared_ptr<OrderByClause> orderby_clause = nullptr;
    std::vector<std::shared_ptr<Expression>> project_exprs;
    std::vector<std::shared_ptr<Expression>> groupby_exprs;
    int limit = -1;

    // project是一定有的，如果为空则报错
    auto project = select_node->project;
    if(project.empty()) return RC::INTERNAL;

    // 生成join子句并bind on条件表达式
    shared_ptr<BinderContext> cur_context;
    if(select_node->join_tree) {
        rc = JoinClause::create(manager, select_node->join_tree, join_tree, outer_context, cur_context);
        if(RM_FAIL(rc)) return rc;
    }
    else {
        cur_context = make_shared<BinderContext>(outer_context);
    }
    /**
     * TODO:
     * 如果存在其他子句，且没有对应的clause，则在当前函数绑定表达式，否则交给clause的create方法绑定。
     */

     // bind select子句表达式
    ContextBinder binder(cur_context);
    for(auto expr : project) {
        vector<shared_ptr<Expression>> bound;
        rc = binder.bind_expression(expr, bound);
        if(RM_FAIL(rc)) return rc;
        project_exprs.insert(project_exprs.end(), bound.begin(), bound.end());
    }
    
    // bind where子句表达式
    if(select_node->where_conj) {
        rc = FilterClause::create(manager, select_node->where_conj, where_clause, cur_context);
        if(RM_FAIL(rc)) return rc;
    }

    select_stmt = make_shared<SelectStmt>(join_tree, where_clause, having_clause, orderby_clause, project_exprs, groupby_exprs, limit);
    return RC::SUCCESS;
}