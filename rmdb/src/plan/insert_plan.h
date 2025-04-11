#pragma once

#include "plan.h"
#include "system/sm_meta.h"
#include "analyze/stmt/stmt.h"

class InsertPlan : public Plan {
public:
    InsertPlan(const TabMeta& table_meta, const std::vector<ColMeta>& decl_cols,
        const std::vector<std::vector<std::shared_ptr<Expression>>>& opt_insert_rows)
    : table_meta_(table_meta), decl_cols_(decl_cols), opt_insert_rows_(opt_insert_rows) {}

    InsertPlan(const TabMeta& table_meta, const std::vector<ColMeta>& decl_cols)
    : table_meta_(table_meta), decl_cols_(decl_cols) {}

    PlanTag type() const override { return PlanTag::INSERT_PLAN; }

    const TabMeta& table_meta() const { return table_meta_; }

    const std::vector<ColMeta>& decl_cols() const { return decl_cols_; }

    const std::vector<std::vector<std::shared_ptr<Expression>>>& opt_insert_rows() const { return opt_insert_rows_; }

private:
    TabMeta table_meta_;
    std::vector<ColMeta> decl_cols_; // 声明要插入的列
    std::vector<std::vector<std::shared_ptr<Expression>>> opt_insert_rows_; // 表示要插入的行，可以有多行。每一行的列数是声明插入列的数量，不足的部分设为null
};