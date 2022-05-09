#pragma once
#ifndef TOMATO_LIGHT_HPP_
#define TOMATO_LIGHT_HPP_

#include "core.hpp"
#include "opengl.hpp"
#include "mesh.hpp"

namespace tom
{
class light
{
public:
    // TODO: more light stuff
    bool active;
    f32 spec_strength;
    v3 pos;
    v3 color;

    light(ogl::wgl_func_ptrs gfx, platform_io plat_io, const char *mesh_path);

    // NOTE: for the model specificily
    void draw();

private:
    ogl::wgl_func_ptrs _gfx;
    mesh _mesh;
};

}  // namespace tom

#endif  // ! TOMATO_LIGHT_HPP_