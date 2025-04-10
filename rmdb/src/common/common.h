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

#include <cassert>
#include <cstring>
#include <memory>
#include <string>
#include <vector>
#include <math.h>
#include "record/rm_defs.h"
#include "value.h"


struct TabCol {
    std::string tab_name;
    std::string col_name;

    friend bool operator<(const TabCol &x, const TabCol &y) {
        return std::make_pair(x.tab_name, x.col_name) < std::make_pair(y.tab_name, y.col_name);
    }
};

// struct Value {
//     AttrType type;  // type of value
//     union {
//         int int_val;      // int value
//         float float_val;  // float value
//     };
//     std::string str_val;  // string value

//     std::shared_ptr<RmRecord> raw;  // raw record buffer

//     void set_int(int int_val_) {
//         type = INTS;
//         int_val = int_val_;
//     }

//     void set_float(float float_val_) {
//         type = FLOATS;
//         float_val = float_val_;
//     }

//     void set_str(std::string str_val_) {
//         type = AttrType::CHARS;
//         str_val = std::move(str_val_);
//     }

//     void init_raw(int len) {
//         assert(raw == nullptr);
//         raw = std::make_shared<RmRecord>(len);
//         if (type == INTS) {
//             assert(len == sizeof(int));
//             *(int *)(raw->data) = int_val;
//         } else if (type == FLOATS) {
//             assert(len == sizeof(float));
//             *(float *)(raw->data) = float_val;
//         } else if (type == AttrType::CHARS) {
//             if (len < (int)str_val.size()) {
//                 throw StringOverflowError();
//             }
//             memset(raw->data, 0, len);
//             memcpy(raw->data, str_val.c_str(), str_val.size());
//         }
//     }
// };

enum CompOp { OP_EQ, OP_NE, OP_LT, OP_GT, OP_LE, OP_GE };

struct Condition {
    TabCol lhs_col;   // left-hand side column
    CompOp op;        // comparison operator
    bool is_rhs_val;  // true if right-hand side is a value (not a column)
    TabCol rhs_col;   // right-hand side column
    Value rhs_val;    // right-hand side value
};

struct SetClause {
    TabCol lhs;
    Value rhs;
};

namespace common {

    int compareIgnoreCase(const char* str1, const char* str2);

    int compare_string(void *arg1, int arg1_max_length, void *arg2, int arg2_max_length);

    int compare_int(void *arg1, void *arg2);

    int compare_float(void *arg1, void *arg2);

    std::string double_to_str(double v);
}