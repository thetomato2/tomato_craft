#pragma once
#ifndef TOMATO_MESH_HPP_
#define TOMATO_MESH_HPP_

#include "core.hpp"
#include "opengl.hpp"

#define POS_LOC      0
#define TEXCOORD_LOC 1
#define NRM_LOC      2

namespace tom
{

class mesh
{
public:
    v3 origin;

    mesh(ogl::wgl_func_ptrs gfx, platform_io plat_io, const char *path);
    ~mesh();

    void bind();
    void unbind();

    u32 ind_cnt() const { return _ind_cnt; }
    u32 vert_cnt() const { return _vert_cnt; }

private:
    u32 _vao;
    u32 _pos_vb;
    u32 _uv_vb;
    u32 _nrm_vb;
    u32 _ind_buf;

    u32 _ind_cnt;
    u32 _vert_cnt;

    const char *_path;

    void load();

    ogl::wgl_func_ptrs _gfx;
    platform_io _io;
};

}  // namespace tom

#endif