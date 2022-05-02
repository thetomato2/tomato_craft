#include "model.hpp"

namespace tom
{

model::model(ogl::wgl_func_ptrs gfx, const char *path) : _mesh(gfx, path)
{
    _gfx = gfx;
}

void model::draw()
{
    _mesh.bind();
    ogl::draw_elements(GL_TRIANGLES, _mesh.ind_cnt(), GL_UNSIGNED_INT, 0);
}
}  // namespace tom
