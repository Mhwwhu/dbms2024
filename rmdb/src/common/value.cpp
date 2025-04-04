
#include "common/value.h"
#include <string.h>

using namespace std;

Value::Value(int val) { set_int(val); }

Value::Value(float val) { set_float(val); }

Value::Value(bool val) { set_boolean(val); }

Value::Value(const char* s, int len /*= 0*/) { set_string(s, len); }

Value::Value(const Value& other)
{
	this->attr_type_ = other.attr_type_;
	this->length_ = other.length_;
	this->own_data_ = other.own_data_;
	this->isnull_ = other.isnull_;
	switch (this->attr_type_) {
	case AttrType::CHARS: {
		if (own_data_ && other.value_.pointer_value_ != nullptr && length_ != 0) {
            this->value_.pointer_value_ = new char[this->length_ + 1];
            memcpy(this->value_.pointer_value_, other.value_.pointer_value_, this->length_);
            this->value_.pointer_value_[this->length_] = '\0';
        }
	} break;
	default: {
		this->value_ = other.value_;
	} break;
	}
}

Value::Value(Value&& other)
{
	this->attr_type_ = other.attr_type_;
	this->length_ = other.length_;
	this->own_data_ = other.own_data_;
	this->value_ = other.value_;
	this->isnull_ = other.isnull_;
	other.own_data_ = false;
	other.length_ = 0;
}

Value& Value::operator=(const Value& other)
{
	if (this == &other) {
		return *this;
	}
	reset();
	this->attr_type_ = other.attr_type_;
	this->length_ = other.length_;
	this->own_data_ = other.own_data_;
	this->isnull_ = other.isnull_;
	switch (this->attr_type_) {
	case AttrType::CHARS: {
		if (own_data_ && other.value_.pointer_value_ != nullptr && length_ != 0) {
            this->value_.pointer_value_ = new char[this->length_ + 1];
            memcpy(this->value_.pointer_value_, other.value_.pointer_value_, this->length_);
            this->value_.pointer_value_[this->length_] = '\0';
        }
	} break;
	default: {
		this->value_ = other.value_;
	} break;
	}
	return *this;
}

Value& Value::operator=(Value&& other)
{
	if (this == &other) {
		return *this;
	}
	reset();
	this->attr_type_ = other.attr_type_;
	this->length_ = other.length_;
	this->own_data_ = other.own_data_;
	this->value_ = other.value_;
	this->isnull_ = other.isnull_;
	other.own_data_ = false;
	other.length_ = 0;
	return *this;
}

void Value::reset()
{
	switch (attr_type_) {
	case AttrType::CHARS:
		if (own_data_ && value_.pointer_value_ != nullptr) {
			delete[] value_.pointer_value_;
			value_.pointer_value_ = nullptr;
		}
		break;
	default: break;
	}

	attr_type_ = AttrType::UNDEFINED;
	length_ = 0;
	own_data_ = false;
	isnull_ = 0;
}

void Value::set_data(const char* data, int length)
{
	switch (attr_type_) {
	case AttrType::CHARS: {
		set_string(data, length);
	} break;
	case AttrType::INTS: {
		value_.int_value_ = *(int*)data;
		length_ = length;
	} break;
	case AttrType::FLOATS: {
		value_.float_value_ = *(float*)data;
		length_ = length;
	} break;
	case AttrType::BOOLEANS: {
		value_.bool_value_ = *(int*)data != 0;
		length_ = length;
	} break;
	default: {
		// logger记录
	} break;
	}
}

void Value::set_null(bool null) {
	if (null) {
		auto type = attr_type_;
		reset();
		attr_type_ = AttrType::UNDEFINED;
		attr_type_ = type;
	}
	isnull_ = null;
}

void Value::set_int(int val)
{
	reset();
	attr_type_ = AttrType::INTS;
	value_.int_value_ = val;
	length_ = sizeof(val);
}

