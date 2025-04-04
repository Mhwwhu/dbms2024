/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
		 http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */


#include "common/type/char_type.h"
#include "common/value.h"
#include "common/common.h"
#include <sstream>

using namespace std;

int CharType::compare(const Value& left, const Value& right) const
{
	if (left.isnull() || right.isnull()) return INT32_MAX;
	return common::compare_string(
		(void*)left.value_.pointer_value_, left.length_, (void*)right.value_.pointer_value_, right.length_);
}

RC CharType::set_value_from_str(Value& val, const string& data) const
{
	val.set_string(data.c_str());
	return RC::SUCCESS;
}

RC CharType::cast_to(const Value& val, AttrType type, Value& result) const
{
	if (val.isnull()) {
		result = Value();
		result.set_type(type);
		result.set_null(true);
		return RC::SUCCESS;
	}
	else
	{
		Value tmp;
		switch (type) {
		case AttrType::CHARS:
			result = val;
			return RC::SUCCESS;
		case AttrType::INTS:
			result = Value(atoi(val.get_string().c_str()));
			return RC::SUCCESS;
		case AttrType::FLOATS:
			result = Value((float)atof(val.get_string().c_str()));
			return RC::SUCCESS;
		default: return RC::UNSUPPORTED;
		}
	}
}

int CharType::cast_cost(AttrType type)
{
	if (type == AttrType::CHARS) {
		return 0;
	}
	if (type == AttrType::INTS) {
		return 1;
	}
	if (type == AttrType::FLOATS) {
		return 1;
	}
	return INT32_MAX;
}

RC CharType::to_string(const Value& val, string& result) const
{
	stringstream ss;
	if (val.isnull()) ss << "null";
	else ss << string(val.value_.pointer_value_);
	result = ss.str();
	return RC::SUCCESS;
}