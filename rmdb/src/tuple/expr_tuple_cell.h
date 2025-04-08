#pragma once

#include "expression/expression.h"
#include "tuple_cell.h"

class ExprTupleCellSpec : public ITupleCellSpec {
public:
    ExprTupleCellSpec(std::shared_ptr<const Expression> expr) : expr_(expr) {}

    bool equals(const ITupleCellSpec& other) const override
    {
        if(auto x = dynamic_cast<const ExprTupleCellSpec*>(&other)) {
            return expr_->equal(*x->expr_);
        }
        return false;
    }

private:
    std::shared_ptr<const Expression> expr_;
};