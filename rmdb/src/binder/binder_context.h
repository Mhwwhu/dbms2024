#pragma once

#include "expression/expression.h"
#include "common/rc.h"
#include "system/sm_meta.h"

#include <set>

class VTableMetaComparator {
public:
    bool operator()(const VirtualTabMeta& a, const VirtualTabMeta& b)
    {
        return a.alias_name < b.alias_name;
    }
};

class BinderContext {
public:
    BinderContext(std::shared_ptr<BinderContext> outer_context) : outer_context_(outer_context) {}

    RC add_table(std::shared_ptr<VirtualTabMeta> vtable_meta)
    {
        // 一些虚拟表可能没有别名，比如子查询，此时不应该有表达式绑定在这上面，因此不加入
        if(vtable_meta->alias_name == "") return RC::SUCCESS;

        if(query_vtables_.count(vtable_meta) == 0) query_vtables_.insert(vtable_meta);
        else return RC::INTERNAL;
        return RC::SUCCESS;
    }

    void set_db(const DbMeta& db) { db_ = db; }

    DbMeta get_db() const { return db_; }

    std::shared_ptr<const BinderContext> outer_context() const { return outer_context_; }

    const std::set<std::shared_ptr<VirtualTabMeta>, VTableMetaComparator> query_vtables() const { return query_vtables_; }

private:
    std::set<std::shared_ptr<VirtualTabMeta>, VTableMetaComparator> query_vtables_;
    std::shared_ptr<const BinderContext> outer_context_;
    DbMeta db_;
};