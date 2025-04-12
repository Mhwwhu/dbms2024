#pragma once

#include "analyze/stmt/stmt.h"
#include "parser/ast.h"
#include "filter_clause.h"
#include "common/common.h"

struct JoinTree {
    common::JoinType type;
    std::shared_ptr<JoinTree> left;
    std::shared_ptr<JoinTree> right;
    std::shared_ptr<FilterClause> condition;
    std::shared_ptr<VirtualTabMeta> vtable;

    JoinTree(common::JoinType type_, std::shared_ptr<JoinTree> left_, std::shared_ptr<JoinTree> right_, std::shared_ptr<FilterClause> condition_,
        std::shared_ptr<VirtualTabMeta> vtable_)
        : type(type), left(std::move(left_)), right(std::move(right_)), condition(std::move(condition_)), vtable(std::move(vtable_)) {}
};

class JoinClause {
public:
    JoinClause(std::shared_ptr<JoinTree> jointree_) : jointree(jointree_) {}

    static RC create(SmManager* sm_manager, std::shared_ptr<ast::JoinNode> join_node, std::shared_ptr<JoinClause>& join,
        std::shared_ptr<BinderContext> outer_context);

private:
    static RC make_jointree(SmManager* sm_manager, std::shared_ptr<ast::JoinNode> join_node, std::shared_ptr<JoinTree>& jointree,
        std::shared_ptr<BinderContext> outer_context);

private:
    std::shared_ptr<JoinTree> jointree;
};