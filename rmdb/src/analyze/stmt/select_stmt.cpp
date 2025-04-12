#include "select_stmt.h"
#include "binder/context_binder.h"

using namespace std;

RC SelectStmt::create(SmManager* manager, std::shared_ptr<ast::SelectNode> select_node, std::shared_ptr<IStmt>& select_stmt,
    std::shared_ptr<BinderContext> outer_context)
{
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

    /**
     * TODO: 首先获取jointree，如果不存在则跳过。使用ContextBinder绑定jointree及其内部的表达式，然后获取到jointree的所有vtable。
     * 接下来绑定project的表达式。
     * 如果存在其他子句，且没有对应的clause，则在当前函数绑定表达式，否则交给clause的create方法绑定。
     */
    
     // test: 这里为了测试链路，暂不实现其他子句，仅支持project

     // bind select子句表达式
    ContextBinder binder(outer_context);
    for(auto expr : project) {
        vector<shared_ptr<Expression>> bound;
        binder.bind_expression(expr, bound);
        project_exprs.insert(project_exprs.end(), bound.begin(), bound.end());
    }

    select_stmt = make_shared<SelectStmt>(join_tree, where_clause, having_clause, orderby_clause, project_exprs, groupby_exprs, limit);
    return RC::SUCCESS;
}