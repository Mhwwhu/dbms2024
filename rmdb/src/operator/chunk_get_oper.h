#pragma once

#include "operator.h"

/**
 * @brief 该operator是用来从chunk中获取tuple的。
 * @details 一个chunk是若干tuple的集合，目前应用于insert语句的values子句，多个values元组构成一个chunk。
 */
class ChunkGetOper : public Operator {
public:
    ChunkGetOper(const std::vector<std::shared_ptr<ITuple>>& chunk, std::vector<TupleSchema>& tuple_schema)
    : chunk_(chunk), tuple_schema_(tuple_schema) {}

    OperatorType type() const override { return OperatorType::CHUNK_GET_OPER; }

    RC open(Context* ctx) override;

    RC next() override;

    RC close() override { return RC::SUCCESS; }

    std::shared_ptr<ITuple> current_tuple() const override { return chunk_[idx_]; }

    RC tuple_schema(TupleSchema& schema) const override 
    {
         schema = tuple_schema_[idx_];
         return RC::SUCCESS;
    }

private:
    std::vector<std::shared_ptr<ITuple>> chunk_;
    std::vector<TupleSchema> tuple_schema_;

    size_t idx_ = -1;
};