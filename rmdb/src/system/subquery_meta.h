#pragma once

#include "sm_meta.h"
#include "analyze/stmt/select_stmt.h"

struct SubqueryMeta : public VirtualTabMeta {
    std::shared_ptr<SelectStmt> subquery;

    SubqueryMeta(std::string alias, common::VirtualTabType type)
     : VirtualTabMeta(alias, type) {}
};