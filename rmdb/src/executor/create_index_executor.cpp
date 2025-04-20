
#include "create_index_executor.h"
#include "common/context.h"
#include "analyze/stmt/create_index_stmt.h"
#include "system/sm_manager.h"
#include "parser/ast.h"

RC CreateIndexExecutor::execute(Context* context)
{
    RC rc = RC::SUCCESS;
    auto stmt = std::dynamic_pointer_cast<CreateIndexStmt>(context->stmt);

    auto sm_manager = context->sm_manager_;

	if(stmt->type() != StmtType::CREATE_INDEX_STMT) {
        return RC::INVALID_ARGUMENT;
    }

	return sm_manager->create_index(stmt->table_meta(), stmt->col_metas(), context);
}




