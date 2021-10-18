cmake_minimum_required(VERSION 3.19)
project(image_processing)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_DEBUG "-std=c++17 -Wall -Werror -g" CACHE STRING "" FORCE)

set(CMAKE_CXX_FLAGS_RELEASE  "${CMAKE_CXX_FLAGS_DEBUG} -O3" CACHE STRING "" FORCE)

set(CMAKE_CXX_FLAGS_SANITIZED "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined,leak" CACHE STRING
        "" FORCE)

mark_as_advanced(
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_SANITIZED
)

add_executable(${CMAKE_PROJECT_NAME})
add_subdirectory(src)
