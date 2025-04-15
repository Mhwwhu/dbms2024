#include "show_tables_executor.h"
#include "common/context.h"
#include "analyze/stmt/show_tables_stmt.h"
#include "system/sm_manager.h"
#include "parser/ast.h"

RC ShowTablesExecutor::execute(Context* context){

    auto stmt = std::dynamic_pointer_cast<ShowTablesStmt>(context->stmt);
    auto sm_manager = context->sm_manager_;
    sm_manager->show_tables(context);
    return RC::SUCCESS;
};