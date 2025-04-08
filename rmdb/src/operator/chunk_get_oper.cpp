#include "chunk_get_oper.h"

RC ChunkGetOper::open(Context* ctx)
{
    if(children_.size() != 0) return RC::INTERNAL;
    if(tuple_schema_.size() != chunk_.size()) return RC::INTERNAL;
    return RC::SUCCESS;
}

RC ChunkGetOper::next()
{
    if(idx_ == chunk_.size() - 1) return RC::RECORD_EOF;
    idx_++;
    return RC::SUCCESS;
}