cmake_minimum_required(VERSION 3.16)
project(machine_learning)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

find_package(raylib)

set(SIMPLE_EXAMPLE_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/simple_example.c
  )

add_executable(simple_example)
target_sources(simple_example
  PRIVATE
  ${SIMPLE_EXAMPLE_SRC}
  )

set(SIMPLE_EXAMPLE_UI_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/simple_example_ui.c
  )

add_executable(simple_example_ui)
target_sources(simple_example_ui
  PRIVATE
  ${SIMPLE_EXAMPLE_UI_SRC}
  )

target_link_libraries(simple_example_ui
  ${raylib_LIBRARIES}
  m
  )
