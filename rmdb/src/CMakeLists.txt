include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(analyze)
add_subdirectory(record)
add_subdirectory(index)
add_subdirectory(system)
add_subdirectory(executor)
add_subdirectory(parser)
add_subdirectory(optimizer)
add_subdirectory(storage)
add_subdirectory(common)
add_subdirectory(replacer)
add_subdirectory(transaction)
add_subdirectory(recovery)
add_subdirectory(expression)
add_subdirectory(tuple)
add_subdirectory(plan)
add_subdirectory(operator)
add_subdirectory(printer)
add_subdirectory(test)

set(SOURCES portal.cpp)

add_library(portal STATIC ${SOURCES})

target_link_libraries(portal executor)

target_link_libraries(parser pthread)

add_executable(rmdb rmdb.cpp)
target_link_libraries(rmdb parser readline pthread plan analyze common transaction portal optimizer printer expression)

# unit_test
add_executable(unit_test unit_test.cpp)
target_link_libraries(unit_test storage lru_replacer record gtest_main)  # add gtest
