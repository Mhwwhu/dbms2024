#pragma once

#include "stmt.h"
#include "system/sm_meta.h"
#include "expression/expression.h"
#include "analyze/clause/filter_clause.h"
#include "parser/ast.h"
#include "system/sm_manager.h"


class DeleteStmt : public IStmt {
public:
    DeleteStmt() = default;
    DeleteStmt(const TabMeta& table_meta, std::shared_ptr<FilterClause> where ): table_meta_(table_meta), where_clause_(where) {};

    StmtType type() const override { return StmtType::DELETE_STMT; }

    const TabMeta& table_meta() const { return table_meta_; }

    const std::shared_ptr<FilterClause>& where_clause() const { return where_clause_; }
    static RC create(SmManager* sm_manager, std::shared_ptr<ast::DeleteNode> delete_node, std::shared_ptr<IStmt>& stmt);
private:
    TabMeta table_meta_;
    std::shared_ptr<FilterClause> where_clause_ = nullptr;
};