#include "drop_index_stmt.h"

RC DropIndexStmt::create(SmManager* sm_manager, std::shared_ptr<ast::DropIndex> node, std::shared_ptr<IStmt>& stmt)
{
    if(sm_manager == nullptr || node == nullptr) return RC::INVALID_ARGUMENT;

    if(node->tab_name == "") return RC::SCHEMA_TABLE_NAME_MISSING;
    if(node->col_names.empty()) return RC::INVALID_ARGUMENT;
    // 检查表是否存在
    if(sm_manager->fhs_.find(node->tab_name) == sm_manager->fhs_.end()) {
        return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    stmt = std::make_shared<DropIndexStmt>(node->tab_name , node->col_names);

    return RC::SUCCESS;
}