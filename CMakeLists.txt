cmake_minimum_required(VERSION 3.0.0)
project(idevicecpp VERSION 0.0.0)

include(CTest)
enable_testing()

include(CheckIncludeFile)
include(CheckIncludeFileCXX)
include(CheckIncludeFiles)
include(ExternalProject)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(idevicecpp src/main.cpp)
target_link_libraries(idevicecpp Plist)
target_link_libraries(idevicecpp pthread)

add_subdirectory(include)
add_subdirectory(deps)
add_subdirectory(src)
add_subdirectory(test)
