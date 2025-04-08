#pragma once

#include "stmt.h"
#include "system/sm_meta.h"
#include "expression/expression.h"
#include "parser/ast.h"
#include "system/sm_manager.h"
#include "select_stmt.h"

class InsertStmt : public IStmt {
public:
    InsertStmt() = default;
    InsertStmt(const TabMeta& table_meta, const std::vector<ColMeta>& decl_cols,
        const std::vector<std::vector<std::shared_ptr<Expression>>> insert_rows)
    : table_meta_(table_meta), decl_cols_(decl_cols), opt_insert_rows_(insert_rows), use_select_(false) {}
    InsertStmt(const TabMeta& table_meta, const std::vector<ColMeta>& decl_cols, std::shared_ptr<SelectStmt> select_stmt)
    : table_meta_(table_meta), decl_cols_(decl_cols), opt_select_stmt_(select_stmt), use_select_(true) {}
    
    StmtType type() const override { return StmtType::INSERT_STMT; }

    static RC create(SmManager* sm_manager, std::shared_ptr<ast::InsertNode> insert_node, std::shared_ptr<IStmt>& stmt);

    const TabMeta& table_meta() const { return table_meta_; }

    const std::vector<ColMeta>& decl_cols() const { return decl_cols_; }

    const std::vector<std::vector<std::shared_ptr<Expression>>>& opt_insert_rows() const { return opt_insert_rows_; }

    std::shared_ptr<SelectStmt> opt_select_stmt() const { return opt_select_stmt_; }

    bool use_select() const { return use_select_; }

private:
    TabMeta table_meta_;
    std::vector<ColMeta> decl_cols_; // 声明要插入的列
    std::vector<std::vector<std::shared_ptr<Expression>>> opt_insert_rows_; // 表示要插入的行，可以有多行。每一行的列数是声明插入列的数量，不足的部分设为null
    std::shared_ptr<SelectStmt> opt_select_stmt_;
    bool use_select_;
};