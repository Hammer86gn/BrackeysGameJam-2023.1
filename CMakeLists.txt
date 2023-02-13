cmake_minimum_required(VERSION 3.24)
project(BrackeysGameJam C)

set(CMAKE_C_STANDARD 17)

include_directories(inc)

add_subdirectory(lib/glfw)
add_subdirectory(lib/glad/cmake)

glad_add_library(glad2 API gl:core=4.0)

file(COPY res DESTINATION "${CMAKE_BINARY_DIR}")

file(GLOB_RECURSE SRC src/**.c)
add_executable(BrackeysGameJam ${SRC})
target_link_libraries(BrackeysGameJam glfw glad2)
