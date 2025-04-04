/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
				 http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */


#include "common/type/integer_type.h"
#include "common/value.h"
#include "common/common.h"

#include <sstream>

using namespace std;

int IntegerType::compare(const Value& left, const Value& right) const
{
	if (left.isnull() || right.isnull()) return INT32_MAX;
	if (right.attr_type() == AttrType::INTS) {
		return common::compare_int((void*)&left.value_.int_value_, (void*)&right.value_.int_value_);
	}
	else if (right.attr_type() == AttrType::FLOATS) {
		return common::compare_float((void*)&left.value_.int_value_, (void*)&right.value_.int_value_);
	}
	return INT32_MAX;
}

RC IntegerType::add(const Value& left, const Value& right, Value& result) const
{
	result.set_int(left.get_int() + right.get_int());
	return RC::SUCCESS;
}

RC IntegerType::subtract(const Value& left, const Value& right, Value& result) const
{
	result.set_int(left.get_int() - right.get_int());
	return RC::SUCCESS;
}

RC IntegerType::multiply(const Value& left, const Value& right, Value& result) const
{
	result.set_int(left.get_int() * right.get_int());
	return RC::SUCCESS;
}

RC IntegerType::negative(const Value& val, Value& result) const
{
	result.set_int(-val.get_int());
	return RC::SUCCESS;
}

RC IntegerType::set_value_from_str(Value& val, const string& data) const
{

	RC                rc = RC::SUCCESS;
	stringstream deserialize_stream;
	deserialize_stream.clear();  // 清理stream的状态，防止多次解析出现异常
	deserialize_stream.str(data);
	int int_value;
	deserialize_stream >> int_value;
	if (!deserialize_stream || !deserialize_stream.eof()) {
		rc = RC::SCHEMA_FIELD_TYPE_MISMATCH;
	}
	else {
		val.set_int(int_value);
	}
	return rc;
}
RC IntegerType::cast_to(const Value& val, AttrType type, Value& result) const
{

	if (val.isnull()) {
		result = Value();
		result.set_type(type);
		result.set_null(true);
		return RC::SUCCESS;
	}
	else {
		switch (type) {
		case AttrType::CHARS:
			result = Value(val.to_string().c_str());
			return RC::SUCCESS;
		case AttrType::FLOATS:
			result = Value((float)val.get_int());
			return RC::SUCCESS;
		case AttrType::INTS:
			result = val;
			return RC::SUCCESS;
		default:
			return RC::UNSUPPORTED;
		}
	}
}
int IntegerType::cast_cost(AttrType type)
{
	switch (type) {
	case AttrType::INTS:
		return 0;
	case AttrType::FLOATS:
		return 1;
	case AttrType::CHARS:
		return 3;
	default:
		return INT32_MAX;
	}
}

RC IntegerType::to_string(const Value& val, string& result) const
{
	stringstream ss;
	if (val.isnull()) ss << "null";
	else ss << val.value_.int_value_;
	result = ss.str();
	return RC::SUCCESS;
}