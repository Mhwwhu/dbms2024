#pragma once

#include "common/rc.h"

class Context;

class CommandExecutor {
public:
// CommandExecutor用来执行DDL和一些CMD语句，这里并没有支持DDL的并发，当前默认DDL和DML不会同时执行，DDL之间也不会同时执行。
    RC execute(Context* context);
};