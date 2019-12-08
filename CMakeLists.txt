###############################################################################
###############################################################################
###############################################################################
### Project Info
cmake_minimum_required(VERSION 3.10)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

set(PROJECT_NAME NewDimension)
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 1)

set(PROJECT_VERSION
    ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})

set(PROJECT_BUILD_TYPE ${CMAKE_BUILD_TYPE})

project(${PROJECT_NAME} VERSION ${PROJECT_VERSION})

set(NEW_DIMENSION_INCLUDE_DIR ./include)
set(NEW_DIMENSION_LIB_OUTPUT_DIR ${CMAKE_BINARY_DIR}/../lib)
set(NEW_DIMENSION_BIN_OUTPUT_DIR ${CMAKE_BINARY_DIR}/../bin)
#set(NEW_DIMENSION_EXTLIB_DIR ./extlibs)

configure_file(${NEW_DIMENSION_INCLUDE_DIR}/config/cmake_config.h.in
    ../${NEW_DIMENSION_INCLUDE_DIR}/config/cmake_config.h)

###############################################################################
### Build specification

include_directories(${NEW_DIMENSION_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "-Wall -Wextra -m64 -O3 -fPIC")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${NEW_DIMENSION_LIB_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${NEW_DIMENSION_LIB_OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${NEW_DIMENSION_BIN_OUTPUT_DIR})

###############################################################################
### Target build

set(NEW_DIMENSION_BIN app)

add_executable(${NEW_DIMENSION_BIN}
    src/main.cpp

    src/engine/Logger.cpp

    src/engine/Core.cpp
    src/engine/Window.cpp
    src/engine/Renderer.cpp
    src/engine/Camera.cpp
)

set_target_properties(${NEW_DIMENSION_BIN} PROPERTIES
    CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS ON
)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${NEW_DIMENSION_BIN} ${SDL2_LIBRARIES})

add_custom_target(${NEW_DIMENSION_BIN}_link ALL
    COMMAND ${CMAKE_COMMAND} -E create_symlink
    ${NEW_DIMENSION_BIN_OUTPUT_DIR}/${NEW_DIMENSION_BIN}
    ${CMAKE_BINARY_DIR}/../${NEW_DIMENSION_BIN})
