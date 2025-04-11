#pragma once

#include "operator.h"
#include "system/sm_meta.h"
#include "record/rm_defs.h"

class InsertOper : public Operator {
public:
    InsertOper(const TabMeta& table_meta, const std::vector<ColMeta>& decl_cols)
    : table_meta_(table_meta), decl_cols_(decl_cols){}

    OperatorType type() const override { return OperatorType::INSERT_OPER; }

    RC open(Context* ctx) override;

    RC next() override { return RC::RECORD_EOF; }

    RC close() override { return RC::SUCCESS; }

    std::shared_ptr<ITuple> current_tuple() const override { return nullptr; }

    RC tuple_schema(TupleSchema& schema) const override { return RC::UNSUPPORTED; }

    bool has_tuple() const override { return false; }

private:
    // 这里向record中加入了bitmap，但目前实际存储中并不保存bitmap。
    RC make_record(std::shared_ptr<ITuple> tuple, std::shared_ptr<RmRecord>& record);

private:
    TabMeta table_meta_;
    std::vector<ColMeta> decl_cols_;

    Context* context_;
};