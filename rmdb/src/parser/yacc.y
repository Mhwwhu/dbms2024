%{
#include "ast.h"
#include "yacc.tab.h"
#include "lex.h"
#include "expression/expression.h"
#include "expression/value_expr.h"
#include "expression/unbound_field_expr.h"
#include "expression/comparison_expr.h"
#include "expression/conjunction_expr.h"
#include <iostream>
#include <memory>


std::string token_name(const char *sql_string, YYLTYPE *llocp)
{
    return std::string(sql_string + llocp->first_column, llocp->last_column - llocp->first_column + 1);
}

int yyerror(YYLTYPE *locp, const char* s, std::shared_ptr<ast::TreeNode>& sql_result, yyscan_t scanner, const char* msg) {
    std::cerr << "Parser Error at line " << locp->first_line << " column " << locp->first_column << ": " << s << std::endl;
    auto error_node = std::make_shared<ast::ErrorNode>();
    error_node->error_msg = msg;
    error_node->line = locp->first_line;
    error_node->col = locp->first_column;
    sql_result = std::move(error_node);
    return 0;
}

using namespace ast;
%}

// request a pure (reentrant) parser
%define api.pure full
// enable location in error handler
%locations
// enable verbose syntax error message
%define parse.error verbose

/** 启用位置标识 **/
%locations
%lex-param { yyscan_t scanner }
/** 这些定义了在yyparse函数中的参数 **/
%parse-param { const char * sql_string }
%parse-param { std::shared_ptr<ast::TreeNode>& sql_result }
%parse-param { void * scanner }

// keywords
%token SHOW TABLES CREATE TABLE DROP DESC INSERT INTO VALUES DELETE FROM ASC ORDER BY ON
WHERE UPDATE SET SELECT INT CHAR FLOAT INDEX AND OR JOIN EXIT HELP TXN_BEGIN TXN_COMMIT TXN_ABORT TXN_ROLLBACK ORDER_BY ENABLE_NESTLOOP ENABLE_SORTMERGE
// non-keywords
%token LEQ NEQ GEQ T_EOF

// type-specific tokens
%token <sv_str> IDENTIFIER VALUE_STRING
%token <sv_int> VALUE_INT
%token <sv_float> VALUE_FLOAT
%token <sv_bool> VALUE_BOOL

// specify types for non-terminal symbol
%type <sv_node> start stmt dbStmt ddl dml txnStmt setStmt insert select delete update
%type <sv_field> field
%type <sv_fields> fieldList
%type <sv_type_len> type
%type <sv_comp_op> compOp
%type <sv_expr> expr valueExpr unboundFieldExpr compExpr conjunctionExpr optWhereClause optHavingClause onClause 
%type <sv_exprs> exprList optGroupbyClause
%type <sv_expr_chunk> insertList
%type <sv_val> value
%type <sv_vals> valueList
%type <sv_str> tbName colName
%type <sv_strs> tableList colNameList optColumnClause
%type <sv_col> col
%type <sv_cols> colList selector
%type <sv_set_clause> setClause
%type <sv_set_clauses> setClauses
%type <sv_cond> condition
/* %type <sv_conds>  */
%type <sv_orderby>  optOrderbyClause
%type <sv_setKnobType> set_knob_type
%type <sv_int> optLimitClause
%type <sv_join> optFromClause joinTree
%type <sv_vtable> virtualTable
%type <sv_join_type> join_type

%%
start:
        stmt ';'
    {
        sql_result = std::move($1);
        YYACCEPT;
    }
    ;

stmt:
        dbStmt
    |   ddl
    |   dml
    |   txnStmt
    /* |   setStmt */
    ;

txnStmt:
        TXN_BEGIN
    {
        $$ = std::make_shared<TxnBegin>();
    }
    |   TXN_COMMIT
    {
        $$ = std::make_shared<TxnCommit>();
    }
    |   TXN_ABORT
    {
        $$ = std::make_shared<TxnAbort>();
    }
    | TXN_ROLLBACK
    {
        $$ = std::make_shared<TxnRollback>();
    }
    ;

dbStmt:
        SHOW TABLES
    {
        $$ = std::make_shared<ShowTables>();
    }
    ;

/* setStmt:
        SET set_knob_type '=' VALUE_BOOL
    {
        $$ = std::make_shared<SetNode>($2, $4);
    }
    ; */

