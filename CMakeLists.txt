cmake_minimum_required(VERSION 3.16)
project(machine_learning)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)


set(SIMPLE_EXAMPLE_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/simple_example.c
  )

add_executable(simple_example)
target_sources(simple_example
  PRIVATE
  ${SIMPLE_EXAMPLE_SRC}
  )
