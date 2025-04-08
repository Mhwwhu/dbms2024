#include "printer.h"
#include "unsafe_printer.h"

std::shared_ptr<IPrinter> PrinterFactory::get_printer(PrinterType type)
{
    switch(type) {
    case UNSAFE_PRINTER:
        return std::make_shared<UnsafePrinter>();
    default:
        return nullptr;
    }
}