#include "update_stmt.h"
#include "system/sm_manager.h"
#include "binder/context_binder.h"
#include "binder/binder_context.h"
#include "analyze/clause/filter_clause.h"

using namespace std;

RC UpdateStmt::create(SmManager* sm_manager, std::shared_ptr<ast::UpdateNode> update_node, std::shared_ptr<IStmt>& stmt)
{
    if(sm_manager == nullptr || update_node == nullptr) {
        return RC::INVALID_ARGUMENT;
    }

    TabMeta table;
    std::map<ColMeta, std::shared_ptr<Expression>> set_list;
    std::shared_ptr<FilterClause> filter;

    // 获取要更新的表元信息
    auto table_name = update_node->tab_name;
    RC rc = sm_manager->db_.get_table(table_name, table);
    if(RM_FAIL(rc)) return rc;

    auto context = make_shared<BinderContext>(nullptr);
    context->add_table(make_shared<TabMeta>(table));
    ContextBinder binder(context);

    // 获取更新的字段并绑定表达式
    for(auto& set_clause : update_node->set_clause) {
        ColMeta col;
        rc = table.get_col(set_clause->col_name, col);
        if(RM_FAIL(rc)) return rc;

        // 绑定表达式
        vector<std::shared_ptr<Expression>> bound_exprs;
        rc = binder.bind_expression(set_clause->expr, bound_exprs);
        if(RM_FAIL(rc)) return rc;
        if(bound_exprs.size() != 1) {
            return RC::INTERNAL;
        }
        set_list[col] = bound_exprs[0];
    }

    // 生成FilterClause
    if(update_node->filter) {
        rc = FilterClause::create(sm_manager, update_node->filter, filter, context);
        if(RM_FAIL(rc)) return rc;
    }

    stmt = make_shared<UpdateStmt>(table, set_list, filter);

    return RC::SUCCESS;
}