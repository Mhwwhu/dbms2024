#pragma once

#include <memory>

#include "printer.h"
#include "buffered_writer.h"

class UnsafePrinter : public IPrinter {
public:
    UnsafePrinter();

    ~UnsafePrinter() override;

    RC init(int fd) override;

    RC write_result(Context* ctx) override;

    RC write_plain_text(const char* buf) override { return RC::UNIMPLEMENTED; }

private:
    RC write_state(Context* ctx);

    RC write_result_internal(Context* ctx);

private:
    int fd_;
    std::unique_ptr<BufferedWriter> writer_;
    std::vector<char> send_message_delimiter_;
};