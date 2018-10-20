cmake_minimum_required(VERSION 3.0.0)
project(idevicecpp VERSION 0.0.0)

add_definitions(-DHAVE_OPENSSL)
include(CTest)
enable_testing()

include(CheckIncludeFile)
include(CheckIncludeFileCXX)
include(CheckIncludeFiles)
include(ExternalProject)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_executable(idevicecpp src/main.cpp)
target_include_directories(idevicecpp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/deps/libplist/include)
target_link_libraries(idevicecpp Plist)
target_link_libraries(idevicecpp pthread)
target_link_libraries(idevicecpp UsbMuxd)
target_include_directories(idevicecpp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/deps/libusbmuxd/include)
add_subdirectory(include)
add_subdirectory(deps)
add_subdirectory(src)
add_subdirectory(test)

