# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
# 项目信息
project (sliceapi)
add_subdirectory(thrift)
add_subdirectory(thrift/client)
# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(./source DIR_SRCS)
aux_source_directory(. DIR_SRCS)
list(REMOVE_ITEM DIR_SRCS "./source/MicroComDocIO.cpp") 
aux_source_directory($ENV{XML} DIR_SRCS)
list(APPEND DIR_SRCS "$ENV{BOOST_ROOT}/libs/iostreams/src/mapped_file.cpp") 

include_directories($ENV{BOOST_ROOT})
include_directories($ENV{XML})
include_directories($ENV{CIMG})
include_directories("$ENV{JPEG}/include")
link_directories("$ENV{JPEG}/lib")
# display include file in project
# 平台判断
IF (CMAKE_SYSTEM_NAME MATCHES "Windows")                                          	
	include_directories(${JAVA_INC}/win32)
#	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./target/win32")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Linux")
        include_directories(${JAVA_INC}/linux)
        #	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "./target/linux")
ENDIF ()
add_compile_options(-std=c++11 -fPIC)
# 指定生成目标
set(TARGET mds)
add_executable(${TARGET} ${DIR_SRCS})

target_link_libraries(${TARGET} pthread X11 jpeg)

set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/deploy")
install(TARGETS ${TARGET} RUNTIME DESTINATION bin
        LIBRARY DESTINATION bin)
