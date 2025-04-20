#pragma once

#include "tuple.h"
#include "tuple_cell.h"
#include <memory>
#include "expression/expression.h"
#include "expr_tuple_cell.h"
#include <vector>

class ExprTuple : public ITuple {
public:
    ExprTuple(const std::vector<std::shared_ptr<Expression>>& exprs)
    : exprs_(exprs) {}
    ~ExprTuple() override = default;

    void set_child(std::shared_ptr<const ITuple> child) { child_tuple_ = child; }

    std::shared_ptr<const ITuple> get_child() const { return child_tuple_; }

    int cell_num() const override { return static_cast<int>(exprs_.size()); }

    RC cell_at(int index, Value& cell) const 
    {
        if(index < 0 || index >= cell_num()) return RC::INVALID_ARGUMENT;
        return get_value(exprs_[index], cell);
    }

    RC spec_at(int index, std::shared_ptr<ITupleCellSpec>& spec) const override
    {
        if(index < 0 || index >= cell_num()) return RC::INVALID_ARGUMENT;
        spec = std::make_shared<ExprTupleCellSpec>(exprs_[index]);
        return RC::SUCCESS;
    }

    RC find_cell(const ITupleCellSpec& spec, Value& cell) const override;
    
private:
    RC get_value(std::shared_ptr<const Expression> expression, Value& value) const;

private:
    std::vector<std::shared_ptr<Expression>> exprs_;
    std::shared_ptr<const ITuple> child_tuple_;
};