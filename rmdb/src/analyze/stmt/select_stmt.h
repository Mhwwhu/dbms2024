#pragma once

#include "stmt.h"
#include "analyze/clause/filter_clause.h"
#include "analyze/clause/orderby_clause.h"
#include "expression/expression.h"
#include "parser/ast.h"

class SelectStmt : public IStmt {
public:
    SelectStmt() = default;
    ~SelectStmt() override = default;

    StmtType type() const override { return StmtType::SELECT_STMT; }

    // RC create(SmManager* manager, std::shared_ptr<ast::SelectNode> select_node, std::shared_ptr<IStmt>& select_query);

    std::shared_ptr<FilterClause> where_clause() const { return where_clause_; }
    std::shared_ptr<FilterClause> having_clause() const { return having_clause_; }
    std::shared_ptr<OrderByClause> orderby_clause() const { return orderby_clause_; }
    int limit() const { return limit_; }
    
private:
    std::shared_ptr<FilterClause> where_clause_ = nullptr;
    std::shared_ptr<FilterClause> having_clause_ = nullptr;
    std::shared_ptr<OrderByClause> orderby_clause_ = nullptr;
    std::vector<std::shared_ptr<Expression>> project_exprs_;
    std::vector<std::shared_ptr<Expression>> groupby_exprs_;
    int limit_ = -1;
};