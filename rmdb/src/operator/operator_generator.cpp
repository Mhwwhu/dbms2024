#include "operator_generator.h"
#include "chunk_get_oper.h"
#include "insert_oper.h"
#include "tuple/expr_tuple.h"

RC OperatorGenerator::generate(std::shared_ptr<Plan> plan, std::shared_ptr<Operator>& oper)
{
    switch(plan->type()) {
    case PlanTag::INSERT_PLAN:
        return create_operator(std::static_pointer_cast<InsertPlan>(plan), oper);
    }
    return RC::SUCCESS;
}

RC OperatorGenerator::create_operator(std::shared_ptr<InsertPlan> plan, std::shared_ptr<Operator>& oper)
{
    // InsertPlan的child最多只能有一个，即ProjectPlan
    if(plan->children().size() == 1 && plan->children().front()->type() != PlanTag::PROJECT_PLAN) return RC::INTERNAL;
    if(plan->children().size() > 1) return RC::INTERNAL;
    auto child = plan->children().empty() ? nullptr : plan->children().front();

    if(!child) {
        std::vector<std::shared_ptr<ITuple>> chunk;
        std::vector<TupleSchema> schema;
        auto rows = plan->opt_insert_rows();
        for(size_t i = 0; i < rows.size(); i++) {
            chunk.push_back(std::make_shared<ExprTuple>(rows[i]));
            schema.push_back(TupleSchema());
            for(auto expr : rows[i]) {
                schema[i].append_cell(std::make_shared<ExprTupleCellSpec>(expr));
            }
        }
        auto child_oper = std::make_shared<ChunkGetOper>(chunk, schema);

        oper = std::make_shared<InsertOper>(plan->table_meta(), plan->decl_cols());
        oper->add_child(child_oper);

        return RC::SUCCESS;
    }
    else if(child->type() == OperatorType::PROJECT_OPER) {
        // TODO
        return RC::UNIMPLEMENTED;
    }
    
    return RC::INTERNAL;
}