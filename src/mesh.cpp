#include "mesh.hpp"
#include "vector.hpp"
#include "obj_loader.hpp"

namespace tom
{

mesh::mesh(ogl::wgl_func_ptrs gfx, platform_io plat_io, const char *path)
{
    _gfx  = gfx;
    _io   = plat_io;
    _path = path;

    load();
}

mesh::~mesh()
{
    _gfx.delete_buffers(1, &_pos_vb);
    _gfx.delete_buffers(1, &_uv_vb);
    _gfx.delete_vert_arr(1, &_vao);
}

void mesh::bind()
{
    // _gfx.bind_buffer(GL_ARRAY_BUFFER, _pos_vb);
    // _gfx.bind_buffer(GL_ARRAY_BUFFER, _uv_vb);
    // _gfx.bind_buffer(GL_ELEMENT_ARRAY_BUFFER, _ind_buf);
    _gfx.bind_vert_arr(_vao);
}

void mesh::unbind()
{
    _gfx.bind_vert_arr(0);
}

void mesh::load()
{
    small_vector<f32, 1024> vert_pos;
    small_vector<f32, 1024> vert_uv;
    small_vector<f32, 1024> vert_nrm;
    small_vector<s32, 256> inds;

    obj_loader *obj = new obj_loader(_io, _path);
    szt j           = 0;
    for (szt i = 0; i < obj->faces.size(); ++i) {
        vert_pos.push_back(obj->pos.data()[obj->faces.data()[i].v1.pos - 1].x);
        vert_pos.push_back(obj->pos.data()[obj->faces.data()[i].v1.pos - 1].y);
        vert_pos.push_back(obj->pos.data()[obj->faces.data()[i].v1.pos - 1].z);
        vert_uv.push_back(obj->uv.data()[obj->faces.data()[i].v1.uv - 1].u);
        vert_uv.push_back(obj->uv.data()[obj->faces.data()[i].v1.uv - 1].v);
        vert_nrm.push_back(obj->nrm.data()[obj->faces.data()[i].v1.nrm - 1].x);
        vert_nrm.push_back(obj->nrm.data()[obj->faces.data()[i].v1.nrm - 1].y);
        vert_nrm.push_back(obj->nrm.data()[obj->faces.data()[i].v1.nrm - 1].z);
        inds.push_back(j++);

        vert_pos.push_back(obj->pos.data()[obj->faces.data()[i].v2.pos - 1].x);
        vert_pos.push_back(obj->pos.data()[obj->faces.data()[i].v2.pos - 1].y);
        vert_pos.push_back(obj->pos.data()[obj->faces.data()[i].v2.pos - 1].z);
        vert_uv.push_back(obj->uv.data()[obj->faces.data()[i].v2.uv - 1].u);
        vert_uv.push_back(obj->uv.data()[obj->faces.data()[i].v2.uv - 1].v);
        vert_nrm.push_back(obj->nrm.data()[obj->faces.data()[i].v2.nrm - 1].x);
        vert_nrm.push_back(obj->nrm.data()[obj->faces.data()[i].v2.nrm - 1].y);
        vert_nrm.push_back(obj->nrm.data()[obj->faces.data()[i].v2.nrm - 1].z);
        inds.push_back(j++);

        vert_pos.push_back(obj->pos.data()[obj->faces.data()[i].v3.pos - 1].x);
        vert_pos.push_back(obj->pos.data()[obj->faces.data()[i].v3.pos - 1].y);
        vert_pos.push_back(obj->pos.data()[obj->faces.data()[i].v3.pos - 1].z);
        vert_uv.push_back(obj->uv.data()[obj->faces.data()[i].v3.uv - 1].u);
        vert_uv.push_back(obj->uv.data()[obj->faces.data()[i].v3.uv - 1].v);
        vert_nrm.push_back(obj->nrm.data()[obj->faces.data()[i].v3.nrm - 1].x);
        vert_nrm.push_back(obj->nrm.data()[obj->faces.data()[i].v3.nrm - 1].y);
        vert_nrm.push_back(obj->nrm.data()[obj->faces.data()[i].v3.nrm - 1].z);
        inds.push_back(j++);
    }

    _ind_cnt = inds.size();

    _gfx.gen_vert_arr(1, &_vao);
    _gfx.bind_vert_arr(_vao);

    _gfx.gen_buffers(1, &_pos_vb);
    _gfx.gen_buffers(1, &_uv_vb);
    _gfx.gen_buffers(1, &_nrm_vb);
    _gfx.gen_buffers(1, &_ind_buf);

    _gfx.bind_buffer(GL_ARRAY_BUFFER, _pos_vb);
    _gfx.buffer_data(GL_ARRAY_BUFFER, sizeof(f32) * vert_pos.size(), vert_pos.data(),
                     GL_STATIC_DRAW);
    _gfx.enable_vert_attrib_array(POS_LOC);
    _gfx.vertex_attrib_ptr(POS_LOC, 3, GL_FLOAT, GL_FALSE, 0, 0);

    _gfx.bind_buffer(GL_ARRAY_BUFFER, _uv_vb);
    _gfx.buffer_data(GL_ARRAY_BUFFER, sizeof(f32) * vert_uv.size(), vert_uv.data(), GL_STATIC_DRAW);
    _gfx.enable_vert_attrib_array(TEXCOORD_LOC);
    _gfx.vertex_attrib_ptr(TEXCOORD_LOC, 2, GL_FLOAT, GL_FALSE, 0, 0);

    _gfx.bind_buffer(GL_ARRAY_BUFFER, _nrm_vb);
    _gfx.buffer_data(GL_ARRAY_BUFFER, sizeof(f32) * vert_nrm.size(), vert_nrm.data(),
                     GL_STATIC_DRAW);
    _gfx.enable_vert_attrib_array(NRM_LOC);
    _gfx.vertex_attrib_ptr(NRM_LOC, 3, GL_FLOAT, GL_FALSE, 0, 0);

    _gfx.bind_buffer(GL_ELEMENT_ARRAY_BUFFER, _ind_buf);
    _gfx.buffer_data(GL_ELEMENT_ARRAY_BUFFER, sizeof(s32) * inds.size(), inds.data(),
                     GL_STATIC_DRAW);

    // NOTE: so the vao is not tampered with
    _gfx.bind_vert_arr(0);
}

}  // namespace tom