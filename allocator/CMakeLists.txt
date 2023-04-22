set(TARGET_NAME allocator)

set(HEADERS allocator.hpp
        simple-memory-manager.hpp
        container.hpp)

set(SOURCES main.cpp
        simple-memory-manager.cpp)

add_executable(${TARGET_NAME} ${HEADERS} ${SOURCES})