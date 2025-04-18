#pragma once

#include "operator.h"

/**
 * @brief 该operator是用来从chunk中获取tuple的。
 * @details 一个chunk是若干tuple的集合，目前应用于insert语句的values子句，多个values元组构成一个chunk。
 */
class ChunkGetOper : public Operator {
public:
    ChunkGetOper(const std::vector<std::shared_ptr<ITuple>>& chunk, std::shared_ptr<TupleSchema> schema)
    : chunk_(chunk), schema_(schema) {}

    OperatorType type() const override { return OperatorType::CHUNK_GET_OPER; }

    RC open(Context* ctx) override;

    RC next() override;

    RC close() override { return RC::SUCCESS; }

    std::shared_ptr<ITuple> current_tuple() const override
    { 
        if(idx_ < 0 || idx_ >= chunk_.size()) return nullptr;
        return chunk_[idx_]; 
    }

    std::shared_ptr<TupleSchema> tuple_schema() const override
    {
        return schema_;
    }

    bool has_tuple() const override { return true; }

private:
    std::vector<std::shared_ptr<ITuple>> chunk_;
    std::shared_ptr<TupleSchema> schema_;

    size_t idx_ = -1;
};