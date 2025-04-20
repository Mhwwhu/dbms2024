#include "command_executor.h"
#include "common/context.h"
#include "create_table_executor.h"
#include "drop_table_executor.h"
#include "show_tables_executor.h"
#include "txn_commit_executor.h"
#include "txn_begin_executor.h"
#include "create_index_executor.h"

RC CommandExecutor::execute(Context* context)
{
    auto stmt = context->stmt;
    RC rc = RC::SUCCESS;

    switch(stmt->type()) {
    case StmtType::CREATE_TABLE_STMT: {
        CreateTableExecutor executor;
        return executor.execute(context);
    }
    case StmtType::DROP_TABLE_STMT: {
        DropTableExecutor executor;
        return executor.execute(context);
    }
    case StmtType::CREATE_INDEX_STMT: {
        CreateIndexExecutor executor;
        rc = executor.execute(context);
        break;
    }
    case StmtType::SHOW_TABLES_STMT: {
        ShowTablesExecutor executor;
        return executor.execute(context);
    }
    case StmtType::TXN_BEGIN_STMT: {
        TxnBeginExecutor executor;
        return executor.execute(context);
    }
    case StmtType::TXN_COMMIT_STMT: {
        TxnCommitExecutor executor;
        return executor.execute(context);
    }
    default: {
        LOG_ERROR("Invalid statement for executor, type = {}", (int)stmt->type());
        return RC::INTERNAL;
    }
    }
}