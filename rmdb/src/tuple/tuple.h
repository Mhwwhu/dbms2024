#pragma once

#include "common/rc.h"
#include "tuple_cell.h"
#include "common/value.h"

class ITuple
{
public:
	ITuple() = default;
	virtual ~ITuple() = default;

	/**
	 * @brief 获取元组中的Cell的个数
	 * @details 个数应该与tuple_schema一致
	 */
	virtual int cell_num() const = 0;

	/**
	 * @brief 获取指定位置的Cell
	 *
	 * @param index 位置
	 * @param[out] cell  返回的Cell
	 */
	virtual RC cell_at(int index, Value& cell) const = 0;

	virtual RC spec_at(int index, ITupleCellSpec& spec) const = 0;

	/**
	 * @brief 根据cell的描述，获取cell的值
	 *
	 * @param spec cell的描述
	 * @param[out] cell 返回的cell
	 */
	virtual RC find_cell(const ITupleCellSpec& spec, Value& cell) const = 0;

	virtual std::string to_string() const
	{
		std::string str;
		const int   cell_num = this->cell_num();
		for (int i = 0; i < cell_num - 1; i++) {
			Value cell;
			cell_at(i, cell);
			str += cell.to_string();
			str += ", ";
		}

		if (cell_num > 0) {
			Value cell;
			cell_at(cell_num - 1, cell);
			str += cell.to_string();
		}
		return str;
	}
};