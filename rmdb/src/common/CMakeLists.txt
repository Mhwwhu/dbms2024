add_subdirectory(type)

set(SOURCES rc.cpp utils.cpp value.cpp)
add_library(common STATIC ${SOURCES})
target_link_libraries(common type)