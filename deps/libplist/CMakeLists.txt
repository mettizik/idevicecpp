add_library(Plist STATIC src/base64.c  src/bplist.c  src/bytearray.c  src/hashtable.c  src/plist.c  src/ptrarray.c  src/time64.c  src/xplist.c libcnary/cnary.c  libcnary/iterator.c  libcnary/list.c  libcnary/node.c  libcnary/node_iterator.c  libcnary/node_list.c)
target_include_directories(Plist PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(Plist PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(Plist PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libcnary/include)
