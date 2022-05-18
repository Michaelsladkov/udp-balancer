cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_COMPILER "clang++")

project(udp-balancer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE CPP_FILES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE H_FILES CONFIGURE_DEPENDS incude/*.h include/*.hpp)

add_compile_options(-g -Wall -Werror)

add_executable(${PROJECT_NAME} ${CPP_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)


add_custom_target(clang-format
  COMMAND
    clang-format
    -style=file
    -i
    ${CPP_FILES} ${H_FILES}
  WORKING_DIRECTORY
    ${CMAKE_SOURCE_DIR}
  COMMENT
    "Running clang-format on sources..."
)
