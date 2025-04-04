#include "command_executor.h"
#include "common/context.h"
#include "create_table_executor.h"

RC CommandExecutor::execute(Context* context)
{
    auto stmt = context->stmt;
    RC rc = RC::SUCCESS;

    switch(stmt->type()) {
    case StmtType::CREATE_TABLE_STMT:
        CreateTableExecutor executor;
        rc = executor.execute(context);
        break;
    }

    return rc;
}