project(fruit-machine)

set(app_SOURCES
    main.cpp
)

add_executable(${PROJECT_NAME}
    ${app_SOURCES}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE fruit-machine-library
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
