#ifndef TOMATO_SHADER_HPP_
#define TOMATO_SHADER_HPP_

#include "common.hpp"
#include "math.hpp"
#include "opengl.hpp"

namespace tom
{
class shader
{
public:
    enum class type
    {
        vertex,
        fragment,
    };

public:
    shader(void *func_ptrs, const char *vert_path, const char *frag_path, bool code = false);
    ~shader();

    u32 get_id() const { return _id; }
    const char *get_vert_code() const { return _vert_code; }
    const char *get_frag_code() const { return _frag_code; }

    void use();
    void set_b32(const char *name, b32 val) const;
    void set_s32(const char *name, s32 val) const;
    void set_f32(const char *name, f32 val) const;
    void set_vec4(const char *name, v4) const;
    void set_mat4(const char *name, m4) const;

private:
    u32 _id;
    char _vert_code[4096];
    char _frag_code[4096];

    void check_shader_compile_errors(u32 shader_id, shader::type type);
    char *read_shader_code(const char *path);
#if TOM_OPENGL
    ogl::wgl_func_ptrs *_func_ptrs;
#endif
};

}  // namespace tom

#endif