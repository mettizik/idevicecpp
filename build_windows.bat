@echo off
if not exist "build" mkdir build
pushd build
    call conan install OpenSSL/1.1.0i@conan/stable -g cmake -pr ../msvc12_86_64_release.conan.pr && echo openssl installed with conan || exit /B %errorlevel%
    call cmake -G "Visual Studio 12 2013 Win64" .. && echo CMake generation finished || exit /B %errorlevel%
    call cmake --build . --target idevicecpp && echo CMake build finished || exit /B %errorlevel%
popd 
