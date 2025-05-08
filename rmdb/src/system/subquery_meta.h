#pragma once

#include "sm_meta.h"
#include "analyze/stmt/select_stmt.h"

struct SubqueryMeta : public VirtualTabMeta {
    std::shared_ptr<SelectStmt> subquery;

    SubqueryMeta(std::string alias)
     : VirtualTabMeta(alias) {}

     virtual std::shared_ptr<VirtualFieldMeta> get_vfield(const std::string& name) override
    {
        return nullptr;
    }

    virtual std::vector<std::shared_ptr<VirtualFieldMeta>> vcols() override
    {
        return std::vector<std::shared_ptr<VirtualFieldMeta>>();
    }

    virtual common::VirtualTabType type() override
    {
        return common::VirtualTabType::SUBQUERY;
    }
};