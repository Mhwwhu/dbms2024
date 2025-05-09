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
    std::vector<std::shared_ptr<RowTuple>> tuples;
    while(RM_SUCC(rc = child->next())) {
        auto cur_row_tuple = static_pointer_cast<RowTuple>(child->current_tuple());
        auto tuple = make_shared<RowTuple>(cur_row_tuple->table_meta(), cur_row_tuple->alias_name());
        tuple->set_record(make_shared<RmRecord>(*cur_row_tuple->get_record()));
        rids.push_back(tuple->get_record()->rid);
        tuples.push_back(tuple);
    }

    if(rc == RC::RECORD_EOF) rc = RC::SUCCESS;
    if(RM_FAIL(rc)) return rc;

    rc = child->close();
    if(RM_FAIL(rc)) return rc;

    //先删索引
    const auto& indexes = table_meta_.indexes;
    for (const auto& index_meta : indexes) {
        auto& index_handle = context->sm_manager_->ihs_.at(index_meta.name);
        for (size_t i = 0; i < rids.size(); ++i) {
            const auto& rid = rids[i];
            const auto& tuple = tuples[i];

            std::vector<Value> index_values;
            // 收集索引列的值
            for (const auto& col_meta : index_meta.cols) {
                Value val;
                size_t col_index = 0;
                // 找到列在表元数据中的位置
                for (; col_index < table_meta_.cols.size(); ++col_index) {
                    if (table_meta_.cols[col_index].name == col_meta.name) {
                        break;
                    }
                }
                if (col_index == table_meta_.cols.size()) {
                    // 未找到列，理论上不应该发生
                    return RC::SCHEMA_FIELD_MISSING;
                }
                // 获取元组中该列的值
                rc = tuple->cell_at(col_index, val);
                if (RM_FAIL(rc)) {
                    return rc;
                }
                index_values.push_back(val);
            }

            // 转换为 const char* 格式的 key
            std::vector<char> key;
            for (const auto& val : index_values) {
                key.insert(key.end(), val.data(), val.data() + val.length());
            }

            // 删除索引项
//delete_oper.cpp:69
            rc = index_handle->delete_entry(key.data(),context->txn_);
            if (RM_FAIL(rc)) {
                return rc;
            }
        }
    }
    // 然后删除这些记录
    auto file_handle = context->sm_manager_->fhs_.at(table_meta_.name).get();
    for(auto& rid : rids) {
        rc = file_handle->delete_record(rid, context);
        if(RM_FAIL(rc)) return rc;
    }

    return RC::SUCCESS;
}