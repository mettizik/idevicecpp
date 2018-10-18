add_library(libplist STATIC src/base64.c  src/bplist.c  src/bytearray.c  src/hashtable.c  src/plist.c  src/ptrarray.c  src/time64.c  src/xplist.c)
target_include_directories(libplist PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(libplist PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
message(WARNING ${CMAKE_CURRENT_SOURCE_DIR})
