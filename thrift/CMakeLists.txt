# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
# 项目信息
project (sliceapi1)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
set(JPEG_LIB_VERSION 80)
aux_source_directory(../source DIR_SRCS)
aux_source_directory(./gen-cpp DIR_SRCS)
list(REMOVE_ITEM DIR_SRCS "./gen-cpp/SliceEntry_server.skeleton.cpp") 
aux_source_directory(. DIR_SRCS)
list(REMOVE_ITEM DIR_SRCS "../source/MicroComDocIO.cpp") 

aux_source_directory($ENV{XML} DIR_SRCS)
list(APPEND DIR_SRCS "$ENV{BOOST_ROOT}/libs/iostreams/src/mapped_file.cpp") 

include_directories($ENV{BOOST_ROOT})
include_directories($ENV{XML})
include_directories($ENV{CIMG})
include_directories("$ENV{JPEG}/include")
link_directories("$ENV{JPEG}/lib")
add_compile_options(-std=c++11)
# 指定生成目标
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
set(CMAKE_LINKER_FLAGS "-static -pthread -lrt -ldl")
set(TARGET server)
add_executable(${TARGET} ${DIR_SRCS})
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
find_package(Threads REQUIRED)
target_link_libraries(${TARGET} libthrift.a Threads::Threads  libjpeg.a )  
set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/deploy")
install(TARGETS ${TARGET} RUNTIME DESTINATION bin
        LIBRARY DESTINATION bin)
# set_target_properties(${TARGET} PROPERTIES LINK_SEARCH_START_STATIC 1)
# set_target_properties(${TARGET} PROPERTIES LINK_SEARCH_END_STATIC 1)