#include "model.hpp"

namespace tom
{

model::model(ogl::wgl_func_ptrs gfx, platform_io plat_io, data_paths paths) :
    _mesh(gfx, plat_io, paths.mesh)
{
    _gfx  = gfx;
    _name = paths.name;
    color = {1.0f, 1.0f, 1.0f};

    if (paths.albedo) {
        load_tex(texture::type::albedo, paths.albedo);
    }
    if (paths.normal) {
        load_tex(texture::type::normal, paths.normal);
    }
}

void model::draw()
{
    if (_tex_alb.is_active()) _tex_alb.bind(GL_TEXTURE0);
    if (_tex_nrm.is_active()) _tex_alb.bind(GL_TEXTURE1);
    _mesh.bind();
    ogl::draw_elements(GL_TRIANGLES, _mesh.ind_cnt(), GL_UNSIGNED_INT, 0);
    _mesh.unbind();
}

void model::load_tex(texture::type type, const char *path)
{
    switch (type) {
        case texture::type::albedo: {
            new (&_tex_alb) texture(type, GL_TEXTURE_2D, path, _gfx);
        } break;
        case texture::type::normal: {
            new (&_tex_nrm) texture(type, GL_TEXTURE_2D, path, _gfx);
        } break;

        default: break;
    }
}
}  // namespace tom
