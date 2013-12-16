cmake_minimum_required(VERSION 2.6)

project(enki)

# Add custom modules for finding dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
                     "${CMAKE_SOURCE_DIR}/cmake/Modules")

add_subdirectory(enki)
#add_subdirectory(examples)
add_subdirectory(viewer)
#add_subdirectory(python)


option(WITH_EXT
       "Build external interface library." ON)
if (WITH_EXT)
  add_subdirectory(ext)
endif (WITH_EXT)


