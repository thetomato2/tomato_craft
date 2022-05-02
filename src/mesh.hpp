#ifndef TOMATO_MESH_HPP_
#define TOMATO_MESH_HPP_

#include "common.hpp"
#include "math.hpp"
#include "opengl.hpp"

#define POS_LOC 0
#define TEX_COORD_LOC 1
#define NRM_LOC 2

namespace tom
{

class mesh
{
public:
    v3 origin;

    mesh(ogl::wgl_func_ptrs gfx, const char *path);
    ~mesh();

    void bind();

    u32 ind_cnt() const { return _ind_cnt; }

private:
    enum class buffer_type{
        index = 0,
        posistion,
        texcoord,
        normal,
    } ;


    u32 _vbo, _vao, _ebo;
    u32 _ind_cnt;
    const char* _path;

    void load();

    ogl::wgl_func_ptrs _gfx;
};

}  // namespace tom

#endif