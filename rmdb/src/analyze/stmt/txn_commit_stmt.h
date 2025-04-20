#pragma once

#include "stmt.h"

class TxnCommitStmt : public IStmt {
public:
    StmtType type() const override { return StmtType::TXN_COMMIT_STMT; }

    static RC create(std::shared_ptr<IStmt>& stmt)
    {
        stmt = std::make_shared<TxnCommitStmt>();
        return RC::SUCCESS;
    }
};