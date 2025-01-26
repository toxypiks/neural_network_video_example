cmake_minimum_required(VERSION 3.16)
project(machine_learning)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

find_package(raylib)

set(XOR_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/xor.c
  )

add_executable(xor)
target_sources(xor
  PRIVATE
  ${XOR_SRC}
  )

target_link_libraries(xor
  ${raylib_LIBRARIES}
  m
  )

set(ADDER_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/adder.c
  )

add_executable(adder)
target_sources(adder
  PRIVATE
  ${ADDER_SRC}
  )

target_link_libraries(adder
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
