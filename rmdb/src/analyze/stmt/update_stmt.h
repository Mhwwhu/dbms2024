#pragma once

#include "stmt.h"
#include "system/sm_meta.h"
#include "parser/ast.h"

class Expression;
class FilterClause;
class SmManager;

class UpdateStmt : public IStmt {
public:
    UpdateStmt(const TabMeta& table, const std::map<ColMeta, std::shared_ptr<Expression>>& set_list, std::shared_ptr<FilterClause> filter)
    : table_(table), set_list_(set_list), filter_(filter) {}
    ~UpdateStmt() override = default;

    StmtType type() const override { return StmtType::UPDATE_STMT; }

    static RC create(SmManager* sm_manager, std::shared_ptr<ast::UpdateNode> update_node, std::shared_ptr<IStmt>& stmt);

    const TabMeta& table_meta() const { return table_; }
    const std::map<ColMeta, std::shared_ptr<Expression>>& set_list() const { return set_list_; }
    std::shared_ptr<FilterClause> filter() const { return filter_; }

private:
    TabMeta table_;
    std::map<ColMeta, std::shared_ptr<Expression>> set_list_;
    std::shared_ptr<FilterClause> filter_;
};