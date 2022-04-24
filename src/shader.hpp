#ifndef TOMATO_SHADER_HPP_
#define TOMATO_SHADER_HPP_

#include "common.hpp"
#include "math.hpp"
#include "opengl.hpp"
// #include "opengl.hpp"
// #include "game.hpp"

namespace tom
{
struct platform_io;
namespace ogl
{
struct wgl_func_ptrs;
}

struct shader
{
    u32 id;
#ifdef TOM_INTERNAL
    const char *vert_code;
    const char *frag_code;
#endif
    ogl::wgl_func_ptrs *func_ptrs;
};

enum class type
{
    vertex,
    fragment,
};

shader shader_init(ogl::wgl_func_ptrs *func_ptrs, const char *vert_code, const char *frag_code);
shader shader_init(ogl::wgl_func_ptrs *func_ptrs, platform_io plat_io, const char *vert_path,
                   const char *frag_path);

void uniform_set_s32(shader shader, const char *name, const s32 val);
void uniform_set_b32(shader shader, const char *name, const b32 val);
void uniform_set_f32(shader shader, const char *name, const f32 val);
void uniform_set_vec4(shader shader, const char *name, const v4 val);
void uniform_set_mat4(shader shader, const char *name, const m4 val);

}  // namespace tom

#endif