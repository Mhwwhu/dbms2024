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

#include "parser/ast.h"
#include "analyze/stmt/stmt.h"
#include "plan/plan.h"
#include "operator/operator.h"
#include "common/rc.h"

// class TransactionManager;

// used for data_send
static int const_offset = -1;

class SmManager;
class LockManager;
class LogManager;
class TransactionManager;
class Transaction;

class Context {
public:
    class SqlResult {
    private:
      std::shared_ptr<Operator> oper_;
      RC return_code_;
      bool has_result_ = false;
    public:
      void set_return_code(RC rc)
      {
        return_code_ = rc;
        has_result_ = true;
      }

      void set_oper(std::shared_ptr<Operator> oper) { oper_ = oper; }

      RC return_code() const { return return_code_; }
      bool has_result() const { return has_result_; }
      std::shared_ptr<Operator> oper() const { return oper_; }
    };

    Context (LockManager *lock_mgr, LogManager *log_mgr, 
            Transaction *txn, SmManager* sm_manager, TransactionManager* txn_mgr, char *data_send = nullptr, int *offset = &const_offset)
        : lock_mgr_(lock_mgr), log_mgr_(log_mgr), txn_(txn), sm_manager_(sm_manager), txn_manager_(txn_mgr),
          data_send_(data_send), offset_(offset) {
            ellipsis_ = false;
          }

    // TransactionManager *txn_mgr_;
    LockManager *lock_mgr_;
    LogManager *log_mgr_;
    Transaction *txn_;
    SmManager* sm_manager_;
    TransactionManager* txn_manager_;
    char *data_send_;
    int *offset_;
    bool ellipsis_;

    std::string sql;
    std::shared_ptr<ast::TreeNode> sql_node;
    std::shared_ptr<IStmt> stmt;
    std::shared_ptr<Plan> plan;
    std::shared_ptr<Operator> oper;

    SqlResult sql_result;
};

