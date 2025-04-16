#include "insert_stmt.h"

using namespace std;

RC InsertStmt::create(SmManager* sm_manager, std::shared_ptr<ast::InsertNode> insert_node, std::shared_ptr<IStmt>& stmt)
{
    RC rc = RC::SUCCESS;
    if(sm_manager == nullptr || insert_node == nullptr) return RC::INVALID_ARGUMENT;

    string table_name = insert_node->tab_name;
    if(table_name == "") return RC::SCHEMA_TABLE_NAME_MISSING;

    // 检查是否存在表
    TabMeta table_meta;
    if(RM_FAIL(rc = sm_manager->db_.get_table(table_name, table_meta))) return rc; 

    // 检查声明插入的列是否存在，如果为空则将设置decl_cols为所有列 && 检查未声明的列是否可以为空
    vector<ColMeta> decl_cols;
    if(insert_node->decl_cols.empty()) {
        decl_cols = table_meta.cols;
    }
    else {
        for(auto col : insert_node->decl_cols) {
            ColMeta col_meta;
            if(RM_FAIL(rc = table_meta.get_col(col, col_meta))) return rc;
            decl_cols.push_back(col_meta);
        }
        for(auto col : table_meta.cols) {
            if(!col.nullable && 
                std::find_if(decl_cols.begin(), decl_cols.end(), [&col](ColMeta& other){ return col.name == other.name; }) == decl_cols.end())
            {
                return RC::FIELD_NULLABLE_CONFLICT;
            }
        }
    }

    //insert_value 
    if(true) {
        auto insert_rows = insert_node->exprs;
        stmt = std::make_shared<InsertStmt>(table_meta, decl_cols, insert_rows);
        return RC::SUCCESS;
    }
    //Todo:insert select 
    else {
        return RC::UNIMPLEMENTED;
    }

    return RC::UNIMPLEMENTED;
}