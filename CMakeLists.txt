cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(protobuf_inspector LANGUAGES C CXX)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

message(STATUS "*** CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE})

message(STATUS "*** CMAKE_C_FLAGS_DEBUG: " ${CMAKE_C_FLAGS_DEBUG})
message(STATUS "*** CMAKE_C_FLAGS_RELEASE: " ${CMAKE_C_FLAGS_RELEASE})
message(STATUS "*** CMAKE_CXX_FLAGS_DEBUG: " ${CMAKE_CXX_FLAGS_DEBUG})
message(STATUS "*** CMAKE_CXX_FLAGS_RELEASE: " ${CMAKE_CXX_FLAGS_RELEASE})

set(CXXFLAGS
  -g
  -Wall
  -Wextra
)
string(REPLACE ";" " " CXXFLAGS "${CXXFLAGS}")
string(APPEND CMAKE_CXX_FLAGS " ")
string(APPEND CMAKE_CXX_FLAGS ${CXXFLAGS})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS FALSE)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include_directories(proto_output/cpp_out)

add_subdirectory(src)

install(FILES README.md DESTINATION doc COMPONENT document RENAME "README.md")