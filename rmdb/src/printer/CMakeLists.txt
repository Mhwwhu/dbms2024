set(SOURCES buffered_writer.cpp
            ring_buffer.cpp
            unsafe_printer.cpp
            printer.cpp
)

add_library(printer STATIC ${SOURCES})