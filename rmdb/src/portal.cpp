#include "portal.h"
#include "executor/command_executor.h"

RC Portal::handle_request(Context* context)
{
    // TODO: 检查context中的oper是否为空，如果为空则代表不是DML语句，此时应构造CommandExecutor来执行DDL或者其他CMD
    RC rc = RC::SUCCESS;
    auto oper = context->oper;

    if(oper != nullptr) {
        context->sql_result.set_oper(oper);
        return rc;
    }

    auto stmt = context->stmt;
    if(stmt == nullptr) {
        rc = RC::INTERNAL;
        return rc;
    }
    CommandExecutor executor;
    rc = executor.execute(context);
    context->sql_result.set_return_code(rc);
    

    return rc;
}