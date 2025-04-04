#pragma once

#include <memory>

#include "common/rc.h"
#include "plan/plan.h"
#include "operator.h"

class OperatorGenerator {
public:
    RC generate(std::shared_ptr<Plan> plan, std::shared_ptr<Operator>& oper);
};