#pragma once

#include "tuple_cell.h"

class PlainTupleCellSpec : public ITupleCellSpec {
public:
    PlainTupleCellSpec(const std::string& name) : name_(name) {}

    bool equals(const ITupleCellSpec& other) const override
    {
        if( auto x = dynamic_cast<const PlainTupleCellSpec*>(&other) ) {
            x->name_ == name_;
        }
        return false;
    }

    std::string name() const override
    {
        return name_;
    }
private:
    std::string name_;
};