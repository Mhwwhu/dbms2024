#pragma once

#include "common/rc.h"
#include <memory>

class Context;

class IPrinter {
public:
    virtual ~IPrinter() = default;

    virtual RC write_result(Context* ctx) = 0;

    virtual RC write_plain_text(const char* buf) = 0;

    virtual RC init(int fd) = 0;
};

enum PrinterType {
    UNSAFE_PRINTER,
    SAFE_PRINTER
};

class PrinterFactory {
public:
    std::shared_ptr<IPrinter> get_printer(PrinterType type);
};