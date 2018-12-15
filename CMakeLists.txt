cmake_minimum_required(VERSION 3.5)
project(app_dummy C)

SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules")
set(CMAKE_C_STANDARD 99)

find_package(asterisk REQUIRED)

add_library(res_dummy SHARED res_dummy.c)
set_target_properties(res_dummy PROPERTIES PREFIX "")

target_link_libraries (res_dummy)

install (TARGETS res_dummy DESTINATION ${ASTERISK_LIBRARY_DIR})
