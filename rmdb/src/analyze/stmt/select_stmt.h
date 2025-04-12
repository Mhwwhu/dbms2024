#pragma once

#include "stmt.h"
#include "analyze/clause/filter_clause.h"
#include "analyze/clause/orderby_clause.h"
#include "analyze/clause/join_clause.h"
#include "expression/expression.h"
#include "parser/ast.h"

class SelectStmt : public IStmt {
public:
    SelectStmt(std::shared_ptr<JoinClause> join, std::shared_ptr<FilterClause> where, std::shared_ptr<FilterClause> having,
        std::shared_ptr<OrderByClause> orderby, const std::vector<std::shared_ptr<Expression>>& project,
        const std::vector<std::shared_ptr<Expression>>& groupby, int limit)
        : join_tree_(join), where_clause_(where), having_clause_(having), orderby_clause_(orderby), project_exprs_(project),
        groupby_exprs_(groupby), limit_(limit) {} 
    ~SelectStmt() override = default;

    StmtType type() const override { return StmtType::SELECT_STMT; }

    static RC create(SmManager* manager, std::shared_ptr<ast::SelectNode> select_node, std::shared_ptr<IStmt>& select_stmt, 
        std::shared_ptr<BinderContext> outer_context);

    std::shared_ptr<JoinClause> join_tree() const { return join_tree_; }
    std::shared_ptr<FilterClause> where_clause() const { return where_clause_; }
    std::shared_ptr<FilterClause> having_clause() const { return having_clause_; }
    std::shared_ptr<OrderByClause> orderby_clause() const { return orderby_clause_; }
    std::vector<std::shared_ptr<Expression>> project_exprs() const { return project_exprs_; }
    std::vector<std::shared_ptr<Expression>> groupby_exprs() const { return groupby_exprs_; }
    int limit() const { return limit_; }
    
private:
    std::shared_ptr<JoinClause> join_tree_ = nullptr;
    std::shared_ptr<FilterClause> where_clause_ = nullptr;
    std::shared_ptr<FilterClause> having_clause_ = nullptr;
    std::shared_ptr<OrderByClause> orderby_clause_ = nullptr;
    std::vector<std::shared_ptr<Expression>> project_exprs_;
    std::vector<std::shared_ptr<Expression>> groupby_exprs_;
    int limit_ = -1;
};