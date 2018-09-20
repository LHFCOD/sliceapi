# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
# 项目信息
project (sliceapi)
add_subdirectory("${PROJECT_SOURCE_DIR}/test")
add_subdirectory("${PROJECT_SOURCE_DIR}/thrift/server")
add_subdirectory("${PROJECT_SOURCE_DIR}/thrift/client")

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(./source DIR_SRCS)

MESSAGE( STATUS ${DIR_SRCS})
list(REMOVE_ITEM DIR_SRCS "./source/MicroComDocIO.cpp") 
MESSAGE( STATUS ${DIR_SRCS})
set(QT_INC "$ENV{QTDIR}/include")
set(JAVA_INC "$ENV{JAVA_HOME}/include")
set(QT_LIB "$ENV{QTDIR}/lib")
MESSAGE( STATUS ${JAVA_INC})
include_directories(${QT_INC})
include_directories(${JAVA_INC})
# display include file in project
FILE(GLOB_RECURSE INC_ALL "./include/*.h")
# 平台判断
IF (CMAKE_SYSTEM_NAME MATCHES "Windows")                                          	
	include_directories(${JAVA_INC}/win32)
#	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./target/win32")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Linux")
        include_directories(${JAVA_INC}/linux)
        #	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "./target/linux")
ENDIF ()
link_directories(${QT_LIB})
add_compile_options(-std=c++0x -fPIC)
# 指定生成目标
set(TARGET mds)
add_library(${TARGET} SHARED ${DIR_SRCS} ${INC_ALL})

target_link_libraries(${TARGET} Qt5Gui Qt5Core Qt5Xml)

set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/deploy")
install(TARGETS ${TARGET} RUNTIME DESTINATION bin
        LIBRARY DESTINATION bin)
set_target_properties(${TARGET} PROPERTIES INSTALL_RPATH ${QT_LIB})
