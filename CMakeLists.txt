cmake_minimum_required(VERSION 3.2)
project(efa-in-multithread)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-O0")

set (CMAKE_CXX_STANDARD 11)

set(LIBFABRIC_LIBRARY /opt/amazon/efa/lib/libfabric.so)
set(LIBFABRIC_INCLUDE_DIR /opt/amazon/efa/include)

include_directories(${LIBFABRIC_INCLUDE_DIR})

add_executable(multi_ep ep_multithread.cpp)
target_link_libraries(multi_ep ${LIBFABRIC_LIBRARY} pthread rt)

