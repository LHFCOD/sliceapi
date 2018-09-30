# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
# 项目信息
project (sliceapi)
aux_source_directory(. DIR_SRCS)
aux_source_directory(../gen-cpp DIR_SRCS)
list(REMOVE_ITEM DIR_SRCS "../gen-cpp/SliceEntry_server.skeleton.cpp")

include_directories($ENV{BOOST_ROOT})
set(TARGET client)
add_executable(${TARGET} ${DIR_SRCS})
target_link_libraries(${TARGET} thrift)
