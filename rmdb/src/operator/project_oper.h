#pragma once

#include "operator.h"
#include "tuple/expr_tuple.h"

class Expression;

class ProjectOper : public Operator {
public:
    ProjectOper(const std::vector<std::shared_ptr<Expression>>& exprs) : exprs_(exprs), expr_tuple_(std::make_shared<ExprTuple>(exprs)) {}

    OperatorType type() const override { return OperatorType::PROJECT_OPER; }

    RC open(Context* ctx) override;

    RC next() override;

    RC close() override;

    std::shared_ptr<ITuple> current_tuple() const override;

    std::shared_ptr<TupleSchema> tuple_schema() const override;

    bool has_tuple() const override { return true; }

    const std::vector<std::shared_ptr<Expression>>& exprs() const { return exprs_; }

private:
    std::vector<std::shared_ptr<Expression>> exprs_;
    std::shared_ptr<ExprTuple> expr_tuple_;
    bool emitted_ = false;
};