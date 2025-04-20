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

#include "rm_defs.h"
#include <memory>

class RmFileHandle;
class Expression;
class Context;

class RecScan {
    const RmFileHandle *file_handle_;
    std::shared_ptr<RmRecord> record_;
    std::shared_ptr<Expression> filter_;
    Rid rid_;
    Context* context_;
public:
    RecScan(const RmFileHandle *file_handle, std::shared_ptr<Expression> filter);

    RC open(Context* ctx);

    RC next();

    RC close();

    std::shared_ptr<RmRecord> record() const;
};
