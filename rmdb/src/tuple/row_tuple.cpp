#include "row_tuple.h"
#include "record/bitmap.h"

using namespace std;

RC RowTuple::cell_at(int index, Value& cell) const 
{
    if(index < 0 || index >= cell_num()) return RC::INVALID_ARGUMENT;
    
    int offset= table_meta_.cols[index].offset;
    int size = table_meta_.cols[index].len;
    int bitmap_offset = table_meta_.cols.back().offset + table_meta_.cols.back().len;
    const char* bitmap = record_->data + bitmap_offset;
    AttrType type = table_meta_.cols[index].type;
    bool is_null = Bitmap::is_set(bitmap, index);

    if(is_null) {
        cell = Value();
        cell.set_type(type);
        cell.set_null(true);
        return RC::SUCCESS;
    }

    cell = Value(type, record_->data + offset, size);
    return RC::SUCCESS;
}

RC RowTuple::spec_at(int index, ITupleCellSpec& spec) const
{
    if(index < 0 || index >= cell_num()) return RC::INVALID_ARGUMENT;
    spec = RowTupleCellSpec(alias_name_, table_meta_.cols[index].name);
    return RC::SUCCESS;
}

RC RowTuple::find_cell(const ITupleCellSpec& spec, Value& cell) const
{
    if(auto row_spec = dynamic_cast<const RowTupleCellSpec*>(&spec)) {
        if(row_spec->alias_table_name() != alias_name_) return RC::NOTFOUND;
        string field_name = row_spec->field_name();
        ColMeta col;
        RC rc = table_meta_.get_col(field_name, col);
        if(RM_FAIL(rc)) return rc;
        return cell_at(col.id, cell);
    }
    
    return RC::NOTFOUND;
}