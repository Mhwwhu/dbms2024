#pragma once

#include <memory>
#include <vector>

#include "common/rc.h"
#include "tuple/tuple.h"
#include "tuple/tuple_schema.h"

class Context;

enum OperatorType {
    PROJECT_OPER,
    INSERT_OPER,
    CHUNK_GET_OPER,
    TABLE_SCAN_OPER,
};

class Operator {
public:
    Operator() = default;
    virtual ~Operator() = default;

    virtual OperatorType type() const = 0;

    virtual RC open(Context*) = 0;

    virtual RC next() = 0;

    virtual RC close() = 0;

    void add_child(std::shared_ptr<Operator> child) { children_.push_back(child); }

    const std::vector<std::shared_ptr<Operator>>& children() const { return children_; }

    virtual std::shared_ptr<ITuple> current_tuple() const = 0;

    virtual std::shared_ptr<TupleSchema> tuple_schema() const = 0;

    virtual bool has_tuple() const = 0;
protected:
    std::vector<std::shared_ptr<Operator>> children_;
};