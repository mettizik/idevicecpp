add_library(iMobileDevice STATIC common/debug.c  common/socket.c  common/thread.c  common/userpref.c  common/utils.c src/afc.c                  src/file_relay.c    src/installation_proxy.c  src/mobilebackup2.c         src/notification_proxy.c     src/screenshotr.c
src/debugserver.c          src/heartbeat.c     src/lockdown.c            src/mobilebackup.c          src/property_list_service.c  src/service.c
src/device_link_service.c  src/house_arrest.c  src/misagent.c            src/mobile_image_mounter.c  src/restore.c                src/syslog_relay.c
src/diagnostics_relay.c    src/idevice.c       src/mobileactivation.c    src/mobilesync.c            src/sbservices.c             src/webinspector.c)
target_compile_definitions(iMobileDevice PRIVATE PACKAGE_STRING="1")
target_include_directories(iMobileDevice PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(iMobileDevice PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(iMobileDevice PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(iMobileDevice PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../libplist/include)
target_include_directories(iMobileDevice PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../libusbmuxd/include)


if (MSVC)
    add_executable(idevicebackup2 tools/idevicebackup2.c)
    target_compile_definitions(idevicebackup2 PRIVATE PACKAGE_STRING="1")
    target_compile_definitions(idevicebackup2 PRIVATE PACKAGE_URL="idevicebackup2")
    target_include_directories(idevicebackup2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
    target_include_directories(idevicebackup2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
    target_include_directories(idevicebackup2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    target_include_directories(idevicebackup2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../libplist/include)
    target_include_directories(idevicebackup2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../libusbmuxd/include)
    target_include_directories(iMobileDevice PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../dirent/include)
    target_link_libraries(idevicebackup2 iMobileDevice)
    target_link_libraries(idevicebackup2 Plist)
    target_link_libraries(idevicebackup2 UsbMuxd)
    target_link_libraries(idevicebackup2 ${CONAN_LIBS_OPENSSL})
else (MSVC)
    target_compile_definitions(iMobileDevice PRIVATE HAVE_STPNCPY)
    target_compile_definitions(iMobileDevice PRIVATE HAVE_VASPRINTF)
    target_compile_definitions(iMobileDevice PRIVATE HAVE_ASPRINTF)
endif (MSVC)

