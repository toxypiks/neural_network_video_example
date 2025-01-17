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

set(IMG2NN_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/img2nn.c
  )

add_executable(img2nn)
target_sources(img2nn
 PRIVATE
  ${IMG2NN_SRC}
  )

target_link_libraries(img2nn
  ${raylib_LIBRARIES}
  m
  )

set(LAYOUT_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/layout.c
  )

add_executable(layout)
target_sources(layout
  PRIVATE
  ${LAYOUT_SRC}
  )

target_link_libraries(layout
  ${raylib_LIBRARIES}
  m
  )
