project(fruit-machine-library)

set(fm_SOURCES
    src/player.cpp
    include/player.h
    src/slotmachine.cpp
    include/slotmachine.h
)

add_library(${PROJECT_NAME} STATIC
    ${fm_SOURCES}
)

target_include_directories(fruit-machine-library
    PUBLIC include
)
