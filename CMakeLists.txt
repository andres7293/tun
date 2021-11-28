cmake_minimum_required(VERSION 3.10)

project(tuntaptcpip)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(src test)

set(SRC 
src/IP.cc
src/UDP.cc
src/ICMP.cc
src/Buffer.cc
src/NetBuf.cc
src/NetDev.cc
src/TunIf.cc
src/Packet.cc
src/Utils.cc)

set(UTEST
test/units/unit.cc)

#Test
add_executable(unit ${UTEST} ${SRC})
target_link_libraries(unit -lgtest -lpthread)

add_executable(tuntaptcpip src/main.cc ${SRC})

