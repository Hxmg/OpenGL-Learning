cmake_minimum_required (VERSION 2.8)

#项目信息
project (OpenGL-Learn)

#查找当前目录下的所有源文件
#并把名称保存到 DIR_SRCS 变量
#aux_source_directory(./src DIR_SRCS)
#option(DEBUG_mode "ON for debug or OFF for release")
#set(abc "" CACHE PATH "1111")
#set(OGRE_UNITY_FILES_PER_UNIT "50" CACHE STRING "Number of files per compilation unit in Unity build.")



add_executable (Main ${DIR_SRCS} ./src/main.cpp ./src/glad.c)


if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    message(STATUS ">> current platform: Linux")
    target_link_libraries (Main libglfw3.a GL X11 pthread Xrandr Xi dl Xcursor Xxf86vm Xinerama)
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    message(STATUS ">> current platform: Windows")
    target_link_libraries (Main opengl32.lib)
    set(GLFW3_LIB_DIR "E:/SDK/glfw-3.2.1.bin.WIN32/lib-vc2015" CACHE PATH "glfw3 path")
    if(GLFW3_LIB_DIR)
        target_link_libraries(Main ${GLFW3_LIB_DIR}/glfw3.lib)
    else()
        message(ERROR "Must set glfw3 lib path")
    endif()
endif()



