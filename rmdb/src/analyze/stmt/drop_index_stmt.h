#include "stmt.h"
#include "system/sm_manager.h"
#include "parser/ast.h"

#include <string>
#include <memory>

class DropIndexStmt : public IStmt {
public:
    DropIndexStmt(const std::string& table_name , const std::vector<std::string> col_names )
    : table_name_(table_name), col_names_(col_names){}

    StmtType type() const override { return StmtType::DROP_INDEX_STMT; }

    static RC create(SmManager* sm_manager, std::shared_ptr<ast::DropIndex> node, std::shared_ptr<IStmt>& stmt);

    const std::string table_name() const { return table_name_; }
    const std::vector<std::string> col_names() const { return col_names_; }

private:
    std::string table_name_;
    std::vector<std::string> col_names_;
};