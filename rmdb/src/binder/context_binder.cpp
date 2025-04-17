#include "context_binder.h"
#include "binder_context.h"
#include "expression/unbound_field_expr.h"
#include "expression/field_expr.h"

using namespace std;

RC ContextBinder::bind_expression(std::shared_ptr<Expression> expr, std::vector<std::shared_ptr<Expression>>& bound_exprs)
{
    switch(expr->type()) {
    case ExprType::UNBOUND_FIELD: {
        return bind_unbound_field_expr(expr, bound_exprs);
    }
    case ExprType::FIELD: {
        return bind_field_expr(expr, bound_exprs);
    }
    case ExprType::VALUE: {
        return bind_value_expr(expr, bound_exprs);
    }

    default: {
        return RC::INTERNAL;
    }
    }
}

RC ContextBinder::bind_unbound_field_expr(std::shared_ptr<Expression> expr, std::vector<std::shared_ptr<Expression>>& bound_exprs)
{
    if(expr == nullptr) return RC::INVALID_ARGUMENT;
    RC rc = RC::SUCCESS;

    auto unbound_field_expr = static_pointer_cast<UnboundFieldExpr>(expr);

    auto table_name = unbound_field_expr->table_name();
    auto field_name = unbound_field_expr->field_name();

    shared_ptr<VirtualTabMeta> vtable;
    auto context = context_;
    bool find_table = false;

    if(table_name == "") {
        if(context_->query_vtables().size() != 1) return RC::FIELD_BIND_ERR;
        vtable = context_->query_vtables().front();
    }
    else {
        while(context) {
            vtable = context->find_vtable(table_name);
            if(!vtable) {
                context = context->outer_context();
            }
            else {
                find_table = true;
                break;
            }
        }
        if(!find_table) return RC::FIELD_BIND_ERR;
    }

    shared_ptr<VirtualFieldMeta> vfield;
    if(!(vfield = vtable->get_vfield(field_name))) return RC::SCHEMA_FIELD_NOT_EXIST;
    auto field_expr = make_shared<FieldExpr>(vfield, vtable);
    field_expr->set_name(vfield->alias_name);
    bound_exprs.push_back(std::move(field_expr));
    return RC::SUCCESS;
}

RC ContextBinder::bind_field_expr(std::shared_ptr<Expression> expr, std::vector<std::shared_ptr<Expression>>& bound_exprs)
{

}

RC ContextBinder::bind_value_expr(std::shared_ptr<Expression> expr, std::vector<std::shared_ptr<Expression>>& bound_exprs)
{
    bound_exprs.push_back(expr);
    return RC::SUCCESS;
}

RC ContextBinder::bind_conjunction_expr(std::shared_ptr<Expression> expr, std::vector<std::shared_ptr<Expression>>& bound_exprs)
{
    
}