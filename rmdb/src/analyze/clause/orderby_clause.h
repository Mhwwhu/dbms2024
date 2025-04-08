#pragma once

#include "common/rc.h"
#include "system/sm_manager.h"
#include "parser/ast.h"

class OrderByClause {
public:
    OrderByClause() = default;
    ~OrderByClause() = default;

    RC create(SmManager* manager, std::shared_ptr<ast::TreeNode> orderby_node, std::shared_ptr<OrderByClause>& orderby_clause)
    {
        return RC::UNIMPLEMENTED;
    }
};