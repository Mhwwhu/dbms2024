/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
		 http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */


#include "common/type/float_type.h"
#include "common/value.h"
#include "common/value.h"
#include "common/common.h"

#include <sstream>

using namespace std;

int FloatType::compare(const Value& left, const Value& right) const
{
	if (left.isnull() || right.isnull()) return INT32_MAX;
	float left_val = left.get_float();
	float right_val = right.get_float();
	return common::compare_float((void*)&left_val, (void*)&right_val);
}

RC FloatType::add(const Value& left, const Value& right, Value& result) const
{
	result.set_float(left.get_float() + right.get_float());
	return RC::SUCCESS;
}
RC FloatType::subtract(const Value& left, const Value& right, Value& result) const
{
	result.set_float(left.get_float() - right.get_float());
	return RC::SUCCESS;
}
RC FloatType::multiply(const Value& left, const Value& right, Value& result) const
{
	result.set_float(left.get_float() * right.get_float());
	return RC::SUCCESS;
}

RC FloatType::divide(const Value& left, const Value& right, Value& result) const
{
	if (right.get_float() > -1E-6 && right.get_float() < 1E-6) {
		result.set_type(AttrType::FLOATS);
		result.set_null(true);
		return RC::SUCCESS;
	}
	else {
		result.set_float(left.get_float() / right.get_float());
	}
	return RC::SUCCESS;
}

RC FloatType::negative(const Value& val, Value& result) const
{
	result.set_float(-val.get_float());
	return RC::SUCCESS;
}

RC FloatType::set_value_from_str(Value& val, const string& data) const
{
	RC                rc = RC::SUCCESS;
	stringstream deserialize_stream;
	deserialize_stream.clear();
	deserialize_stream.str(data);

	float float_value;
	deserialize_stream >> float_value;
	if (!deserialize_stream || !deserialize_stream.eof()) {
		rc = RC::SCHEMA_FIELD_TYPE_MISMATCH;
	}
	else {
		val.set_float(float_value);
	}
	return rc;
}

RC FloatType::cast_to(const Value& val, AttrType type, Value& result) const
{
	if (val.isnull()) {
		result = Value();
		result.set_type(type);
		result.set_null(true);
		return RC::SUCCESS;
	}
	else {
		switch (type) {
		case AttrType::FLOATS:
			result = val;
			return RC::SUCCESS;
		case AttrType::INTS:
			result = Value((int)val.get_float());
			return RC::SUCCESS;
		case AttrType::CHARS:
			result = Value(val.to_string().c_str());
			return RC::SUCCESS;
		default:
			return RC::UNSUPPORTED;
		}
	}
}
int FloatType::cast_cost(AttrType type)
{
	switch (type) {
	case AttrType::FLOATS:
		return 0;
	case AttrType::INTS:
		return 2;
	case AttrType::CHARS:
		return 3;
	default:
		return INT32_MAX;
	}
}

RC FloatType::to_string(const Value& val, string& result) const

{
	stringstream ss;
	if (val.isnull()) ss << "null";
	else ss << common::double_to_str(val.value_.float_value_);
	result = ss.str();
	return RC::SUCCESS;
}
