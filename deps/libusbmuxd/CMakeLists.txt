add_library(UsbMuxd STATIC src/libusbmuxd.c common/collection.c  common/socket.c)
target_compile_definitions(UsbMuxd PRIVATE PACKAGE_STRING="1")
target_compile_definitions(UsbMuxd PRIVATE HAVE_STPNCPY=1)
target_include_directories(UsbMuxd PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(UsbMuxd PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(UsbMuxd PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/common)

