cmake_minimum_required(VERSION 3.10)
project(nasal)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(src)

if(ENABLE_TESTS)
  enable_testing()
endif()
