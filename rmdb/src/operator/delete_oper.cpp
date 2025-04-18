#include "delete_oper.h"
#include "tuple/row_tuple.h"
#include "common/context.h"
#include "system/sm_manager.h"

using namespace std;

RC DeleteOper::open(Context* context)
{
    if(children_.size() != 1) return RC::INTERNAL;
    auto child = children_[0];
    RC rc = child->open(context);
    if(RM_FAIL(rc)) return rc;

    // 首先收集待删除的记录
    std::vector<Rid> rids;
    while(RM_SUCC(rc = child->next())) {
        auto tuple = static_pointer_cast<RowTuple>(child->current_tuple());
        rids.push_back(tuple->get_record()->rid);
    }

    if(rc == RC::RECORD_EOF) rc = RC::SUCCESS;
    if(RM_FAIL(rc)) return rc;

    rc = child->close();
    if(RM_FAIL(rc)) return rc;

    // 然后删除这些记录
    auto file_handle = context->sm_manager_->fhs_.at(table_meta_.name).get();
    for(auto& rid : rids) {
        rc = file_handle->delete_record(rid, context);
        if(RM_FAIL(rc)) return rc;
    }

    return RC::SUCCESS;
}