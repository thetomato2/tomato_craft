#ifndef TOMATO_TEXTURE_HPP_
#define TOMATO_TEXTURE_HPP_

#include "common.hpp"
#include "opengl.hpp"

namespace tom
{

class texture
{
public:
    enum class type
    {
        albedo,
        normal
    };

    texture();
    texture(texture::type type, GLenum texture_target, const char *path, ogl::wgl_func_ptrs gfx);
    void bind(GLenum tex_unit);

    const char *get_path() const { return _path; }
    const char is_active() const { return _active; }
    texture::type get_type() const { return _type; }

private:
    bool _active;
    texture::type _type;
    const char *_path;
    GLenum _tex_target;
    GLuint _tex_obj;
    ogl::wgl_func_ptrs _gfx;
};

}  // namespace tom

#endif
