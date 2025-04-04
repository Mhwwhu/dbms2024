set(SOURCES analyze.cpp)
add_library(analyze STATIC ${SOURCES})

add_subdirectory(clause)
add_subdirectory(stmt)

target_link_libraries(analyze stmt)