#pragma once

#include <memory>

#include "system/sm_meta.h"
#include "binder_context.h"

class JointreeContext {
    JointreeContext(std::shared_ptr<BinderContext> outer)
    : outer_context_(outer), is_leaf_(true) {}

    JointreeContext(std::shared_ptr<VirtualTabMeta> vtable, std::shared_ptr<BinderContext> outer)
    : outer_context_(outer), is_leaf_(true) 
    {
        vtables_.insert(vtable);
    }

    RC set_children(std::shared_ptr<JointreeContext> left, std::shared_ptr<JointreeContext> right)
    {
        left_context_ = left;
        right_context_ = right;

        vtables_ = left->vtables_;
        for(auto vtable : right->vtables_) {
            if(vtables_.count(vtable) != 0) return RC::DUPLICATE_ALIAS_NAME;
            vtables_.insert(vtable);
        }
        is_leaf_ = false;
        return RC::SUCCESS;
    }

    std::shared_ptr<const BinderContext> outer_context() const { return outer_context_; }
    std::shared_ptr<const JointreeContext> left_child() const { return left_context_; }
    std::shared_ptr<const JointreeContext> right_child() const { return right_context_; }
    const std::set<std::shared_ptr<VirtualTabMeta>, VTableMetaComparator>& vtables() const { return vtables_; }
    bool is_leaf() const { return is_leaf_; }

private:
    std::shared_ptr<const BinderContext> outer_context_;
    std::shared_ptr<const JointreeContext> left_context_;
    std::shared_ptr<const JointreeContext> right_context_;
    std::set<std::shared_ptr<VirtualTabMeta>, VTableMetaComparator> vtables_;
    bool is_leaf_;
};