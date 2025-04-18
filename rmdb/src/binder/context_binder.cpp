#include "context_binder.h"
#include "binder_context.h"
#include "expression/unbound_field_expr.h"
#include "expression/field_expr.h"
#include "expression/comparison_expr.h"
#include "expression/conjunction_expr.h"

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
    case ExprType::COMPARISON: {
        return bind_comp_expr(expr, bound_exprs);
    }
    case ExprType::CONJUNCTION: {
        return bind_conjunction_expr(expr, bound_exprs);
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
    if(expr == nullptr) return RC::INVALID_ARGUMENT;

    auto conj_expr = static_pointer_cast<ConjunctionExpr>(expr);
    std::vector<std::shared_ptr<Expression>> bound_conj_exprs;
    RC rc = bind_expression(conj_expr->left(), bound_conj_exprs);
    if(RM_FAIL(rc)) return rc;
    rc = bind_expression(conj_expr->right(), bound_conj_exprs);
    if(RM_FAIL(rc)) return rc;
    auto left = bound_conj_exprs[0];
    auto right = bound_conj_exprs[1];
    auto new_conj_expr = make_shared<ConjunctionExpr>(left, right, conj_expr->conj_type());
    new_conj_expr->set_name(conj_expr->name());
    bound_exprs.push_back(new_conj_expr);
    return RC::SUCCESS;
}

RC ContextBinder::bind_comp_expr(std::shared_ptr<Expression> expr, std::vector<std::shared_ptr<Expression>>& bound_exprs)
{
    if(expr == nullptr) return RC::INVALID_ARGUMENT;

    std::vector<std::shared_ptr<Expression>> bound_comp_exprs;
    auto comp_expr = static_pointer_cast<ComparisonExpr>(expr);
    RC rc = bind_expression(comp_expr->left(), bound_comp_exprs);
    if(RM_FAIL(rc)) return rc;
    rc = bind_expression(comp_expr->right(), bound_comp_exprs);
    if(RM_FAIL(rc)) return rc;
    auto left = bound_comp_exprs[0];
    auto right = bound_comp_exprs[1];
    auto new_comp_expr = make_shared<ComparisonExpr>(left, right, comp_expr->op());
    new_comp_expr->set_name(comp_expr->name());
    bound_exprs.push_back(new_comp_expr);
    return RC::SUCCESS;
}