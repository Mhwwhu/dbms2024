#pragma once

#include "common/rc.h"
#include "common/context.h"
#include "transaction/transaction.h"
#include "transaction/transaction_manager.h"

class TxnCommitExecutor {
public:
    RC execute(Context* ctx)
    {
        auto txn = ctx->txn_;
        if(txn->get_state() != TransactionState::GROWING || txn->get_txn_mode() == false) {
            LOG_ERROR("Transaction is not begun");
            return RC::TXN_STATE_ERR;
        }
        RC rc = ctx->txn_manager_->commit(txn, ctx->log_mgr_);
        if(RM_FAIL(rc)) {
            LOG_ERROR("Failed to commit. txn_id = {}, rc = {}", txn->get_transaction_id(), strrc(rc));
            return rc;
        }
        return RC::SUCCESS;
    }
};