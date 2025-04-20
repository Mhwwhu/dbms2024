set(SOURCES optimizer.cpp
            index_select_optimize_rule.cpp)

add_library(optimizer STATIC ${SOURCES})

target_link_libraries(optimizer operator)