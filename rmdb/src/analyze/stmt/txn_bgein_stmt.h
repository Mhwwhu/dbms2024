#pragma once

#include "stmt.h"

class TxnBeginStmt : public IStmt {
public:
    StmtType type() const override { return StmtType::TXN_BEGIN_STMT; }

    static RC create(std::shared_ptr<IStmt>& stmt)
    {
        stmt = std::make_shared<TxnBeginStmt>();
        return RC::SUCCESS;
    }
};