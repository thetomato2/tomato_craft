#ifndef TOMATO_MODEL_HPP_
#define TOMATO_MODEL_HPP_

#include "common.hpp"
#include "mesh.hpp"
#include "opengl.hpp"

namespace tom
{
class model
{
public:
    model(ogl::wgl_func_ptrs gfx, const char *path); 

    void draw();

private:
    mesh _mesh;

    ogl::wgl_func_ptrs _gfx;
    
};

}  // namespace tom

#endif  // !TOMATO_MODEL_HPP_