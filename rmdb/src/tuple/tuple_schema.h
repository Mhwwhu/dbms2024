#pragma once

#include <vector>
#include <memory>

#include "tuple_cell.h"

class TupleSchema
{
public:
	void append_cell(std::shared_ptr<ITupleCellSpec> cell) { cells_.push_back(cell); }
	int  cell_num() const { return static_cast<int>(cells_.size()); }

	const std::shared_ptr<ITupleCellSpec> cell_at(int i) const { return cells_[i]; }

private:
	std::vector<std::shared_ptr<ITupleCellSpec>> cells_;
};