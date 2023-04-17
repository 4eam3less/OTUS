set(TARGET_NAME allocator)

add_executable(${TARGET_NAME} allocator.hpp simple-memory-manager.hpp simple-memory-manager.cpp main.cpp)