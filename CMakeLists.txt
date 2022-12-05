cmake_minimum_required(VERSION 3.20)
project(test_code)
set(CMAKE_CXX_STANDARD 11)

add_executable(Test
    example/test.cpp
    src/threespace_api_export.cpp
    src/threespace_api.cpp
    src/threespace_device.cpp
    src/threespace_dongle.cpp
    src/threespace_sensor.cpp
    src/yost/yost_core_api.cpp
    src/yost/yost_fair_mutex.cpp
    src/yost/yost_math.cpp
    src/serial/serial_enumerator_linux.cpp
    src/serial/serial_enumerator_osx.cpp
    src/serial/serial_enumerator_win.cpp
    src/serial/serial_enumerator.cpp
    src/serial/serial.cc
    src/serial/impl/unix.cc
    src/serial/impl/win.cc
)

target_include_directories(Test
    PRIVATE
    include/
    include/yost/
    include/rapidxml/
    include/serial/
    include/serial/impl
    include/serial/yost
)