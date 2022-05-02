#include "mesh.hpp"

namespace tom
{

mesh::mesh(ogl::wgl_func_ptrs gfx, const char *path)
{
    _gfx  = gfx;
    _path = path;

    load();
}

mesh::~mesh()
{
    _gfx.delete_buffers(1, &_vbo);
    _gfx.delete_buffers(1, &_ebo);
    _gfx.delete_vert_arr(1, &_vao);
}

void mesh::bind()
{
    _gfx.bind_buffer(GL_ARRAY_BUFFER, _vbo);
    _gfx.bind_buffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    _gfx.bind_vert_arr(_vao);
}

void mesh::load()
{
    // TODO: obj/wavefront loader

    // clang-format off
        f32 verts[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
        };
        
        s32 inds[36];
        for (s32 i = 0; i < ARRAY_COUNT(inds); ++i) {
            inds[i] = i;
        }
        
        _ind_cnt = 36;

    // clang-format on

    _gfx.gen_vert_arr(1, &_vao);
    _gfx.gen_buffers(1, &_vbo);
    _gfx.gen_buffers(1, &_ebo);
    _gfx.bind_vert_arr(_vao);

    _gfx.bind_buffer(GL_ARRAY_BUFFER, _vbo);
    _gfx.buffer_data(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    _gfx.bind_buffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    _gfx.buffer_data(GL_ELEMENT_ARRAY_BUFFER, sizeof(inds), inds, GL_STATIC_DRAW);

    // position attribute
    _gfx.vertex_attrib_ptr(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    _gfx.enable_vert_attrib_array(0);
    // texture coord attribute
    _gfx.vertex_attrib_ptr(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                           (void *)(3 * sizeof(float)));
    _gfx.enable_vert_attrib_array(1);
}

}  // namespace tom