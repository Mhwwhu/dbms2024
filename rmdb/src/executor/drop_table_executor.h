#pragma once

#include "common/rc.h"

class Context;

class DropTableExecutor {
public:
    RC execute(Context* context);
};