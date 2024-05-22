cmake_minimum_required(VERSION 3.18)

project(linalg)

find_package(Chrono COMPONENTS Irrlicht
             CONFIG)

if (NOT Chrono_FOUND)
  message("Could not find Chrono or one of its required modules")
  return()
endif()

set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD ${CHRONO_CXX_STANDARD})


include_directories(${CHRONO_INCLUDE_DIRS})

add_executable(my_demo Collisions.cpp)

target_link_libraries(my_demo ${CHRONO_LIBRARIES})