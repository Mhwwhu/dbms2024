set(SOURCES field_expr.cpp
            conjunction_expr.cpp
            comparison_expr.cpp)

add_library(expression STATIC ${SOURCES})

target_link_libraries(expression tuple)