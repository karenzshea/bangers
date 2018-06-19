cmake_minimum_required (VERSION 3.4)

project (sample_route_pbf LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 14)

find_package(Protobuf REQUIRED)

if(NOT TARGET protobuf::libprotobuf)
  if(PROTOBUF_LIBRARY)
    add_library(protobuf::libprotobuf UNKNOWN IMPORTED)
    set_target_properties(protobuf::libprotobuf PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES "${PROTOBUF_INCLUDE_DIR}")
    if(EXISTS "${PROTOBUF_LIBRARY}")
      set_target_properties(protobuf::libprotobuf PROPERTIES
        IMPORTED_LOCATION "${PROTOBUF_LIBRARY}")
    endif()
    if(EXISTS "${PROTOBUF_LIBRARY_RELEASE}")
      set_property(TARGET protobuf::libprotobuf APPEND PROPERTY
        IMPORTED_CONFIGURATIONS RELEASE)
      set_target_properties(protobuf::libprotobuf PROPERTIES
        IMPORTED_LOCATION_RELEASE "${PROTOBUF_LIBRARY_RELEASE}")
    endif()
    if(EXISTS "${PROTOBUF_LIBRARY_DEBUG}")
      set_property(TARGET protobuf::libprotobuf APPEND PROPERTY
        IMPORTED_CONFIGURATIONS DEBUG)
      set_target_properties(protobuf::libprotobuf PROPERTIES
        IMPORTED_LOCATION_DEBUG "${PROTOBUF_LIBRARY_DEBUG}")
    endif()
  endif()
endif()

include_directories ("${PROJECT_SOURCE_DIR}/google-generated")# "${PROTOBUF_INCLUDE_DIR}")

add_executable(route-pbf-gen
    pbf-write.cpp
    ${PROJECT_SOURCE_DIR}/google-generated/route.pb.cc
)
add_executable(route-pbf-read
    pbf-read.cpp
    ${PROJECT_SOURCE_DIR}/google-generated/route.pb.cc
)

target_link_libraries(route-pbf-gen protobuf::libprotobuf)
target_link_libraries(route-pbf-read protobuf::libprotobuf)
