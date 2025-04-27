#include "insert_oper.h"
#include "common/context.h"
#include "record/bitmap.h"
#include "system/sm_manager.h"

using namespace std;

RC InsertOper::open(Context* ctx)
{
    if(children_.size() != 1) return RC::INTERNAL;

    auto child = children_.front();

    if(child->type() != OperatorType::CHUNK_GET_OPER && child->type() != OperatorType::PROJECT_OPER) return RC::INTERNAL;

    RC rc = child->open(ctx);
    if(RM_FAIL(rc)) {
        return rc;
    }

    auto& file_handle = ctx->sm_manager_->fhs_.at(table_meta_.name);
    while(RM_SUCC(rc = child->next())) {
        auto tuple = child->current_tuple();
        if(tuple->cell_num() > decl_cols_.size()) return RC::IMPLICIT_INSERT_FIELD;

        std::shared_ptr<RmRecord> record;
        rc = make_record(tuple, record);
        if(RM_FAIL(rc)) return rc;

        Rid rid;
        rc = file_handle->insert_record(record->data, rid, ctx);
        if(RM_FAIL(rc)) return rc;


         // 获取表的索引元数据
         const auto& indexes = table_meta_.indexes;
         for (const auto& index_meta : indexes) {
             std::vector<Value> index_values;
             // 收集索引列的值
             for (const auto& col_meta : index_meta.cols) {
                 Value val;
                 size_t col_index = 0;
                 // 找到列在 decl_cols_ 中的位置
                 for (; col_index < decl_cols_.size(); ++col_index) {
                     if (decl_cols_[col_index].name == col_meta.name) {
                         break;
                     }
                 }
                 if (col_index == decl_cols_.size()) {
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

             auto& index_handle = ctx->sm_manager_->ihs_.at(index_meta.name);
             // 插入索引项
             int pg_id;//没用
             vector<char> key;
             for(auto val : index_values) {
                 key.insert(key.end(), val.data(), val.data() + val.length());
             }
             rc = index_handle->insert_entry(key.data(), rid , ctx->txn_, pg_id);
             if (RM_FAIL(rc)) {
                 return rc;
             }
         }
    }

    child->close();
    if(rc != RC::RECORD_EOF) return rc;
    return RC::SUCCESS;
}

RC InsertOper::make_record(std::shared_ptr<ITuple> tuple, std::shared_ptr<RmRecord>& record)
{
    vector<Value> values;
    RC rc = RC::SUCCESS;
    for(size_t i = 0; i < tuple->cell_num(); i++) {
        Value val;
        if(RM_FAIL(rc = tuple->cell_at(i, val))) return rc;
        values.push_back(val);
    }
    while(values.size() < decl_cols_.size()) {
        Value v;
        v.set_null(true);
        values.push_back(v);
    }

    size_t record_size = 0;
    for(auto col : table_meta_.cols) {
        record_size += col.len;
    }
    size_t bitmap_offset = record_size;
    size_t bitmap_size = table_meta_.cols.size() / 8 + 1; // bitmap的大小
    record_size += bitmap_size; 

    char* record_buf = new char[record_size];
    memset(record_buf, 0, record_size);

    Bitmap::init(record_buf + bitmap_offset, bitmap_size, true);
    
    int iter = 0;
    for(auto col : decl_cols_) {
        int offset = col.offset;
        int size = col.len;
        int id = col.id;
        // 检查是否为null，如果不是才要拷贝data
        if(!values[iter].isnull()) {
            memcpy(record_buf + offset, values[iter].data(), std::min(size, values[iter].length()));
            Bitmap::reset(record_buf + bitmap_offset, id);
        }
        else if(col.nullable) {
            memset(record_buf + offset, 0, size);
        }
        else {
            // not nullable的字段插入了null值，失败
            return RC::FIELD_NULLABLE_CONFLICT;
        }
        iter++;
    }
    record = std::make_shared<RmRecord>(record_size, record_buf);
    return RC::SUCCESS;
}
