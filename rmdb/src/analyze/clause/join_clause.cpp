#include "join_clause.h"
#include "binder/binder_context.h"
#include "binder/jointree_context.h"

using namespace std;
using namespace common;
using VTableType = ast::VirtualTableNode::Type;

RC JoinClause::make_jointree(SmManager* sm_manager, std::shared_ptr<ast::JoinNode> join_node, std::shared_ptr<JoinTree>& jointree,
    std::shared_ptr<JointreeContext> jointree_context)
{
    // TODO: 绑定join的on条件表达式
    if(sm_manager == nullptr || join_node == nullptr) return RC::INVALID_ARGUMENT;
    RC rc = RC::SUCCESS;
    auto db = sm_manager->db_;

    std::shared_ptr<FilterClause> condition;
    shared_ptr<VirtualTabMeta> vtable_meta;
    shared_ptr<JoinTree> left, right;

    // 如果当前节点就是叶子节点，则找到对应vtable的meta信息，然后构建jointree
    if(join_node->type == JoinType::NONE) {
        auto vtable = join_node->vtable;
        // 检查表是否存在，如果是子查询则检查合法性并创建SelectStmt
        if(vtable->type == VTableType::TABLE_OR_VIEW) {
            if(db.is_table(vtable->name)) {
                auto tab_meta = make_shared<TabMeta>();
                db.get_table(vtable->name, *tab_meta);
                rc = jointree_context->set_vtable(tab_meta);
                if(RM_FAIL(rc)) return rc;
                vtable_meta = tab_meta;
            }
            else if(false) {
                // TODO: 完成view的检查
            }
            // 如果table和view中都不存在，则报错
            else return RC::SCHEMA_TABLE_NOT_EXIST;
        }
        else if(vtable->type == VTableType::SUBQUERY) {
            // TODO: 处理subquery
            return RC::UNIMPLEMENTED;
        }
        else return RC::INTERNAL;
    }
    else {
        // 如果类型不是none，则有两个子树，分别构造两棵子树
        shared_ptr<JointreeContext> left_context, right_context;
        rc = make_jointree(sm_manager, join_node->left, left, left_context);
        if(RM_FAIL(rc)) return rc;
        rc = make_jointree(sm_manager, join_node->right, right, right_context);
        if(RM_FAIL(rc)) return rc;
        rc = jointree_context->set_children(left_context, right_context);
        if(RM_FAIL(rc)) return rc;
    }

    // 创建当前节点的filter clause
    if(join_node->conjunction) rc = FilterClause::create(sm_manager, join_node->conjunction, condition, jointree_context);
    if(RM_FAIL(rc)) return rc;
    jointree = make_shared<JoinTree>(join_node->type, left, right, condition, vtable_meta);

    return RC::SUCCESS;
}

RC JoinClause::create(SmManager* sm_manager, std::shared_ptr<ast::JoinNode> join_node, std::shared_ptr<JoinClause>& join,
    std::shared_ptr<BinderContext> outer_context, std::shared_ptr<BinderContext>& cur_context)
{
    if(sm_manager == nullptr || join_node == nullptr) return RC::INVALID_ARGUMENT;

    std::shared_ptr<JoinTree> jointree;
    auto jointree_context = make_shared<JointreeContext>(outer_context);
    RC rc = make_jointree(sm_manager, join_node, jointree, jointree_context);
    if(RM_FAIL(rc)) return rc;

    cur_context = make_shared<BinderContext>(outer_context);
    for(auto vtable : jointree_context->vtables()) {
        cur_context->add_table(vtable);
    }

    join = make_shared<JoinClause>(jointree);

    return RC::SUCCESS;
}