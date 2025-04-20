
#pragma once

#include "stmt.h"
#include "system/sm_manager.h"
#include "parser/ast.h"

class CreateIndexStmt : public IStmt
{
public:
	CreateIndexStmt(TabMeta& table_meta , std::vector<ColMeta>& col_metas): table_meta_(table_meta) ,col_metas_(col_metas) {}

	virtual ~CreateIndexStmt() = default;

	StmtType type() const override { return StmtType::CREATE_INDEX_STMT; }

    TabMeta& table_meta()  { return table_meta_; }
    const std::vector<ColMeta>& col_metas() const { return col_metas_; }

    static RC create(SmManager* sm_manager, std::shared_ptr<ast::CreateIndex> create_index_node, std::shared_ptr<IStmt>& stmt);
	bool unique() const { return unique_; }

private:
	TabMeta table_meta_;
    std::vector<ColMeta> col_metas_;
	bool unique_;
};
