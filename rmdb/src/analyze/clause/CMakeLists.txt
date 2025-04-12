set(SOURCES filter_clause.cpp
            join_clause.cpp)

add_library(clause STATIC ${SOURCES})

target_link_libraries(clause expression parser)