#include "shader.hpp"

namespace tom
{

shader::shader(const std::string &vert_path, const std::string &frag_path)
{
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
}

shader::~shader()
{
    // TODO: delete the shader???
}

std::string shader::read_shader_code(const std::string &path)
{
    std::string result;
    std::ifstream shader_file;

    shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        shader_file.open(path);
        std::stringstream vert_ss;
        vert_ss << shader_file.rdbuf();
        shader_file.close();
        result = vert_ss.str();
    } catch (std::ifstream::failure &e) {
        std::cout << "ERROR -> could not read vert code file! ::" << e.what() << std::endl;
        INVALID_CODE_PATH;
    }

    return result;
}
void shader::check_shader_compile_errors(u32 shader_id, shader::type type)
{
    b32 success;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        char info_buf[1024];
        glGetShaderInfoLog(shader_id, ARRAY_COUNT(info_buf), NULL, info_buf);
        std::cout << "ERROR -> ";
        switch (type) {
            case shader::type::vertex: {
                std::cout << "Vertex ";
            } break;
            case shader::type::fragment: {
                std::cout << "Fragment ";
            } break;
            default: {
                INVALID_CODE_PATH;
            } break;
        }
        std::cout << "shader failed to compile!\n"
                  << info_buf << "\n -- ------------------------------------------- -- "
                  << std::endl;
    }
    TOM_ASSERT(success);
}

void shader::use()
{
    glUseProgram(_id);
}

void shader::set_b32(const char *name, const b32 val) const
{
    s32 uni_loc = glGetUniformLocation(_id, name);
    glUniform1i(uni_loc, val);
}

void shader::set_s32(const char *name, const s32 val) const
{
    s32 uni_loc = glGetUniformLocation(_id, name);
    glUniform1i(uni_loc, val);
}

void shader::set_f32(const char *name, const f32 val) const
{
    s32 uni_loc = glGetUniformLocation(_id, name);
    glUniform1f(uni_loc, val);
}

void shader::set_vec4(const char *name, v4 val) const
{
    s32 uni_loc = glGetUniformLocation(_id, name);
    glUniform4fv(uni_loc, 1, &val.e[0]);
}

void shader::set_mat4(const char *name, m4 val) const
{
    // NOTE: remember that tranposed is called here to make the matrix column-major
    m4 transposed = mat::transpose(val);
    s32 uni_loc = glGetUniformLocation(_id, name);
    glUniformMatrix4fv(uni_loc, 1, GL_FALSE, &transposed.e[0][0]);
}

}  // namespace tom