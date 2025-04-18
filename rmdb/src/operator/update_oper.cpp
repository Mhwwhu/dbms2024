#include "update_oper.h"
#include "common/context.h"
#include "record/rm_defs.h"
#include "tuple/row_tuple.h"
#include "record/bitmap.h"
#include "system/sm_manager.h"

using namespace std;

RC UpdateOper::open(Context* ctx)
{
    if(children_.size() != 1) {
        return RC::INTERNAL;
    }

    auto child = children_.front();
    RC rc = child->open(ctx);
    if(RM_FAIL(rc)) return rc;

    // 收集要更改的记录
    vector<shared_ptr<RmRecord>> records;
    auto tuple = make_shared<RowTuple>(table_, table_.name);

    while(RM_SUCC(rc = child->next())) {
        auto tuple = static_pointer_cast<RowTuple>(child->current_tuple());
        records.push_back(tuple->get_record());
    }
    if(rc == RC::RECORD_EOF) rc = RC::SUCCESS;
    if(RM_FAIL(rc)) return rc;

    rc = child->close();
    if(RM_FAIL(rc)) return rc;

    // 根据set_list生成新的记录
    int bitmap_size = table_.cols.size() / 8 + 1;
    int bitmap_offset = table_.cols.back().offset + table_.cols.back().len;

    for(auto record : records) {
        tuple->set_record(record);
        auto data = record->data;

        // 根据tuple计算出要更新字段的值，存入new_fields中
        map<ColMeta, Value> new_fields;
        for(auto field_set : set_list_) {
            Value val;
            rc = field_set.second->get_value(*tuple, val);
            if(RM_FAIL(rc)) return rc;
            new_fields[field_set.first] = std::move(val);
        }

        // 将record的旧字段替换为新字段
        for(auto field_set : set_list_) {
            auto field_meta = field_set.first;
            auto value = new_fields[field_meta];
            if(value.isnull() && !field_meta.nullable) {
                return RC::FIELD_NULLABLE_CONFLICT;
            }
            memset(data + field_meta.offset, 0, field_meta.len);
            if(!value.isnull()) {
                memcpy(data + field_meta.offset, value.data(), min(value.length(), field_meta.len));
                Bitmap::reset(data + bitmap_offset, field_meta.id);
            }
            else {
                Bitmap::set(data + bitmap_offset, field_meta.id);
            }
        }
    }

    // 更新记录
    auto file_handle = ctx->sm_manager_->fhs_.at(table_.name).get();
    for(auto record : records) {
        rc = file_handle->update_record(record->rid, record->data, ctx);
        if(RM_FAIL(rc)) return rc;
    }

    // TODO: 更新索引

    return rc;
}