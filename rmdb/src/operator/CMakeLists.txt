set(SOURCES operator_generator.cpp)

add_library(operator STATIC ${SOURCES})

target_link_libraries(operator plan)