set(TARGET_NAME editor)

include_directories("shapes")

set(HEADERS view.hpp
        document.hpp
        observer.hpp
        shapes/circle.hpp
        shapes/rectangle.hpp
        shapes/utility.hpp
        )

set(SOURCES main.cpp)

add_executable(${TARGET_NAME} ${HEADERS} ${SOURCES})
