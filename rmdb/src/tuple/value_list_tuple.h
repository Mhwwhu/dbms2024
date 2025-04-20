#pragma once

#include "tuple.h"

#include <vector>

class ValueListTuple : public ITuple {
public:
    ValueListTuple(const std::vector<Value>& cells, 
                   const std::vector<std::shared_ptr<ITupleCellSpec>>& specs)
        : cells_(cells), specs_(specs) {}
    ~ValueListTuple() override = default;

    int cell_num() const override { return static_cast<int>(cells_.size()); }

    RC cell_at(int index, Value& cell) const override {
        if (index < 0 || index >= cell_num()) return RC::INVALID_ARGUMENT;
        cell = cells_[index];
        return RC::SUCCESS;
    }

    RC spec_at(int index, std::shared_ptr<ITupleCellSpec>& spec) const override {
        if (index < 0 || index >= cell_num()) return RC::INVALID_ARGUMENT;
        spec = specs_[index];
        return RC::SUCCESS;
    }

    RC find_cell(const ITupleCellSpec& spec, Value& cell) const override {
        for (size_t i = 0; i < specs_.size(); ++i) {
            if (specs_[i]->equals(spec)) {
                cell = cells_[i];
                return RC::SUCCESS;
            }
        }
        return RC::NOTFOUND;
    }

private:
    std::vector<Value> cells_;
    std::vector<std::shared_ptr<ITupleCellSpec>> specs_;
};