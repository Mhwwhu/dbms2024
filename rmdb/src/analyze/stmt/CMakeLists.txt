set(SOURCES create_table_stmt.cpp
            drop_table_stmt.cpp
            insert_stmt.cpp)

add_library(stmt STATIC ${SOURCES})