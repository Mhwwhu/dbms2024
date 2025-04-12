#pragma once

#include <string>

#include "common/rc.h"
#include "tuple/tuple.h"
#include "common/value.h"
#include "common/common.h"

enum class ExprType
{
	NONE,
	UNBOUND_STAR,         ///< 星号，表示所有字段
	UNBOUND_FIELD,        ///< 未绑定的字段，需要在analyze阶段解析为FieldExpr

	FIELD,        ///< 字段。在实际执行时，根据行数据内容提取对应字段的值
	VALUE,        ///< 常量值
	COMPARISON,   ///< 需要做比较的表达式
	CONJUNCTION,  ///< 由若干ConjunctionExpr和其他expr组成的条件树
};

class Expression
{
public:
	Expression() = default;
	virtual ~Expression() = default;

	/**
	 * @brief 判断两个表达式是否相等
	 */
	virtual bool equal(const Expression& other) const = 0;
	/**
	 * @brief 根据具体的tuple，来计算当前表达式的值。tuple有可能是一个具体某个表的行数据
	 */
	virtual RC get_value(const ITuple& tuple, Value& value) const = 0;

	/**
	 * @brief 在没有实际运行的情况下，也就是无法获取tuple的情况下，尝试获取表达式的值
	 * @details 有些表达式的值是固定的，比如ValueExpr，这种情况下可以直接获取值
	 */
	virtual RC try_get_value(Value& value) const = 0;

	/**
	 * @brief 表达式的类型
	 * 可以根据表达式类型来转换为具体的子类
	 */
	virtual ExprType type() const = 0;

	/**
	 * @brief 表达式值的类型
	 * @details 一个表达式运算出结果后，只有一个值
	 */
	virtual AttrType value_type() const = 0;

	/**
	 * @brief 表达式值的长度
	 */
	virtual int value_length() const = 0;

	/**
	 * @brief 表达式的名字，比如是字段名称，或者用户在执行SQL语句时输入的内容
	 */
	virtual const char* name() const { return name_.c_str(); }
	virtual void        set_name(std::string name) { name_ = name; }

private:
	std::string name_;
};