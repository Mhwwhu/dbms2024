#include "drop_table_stmt.h"

RC DropTableStmt::create(SmManager* sm_manager, std::shared_ptr<ast::DropTable> node, std::shared_ptr<IStmt>& stmt)
{
    if(sm_manager == nullptr || node == nullptr) return RC::INVALID_ARGUMENT;

    if(node->tab_name == "") return RC::SCHEMA_TABLE_NAME_MISSING;

    // 检查表是否存在
    if(sm_manager->fhs_.find(node->tab_name) == sm_manager->fhs_.end()) {
        return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    stmt = std::make_shared<DropTableStmt>(node->tab_name);

    return RC::SUCCESS;
}