#include "shader.hpp"

namespace tom
{

shader::shader(void *func_ptrs, const char *vert_path, const char *frag_path, bool code)
{
#if TOM_OPENGL
    _func_ptrs = (ogl::wgl_func_ptrs *)(func_ptrs);
    if (code) {
        u32 vert_id;
        vert_id = _func_ptrs->create_shader(GL_VERTEX_SHADER);
        // NOTE: need a pointless pointer to a pointer so I can pass my pointer as a pointer
        _func_ptrs->shader_source(vert_id, 1, &vert_path, NULL);
        _func_ptrs->compile_shader(vert_id);
        check_shader_compile_errors(vert_id, shader::type::vertex);

        u32 frag_id;
        frag_id = _func_ptrs->create_shader(GL_FRAGMENT_SHADER);
        // NOTE: need a pointless pointer to a pointer so I can pass my pointer as a pointer
        _func_ptrs->shader_source(frag_id, 1, &frag_path, NULL);
        _func_ptrs->compile_shader(frag_id);
        check_shader_compile_errors(frag_id, shader::type::fragment);

        _id = _func_ptrs->create_program();
        _func_ptrs->attach_shader(_id, vert_id);
        _func_ptrs->attach_shader(_id, frag_id);
        _func_ptrs->link_program(_id);

        // check for compilation errors
        b32 success;
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
#endif
#if 0
    _vert_code = read_shader_code(vert_path);
    _frag_code = read_shader_code(frag_path);

    u32 vert_id;
    vert_id = glCreateShader(GL_VERTEX_SHADER);
    // NOTE: need a pointless pointer to a pointer so I can pass my pointer as a pointer
    const char *vert_code_ptr = _vert_code.c_str();
    glShaderSource(vert_id, 1, &vert_code_ptr, NULL);
    glCompileShader(vert_id);
    check_shader_compile_errors(vert_id, shader::type::vertex);

    u32 frag_id;
    frag_id = glCreateShader(GL_FRAGMENT_SHADER);
    // NOTE: need a pointless pointer to a pointer so I can pass my pointer as a pointer
    const char *frag_code_ptr = _frag_code.c_str();
    glShaderSource(frag_id, 1, &frag_code_ptr, NULL);
    glCompileShader(frag_id);
    check_shader_compile_errors(frag_id, shader::type::fragment);

    _id = glCreateProgram();
    glAttachShader(_id, vert_id);
    glAttachShader(_id, frag_id);
    glLinkProgram(_id);

    // check for compilation errors
    b32 success;
    glGetProgramiv(_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        char info_buf[1024];
        glGetProgramInfoLog(_id, ARRAY_COUNT(info_buf), NULL, info_buf);
        std::cout << "ERROR -> Shader pogram failed to compile!\n"
                  << info_buf << "\n -- ------------------------------------------- -- "
                  << std::endl;
    }
    TOM_ASSERT(success);

    // cleanup
    glDeleteShader(vert_id);
    glDeleteShader(frag_id);
#endif
}

shader::~shader()
{
    // TODO: delete the shader???
}

char *shader::read_shader_code(const char *path)
{
    char result[] = "empty";
    // TODO: this

    return result;
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

        printf("shader failed to compile!\n%s\n -- ------------------------------------------- -- ",
               info_buf);
    }
    TOM_ASSERT(success);
}

void shader::use()
{
#if TOM_OPENGL
    _func_ptrs->use_program(_id);
#else
    INVALID_CODE_PATH;
#endif
}

void shader::set_b32(const char *name, const b32 val) const
{
#if TOM_OPENGL
    s32 uni_loc = _func_ptrs->get_uniform_loc(_id, name);
    _func_ptrs->set_uniform_s32(uni_loc, val);
#else
    INVALID_CODE_PATH;
#endif
}

void shader::set_s32(const char *name, const s32 val) const
{
#if TOM_OPENGL
    s32 uni_loc = _func_ptrs->get_uniform_loc(_id, name);
    _func_ptrs->set_uniform_s32(uni_loc, val);
#else
    INVALID_CODE_PATH;
#endif
}

void shader::set_f32(const char *name, const f32 val) const
{
#if TOM_OPENGL
    s32 uni_loc = _func_ptrs->get_uniform_loc(_id, name);
    _func_ptrs->set_uniform_f32(uni_loc, val);
#else
    INVALID_CODE_PATH;
#endif
}

void shader::set_vec4(const char *name, v4 val) const
{
#if TOM_OPENGL
    s32 uni_loc = _func_ptrs->get_uniform_loc(_id, name);
    _func_ptrs->set_uniform_v4(uni_loc, 1, &val.e[0]);
#else
    INVALID_CODE_PATH;
#endif
}

void shader::set_mat4(const char *name, m4 val) const
{
#if TOM_OPENGL
    // NOTE: remember that tranposed is called here to make the matrix column-major
    m4 transposed = mat::transpose(val);
    s32 uni_loc   = _func_ptrs->get_uniform_loc(_id, name);
    _func_ptrs->set_uniform_m4(uni_loc, 1, GL_FALSE, &transposed.e[0][0]);
#else
    INVALID_CODE_PATH;
#endif
}

}  // namespace tom