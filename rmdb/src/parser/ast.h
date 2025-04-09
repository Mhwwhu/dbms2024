/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */
#pragma once

#include <vector>
#include <string>
#include <memory>

#include "common/type/attr_type.h"
#include "expression/expression.h"

namespace ast {

enum SetKnobType {
    EnableNestLoop, EnableSortMerge
};

// Base class for tree nodes
struct TreeNode {
    virtual ~TreeNode() = default;  // enable polymorphism
};

struct Help : public TreeNode {
};

struct ShowTables : public TreeNode {
};

struct TxnBegin : public TreeNode {
};

struct TxnCommit : public TreeNode {
};

struct TxnAbort : public TreeNode {
};

struct TxnRollback : public TreeNode {
};

struct TypeLen : public TreeNode {
    AttrType type;
    int len;

    TypeLen(AttrType type_, int len_) : type(type_), len(len_) {}
};

struct Field : public TreeNode {
    std::string col_name;
    std::shared_ptr<TypeLen> type_len;

    Field(std::string col_name_, std::shared_ptr<TypeLen> type_len_) :
            col_name(std::move(col_name_)), type_len(std::move(type_len_)) {}
};

struct CreateTable : public TreeNode {
    std::string tab_name;
    std::vector<std::shared_ptr<Field>> fields;

    CreateTable(std::string tab_name_, std::vector<std::shared_ptr<Field>> fields_) :
            tab_name(std::move(tab_name_)), fields(std::move(fields_)) {}
};

struct DropTable : public TreeNode {
    std::string tab_name;

    DropTable(std::string tab_name_) : tab_name(std::move(tab_name_)) {}
};

struct DescTable : public TreeNode {
    std::string tab_name;

    DescTable(std::string tab_name_) : tab_name(std::move(tab_name_)) {}
};

struct CreateIndex : public TreeNode {
    std::string tab_name;
    std::vector<std::string> col_names;

    CreateIndex(std::string tab_name_, std::vector<std::string> col_names_) :
            tab_name(std::move(tab_name_)), col_names(std::move(col_names_)) {}
};

struct DropIndex : public TreeNode {
    std::string tab_name;
    std::vector<std::string> col_names;

    DropIndex(std::string tab_name_, std::vector<std::string> col_names_) :
            tab_name(std::move(tab_name_)), col_names(std::move(col_names_)) {}
};

struct Col : public TreeNode {
    std::string tab_name;
    std::string col_name;

    Col(std::string tab_name_, std::string col_name_) :
            tab_name(std::move(tab_name_)), col_name(std::move(col_name_)) {}
};

struct SetClause : public TreeNode {
    std::string col_name;
    std::shared_ptr<Value> val;

    SetClause(std::string col_name_, std::shared_ptr<Value> val_) :
            col_name(std::move(col_name_)), val(std::move(val_)) {}
};

struct ConditionNode : public TreeNode {
    virtual ~ConditionNode() = default;
};

struct CompareNode : public ConditionNode {
    enum CompOp {
        EQ, NE, LT, GT, LE, GE
    };

    std::shared_ptr<Expression> left;
    std::shared_ptr<Expression> right;
    CompOp comp;

    CompareNode(std::shared_ptr<Expression> left_, std::shared_ptr<Expression> right_, CompOp comp_)
    : left(left_), right(right_), comp(comp_) {}
};

struct ConjunctionNode : public TreeNode {
    enum ConjunctionType {
        AND, OR, NONE
    };

    std::shared_ptr<ConjunctionNode> left;
    std::shared_ptr<ConjunctionNode> right;
    std::shared_ptr<ConditionNode> condition;
    ConjunctionType type;

    ConjunctionNode(std::shared_ptr<ConditionNode> condition_)
    : condition(condition), type(ConjunctionType::NONE) {}

    ConjunctionNode(std::shared_ptr<ConjunctionNode> left_, std::shared_ptr<ConjunctionNode> right_, ConjunctionType type_)
    : left(left_), right(right_), type(type_) {}
};

struct OrderByNode : public TreeNode
{
    enum OrderByDir {
        OrderBy_DEFAULT,
        OrderBy_ASC,
        OrderBy_DESC
    };

