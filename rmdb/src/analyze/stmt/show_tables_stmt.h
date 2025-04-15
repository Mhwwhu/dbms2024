
#pragma once

#include "stmt.h"
#include "parser/ast.h"

using namespace std;

class ShowTablesStmt: public IStmt {
    public:
        ShowTablesStmt() = default;
    
        StmtType type() const override { return StmtType::SHOW_TABLES_STMT; }
    
        static RC create(std::shared_ptr<ast::ShowTables> node, std::shared_ptr<IStmt>& stmt);
    
    };