ddl:
        CREATE TABLE tbName '(' fieldList ')'
    {
        $$ = std::make_shared<CreateTable>($3, $5);
    }
    |   DROP TABLE tbName
    {
        $$ = std::make_shared<DropTable>($3);
    }
    |   DESC tbName
    {
        $$ = std::make_shared<DescTable>($2);
    }
    /* |   CREATE INDEX tbName '(' colNameList ')'
    {
        $$ = std::make_shared<CreateIndex>($3, $5);
    }
    |   DROP INDEX tbName '(' colNameList ')'
    {
        $$ = std::make_shared<DropIndex>($3, $5);
    } */
    ;

dml:
    update {
        $$ = std::move($1);
    }
    | delete {
        $$ = std::move($1);
    }
    | select {
        $$ = std::move($1);
    }
    | insert {
        $$ = std::move($1);
    }
    ;

insert:
    INSERT INTO tbName optColumnClause insertList {
        $$ = std::make_shared<InsertNode>($3, $4, $5);
    }
    ;

select:
    SELECT exprList optFromClause optGroupbyClause optHavingClause optWhereClause optOrderbyClause optLimitClause {
        $$ = std::make_shared<SelectNode>($2, $3, $4, $5, $6, $7, $8);
    }
    ;

delete:
    DELETE FROM tbName optWhereClause {
        $$ = std::make_shared<DeleteNode>($3, $4);
    }
    ;

update:
    UPDATE tbName SET setClauses optWhereClause {
        $$ = std::make_shared<UpdateNode>($2, $4, $5);
    }
    ;
    
optFromClause:
    { $$ = nullptr; }
    | FROM joinTree {
        $$ = std::move($2);
    }
    ;

virtualTable:
    tbName {
        $$ = std::make_shared<VirtualTableNode>($1, $1);
    }
    ;

joinTree:
    virtualTable {
        $$ = std::make_shared<JoinNode>(std::move($1));
    }
    | joinTree join_type joinTree onClause {
        $$ = std::make_shared<JoinNode>(std::move($1), std::move($3), std::move($4), $2);
    }
    | joinTree ',' joinTree {
        $$ = std::make_shared<JoinNode>(std::move($1), std::move($3), nullptr, common::JoinType::CARTESIAN_PRODUCT);
    }
    | '(' joinTree ')' {
        $$ = std::move($2);
    }
    ;

join_type:
    JOIN {
        $$ = common::JoinType::INNER_JOIN;
    }
    ;

onClause:
    ON  {
        $$ = nullptr;
    }
    ;


optGroupbyClause:
    { $$ = std::vector<std::shared_ptr<Expression>>(); };

optHavingClause:
    { $$ = nullptr; };

optWhereClause:
    { $$ = nullptr; }
    | WHERE conjunctionExpr {
        $$ = std::move($2);
    }
    ;

optOrderbyClause:
    { $$ = nullptr; };

optLimitClause:
    { $$ = -1; };

optColumnClause:
    { $$ = std::vector<std::string>(); }
    |'(' colNameList ')' {
        $$ = std::vector<std::string>();
        std::move($2.begin(), $2.end(), std::back_inserter($$));
    }
    ;

insertList: 
    VALUES '(' exprList ')'  {
        $$ = std::vector<std::vector<std::shared_ptr<Expression>>>();
        $$.push_back(std::move($3));
    } | insertList ',' '(' exprList ')' {
        $$ = std::vector<std::vector<std::shared_ptr<Expression>>>();
        std::move($1.begin(), $1.end(), std::back_inserter($$));
        $$.push_back(std::move($4));
    }
    ;

fieldList:
        field
    {
        $$ = std::vector<std::shared_ptr<Field>>{$1};
    }
    |   fieldList ',' field
    {
        $$.push_back($3);
    }
    ;

colNameList:
        colName
    {
        $$ = std::vector<std::string>{$1};
    }
    | colNameList ',' colName
    {
        $$.push_back($3);
    }
    ;

field:
        colName type
    {
        $$ = std::make_shared<Field>($1, $2);
    }
    ;

type:
        INT
    {
        $$ = std::make_shared<TypeLen>(AttrType::INTS, sizeof(int));
    }
    |   CHAR '(' VALUE_INT ')'
    {
        $$ = std::make_shared<TypeLen>(AttrType::CHARS, $3);
    }
    |   FLOAT
    {
        $$ = std::make_shared<TypeLen>(AttrType::FLOATS, sizeof(float));
    }
    ;

valueList:
        value
    {
        $$ = std::vector<std::shared_ptr<Value>>{$1};
    }
    |   valueList ',' value
    {
        $$.push_back($3);
    }
    ;

