set(SOURCES command_executor.cpp
            create_table_executor.cpp
            drop_table_executor.cpp
)

add_library(executor STATIC ${SOURCES})

target_link_libraries(executor stmt system)