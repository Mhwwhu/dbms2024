set(SOURCES command_executor.cpp
            create_table_executor.cpp
            drop_table_executor.cpp
            show_tables_executor.cpp
            create_index_executor.cpp
            drop_index_executor.cpp
)

add_library(executor STATIC ${SOURCES})

target_link_libraries(executor stmt system)