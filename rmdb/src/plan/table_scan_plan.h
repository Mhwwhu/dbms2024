#pragma once

#include "plan.h"
#include "system/sm_meta.h"
#include "analyze/stmt/stmt.h"

class TableScanPlan : public Plan {
public:

    PlanTag type() const { return PlanTag::TABLE_GET_PLAN; }

    
};