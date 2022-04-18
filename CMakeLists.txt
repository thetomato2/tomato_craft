cmake_minimum_required(VERSION 3.20)

project ("Tomato_Craft"
        VERSION 0.1
        DESCRIPTION "My personal voxel game"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_UNITY_BUILD OFF)

set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(SHADER_DIR ${CMAKE_CURRENT_LIST_DIR}/shaders)
set(EXTERN_DIR ${CMAKE_CURRENT_LIST_DIR}/external)
set(BUILD_DIR ${CMAKE_CURRENT_LIST_DIR}/build)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR})

list(APPEND COMPILE_FLAGS
    -fp:fast
    -fp:except-
    # -FC
    # -Gm-
    -GR-
    # -GS
    # -EHsc
    # -Od
    # -Oi
    #-WX
    -W4
    # -wd4201
    # -wd4100
    # -wd4189
    # -wd4505
    # -wd4127
    # -Z7
    -Zc:inline
    -Zc:wchar_t
    # -Zo
    )

list(APPEND COMPILE_DEFS
    TOM_INTERNAL
    TOM_WIN32
    )

list(APPEND LINKER_FLAGS
    # -STACK:0x100000,0x100000
    -incremental:no
    -opt:ref
    )

list(APPEND COMMON_LINKER_LIBS
    user32.lib
    gdi32.lib
    winmm.lib
    kernel32.lib
    Ole32.lib
    opengl32.lib
    )

file(GLOB SHADERS
    ${SHADER_DIR}/*.comp
    ${SHADER_DIR}/*.frag
    ${SHADER_DIR}/*.geom
    ${SHADER_DIR}/*.vert
    )


add_library(imgui STATIC
    ${EXTERN_DIR}/imgui/imconfig.h
    ${EXTERN_DIR}/imgui/imgui.cpp
    ${EXTERN_DIR}/imgui/imgui.h
    ${EXTERN_DIR}/imgui/imgui_demo.cpp
    ${EXTERN_DIR}/imgui/imgui_draw.cpp
    ${EXTERN_DIR}/imgui/imgui_impl_win32.cpp
    ${EXTERN_DIR}/imgui/imgui_impl_win32.h
    ${EXTERN_DIR}/imgui/imgui_impl_opengl3.cpp
    ${EXTERN_DIR}/imgui/imgui_impl_opengl3.h
    ${EXTERN_DIR}/imgui/imgui_impl_opengl3_loader.h
    ${EXTERN_DIR}/imgui/imgui_internal.h
    ${EXTERN_DIR}/imgui/imgui_stdlib.cpp
    ${EXTERN_DIR}/imgui/imgui_stdlib.h
    ${EXTERN_DIR}/imgui/imgui_tables.cpp
    ${EXTERN_DIR}/imgui/imgui_widgets.cpp
    ${EXTERN_DIR}/imgui/imstb_rectpack.h
    ${EXTERN_DIR}/imgui/imstb_textedit.h
    ${EXTERN_DIR}/imgui/imstb_truetype.h
    )

add_library(stb STATIC
    ${EXTERN_DIR}/stb/stb_image.h
    ${EXTERN_DIR}/stb/stb_image.cpp
    )

add_executable(tomato_craft WIN32
    ${SOURCE_DIR}/imgui_style.h
    ${SOURCE_DIR}/common.hpp
    # ${SOURCE_DIR}/camera.hpp
    ${SOURCE_DIR}/color.hpp
    ${SOURCE_DIR}/shader.hpp
    ${SOURCE_DIR}/intrinsic.hpp
    ${SOURCE_DIR}/game.hpp
    ${SOURCE_DIR}/math.hpp
    ${SOURCE_DIR}/glext.h
    ${SOURCE_DIR}/opengl.hpp
    ${SOURCE_DIR}/utils.hpp
    ${SOURCE_DIR}/game.cpp
    ${SOURCE_DIR}/opengl.cpp
    ${SOURCE_DIR}/shader.cpp
    ${SOURCE_DIR}/win32_platform.cpp
    ${SOURCE_DIR}/win32_platform.cpp
    )

target_include_directories(tomato_craft PRIVATE 
     ${EXTERN_DIR}/imgui
     ${EXTERN_DIR}/stb
    )

target_compile_options(tomato_craft  PRIVATE
    ${Compile_FLags}
    # -MTd
    )

    # set_target_properties(tomato_craft  PROPERTIES
    #     VS_DEBUGGER_WORKING_DIRECTORY "$(TargetDir)")

target_compile_definitions(tomato_craft  PRIVATE ${COMPILE_DEFS})

target_link_libraries(tomato_craft ${COMMON_LINKER_LIBS} imgui stb)

target_link_options(tomato_craft PRIVATE
    ${LINKER_FLAGS}
    # -NODEFAULTLIB
    )

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY
        VS_STARTUP_PROJECT tomato_craft )

add_custom_command(
    TARGET tomato_craft POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${SHADER_DIR} $<TARGET_FILE_DIR:tomato_craft>
    DEPENDS ${SHADERS})