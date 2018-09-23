# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
# 项目信息
project (sliceapi)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(./source DIR_SRCS)
aux_source_directory(. DIR_SRCS)
MESSAGE( STATUS ${DIR_SRCS})
list(REMOVE_ITEM DIR_SRCS "./source/MicroComDocIO.cpp") 
MESSAGE( STATUS ${DIR_SRCS})
set(QT_INC "$ENV{QTDIR}/include")
set(JAVA_INC "$ENV{JAVA_HOME}/include")
set(QT_LIB "$ENV{QTDIR}/lib")
set(XML "/home/mi/software/pugixml/src")
aux_source_directory(${XML} DIR_SRCS)
MESSAGE( STATUS ${JAVA_INC})
include_directories(${QT_INC})
include_directories(${JAVA_INC})
include_directories($ENV{BOOST_ROOT})
include_directories(${XML})
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
add_compile_options(-std=c++11 -fPIC)
# 指定生成目标
set(TARGET mds)
add_executable(${TARGET} ${DIR_SRCS} ${INC_ALL} source/Utils.cpp "/home/mi/software/boost_1_68_0/libs/iostreams/src/mapped_file.cpp")

target_link_libraries(${TARGET} Qt5Gui Qt5Core Qt5Xml)

set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/deploy")
install(TARGETS ${TARGET} RUNTIME DESTINATION bin
        LIBRARY DESTINATION bin)
set_target_properties(${TARGET} PROPERTIES INSTALL_RPATH ${QT_LIB})
