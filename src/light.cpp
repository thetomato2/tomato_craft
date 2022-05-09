#include "light.hpp"

namespace tom
{

light::light(ogl::wgl_func_ptrs gfx, platform_io plat_io, const char *mesh_path) :
    active(true),
    pos({ 0.0f, 0.0f, 0.0f }),
    color({ 1.0f, 1.0f, 1.0f }),
    _gfx(gfx),
    _mesh(gfx, plat_io, mesh_path)
{
}

void light::draw()
{
    _mesh.bind();
    _gfx.draw_elements(GL_TRIANGLES, _mesh.ind_cnt(), GL_UNSIGNED_INT, 0);
    _mesh.unbind();
}
}  // namespace tom