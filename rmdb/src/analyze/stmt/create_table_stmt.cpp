#include "create_table_stmt.h"

using namespace std;

RC CreateTableStmt::create(SmManager* manager, std::shared_ptr<ast::CreateTable> node, std::shared_ptr<IStmt>& stmt)
{
    RC rc = RC::SUCCESS;

    if(manager == nullptr || node == nullptr) return RC::INVALID_ARGUMENT;

    string table_name = node->tab_name;
    auto field_defs = node->fields;

    if(table_name == "") return RC::SCHEMA_TABLE_NAME_MISSING;
    if(field_defs.size() == 0) return RC::SCHEMA_FIELD_MISSING;

    stmt = make_shared<CreateTableStmt>(table_name, field_defs);

    return rc;
}