void Value::set_float(float val)
{
	reset();
	attr_type_ = AttrType::FLOATS;
	value_.float_value_ = val;
	length_ = sizeof(val);
}

void Value::set_boolean(bool val)
{
	reset();
	attr_type_ = AttrType::BOOLEANS;
	value_.bool_value_ = val;
	length_ = sizeof(val);
}

void Value::set_string(const char* s, int len /*= 0*/)
{
	reset();
	attr_type_ = AttrType::CHARS;
	if (s == nullptr) {
		value_.pointer_value_ = nullptr;
		length_ = 0;
	}
	else {
		own_data_ = true;
		if (len > 0) {
			len = strnlen(s, len);
		}
		else {
			len = strlen(s);
		}
		value_.pointer_value_ = new char[len + 1];
		length_ = len;

		memcpy(value_.pointer_value_, s, len);
		value_.pointer_value_[len] = '\0';
		//len 不包含\0
	}
}



void Value::set_value(const Value& value)
{
	switch (value.attr_type_) {
	case AttrType::INTS: {
		set_int(value.get_int());
	} break;
	case AttrType::FLOATS: {
		set_float(value.get_float());
	} break;
	case AttrType::CHARS: {
		set_string(value.get_string().c_str());
	} break;
	case AttrType::BOOLEANS: {
		set_boolean(value.get_boolean());
	} break;
	default: {
		
	} break;
	}
}

const char* Value::data() const
{
	switch (attr_type_) {
	case AttrType::CHARS: {
		return value_.pointer_value_;
	} break;
	default: {
		return (const char*)&value_;
	} break;
	}
}

string Value::to_string() const
{
	string res;
	if (this->isnull()) res = "null";
	else {
		RC     rc = DataType::type_instance(this->attr_type_)->to_string(*this, res);
		if (RM_FAIL(rc)) {
			return "";
		}
	}
	return res;
}

int Value::compare(const Value& other) const { return DataType::type_instance(this->attr_type_)->compare(*this, other); }

int Value::get_int() const
{
	switch (attr_type_) {
	case AttrType::CHARS: {
		try {
			return (int)(std::stol(value_.pointer_value_));
		}
		catch (exception const& ex) {
			return 0;
		}
	}
	case AttrType::INTS: {
		return value_.int_value_;
	}
	case AttrType::FLOATS: {
		return (int)(value_.float_value_);
	}
	case AttrType::BOOLEANS: {
		return (int)(value_.bool_value_);
	}
	default: {
		return 0;
	}
	}
	return 0;
}

float Value::get_float() const
{
	switch (attr_type_) {
	case AttrType::CHARS: {
		try {
			return std::stof(value_.pointer_value_);
		}
		catch (exception const& ex) {
			return 0.0;
		}
	} break;
	case AttrType::INTS: {
		return float(value_.int_value_);
	} break;
	case AttrType::FLOATS: {
		return value_.float_value_;
	} break;
	case AttrType::BOOLEANS: {
		return float(value_.bool_value_);
	} break;
	default: {
		return 0;
	}
	}
	return 0;
}

string Value::get_string() const { return this->to_string(); }

bool Value::get_boolean() const
{
	switch (attr_type_) {
	case AttrType::CHARS: {
		try {
			float val = std::stof(value_.pointer_value_);
			if (val >= 1E-6 || val <= -1E-6) {
				return true;
			}

			int int_val = std::stol(value_.pointer_value_);
			if (int_val != 0) {
				return true;
			}

			return value_.pointer_value_ != nullptr;
		}
		catch (exception const& ex) {
			return value_.pointer_value_ != nullptr;
		}
	} break;
	case AttrType::INTS: {
		return value_.int_value_ != 0;
	} break;
	case AttrType::FLOATS: {
		float val = value_.float_value_;
		return val >= 1E-6 || val <= -1E-6;
	} break;
	case AttrType::BOOLEANS: {
		return value_.bool_value_;
	} break;
	default: {
		return false;
	}
	}
	return false;
}