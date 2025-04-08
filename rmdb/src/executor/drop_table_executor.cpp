#include "drop_table_executor.h"
#include "analyze/stmt/drop_table_stmt.h"
#include "common/context.h"

RC DropTableExecutor::execute(Context* context)
{
    auto stmt = std::dynamic_pointer_cast<DropTableStmt>(context->stmt);

    auto sm_manager = context->sm_manager_;

    sm_manager->drop_table(stmt->table_name(), context);

    return RC::SUCCESS;
}