set(SOURCES operator_generator.cpp
            chunk_get_oper.cpp
            insert_oper.cpp)

add_library(operator STATIC ${SOURCES})

target_link_libraries(operator plan record tuple)