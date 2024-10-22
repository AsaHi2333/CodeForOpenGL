# CMakeList.txt: OpenGLforStudy 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# 将源代码添加到此项目的可执行文件。
#add_executable (OpenGLforStudy "main.cpp" "OpenGLforStudy.h")

#将需要拷贝的资源路径放入ASSETS里
file(GLOB ASSETS "./assets"  "./ThirdParty")

#将ASSETS指代的目录集合的内容，都拷贝到可执行文件的目录下
file(COPY ${ASSETS} DESTINATION ${CMAKE_BINARY_DIR} )

#添加include查找路径
include_directories(
	SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/include
)
#将库链接到可执行程序
link_directories(
	SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/libs
)

#将wrapper文件夹纳入到编译系统
add_subdirectory(wrapper)
add_subdirectory(application)

#搜索所有的cpp，加入SRCS变量中
#当目录有多个main函数时不可用
#aux_source_directory(. SRCS)#注意里面有两个参数，.是第一个参数，表示当前目录

#本工程所有cpp文件编译链接，生成exe
#add_executable(glstudy ${SRCS} "glad.c")

add_executable(glstudy "main.cpp" "glad.c")
add_executable(exp "mainExp.cpp" "glad.c")


#将wrapper.lib以及Opengl下的lib链接到softRender
target_link_libraries(glstudy application wrapper glut32.lib glfw3.lib glfw3dll.lib glew32.lib glew32s.lib)
target_link_libraries(exp wrapper glut32.lib glfw3.lib glfw3dll.lib glew32.lib glew32s.lib)

# TODO: 如有需要，请添加测试并安装目标。
