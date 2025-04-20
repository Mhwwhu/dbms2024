#pragma once

#include "common/rc.h"

class Context;

class CreateIndexExecutor {
public:
    RC execute(Context* context);
};