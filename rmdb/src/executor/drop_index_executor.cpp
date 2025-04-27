#include "drop_index_executor.h"
#include "analyze/stmt/drop_index_stmt.h"
#include "common/context.h"

RC DropIndexExecutor::execute(Context* context)
{
    auto stmt = std::dynamic_pointer_cast<DropIndexStmt>(context->stmt);

    auto sm_manager = context->sm_manager_;

    return sm_manager->drop_index(stmt->table_name(),stmt->col_names(),context);

}