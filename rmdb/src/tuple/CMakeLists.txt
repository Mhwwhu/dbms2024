set(SOURCES expr_tuple.cpp
            row_tuple.cpp)

add_library(tuple STATIC ${SOURCES})

target_link_libraries(tuple common record)