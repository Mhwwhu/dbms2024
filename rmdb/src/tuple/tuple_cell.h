#pragma once

#include <iostream>

class ITupleCellSpec
{
public:
	ITupleCellSpec() = default;
    virtual ~ITupleCellSpec() = default;

	virtual bool equals(const ITupleCellSpec& other) const = 0;

	virtual std::string name() const = 0;
};