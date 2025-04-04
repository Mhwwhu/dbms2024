#pragma once

#include "common/rc.h"

class Context;

class CommandExecutor {
public:
    RC execute(Context* context);
};