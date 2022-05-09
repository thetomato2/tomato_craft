#pragma once
#ifndef TOMATO_SHADER_HPP_
#define TOMATO_SHADER_HPP_

#include "core.hpp"
// #include "opengl.hpp"
// #include "game.hpp"

namespace tom
{
struct platform_io;
namespace ogl
{
struct wgl_func_ptrs;
}

class shader
{
public:
    enum class type
    {
        vertex,
        fragment,
    };

public:
    shader(ogl::wgl_func_ptrs *func_ptrs, const char *vert_code, const char *frag_code);
    shader(ogl::wgl_func_ptrs *func_ptrs, platform_io plat_io, const char *vert_path,
           const char *frag_path);
    ~shader();

    u32 get_id() const { return _id; }
    const char *get_vert_code() const { return _vert_code; }
    const char *get_frag_code() const { return _frag_code; }

    void use();
    void set_b32(const char *name, b32 val);
    void set_s32(const char *name, s32 val);
    void set_f32(const char *name, f32 val);
    void set_v3(const char *name, v3 val);
    void set_v4(const char *name, v4 val);
    void set_m4(const char *name, m4 val);

private:
    u32 _id;
    const char *_vert_code;
    const char *_frag_code;
    ogl::wgl_func_ptrs *_func_ptrs;

    void init();
    void check_shader_compile_errors(u32 shader_id, shader::type type);
};

}  // namespace tom

#endif