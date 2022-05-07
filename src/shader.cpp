#include "shader.hpp"

#include "opengl.hpp"
#include "game.hpp"
namespace tom
{

shader::shader(ogl::wgl_func_ptrs *func_ptrs, const char *vert_code, const char *frag_code)
{
    _func_ptrs = func_ptrs;

    _vert_code = vert_code;
    _frag_code = frag_code;

    init();
}

shader::shader(ogl::wgl_func_ptrs *func_ptrs, const platform_io plat_io, const char *vert_path,
               const char *frag_path)
{
    _func_ptrs = func_ptrs;

    auto vert_file_res = plat_io.platform_read_entire_file(0, vert_path);
    auto frag_file_res = plat_io.platform_read_entire_file(0, frag_path);

    if (vert_file_res.content_size != 0) {
        _vert_code = (const char *)vert_file_res.contents;
    } else {
        printf("ERROR-> Failed to read Vertex shader!\n");
        INVALID_CODE_PATH;
    }

    if (frag_file_res.content_size != 0) {
        _frag_code = (const char *)frag_file_res.contents;
    } else {
        printf("ERROR-> Failed to read Fragment shader!\n");
        INVALID_CODE_PATH;
    }

    init();
}

shader::~shader()
{
    // TODO: delete the shader???
}

void shader::check_shader_compile_errors(u32 shader_id, shader::type type)
{
    b32 success;
    _func_ptrs->get_shader_iv(shader_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        char info_buf[1024];
        _func_ptrs->get_shader_info_log(shader_id, ARRAY_COUNT(info_buf), NULL, info_buf);
        printf("ERROR -> ");
        switch (type) {
            case shader::type::vertex: {
                printf("Vertex ");
            } break;
            case shader::type::fragment: {
                printf("Fragment ");
            } break;
            default: {
                INVALID_CODE_PATH;
            } break;
        }

        printf(
            "shader failed to compile!\n%s\n -- ------------------------------------------- "
            "-- ",
            info_buf);
    }
    TOM_ASSERT(success);
}

void shader::init()
{
    u32 vert_id;
    vert_id = _func_ptrs->create_shader(GL_VERTEX_SHADER);
    // NOTE: need a pointless pointer to a pointer so I can pass my pointer as a pointer
    _func_ptrs->shader_source(vert_id, 1, &_vert_code, NULL);
    _func_ptrs->compile_shader(vert_id);
    check_shader_compile_errors(vert_id, shader::type::vertex);

    u32 frag_id;
    frag_id = _func_ptrs->create_shader(GL_FRAGMENT_SHADER);
    // NOTE: need a pointless pointer to a pointer so I can pass my pointer as a pointer
    _func_ptrs->shader_source(frag_id, 1, &_frag_code, NULL);
    _func_ptrs->compile_shader(frag_id);
    check_shader_compile_errors(frag_id, shader::type::fragment);

    // _id = _func_ptrs->create_program();
    _id = _func_ptrs->create_program();
    _func_ptrs->attach_shader(_id, vert_id);
    _func_ptrs->attach_shader(_id, frag_id);
    _func_ptrs->link_program(_id);

    // check for compilation errors
    b32 success;

    _func_ptrs->validate_program(_id);
    _func_ptrs->get_program_iv(_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        char info_buf[1024];
        _func_ptrs->get_program_info_log(_id, ARRAY_COUNT(info_buf), NULL, info_buf);
        printf(
            "ERROR -> Shader pogram failed to compile!\n%s\n -- "
            "------------------------------------------- -- ",
            info_buf);
    }
    TOM_ASSERT(success);

    // cleanup
    _func_ptrs->delete_shader(vert_id);
    _func_ptrs->delete_shader(frag_id);
}

void shader::use()
{
    _func_ptrs->use_program(_id);
}

void shader::set_b32(const char *name, const b32 val)
{
    s32 uni_loc = _func_ptrs->get_uniform_loc(_id, name);
    TOM_ASSERT(uni_loc != -1);  // failed to find uniform
    _func_ptrs->set_uniform_s32(uni_loc, val);
}

void shader::set_s32(const char *name, const s32 val)
{
    s32 uni_loc = _func_ptrs->get_uniform_loc(_id, name);
    TOM_ASSERT(uni_loc != -1);  // failed to find uniform
    _func_ptrs->set_uniform_s32(uni_loc, val);
}

void shader::set_f32(const char *name, const f32 val)
{
    s32 uni_loc = _func_ptrs->get_uniform_loc(_id, name);
    TOM_ASSERT(uni_loc != -1);  // failed to find uniform
    _func_ptrs->set_uniform_f32(uni_loc, val);
}

void shader::set_v3(const char *name, const v3 val)
{
    s32 uni_loc = _func_ptrs->get_uniform_loc(_id, name);
    TOM_ASSERT(uni_loc != -1);  // failed to find uniform
    _func_ptrs->set_uniform_v3(uni_loc, 1, &val.e[0]);
}

void shader::set_v4(const char *name, const v4 val)
{
    s32 uni_loc = _func_ptrs->get_uniform_loc(_id, name);
    TOM_ASSERT(uni_loc != -1);  // failed to find uniform
    _func_ptrs->set_uniform_v4(uni_loc, 1, &val.e[0]);
}

void shader::set_m4(const char *name, const m4 val)
{
    // NOTE: tranposed is called here to make the matrix column-major for OpenGL
    m4 transposed = mat::transpose(val);
    s32 uni_loc   = _func_ptrs->get_uniform_loc(_id, name);
    TOM_ASSERT(uni_loc != -1);  // failed to find uniform
    _func_ptrs->set_uniform_m4(uni_loc, 1, GL_FALSE, &transposed.e[0]);
}

}  // namespace tom