cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(libpym)

add_library(libpym STATIC)

target_include_directories(libpym PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

file(GLOB_RECURSE SOURCES
  ${PROJECT_SOURCE_DIR}/src/**/*.cpp
)

target_sources(libpym PRIVATE ${SOURCES})

execute_process(
    COMMAND ${CMAKE_COMMAND} -E create_symlink 
            ${CMAKE_BINARY_DIR}/compile_commands.json
            ${CMAKE_SOURCE_DIR}/compile_commands.json
)

# target_compile_options(libpym -Wall -Wextra -Werror -pedantic)
