#pragma once

#include "stmt.h"
#include "system/sm_manager.h"
#include "parser/ast.h"

#include <string>
#include <memory>

class DropTableStmt : public IStmt {
public:
    DropTableStmt(const std::string& table_name)
    : table_name_(table_name) {}

    StmtType type() const override { return StmtType::DROP_TABLE_STMT; }

    static RC create(SmManager* sm_manager, std::shared_ptr<ast::DropTable> node, std::shared_ptr<IStmt>& stmt);

    const std::string table_name() const { return table_name_; }

private:
    std::string table_name_;
};