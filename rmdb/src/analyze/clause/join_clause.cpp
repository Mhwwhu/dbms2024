#include "join_clause.h"

using namespace std;
using namespace common;
using VTableType = ast::VirtualTableNode::Type;

RC JoinClause::make_jointree(SmManager* sm_manager, std::shared_ptr<ast::JoinNode> join_node, std::shared_ptr<JoinTree>& jointree,
    std::shared_ptr<BinderContext> outer_context)
{
    if(sm_manager == nullptr || join_node == nullptr) return RC::INVALID_ARGUMENT;
    RC rc = RC::SUCCESS;
    auto db = sm_manager->db_;

    // 创建当前节点的filter clause
    std::shared_ptr<FilterClause> condition;
    if(join_node->conjunction) FilterClause::create(sm_manager, join_node->conjunction, condition, outer_context);

    if(join_node->type == JoinType::NONE) {
        auto vtable = join_node->vtable;
        // 检查表是否存在，如果是子查询则检查合法性并创建SelectStmt
        if(vtable->type == VTableType::TABLE_OR_VIEW) {
            if(db.is_table(vtable->name)) {
                auto tab_meta = make_shared<TabMeta>();
                db.get_table(vtable->name, *tab_meta);
                jointree = make_shared<JoinTree>(JoinType::NONE, nullptr, nullptr, condition, tab_meta);
                return RC::SUCCESS;
            }
            if(false) {
                // TODO: 完成view的检查
            }
            // 如果table和view中都不存在，则报错
            return RC::SCHEMA_TABLE_NOT_EXIST;
        }
        if(vtable->type == VTableType::SUBQUERY) {
            // TODO: 处理subquery
            return RC::UNIMPLEMENTED;
        }
        return RC::INTERNAL;
    }

    // 如果类型不是none，则有两个子树，分别构造两棵子树

    shared_ptr<JoinTree> left, right;
    rc = make_jointree(sm_manager, join_node->left, left, outer_context);
    if(RM_FAIL(rc)) return rc;
    rc = make_jointree(sm_manager, join_node->right, right, outer_context);
    if(RM_FAIL(rc)) return rc;

    jointree = make_shared<JoinTree>(join_node->type, left, right, condition, nullptr);

    return RC::SUCCESS;
}

RC JoinClause::create(SmManager* sm_manager, std::shared_ptr<ast::JoinNode> join_node, std::shared_ptr<JoinClause>& join,
    std::shared_ptr<BinderContext> outer_context)
{
    if(sm_manager == nullptr || join_node == nullptr) return RC::INVALID_ARGUMENT;

    std::shared_ptr<JoinTree> jointree;
    RC rc = make_jointree(sm_manager, join_node, jointree, outer_context);
    if(RM_FAIL(rc)) return rc;

    join = make_shared<JoinClause>(jointree);

    return RC::SUCCESS;
}