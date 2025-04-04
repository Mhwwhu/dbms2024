#pragma once

#include "common/rc.h"
#include "system/sm_manager.h"
#include "parser/ast.h"

enum StmtType {
    SELECT_STMT,
    DELETE_STMT,
    INSERT_STMT,
    UPDATE_STMT,
    CREATE_TABLE_STMT,
    CREATE_INDEX_STMT,
    DROP_TABLE_STMT,
    DROP_INDEX_STMT,
    DESC_TABLE_STMT,
    SET_VARIABLE_STMT,
};

class IStmt {
public:
    IStmt() = default;
    virtual ~IStmt() = default;

    virtual StmtType type() const = 0;

    static bool is_dml(StmtType type)
    {
        return type == StmtType::SELECT_STMT
            || type == StmtType::DELETE_STMT
            || type == StmtType::INSERT_STMT
            || type == StmtType::UPDATE_STMT;
    }
};