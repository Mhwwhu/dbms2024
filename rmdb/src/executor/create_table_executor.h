#pragma once

#include "common/rc.h"

class Context;

class CreateTableExecutor {
public:
    RC execute(Context* context);
};