#ifndef TOMATO_MODEL_HPP_
#define TOMATO_MODEL_HPP_

#include "common.hpp"
#include "opengl.hpp"
#include "mesh.hpp"
#include "texture.hpp"

namespace tom
{

// TODO: add normal, spec, rough, etc... textures
class model
{
public:
    v3 color;

    struct data_paths
    {
        const char *name;
        const char *mesh;
        const char *albedo;
        const char *normal;
    };

    model(ogl::wgl_func_ptrs gfx, platform_io plat_io, data_paths paths);

    void draw();

    const char *name() const { return _name; }

private:
    const char *_name;
    mesh _mesh;
    texture _tex_alb;
    texture _tex_nrm;
    ogl::wgl_func_ptrs _gfx;

    void load_tex(texture::type type, const char *path);
};

}  // namespace tom

#endif  // !TOMATO_MODEL_HPP_