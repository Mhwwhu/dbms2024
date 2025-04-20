#pragma once

#include "stmt.h"

class TxnAbortStmt : public IStmt {
public:
    StmtType type() const override { return StmtType::TXN_ABORT_STMT; }

    static RC create(std::shared_ptr<IStmt>& stmt)
    {
        stmt = std::make_shared<TxnAbortStmt>();
        return RC::SUCCESS;
    }
};