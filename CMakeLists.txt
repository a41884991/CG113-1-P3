cmake_minimum_required(VERSION 3.5)

project(RollerCoasters)


set(SRC_DIR ${PROJECT_SOURCE_DIR}/src/)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/)
set(LIB_DIR ${PROJECT_SOURCE_DIR}/lib/)
set(IMGUI_DIR ${INCLUDE_DIR}imgui/)
set(SHADER_DIR ${SRC_DIR}Shader/)
set(RESOURCE_DIR ${PROJECT_SOURCE_DIR}/resource/)
set(DLL_DIR ${PROJECT_SOURCE_DIR}/dll/)

set(OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/release)

include_directories(${INCLUDE_DIR})
include_directories(${INCLUDE_DIR}glm/)
include_directories(${INCLUDE_DIR}glad/include/)
include_directories(${INCLUDE_DIR}GLFW/)
include_directories(${INCLUDE_DIR}assimp/)
include_directories(${IMGUI_DIR})
include_directories(${SRC_DIR})

add_Definitions("-D_XKEYCHECK_H")
add_definitions(-DPROJECT_DIR="${PROJECT_SOURCE_DIR}")
# set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

add_executable(RollerCoasters
    ${SRC_DIR}MainWindow/MainWindow.cpp
    ${SRC_DIR}ControlWindow/ControlWindow.cpp
    ${SRC_DIR}MainView/MainView.cpp
    ${SRC_DIR}ShaderProgram/ShaderProgram.cpp
    ${SRC_DIR}Material/Material.cpp
    ${SRC_DIR}Camera/Camera.cpp
    ${SRC_DIR}ControlPoint/ControlPoint.cpp
    ${SRC_DIR}Track/Track.cpp
    ${SRC_DIR}Model/Mesh.cpp
    ${SRC_DIR}Model/Model.cpp
    ${SRC_DIR}main.cpp
    ${INCLUDE_DIR}glad/src/glad.c)

add_library(ImGUI
    ${IMGUI_DIR}imconfig.h
    ${IMGUI_DIR}imgui.h
    ${IMGUI_DIR}imgui_internal.h
    ${IMGUI_DIR}imstb_rectpack.h
    ${IMGUI_DIR}imstb_textedit.h
    ${IMGUI_DIR}imstb_truetype.h
    ${IMGUI_DIR}backends/imgui_impl_glfw.h
    ${IMGUI_DIR}backends/imgui_impl_opengl3.h
    ${IMGUI_DIR}backends/imgui_impl_opengl3_loader.h
    ${IMGUI_DIR}imgui.cpp
    ${IMGUI_DIR}imgui_demo.cpp
    ${IMGUI_DIR}imgui_draw.cpp
    ${IMGUI_DIR}imgui_tables.cpp
    ${IMGUI_DIR}imgui_widgets.cpp
    ${IMGUI_DIR}backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}backends/imgui_impl_opengl3.cpp)

target_link_libraries(RollerCoasters
    ${LIB_DIR}glfw3.lib
    ${LIB_DIR}OpenGL32.lib
    ${LIB_DIR}assimp-vc142-mt.lib)

add_custom_command(

    # 指令依附的目標
    TARGET RollerCoasters

    # 自訂指令的執行時機
    POST_BUILD

    # COMMAND關鍵字後為執行指令
    COMMAND
    ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:RollerCoasters>/Shader
    COMMAND
    ${CMAKE_COMMAND} -E copy_directory ${SHADER_DIR} $<TARGET_FILE_DIR:RollerCoasters>/Shader

    COMMAND
    ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:RollerCoasters>/resource
    COMMAND
    ${CMAKE_COMMAND} -E copy_directory ${RESOURCE_DIR} $<TARGET_FILE_DIR:RollerCoasters>/resource

    COMMAND
    ${CMAKE_COMMAND} -E copy_directory ${DLL_DIR} $<TARGET_FILE_DIR:RollerCoasters>
)

target_link_libraries(RollerCoasters ImGUI)
