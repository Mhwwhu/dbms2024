#pragma once

#include "common/rc.h"

class Context;

class ShowTablesExecutor  {
public:
    ShowTablesExecutor() = default;
    ~ShowTablesExecutor() = default;
    RC execute(Context* context);
};
