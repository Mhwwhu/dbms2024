#include "create_index_stmt.h"



RC CreateIndexStmt::create(SmManager* sm_manager, std::shared_ptr<ast::CreateIndex> create_index_node, std::shared_ptr<IStmt>& stmt)
{
	RC rc = RC::SUCCESS;
	std::string tab_name = create_index_node->tab_name;
	if (tab_name.empty()) {
        //LogWarn
		return RC::INVALID_ARGUMENT;
	}
	for (auto col_name : create_index_node->col_names) {
		if (col_name.empty()) {
            //LogWarn
			return RC::INVALID_ARGUMENT;
		}
	}

	TabMeta tab_meta;
	if ((rc = sm_manager->db_.get_table(tab_name, tab_meta)) != RC::SUCCESS) {
		return rc;
	}

	std::vector<ColMeta> col_metas;
	for (auto col_name : create_index_node->col_names) {
		if (!tab_meta.is_col(col_name)) {
			//logwarn
			return RC::SCHEMA_FIELD_NOT_EXIST;
		}
		ColMeta col_meta;
		tab_meta.get_col(col_name , col_meta);
		col_metas.push_back(col_meta);
	}


	stmt = std::make_shared<CreateIndexStmt>(tab_meta, col_metas);
	return RC::SUCCESS;
}
