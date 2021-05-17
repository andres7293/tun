cmake_minimum_required(VERSION 3.10)

project(tuntaptcpip)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SRC 
src/ICMP.cc
src/IP.cc
src/NetBuf.cc
src/NetDev.cc
src/TunIf.cc
src/Utils.cc)

set(UTEST
test/test.cc)

add_executable(tuntaptcpip src/main.cc ${SRC})

#Test
add_executable(test ${UTEST} ${SRC})
target_link_libraries(test -lgtest -lpthread)
