#pragma once

#include <memory>

#include "common/rc.h"
#include "plan/plan.h"
#include "operator.h"
#include "plan/insert_plan.h"
#include "plan/project_plan.h"
#include "plan/table_scan_plan.h"

class OperatorGenerator {
public:
    RC generate(std::shared_ptr<Plan> plan, std::shared_ptr<Operator>& oper);

private:
    RC create_operator(std::shared_ptr<InsertPlan> plan, std::shared_ptr<Operator>& oper); 
    RC create_operator(std::shared_ptr<ProjectPlan> plan, std::shared_ptr<Operator>& oper); 
    RC create_operator(std::shared_ptr<TableScanPlan> plan, std::shared_ptr<Operator>& oper);
};