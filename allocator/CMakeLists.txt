set(TARGET_NAME allocator)

set(HEADERS reserve-allocator.hpp
        simple-memory-manager.hpp
        pretty-function-info.hpp
        binary-tree.hpp)

set(SOURCES main.cpp
        simple-memory-manager.cpp)

add_executable(${TARGET_NAME} ${HEADERS} ${SOURCES})