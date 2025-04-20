#pragma once

#include "common/rc.h"
#include "common/context.h"
#include "transaction/transaction.h"

class TxnBeginExecutor {
public:
    RC execute(Context* ctx)
    {
        auto txn = ctx->txn_;
        if(txn->get_state() != TransactionState::GROWING || txn->get_txn_mode() == true) {
            LOG_ERROR("Transaction {} has not been committed", txn->get_transaction_id());
            return RC::TXN_STATE_ERR;
        }
        txn->set_txn_mode(true);
        return RC::SUCCESS;
    }
};