#ifndef TOMATO_OBJ_LOADER_HPP_
#define TOMATO_OBJ_LOADER_HPP_

#include "core.hpp"
#include "vector.hpp"

namespace tom
{

struct vert_ind
{
    s32 pos;
    s32 nrm;
    s32 uv;
};

struct face_inds
{
    vert_ind v1;
    vert_ind v2;
    vert_ind v3;
};

struct obj_loader
{
    obj_loader(platform_io plat_io, const char *path);

    char name[1024];

    small_vector<v3, 1024> pos;
    small_vector<v2, 1024> uv;
    small_vector<v3, 1024> nrm;
    small_vector<face_inds, 1024> faces;
};

}  // namespace tom

#endif