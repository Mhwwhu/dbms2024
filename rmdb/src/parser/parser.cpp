#include "parser.h"
#include "common/context.h"

using namespace std;

int sql_parse(const char* sql, std::shared_ptr<ast::TreeNode>& sql_result);

RC Parser::handle_request(Context* ctx)
{
    RC rc = RC::SUCCESS;

    auto& sql_result = ctx->sql_result;
    auto sql_string = ctx->sql;

    shared_ptr<ast::TreeNode> root;
    parse(sql_string.c_str(), root);
    if(root == nullptr) {
        LOG_ERROR("Empty parse tree");
        sql_result.set_return_code(RC::INTERNAL);
        return RC::INTERNAL;
    }

    if(auto error_node = dynamic_pointer_cast<ast::ErrorNode>(root)) {
        LOG_ERROR("Syntax error: {}", error_node->error_msg);
        sql_result.set_return_code(RC::SQL_SYNTAX);
        return RC::SQL_SYNTAX;
    }

    ctx->sql_node = std::move(root);

    return RC::SUCCESS;
}

RC Parser::parse(const char* sql, std::shared_ptr<ast::TreeNode>& sql_result)
{
    sql_parse(sql, sql_result);
	return RC::SUCCESS;
}