    std::vector<std::pair<std::shared_ptr<Expression>, OrderByDir>> units;
    OrderByNode(std::vector<std::pair<std::shared_ptr<Expression>, OrderByDir>> units_) :
       units(std::move(units_)) {}
};

struct InsertNode : public TreeNode {
    std::string tab_name;
    std::vector<std::string> decl_cols;
    std::vector<std::vector<std::shared_ptr<Expression>>> exprs;

    InsertNode(const std::string& tab_name_, const std::vector<std::string>& decl_cols_,
        const std::vector<std::vector<std::shared_ptr<Expression>>>& exprs_) :
            tab_name(std::move(tab_name_)), decl_cols(decl_cols_), exprs(std::move(exprs_)) {}
};

struct JoinNode : public TreeNode {
    enum JoinType {
        INNER_JOIN, LEFT_JOIN, RIGHT_JOIN, FULL_JOIN, NONE
    };

    std::shared_ptr<JoinNode> left;
    std::shared_ptr<JoinNode> right;
    std::shared_ptr<ConjunctionNode> conjunction;
    std::string table_name;
    JoinType type;

    JoinNode(std::shared_ptr<JoinNode> left_, std::shared_ptr<JoinNode> right_,
            std::shared_ptr<ConjunctionNode> conjunction_, JoinType type_) :
            left(left_), right(right_), conjunction(conjunction_), type(type_) {}

    JoinNode(std::string table_name_) : table_name(table_name_), type(JoinType::NONE) {}
};

// struct SelectNode : public TreeNode {
//     std::vector<std::shared_ptr<Col>> cols;
//     std::vector<std::string> tabs;
//     std::vector<std::shared_ptr<BinaryExpr>> conds;
//     std::vector<std::shared_ptr<JoinExpr>> jointree;

    
//     bool has_sort;
//     std::shared_ptr<OrderBy> order;


//     SelectNode(std::vector<std::shared_ptr<Col>> cols_,
//                std::vector<std::string> tabs_,
//                std::vector<std::shared_ptr<BinaryExpr>> conds_,
//                std::shared_ptr<OrderBy> order_) :
//             cols(std::move(cols_)), tabs(std::move(tabs_)), conds(std::move(conds_)), 
//             order(std::move(order_)) {
//                 has_sort = (bool)order;
//             }
// };

// // set enable_nestloop
// struct SetNode : public TreeNode {
//     SetKnobType set_knob_type_;
//     bool bool_val_;

//     SetNode(SetKnobType &type, bool bool_value) : 
//         set_knob_type_(type), bool_val_(bool_value) { }
// };

// Semantic value
struct SemValue {
    int sv_int;
    float sv_float;
    std::string sv_str;
    bool sv_bool;
    std::vector<std::string> sv_strs;

    CompareNode::CompOp sv_comp_op;

    std::shared_ptr<TreeNode> sv_node;

    std::shared_ptr<TypeLen> sv_type_len;

    std::shared_ptr<Field> sv_field;
    std::vector<std::shared_ptr<Field>> sv_fields;

    std::shared_ptr<Expression> sv_expr;
    std::vector<std::shared_ptr<Expression>> sv_exprs;
    std::vector<std::vector<std::shared_ptr<Expression>>> sv_expr_chunk;

    std::shared_ptr<Value> sv_val;
    std::vector<std::shared_ptr<Value>> sv_vals;

    std::shared_ptr<Col> sv_col;
    std::vector<std::shared_ptr<Col>> sv_cols;

    std::shared_ptr<SetClause> sv_set_clause;
    std::vector<std::shared_ptr<SetClause>> sv_set_clauses;

    std::shared_ptr<ConjunctionNode> sv_conjunction;
    std::vector<std::shared_ptr<ConjunctionNode>> sv_conjunctions;

    std::shared_ptr<ConditionNode> sv_cond;
    std::vector<std::shared_ptr<ConditionNode>> sv_conds;

    std::shared_ptr<CompareNode> sv_compare;
    std::vector<std::shared_ptr<CompareNode>> sv_compares;

    std::shared_ptr<OrderByNode> sv_orderby;

    SetKnobType sv_setKnobType;
};

extern std::shared_ptr<ast::TreeNode> parse_tree;

}

#define YYSTYPE ast::SemValue
