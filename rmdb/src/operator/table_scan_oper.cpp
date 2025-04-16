#include "table_scan_oper.h"
#include "common/context.h"
#include "system/sm_manager.h"
#include "tuple/row_tuple.h"
#include "expression/conjunction_expr.h"

using namespace std;

TableScanOper::TableScanOper(const TabMeta& table, std::shared_ptr<ConjunctionExpr> filter): table_(table), filter_(filter)
{
    tuple_schema_ = make_shared<TupleSchema>();
    for(auto col : table.cols) {
        tuple_schema_->append_cell(make_shared<RowTupleCellSpec>(table.name, col.name));
    }
}

RC TableScanOper::open(Context* ctx)
{
    auto file_handler = ctx->sm_manager_->fhs_[table_.name].get();
    scanner_ = make_unique<RecScan>(file_handler, filter_);

    RC rc = scanner_->open(ctx);
    if(RM_FAIL(rc)) return rc;
}

RC TableScanOper::next() 
{
    RC rc = RC::SUCCESS;
    bool filter_result;
    while(RM_SUCC(rc = scanner_->next())) {
        auto record = scanner_->record();
        tuple_->set_record(record);
        rc = filter(tuple_, filter_result);
        if(RM_FAIL(rc)) return rc;

        if(filter_result) {
            break;
        }
    }

    return rc;
}

RC TableScanOper::close() 
{
    return scanner_->close();
}

std::shared_ptr<ITuple> TableScanOper::current_tuple() const 
{
    return tuple_;
}

std::shared_ptr<TupleSchema> TableScanOper::tuple_schema() const 
{
    return tuple_schema_;
}

RC TableScanOper::filter(std::shared_ptr<RowTuple> tuple, bool& result)
{
    RC rc = RC::SUCCESS;
    Value val;
    rc = filter_->get_value(*tuple, val);
    if(RM_FAIL(rc)) return rc;
    result = val.get_boolean();
    return RC::SUCCESS;
}