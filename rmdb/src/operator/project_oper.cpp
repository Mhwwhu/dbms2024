#include "project_oper.h"

using namespace std;

RC ProjectOper::open(Context* ctx) 
{
    if(children_.size() == 0) return RC::SUCCESS;
    if(children_.size() == 1) {
        auto child = children_.front();
        RC rc = child->open(ctx);
        if(RM_FAIL(rc)) return rc;
        return RC::SUCCESS;
    }
    return RC::INTERNAL;
}

RC ProjectOper::next() 
{
    if(children_.empty()) {
        if(!emitted_) {
            emitted_ = true;
            return RC::SUCCESS;
        }
        return RC::RECORD_EOF;
    }
    // 如果有子算子，则调用子算子的next
    return children_.front()->next();
}

RC ProjectOper::close() 
{
    if(!children_.empty()) return children_.front()->close();
    return RC::SUCCESS;
}

std::shared_ptr<ITuple> ProjectOper::current_tuple() const 
{
    if(children_.empty() && emitted_) {
        return expr_tuple_;
    }
    if(children_.empty()) {
        return nullptr;
    }
    expr_tuple_->set_child(children_.front()->current_tuple());
    return expr_tuple_;
}

std::shared_ptr<TupleSchema> ProjectOper::tuple_schema() const 
{
    auto schema = make_shared<TupleSchema>();
    for(auto expr : exprs_) {
        schema->append_cell(make_shared<ExprTupleCellSpec>(expr));
    }
    return schema;
}