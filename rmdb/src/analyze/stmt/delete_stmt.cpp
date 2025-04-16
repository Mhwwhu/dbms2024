#include "stmt/delete_stmt.h"

RC DeleteStmt::create(SmManager* sm_manager, std::shared_ptr<ast::DeleteNode> delete_node, std::shared_ptr<IStmt>& stmt){
    RC rc = RC::SUCCESS;
    if(sm_manager == nullptr || delete_node == nullptr) return RC::INVALID_ARGUMENT;

    std::string table_name = delete_node->tab_name;
    if(table_name == "") return RC::SCHEMA_TABLE_NAME_MISSING;

    TabMeta table_meta;
    if(RM_FAIL(rc = sm_manager->db_.get_table(table_name, table_meta))) return rc; 
    
    std::shared_ptr<FilterClause> where_clause;
    if(delete_node->where_conj != nullptr){
        if(RM_FAIL(rc = FilterClause::create(sm_manager, delete_node->where_conj, where_clause , nullptr))) return rc;
    }

    stmt = std::make_shared<DeleteStmt>(table_meta,where_clause);

    return rc;
}