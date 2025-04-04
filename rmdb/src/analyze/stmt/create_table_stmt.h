#pragma once

#include "stmt.h"
#include "expression/expression.h"

class CreateTableStmt : public IStmt {
public:
    CreateTableStmt(const std::string& table_name, const std::vector<std::shared_ptr<ast::Field>>& field_defs)
    : table_name_(table_name), field_defs_(field_defs) {}
    ~CreateTableStmt() override = default;

    StmtType type() const override { return StmtType::CREATE_TABLE_STMT; }

    static RC create(SmManager* manager, std::shared_ptr<ast::CreateTable> create_table_node, std::shared_ptr<IStmt>& stmt);

    const std::string table_name() const { return table_name_; }

    const std::vector<std::shared_ptr<ast::Field>> field_defs() const { return field_defs_; }
    
private:
    std::string table_name_;
    std::vector<std::shared_ptr<ast::Field>> field_defs_;
};