#pragma once

#include "common/rc.h"

class Context;

class DropIndexExecutor {
public:
    RC execute(Context* context);
};