value:
        VALUE_INT
    {
        $$ = std::make_shared<Value>($1);
    }
    |   VALUE_FLOAT
    {
        $$ = std::make_shared<Value>($1);
    }
    |   VALUE_STRING
    {
        $$ = std::make_shared<Value>($1.c_str());
    }
    |   VALUE_BOOL
    {
        $$ = std::make_shared<Value>($1);
    }
    ;

/* condition:
        col op expr
    {
        $$ = std::make_shared<BinaryExpr>($1, $2, $3);
    }
    ; */

/* optWhereClause:
         {  }
    |   WHERE whereClause
    {
        $$ = $2;
    }
    ; */

/* whereClause:
        condition 
    {
        $$ = std::vector<std::shared_ptr<BinaryExpr>>{$1};
    }
    |   whereClause AND condition
    {
        $$.push_back($3);
    }
    ; */

col:
        tbName '.' colName
    {
        $$ = std::make_shared<Col>($1, $3);
    }
    |   colName
    {
        $$ = std::make_shared<Col>("", $1);
    }
    ;

colList:
        col
    {
        $$ = std::vector<std::shared_ptr<Col>>{$1};
    }
    |   colList ',' col
    {
        $$.push_back($3);
    }
    ;

compOp:
    '=' { $$ = common::CompOp::EQ; }
    | '<' { $$ = common::CompOp::LT; }
    | '>' { $$ = common::CompOp::GT; }
    | NEQ { $$ = common::CompOp::NE; }
    | LEQ { $$ = common::CompOp::LE; }
    | GEQ { $$ = common::CompOp::GE; }
    ;

exprList:
    expr {
        $$ = std::vector<std::shared_ptr<Expression>>();
        $$.push_back(std::move($1));
    } | exprList ',' expr {
        $$ = std::vector<std::shared_ptr<Expression>>();
        std::move($1.begin(), $1.end(), std::back_inserter($$));
        $$.push_back(std::move($3));
    }

expr:
    '(' expr ')' {
        $$ = std::move($2);
    } 
    | valueExpr {
        $$ = std::move($1);
    }
    | unboundFieldExpr {
        $$ = std::move($1);
    }
    | compExpr {
        $$ = std::move($1);
    }

valueExpr:
    value {
        $$ = std::make_shared<ValueExpr>(*$1);
    }

unboundFieldExpr:
    tbName '.' colName {
        $$ = std::make_shared<UnboundFieldExpr>($1, $3);
    }
    | colName {
        $$ = std::make_shared<UnboundFieldExpr>("", $1);
    }

compExpr:
    expr compOp expr {
        $$ = std::make_shared<ComparisonExpr>(std::move($1), std::move($3), $2);
    }

conjunctionExpr:
    expr {
        $$ = std::move($1);
    }
    | expr AND expr {
        $$ = std::make_shared<ConjunctionExpr>(std::move($1), std::move($3), common::ConjunctionType::AND);
    }
    | expr OR expr {
        $$ = std::make_shared<ConjunctionExpr>(std::move($1), std::move($3), common::ConjunctionType::OR);
    }

setClauses:
        setClause
    {
        $$ = std::vector<std::shared_ptr<SetClause>>{$1};
    }
    |   setClauses ',' setClause
    {
        $$.push_back($3);
    }
    ;

setClause:
        colName '=' expr
    {
        $$ = std::make_shared<SetClause>($1, $3);
    }
    ;

/* selector:
        '*'
    {
        $$ = {};
    }
    |   colList
    ; */

/* tableList:
        tbName
    {
        $$ = std::vector<std::string>{$1};
    }
    |   tableList ',' tbName
    {
        $$.push_back($3);
    }
    |   tableList JOIN tbName
    {
        $$.push_back($3);
    }
    ; */

/* opt_order_clause:
    ORDER BY order_clause      
    { 
        $$ = $3; 
    }
    |   { }
    ;

order_clause:
      col  opt_asc_desc 
    { 
        $$ = std::make_shared<OrderBy>($1, $2);
    }
    ;   

opt_asc_desc:
    ASC          { $$ = OrderBy_ASC;     }
    |  DESC      { $$ = OrderBy_DESC;    }
    |       { $$ = OrderBy_DEFAULT; }
    ;     */

set_knob_type:
    ENABLE_NESTLOOP { $$ = EnableNestLoop; }
    |   ENABLE_SORTMERGE { $$ = EnableSortMerge; }
    ;

tbName: IDENTIFIER;

colName: IDENTIFIER;
%%

extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, std::shared_ptr<ast::TreeNode>& sql_result) {
  yyscan_t scanner;
  yylex_init(&scanner);
  scan_string(s, scanner);
  int result = yyparse(s, sql_result, scanner);
  yylex_destroy(scanner);
  return result;
}