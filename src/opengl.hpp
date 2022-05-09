#pragma once
#ifndef TOMATO_OPENGL_HPP_
#define TOMATO_OPENGL_HPP_
#include "core.hpp"

namespace tom
{
namespace ogl
{

// Function alias's
// const auto draw_arrays    = glDrawArrays;
// const auto draw_elements  = glDrawElements;
// const auto gen_tex        = glGenTextures;
// const auto bind_tex       = glBindTexture;
// const auto tex_params_s32 = glTexParameteri;
// const auto tex_img_2d = glTexImage2D;
// const auto poly_mode = glPolygonMode;
// const auto enable   = glEnable;
const auto get_int4 = glGetIntegerv;

using get_ogl_func_ptr = void *(*)(const char *);

using _gl_clear_color           = void *(*)(f32, f32, f32, f32);
using _gl_clear                 = void *(*)(u32);
using _gl_draw_arrays           = void *(*)(u32, s32, s32);
using _gl_draw_elements         = void *(*)(u32, s32, u32, const void *);
using _gl_gen_textures          = void *(*)(s32, u32 *);
using _gl_bind_texture          = void *(*)(u32, u32);
using _gl_texture_parameter_s32 = void *(*)(u32, u32, s32);
using _gl_tex_img_2d            = void *(*)(u32, s32, s32, s32, s32, s32, u32, u32, const void *);
using _gl_poly_mode             = void *(*)(u32, u32);
using _gl_enable                = void *(*)(u32);
using _gl_get_s32               = void *(*)(u32, s32 *);

// TODO: not use a struct?
struct wgl_func_ptrs
{
    b32 is_init;
    _gl_clear_color clear_color;
    _gl_clear clear;
    _gl_draw_arrays draw_arrays;
    _gl_draw_elements draw_elements;
    _gl_gen_textures gen_textures;
    _gl_bind_texture bind_texture;
    _gl_texture_parameter_s32 tex_param_s32;
    _gl_tex_img_2d tex_img_2d;
    _gl_poly_mode poly_mode;
    _gl_enable enable;
    _gl_get_s32 get_s32;
    PFNGLCREATEPROGRAMPROC create_program;
    PFNGLCREATESHADERPROC create_shader;
    PFNGLSHADERSOURCEPROC shader_source;
    PFNGLCOMPILESHADERPROC compile_shader;
    PFNGLGETSHADERIVPROC get_shader_iv;
    PFNGLGETSHADERINFOLOGPROC get_shader_info_log;
    PFNGLATTACHSHADERPROC attach_shader;
    PFNGLLINKPROGRAMPROC link_program;
    PFNGLGETPROGRAMIVPROC get_program_iv;
    PFNGLGETPROGRAMINFOLOGPROC get_program_info_log;
    PFNGLUSEPROGRAMPROC use_program;
    PFNGLGENBUFFERSPROC gen_buffers;
    PFNGLBINDBUFFERPROC bind_buffer;
    PFNGLBUFFERDATAPROC buffer_data;
    PFNGLGETATTRIBLOCATIONPROC get_attrib_loc;
    PFNGLENABLEVERTEXATTRIBARRAYPROC enable_vert_attrib_array;
    PFNGLDISABLEVERTEXATTRIBARRAYPROC disable_vert_attrib_array;
    PFNGLVERTEXATTRIBPOINTERPROC vertex_attrib_ptr;
    PFNGLGETUNIFORMLOCATIONPROC get_uniform_loc;
    PFNGLUNIFORM1IPROC set_uniform_s32;
    PFNGLUNIFORM1FPROC set_uniform_f32;
    PFNGLUNIFORM3FVPROC set_uniform_v3;
    PFNGLUNIFORM4FVPROC set_uniform_v4;
    PFNGLUNIFORMMATRIX4FVPROC set_uniform_m4;
    PFNGLDELETESHADERPROC delete_shader;
    PFNGLGENVERTEXARRAYSPROC gen_vert_arr;
    PFNGLBINDVERTEXARRAYPROC bind_vert_arr;
    PFNGLGENERATEMIPMAPPROC gen_mipmap;
    PFNGLACTIVETEXTUREPROC active_tex;
    PFNGLVALIDATEPROGRAMPROC validate_program;
    PFNGLDELETEBUFFERSPROC delete_buffers;
    PFNGLDELETEVERTEXARRAYSPROC delete_vert_arr;
    PFNGLDRAWELEMENTSBASEVERTEXPROC draw_elements_base_vert;
};

bool init_func_ptrs(wgl_func_ptrs *func_ptrs, get_ogl_func_ptr get_func_ptr);

}  // namespace ogl
}  // namespace tom

#endif  // TOMATO_OPENGL_HPP_
