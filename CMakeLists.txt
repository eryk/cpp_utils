cmake_minimum_required(VERSION 3.16)
project(utils)

set(CMAKE_CXX_STANDARD 17)

set(NANOLOG /opt/NanoLog/runtime)

set(CMAKE_CXX_FLAGS "-L ${NANOLOG} -pthread -lrt")

include_directories(${NANOLOG})

add_executable(utils test.cc)

target_link_libraries(utils
        libNanoLog.a
        )