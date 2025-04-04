#pragma once

#include "rc.h"
#include "system/sm_manager.h"
#include "parser/ast.h"

class FilterClause {
public:
    FilterClause() = default;
    ~FilterClause() = default;

    RC create(SmManager* manager, std::shared_ptr<ast::TreeNode> filter_node, std::shared_ptr<FilterClause>& filter_clause)
    {
        return RC::UNIMPLEMENTED;
    }
};