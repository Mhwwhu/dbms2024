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
#include "common/common.h"

namespace ast {

struct JoinNode;

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
    std::shared_ptr<Expression> expr;

    SetClause(std::string col_name_, std::shared_ptr<Expression> expr_) :
            col_name(std::move(col_name_)), expr(std::move(expr_)) {}
};

struct OrderByUnitNode : public TreeNode {
    std::shared_ptr<Expression> expr;
    common::OrderByDir direction;

    OrderByUnitNode(std::shared_ptr<Expression> expr_, common::OrderByDir dir) : expr(std::move(expr_)), direction(dir) {}
};

struct OrderByNode : public TreeNode
{
    std::vector<OrderByUnitNode> units;
    OrderByNode(std::vector<OrderByUnitNode> units_) :
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

struct SelectNode : public TreeNode {
    std::vector<std::shared_ptr<Expression>> project;
    std::shared_ptr<JoinNode> join_tree;
    std::vector<std::shared_ptr<Expression>> group_by;
    std::shared_ptr<Expression> having_conj;
    std::shared_ptr<Expression> where_conj;
    std::shared_ptr<OrderByNode> orderby;
    int limit = -1;

    SelectNode( const std::vector<std::shared_ptr<Expression>>& project_,
                std::shared_ptr<JoinNode> join_tree_,
                const std::vector<std::shared_ptr<Expression>>& group_by_,
                std::shared_ptr<Expression> having_conj_,
                std::shared_ptr<Expression> where_conj_,
                std::shared_ptr<OrderByNode> orderby_,
                int limit_)
                : project(std::move(project_)), join_tree(std::move(join_tree_)), group_by(std::move(group_by_)),
                having_conj(std::move(having_conj_)), where_conj(std::move(where_conj_)), orderby(std::move(orderby_)),  limit(limit_)
                {}
};

struct VirtualTableNode : public TreeNode {
    enum Type {
        TABLE_OR_VIEW, SUBQUERY
    };
    std::string alias;
    Type type;
    std::string name;
    std::shared_ptr<SelectNode> subquery;

    VirtualTableNode(std::string alias_, std::string name_) : alias(alias_), type(Type::TABLE_OR_VIEW), name(name_) {}
    VirtualTableNode(std::string alias_, std::shared_ptr<SelectNode> subquery_) : alias(alias_), subquery(std::move(subquery_)) {}
};

struct JoinNode : public TreeNode {
    std::shared_ptr<JoinNode> left;
    std::shared_ptr<JoinNode> right;
    std::shared_ptr<Expression> conjunction;
    std::shared_ptr<VirtualTableNode> vtable;
    common::JoinType type;

    JoinNode(std::shared_ptr<JoinNode> left_, std::shared_ptr<JoinNode> right_,
            std::shared_ptr<Expression> conjunction_, common::JoinType type_) :
            left(left_), right(right_), conjunction(conjunction_), type(type_) {}

    JoinNode(std::shared_ptr<VirtualTableNode> vtable_) : vtable(vtable_), type(common::JoinType::NONE) {}
};

struct DeleteNode : public TreeNode {
    std::string tab_name;
    std::shared_ptr<Expression> where_conj;

    DeleteNode(std::string tab_name_, std::shared_ptr<Expression> where_conj_) :
            tab_name(std::move(tab_name_)), where_conj(std::move(where_conj_)) {}
};

struct UpdateNode : public TreeNode {
    std::string tab_name;
    std::vector<std::shared_ptr<SetClause>> set_clause;
    std::shared_ptr<Expression> filter;

    UpdateNode(const std::string& tab_name_, const std::vector<std::shared_ptr<SetClause>>& set_clause_ , std::shared_ptr<Expression> filter_)
    : tab_name(tab_name_), set_clause(set_clause_), filter(std::move(filter_)) {}
};

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

    common::CompOp sv_comp_op;

    common::JoinType sv_join_type;

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

    std::shared_ptr<OrderByNode> sv_orderby;

    std::shared_ptr<JoinNode> sv_join;

    std::shared_ptr<VirtualTableNode> sv_vtable;

    common::SetKnobType sv_setKnobType;
};

extern std::shared_ptr<ast::TreeNode> parse_tree;

}

#define YYSTYPE ast::SemValue
