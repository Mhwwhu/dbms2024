#include "unsafe_printer.h"
#include "common/context.h"

#include <unistd.h>

using namespace std;

UnsafePrinter::UnsafePrinter()
{
    send_message_delimiter_.assign(1, '\0');
}

UnsafePrinter::~UnsafePrinter()
{
    if(fd_ >= 0) {
        close(fd_);
        fd_ = -1;
    }
}

RC UnsafePrinter::init(int fd)
{
    fd_ = fd;
    writer_ = std::make_unique<BufferedWriter>(fd);
    return RC::SUCCESS;
}

RC UnsafePrinter::write_state(Context* ctx)
{
    auto sql_result = ctx->sql_result;

    if(!sql_result.has_result()) return RC::INTERNAL;

    string result = RM_SUCC(sql_result.return_code()) ? "SUCCESS" : "FAILURE";
    result += "\n";

    RC rc = writer_->writen(result.c_str(), result.size());

    if(RM_FAIL(rc)) return RC::IOERR_WRITE;

    return RC::SUCCESS;
}

RC UnsafePrinter::write_result_internal(Context* ctx)
{
    auto sql_result = ctx->sql_result;

    if((sql_result.has_result() && RM_FAIL(sql_result.return_code())) || !sql_result.oper()) {
        return write_state(ctx);
    }

    auto oper = sql_result.oper();
    RC rc = oper->open(ctx);
    if(RM_FAIL(rc)) {
        oper->close();
        sql_result.set_return_code(rc);
        return write_state(ctx);
    }

    return RC::UNIMPLEMENTED;
}

RC UnsafePrinter::write_result(Context* ctx)
{
    RC rc;
    write_result_internal(ctx);

    rc = writer_->writen(send_message_delimiter_.data(), send_message_delimiter_.size());
    if(RM_FAIL(rc)) return rc;

    writer_->flush();

    return RC::SUCCESS;
}