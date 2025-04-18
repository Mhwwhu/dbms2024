#include "show_tables_executor.h"
#include "common/context.h"
#include "analyze/stmt/show_tables_stmt.h"
#include "system/sm_manager.h"
#include "parser/ast.h"
#include "tuple/plain_tuple_cell.h"
#include "tuple/value_list_tuple.h"
#include "operator/chunk_get_oper.h"

using namespace std;

RC ShowTablesExecutor::execute(Context* context){

    auto stmt = std::dynamic_pointer_cast<ShowTablesStmt>(context->stmt);
    auto sm_manager = context->sm_manager_;
    auto tables = sm_manager->tables();

    auto tuples = vector<shared_ptr<ITuple>>();
    auto schema = make_shared<TupleSchema>();
    schema->append_cell(make_shared<PlainTupleCellSpec>("Tables"));
    for(auto& table : tables) {
        auto cells = vector<Value>();
        auto specs = vector<shared_ptr<ITupleCellSpec>>();
        cells.push_back(Value(table.name.c_str()));
        specs.push_back(make_shared<PlainTupleCellSpec>(table.name));
        auto tuple = make_shared<ValueListTuple>(cells, specs);
        tuples.push_back(std::move(tuple));
    }

    auto chunk_get_oper = make_shared<ChunkGetOper>(tuples, schema);
    context->sql_result.set_oper(chunk_get_oper);

    return RC::SUCCESS;
};