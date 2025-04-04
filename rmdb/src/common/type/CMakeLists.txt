set(SOURCES attr_type.cpp
            char_type.cpp
            data_type.cpp
            float_type.cpp
            integer_type.cpp)

add_library(type STATIC ${SOURCES})
target_link_libraries(type common)