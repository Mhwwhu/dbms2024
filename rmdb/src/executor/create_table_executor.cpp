#include "create_table_executor.h"
#include "common/context.h"
#include "analyze/stmt/create_table_stmt.h"
#include "system/sm_manager.h"
#include "parser/ast.h"

RC CreateTableExecutor::execute(Context* context)
{
    RC rc = RC::SUCCESS;

    auto stmt = std::dynamic_pointer_cast<CreateTableStmt>(context->stmt);

    auto sm_manager = context->sm_manager_;

    std::vector<ColDef> col_defs;
    for(auto field_def : stmt->field_defs()) {
        col_defs.push_back(ColDef{
            .name = field_def->col_name,
            .type = field_def->type_len->type,
            .len = field_def->type_len->len
        });
    }
    sm_manager->create_table(stmt->table_name(), col_defs, context);

    return rc;
}