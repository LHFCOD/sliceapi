# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
# 项目信息
project (sliceapi)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(../source DIR_SRCS)
aux_source_directory(. DIR_SRCS)
aux_source_directory(./gen-cpp/ DIR_SRCS)
list(REMOVE_ITEM DIR_SRCS "../source/MicroComDocIO.cpp") 
aux_source_directory($ENV{XML} DIR_SRCS)
list(APPEND DIR_SRCS "$ENV{BOOST_ROOT}/libs/iostreams/src/mapped_file.cpp") 

include_directories($ENV{BOOST_ROOT})
include_directories($ENV{XML})
include_directories($ENV{CIMG})

add_compile_options(-std=c++11 -fPIC)
# 指定生成目标
set(TARGET server)
add_executable(${TARGET} ${DIR_SRCS})
target_link_libraries(${TARGET} pthread X11 jpeg thrift)
set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/deploy")
install(TARGETS ${TARGET} RUNTIME DESTINATION bin
        LIBRARY DESTINATION bin)
