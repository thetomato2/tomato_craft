#ifndef TOMATO_OPENGL_HPP_
#define TOMATO_OPENGL_HPP_
#include "common.hpp"

namespace tom
{
namespace ogl
{

struct wgl_func_ptrs
{
    b32 is_init;
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
    PFNGLUNIFORM4FVPROC set_uniform_v4;
    PFNGLUNIFORMMATRIX4FVPROC set_uniform_m4;
    PFNGLDELETESHADERPROC delete_shader;
    PFNGLGENVERTEXARRAYSPROC gen_vert_arr;
    PFNGLBINDVERTEXARRAYPROC bind_vert_arr;
    PFNGLGENERATEMIPMAPPROC gen_mipmap;
    PFNGLACTIVETEXTUREPROC active_tex;
    PFNGLVALIDATEPROGRAMPROC validate_program;
};

using get_ogl_func_ptr = void *(*)(const char *);

// Function alias's
const auto clear_color    = glClearColor;
const auto clear          = glClear;
const auto draw_arrays    = glDrawArrays;
const auto draw_elements  = glDrawElements;
const auto gen_tex        = glGenTextures;
const auto bind_tex       = glBindTexture;
const auto tex_params_s32 = glTexParameteri;
const auto tex_img_2d     = glTexImage2D;
const auto poly_mode      = glPolygonMode;
const auto enable         = glEnable;
const auto get_int4       = glGetIntegerv;

bool init_func_ptrs(wgl_func_ptrs *func_ptrs, get_ogl_func_ptr get_func_ptr);

}  // namespace ogl
}  // namespace tom

#endif  // TOMATO_OPENGL_HPP_
