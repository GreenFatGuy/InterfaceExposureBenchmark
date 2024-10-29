cmake_minimum_required(VERSION 3.10)

project(LibExposeBench)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the variable to choose between shared and static libraries
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries")
set(DERIVE_FINAL ON CACHE BOOL "Derive final class")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -march=native -flto=thin")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -flto=thin")

add_compile_options(${RELEASE_COMPILE_FLAGS})

include_directories(AFTER SYSTEM ${CMAKE_SOURCE_DIR})

# Find Google Benchmark
find_package(benchmark REQUIRED)

if (DERIVE_FINAL)
    add_compile_definitions(DERIVE_FINAL)
    message(STATUS "Deriving final class")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SRC_SRCS
    sources/impl.cpp)

set(FAST_PIMPL_SRCS
    fast-pimpl/impl.cpp)

set(PIMPL_SRCS
    pimpl/impl.cpp)

set(VRT_SRCS
    virtual/impl.cpp)

if (BUILD_SHARED_LIBS)
    message(STATUS "Building shared libraries")
    add_library(expose_srcs SHARED ${SRC_SRCS})
    add_library(expose_pimpl SHARED ${PIMPL_SRCS})
    add_library(expose_fast_pimpl SHARED ${FAST_PIMPL_SRCS})
    add_library(expose_vrt SHARED ${VRT_SRCS})
else()
    message(STATUS "Building static libraries")
    add_library(expose_srcs STATIC ${SRC_SRCS})
    add_library(expose_pimpl STATIC ${PIMPL_SRCS})
    add_library(expose_fast_pimpl STATIC ${FAST_PIMPL_SRCS})
    add_library(expose_vrt STATIC ${VRT_SRCS})
endif()

add_executable(expose_bench main.cpp)
target_link_libraries(expose_bench expose_srcs expose_pimpl expose_fast_pimpl expose_vrt benchmark::benchmark)

add_custom_command(TARGET expose_bench POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_BINARY_DIR}/compile_commands.json
    ${CMAKE_SOURCE_DIR}/compile_commands.json
)

