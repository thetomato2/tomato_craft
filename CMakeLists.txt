cmake_minimum_required(VERSION 3.21)

project ("Tomato_Craft"
        VERSION 0.1
        DESCRIPTION "My personal voxel game"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_UNITY_BUILD ON)


# Note: by default ENABLE_DEVELOPER_MODE is True
# This means that all analysis (sanitizers, static analysis)
# is enabled and all warnings are treated as errors
# if you want to switch this behavior, change TRUE to FALSE
# set(ENABLE_DEVELOPER_MODE
#     TRUE
#     CACHE BOOL "Enable 'developer mode'")

# # Change this to false if you want to disable warnings_as_errors in developer mode
# set(OPT_WARNINGS_AS_ERRORS_DEVELOPER_DEFAULT TRUE)


set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(SHADER_DIR ${CMAKE_CURRENT_LIST_DIR}/shaders)
set(EXTERN_DIR ${CMAKE_CURRENT_LIST_DIR}/external)
# set(BUILD_DIR ${CMAKE_CURRENT_LIST_DIR}/build)

# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR})
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_DIR})
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR})

# find_package(assimp CONFIG REQUIRED)


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
  ann  # -Zo
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
    ${SOURCE_DIR}/GL/glext.h
    ${SOURCE_DIR}/GL/wglext.h
    ${SOURCE_DIR}/imgui_style.h
    ${SOURCE_DIR}/common.hpp
    ${SOURCE_DIR}/camera.hpp
    ${SOURCE_DIR}/camera.cpp
    ${SOURCE_DIR}/color.hpp
    ${SOURCE_DIR}/entity.hpp
    ${SOURCE_DIR}/intrinsic.hpp
    ${SOURCE_DIR}/game.hpp
    ${SOURCE_DIR}/game.cpp
    ${SOURCE_DIR}/math.hpp
    ${SOURCE_DIR}/mesh.hpp
    ${SOURCE_DIR}/mesh.cpp
    ${SOURCE_DIR}/model.hpp
    ${SOURCE_DIR}/model.cpp
    ${SOURCE_DIR}/obj_loader.hpp
    ${SOURCE_DIR}/obj_loader.cpp
    ${SOURCE_DIR}/opengl.hpp
    ${SOURCE_DIR}/opengl.cpp
    ${SOURCE_DIR}/shader.hpp
    ${SOURCE_DIR}/shader.cpp
    ${SOURCE_DIR}/vector.hpp
    ${SOURCE_DIR}/texture.hpp
    ${SOURCE_DIR}/texture.cpp
    ${SOURCE_DIR}/utils.hpp
    ${SOURCE_DIR}/win32_platform.hpp
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


# if(MSVC)
#     get_all_targets(all_targets)
#     set_target_properties(${all_targets} PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=$(VC_ExecutablePath_x64);%PATH%")
# endif(


target_compile_definitions(tomato_craft  PRIVATE ${COMPILE_DEFS})

target_link_libraries(tomato_craft PRIVATE ${COMMON_LINKER_LIBS} imgui stb)

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