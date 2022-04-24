#include "shader.hpp"
#include "game.hpp"
namespace tom
{

internal void check_shader_compile_errors(ogl::wgl_func_ptrs *func_ptrs, u32 shader_id, type type)
{
    b32 success;
    func_ptrs->get_shader_iv(shader_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        char info_buf[1024];
        func_ptrs->get_shader_info_log(shader_id, ARRAY_COUNT(info_buf), NULL, info_buf);
        printf("ERROR -> ");
        switch (type) {
            case type::vertex: {
                printf("Vertex ");
            } break;
            case type::fragment: {
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

internal u32 create_shader(ogl::wgl_func_ptrs *func_ptrs, const char *vert_code,
                           const char *frag_code)
{
    u32 vert_id;
    vert_id = func_ptrs->create_shader(GL_VERTEX_SHADER);
    // NOTE: need a pointless pointer to a pointer so I can pass my pointer as a pointer
    func_ptrs->shader_source(vert_id, 1, &vert_code, NULL);
    func_ptrs->compile_shader(vert_id);
    check_shader_compile_errors(func_ptrs, vert_id, type::vertex);

    u32 frag_id;
    frag_id = func_ptrs->create_shader(GL_FRAGMENT_SHADER);
    // NOTE: need a pointless pointer to a pointer so I can pass my pointer as a pointer
    func_ptrs->shader_source(frag_id, 1, &frag_code, NULL);
    func_ptrs->compile_shader(frag_id);
    check_shader_compile_errors(func_ptrs, frag_id, type::fragment);

    // _id = _func_ptrs->create_program();
    u32 shader_id = func_ptrs->create_program();
    func_ptrs->attach_shader(shader_id, vert_id);
    func_ptrs->attach_shader(shader_id, frag_id);
    func_ptrs->link_program(shader_id);

    // check for compilation errors
    b32 success;

    func_ptrs->validate_program(shader_id);
    func_ptrs->get_program_iv(shader_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        char info_buf[1024];
        func_ptrs->get_program_info_log(shader_id, ARRAY_COUNT(info_buf), NULL, info_buf);
        printf(
            "ERROR -> Shader pogram failed to compile!\n%s\n -- "
            "------------------------------------------- -- ",
            info_buf);
    }
    TOM_ASSERT(success);

    // cleanup
    func_ptrs->delete_shader(vert_id);
    func_ptrs->delete_shader(frag_id);

    return shader_id;
}

shader shader_init(ogl::wgl_func_ptrs *func_ptrs, const char *vert_code, const char *frag_code)
{
    shader result;
    result.func_ptrs = func_ptrs;

#ifdef TOM_INTERNAL
    result.vert_code = vert_code;
    result.frag_code = frag_code;
#endif

    result.id = create_shader(func_ptrs, vert_code, frag_code);

    return result;
}

shader shader_init(ogl::wgl_func_ptrs *func_ptrs, const platform_io plat_io, const char *vert_path,
            const char *frag_path)
{
    shader result;
    result.func_ptrs = func_ptrs;

    auto vert_file_res = plat_io.platform_read_entire_file(0, vert_path);
    auto frag_file_res = plat_io.platform_read_entire_file(0, frag_path);

    if (vert_file_res.content_size == 0) {
        printf("ERROR-> Failed to read Vertex shader!\n");
        INVALID_CODE_PATH;
    }

    if (frag_file_res.content_size == 0) {
        printf("ERROR-> Failed to read Fragment shader!\n");
        INVALID_CODE_PATH;
    }
    auto vert_code = (const char *)vert_file_res.contents;
    auto frag_code = (const char *)frag_file_res.contents;

#ifdef TOM_INTERNAL
    result.vert_code = vert_code;
    result.frag_code = frag_code;
#endif

    result.id = create_shader(func_ptrs, vert_code, frag_code);

    return result;
}

void uniform_set_s32(shader shader, const char *name, const s32 val)
{
    s32 uni_loc = shader.func_ptrs->get_uniform_loc(shader.id, name);
    TOM_ASSERT(uni_loc != -1);  // failed to find uniform
    shader.func_ptrs->set_uniform_s32(uni_loc, val);
}

void uniform_set_b32(shader shader, const char *name, const b32 val)
{
    uniform_set_s32(shader, name, val);
}

void uniform_set_f32(shader shader, const char *name, const f32 val)
{
    s32 uni_loc = shader.func_ptrs->get_uniform_loc(shader.id, name);
    TOM_ASSERT(uni_loc != -1);  // failed to find uniform
    shader.func_ptrs->set_uniform_f32(uni_loc, val);
}

void uniform_set_vec4(shader shader, const char *name, const v4 val)
{
    s32 uni_loc = shader.func_ptrs->get_uniform_loc(shader.id, name);
    TOM_ASSERT(uni_loc != -1);  // failed to find uniform
    shader.func_ptrs->set_uniform_v4(uni_loc, 1, &val.e[0]);
}

void uniform_set_mat4(shader shader, const char *name, const m4 val)
{
    m4 transposed = mat::transpose(val);
    s32 uni_loc   = shader.func_ptrs->get_uniform_loc(shader.id, name);
    TOM_ASSERT(uni_loc != -1);  // failed to find uniform
    shader.func_ptrs->set_uniform_m4(uni_loc, 1, GL_FALSE, &transposed.e[0][0]);
}

}  // namespace tom