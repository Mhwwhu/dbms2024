set(SOURCES optimizer.cpp)

add_library(optimizer STATIC ${SOURCES})

target_link_libraries(optimizer operator)