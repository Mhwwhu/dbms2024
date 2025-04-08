#pragma once

#include <memory>

#include "common/rc.h"
#include "plan/plan.h"
#include "operator.h"
#include "plan/insert_plan.h"

class OperatorGenerator {
public:
    RC generate(std::shared_ptr<Plan> plan, std::shared_ptr<Operator>& oper);

private:
    RC create_operator(std::shared_ptr<InsertPlan> plan, std::shared_ptr<Operator>& oper); 
};