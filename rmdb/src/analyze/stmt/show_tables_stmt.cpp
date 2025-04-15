#include "show_tables_stmt.h"

RC ShowTablesStmt::create(std::shared_ptr<ast::ShowTables> node, std::shared_ptr<IStmt>& stmt){
    RC rc = RC::SUCCESS;
    stmt = make_shared<ShowTablesStmt>();
    return rc;
}