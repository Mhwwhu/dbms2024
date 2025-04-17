#pragma once

#include "expression/expression.h"
#include "common/rc.h"
#include "system/sm_meta.h"

class BinderContext {
public:
    BinderContext(std::shared_ptr<BinderContext> outer_context) : outer_context_(outer_context) {}

    RC add_table(std::shared_ptr<VirtualTabMeta> vtable_meta)
    {
        // 一些虚拟表可能没有别名，比如子查询，此时不应该有表达式绑定在这上面，因此不加入
        if(vtable_meta->alias_name == "") return RC::SUCCESS;
        bool find_table = false;
        for(auto vtable : query_vtables_) {
            if(vtable->alias_name == vtable_meta->alias_name) {
                find_table = true;
                break;
            }
        }
        
        if(!find_table) query_vtables_.push_back(vtable_meta);
        else return RC::INTERNAL;
        return RC::SUCCESS;
    }

    std::shared_ptr<VirtualTabMeta> find_vtable(const std::string& name) const
    {
        for(auto vtable : query_vtables_) {
            if(vtable->alias_name == name) return vtable;
        }
        return nullptr;
    }

    void set_db(const DbMeta& db) { db_ = db; }

    DbMeta get_db() const { return db_; }

    std::shared_ptr<const BinderContext> outer_context() const { return outer_context_; }

    const std::vector<std::shared_ptr<VirtualTabMeta>>& query_vtables() const { return query_vtables_; }

private:
    std::vector<std::shared_ptr<VirtualTabMeta>> query_vtables_;
    std::shared_ptr<const BinderContext> outer_context_;
    DbMeta db_;
};