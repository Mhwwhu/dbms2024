#pragma once

#include <iostream>

class ITupleCellSpec
{
public:
	ITupleCellSpec() = default;
    virtual ~ITupleCellSpec() = default;

	virtual bool equals(const ITupleCellSpec& other) const = 0;
};

class RowTupleCellSpec : public ITupleCellSpec {
public:
    RowTupleCellSpec() = default;
    RowTupleCellSpec(const std::string& table_name, const std::string& field_name)
    : table_name_(table_name), field_name_(field_name) {}

    bool equals(const ITupleCellSpec& other) const 
    {
        if( auto x = dynamic_cast<const RowTupleCellSpec*>(&other) ) {
            return x->field_name_ == field_name_ && x->table_name_ == table_name_;
        }
        return false;
    }

private:
    std::string table_name_;
    std::string field_name_;
};