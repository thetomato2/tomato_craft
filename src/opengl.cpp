#include "opengl.hpp"

namespace tom
{
namespace ogl
{

bool init_func_ptrs(wgl_func_ptrs *func_ptrs, get_ogl_func_ptr get_func_ptr)
{
    func_ptrs->clear_color         = (_gl_clear_color)glClearColor;
    func_ptrs->clear               = (_gl_clear)glClear;
    func_ptrs->draw_arrays         = (_gl_draw_arrays)glDrawArrays;
    func_ptrs->draw_elements       = (_gl_draw_elements)glDrawElements;
    func_ptrs->gen_textures        = (_gl_gen_textures)glGenTextures;
    func_ptrs->bind_texture        = (_gl_bind_texture)glBindTexture;
    func_ptrs->tex_param_s32       = (_gl_texture_parameter_s32)glTexParameteri;
    func_ptrs->tex_img_2d          = (_gl_tex_img_2d)glTexImage2D;
    func_ptrs->poly_mode           = (_gl_poly_mode)glPolygonMode;
    func_ptrs->enable              = (_gl_enable)glEnable;
    func_ptrs->get_s32             = (_gl_get_s32)glGetIntegerv;
    func_ptrs->create_program      = (PFNGLCREATEPROGRAMPROC)get_func_ptr("glCreateProgram");
    func_ptrs->create_shader       = (PFNGLCREATESHADERPROC)get_func_ptr("glCreateShader");
    func_ptrs->shader_source       = (PFNGLSHADERSOURCEPROC)get_func_ptr("glShaderSource");
    func_ptrs->compile_shader      = (PFNGLCOMPILESHADERPROC)get_func_ptr("glCompileShader");
    func_ptrs->get_shader_iv       = (PFNGLGETSHADERIVPROC)get_func_ptr("glGetShaderiv");
    func_ptrs->get_shader_info_log = (PFNGLGETSHADERINFOLOGPROC)get_func_ptr("glGetShaderInfoLog");
    func_ptrs->attach_shader       = (PFNGLATTACHSHADERPROC)get_func_ptr("glAttachShader");
    func_ptrs->link_program        = (PFNGLLINKPROGRAMPROC)get_func_ptr("glLinkProgram");
    func_ptrs->get_program_iv      = (PFNGLGETPROGRAMIVPROC)get_func_ptr("glGetProgramiv");
    func_ptrs->get_program_info_log =
        (PFNGLGETPROGRAMINFOLOGPROC)get_func_ptr("glGetProgramInfoLog");
    func_ptrs->use_program    = (PFNGLUSEPROGRAMPROC)get_func_ptr("glUseProgram");
    func_ptrs->gen_buffers    = (PFNGLGENBUFFERSPROC)get_func_ptr("glGenBuffers");
    func_ptrs->bind_buffer    = (PFNGLBINDBUFFERPROC)get_func_ptr("glBindBuffer");
    func_ptrs->buffer_data    = (PFNGLBUFFERDATAPROC)get_func_ptr("glBufferData");
    func_ptrs->get_attrib_loc = (PFNGLGETATTRIBLOCATIONPROC)get_func_ptr("glGetAttribLocation");
    func_ptrs->enable_vert_attrib_array =
        (PFNGLENABLEVERTEXATTRIBARRAYPROC)get_func_ptr("glEnableVertexAttribArray");
    func_ptrs->disable_vert_attrib_array =
        (PFNGLDISABLEVERTEXATTRIBARRAYPROC)get_func_ptr("glDisableVertexAttribArray");
    func_ptrs->get_uniform_loc = (PFNGLGETUNIFORMLOCATIONPROC)get_func_ptr("glGetUniformLocation");
    func_ptrs->set_uniform_s32 = (PFNGLUNIFORM1IPROC)get_func_ptr("glUniform1i");
    func_ptrs->set_uniform_f32 = (PFNGLUNIFORM1FPROC)get_func_ptr("glUniform1f");
    func_ptrs->set_uniform_v3  = (PFNGLUNIFORM3FVPROC)get_func_ptr("glUniform3fv");
    func_ptrs->set_uniform_v4  = (PFNGLUNIFORM4FVPROC)get_func_ptr("glUniform4fv");
    func_ptrs->set_uniform_m4  = (PFNGLUNIFORMMATRIX4FVPROC)get_func_ptr("glUniformMatrix4fv");
    func_ptrs->delete_shader   = (PFNGLDELETESHADERPROC)get_func_ptr("glDeleteShader");
    func_ptrs->vertex_attrib_ptr =
        (PFNGLVERTEXATTRIBPOINTERPROC)get_func_ptr("glVertexAttribPointer");
    func_ptrs->gen_vert_arr     = (PFNGLGENVERTEXARRAYSPROC)get_func_ptr("glGenVertexArrays");
    func_ptrs->bind_vert_arr    = (PFNGLBINDVERTEXARRAYPROC)get_func_ptr("glBindVertexArray");
    func_ptrs->gen_mipmap       = (PFNGLGENERATEMIPMAPPROC)get_func_ptr("glGenerateMipmap");
    func_ptrs->active_tex       = (PFNGLACTIVETEXTUREPROC)get_func_ptr("glActiveTexture");
    func_ptrs->validate_program = (PFNGLVALIDATEPROGRAMPROC)get_func_ptr("glValidateProgram");
    func_ptrs->delete_buffers   = (PFNGLDELETEBUFFERSPROC)get_func_ptr("glDeleteBuffers");
    func_ptrs->delete_vert_arr  = (PFNGLDELETEVERTEXARRAYSPROC)get_func_ptr("glDeleteVertexArrays");
    func_ptrs->draw_elements_base_vert =
        (PFNGLDRAWELEMENTSBASEVERTEXPROC)get_func_ptr("glDrawElementsBaseVertex");

    return true;
}

}  // namespace ogl
}  // namespace tom