#pragma once

#include "tuple.h"
#include "tuple_cell.h"
#include <memory>
#include "row_tuple_cell.h"
#include "system/sm_meta.h"
#include <vector>

class RmRecord;

class RowTuple : public ITuple {
public:
    RowTuple(const TabMeta& table_meta) : table_meta_(table_meta) {}
    ~RowTuple() override = default;

    int cell_num() const override { return static_cast<int>(table_meta_.cols.size()); }

    RC cell_at(int index, Value& cell) const;

    RC spec_at(int index, ITupleCellSpec& spec) const override;

    RC find_cell(const ITupleCellSpec& spec, Value& cell) const override;

    void set_record(std::shared_ptr<RmRecord> record) { record_ = record; }

    std::shared_ptr<RmRecord> get_record() const { return record_; }
    const TabMeta& table_meta() const { return table_meta_; }

private:
    std::shared_ptr<RmRecord> record_;
    TabMeta table_meta_;
};