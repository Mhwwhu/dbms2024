set(SOURCES create_table_stmt.cpp
            drop_table_stmt.cpp
            insert_stmt.cpp
            select_stmt.cpp)

add_library(stmt STATIC ${SOURCES})

target_link_libraries(stmt binder)