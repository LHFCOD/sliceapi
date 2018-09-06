# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
# 项目信息
project (test)
# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)
MESSAGE( STATUS ${DIR_SRCS})
set(QT_INC "$ENV{QTDIR}/include")
set(JAVA_INC "$ENV{JAVA_HOME}/include")
set(QT_LIB "$ENV{QTDIR}/lib")
MESSAGE( STATUS ${JAVA_INC})
MESSAGE( STATUS ${QT_INC})
include_directories(${QT_INC})
include_directories(${JAVA_INC})
# 平台判断
IF (CMAKE_SYSTEM_NAME MATCHES "Windows")
        include_directories(${JAVA_INC}/win32)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Linux")
        include_directories(${JAVA_INC}/linux)
ENDIF ()
## debug or release
#if (CMAKE_BUILD_TYPE STREQUAL "Debug")
#    set(MDS_PATH "${MDS_PATH}/x64/Debug")
#else ()
#    set(MDS_PATH "${MDS_PATH}/x64/Release")
#endif ()
MESSAGE( STATUS ${MDS_PATH})
link_directories(${QT_LIB})
add_compile_options(-std=c++11 -fPIC)
# 指定生成目标
set(TARGET test1)
add_executable(${TARGET} ${DIR_SRCS})
target_link_libraries(${TARGET} mds Qt5Gui Qt5Core Qt5Xml)
