#pragma once

#include"operator.h"

class Expression;

class FilterOper : public Operator {
public:
    FilterOper(std::shared_ptr<Expression> expr) : expr_(expr) {}
    ~FilterOper() override = default;

    OperatorType type() const override { return OperatorType::FILTER_OPER; }

    RC open(Context* context) override;

    RC next() override;

    RC close() override;

    std::shared_ptr<ITuple> current_tuple() const override { return children_[0]->current_tuple(); }

    std::shared_ptr<TupleSchema> tuple_schema() const override { return children_[0]->tuple_schema(); }

    bool has_tuple() const override { return true; }

private:
    std::shared_ptr<Expression> expr_;
};