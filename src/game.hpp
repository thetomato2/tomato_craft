#ifndef TOMATO_GAME_HPP_
#define TOMATO_GAME_HPP_

#include <stb_image.h>

#include "common.hpp"
#include "camera.hpp"
#include "input.hpp"
#include "opengl.hpp"
#include "shader.hpp"
#include "model.hpp"
#include "texture.hpp"
#include "obj_loader.hpp"
#include "vector.hpp"

namespace tom
{

namespace game
{
struct game_memory
{
    b32 is_initialized;
    b32 line_mode;

    u64 permanent_storage_size;
    void *permanent_storage;  // NOTE: required to be cleared to 0!

    u64 transient_storage_size;
    void *transient_storage;  // NOTE: required to be cleared to 0!

    platform_io plat_io;
    window_dims win_dims;
    b32 win_resize;

#if TOM_OPENGL
    ogl::wgl_func_ptrs ogl_func_ptrs;
#endif
};

struct game_input
{
    global_var constexpr u32 controller_cnt = 4;

    input::mouse mouse;
    input::keyboard keyboard;
    input::controller controllers[controller_cnt];
};

struct game_state
{
    memory_arena arena;
    bool running;
    bool line_mode;

    input::keyboard keyboard;
    // camera cam;
    input::mouse mouse;
    struct
    {
        m4 view;
        m4 proj;
    } vp;

    camera camera;
    f32 fov;
    f32 fov_old;
    f32 time_last;
    v4 clear_color;

    u32 text_1;
    shader main_shader;

    vector<model> models;

    texture tex1;
    texture tex2;

    f32 scaler;

    v3 model_loc;
    v3 model_rot;

    s32 max_cubes;
    s32 n_cubes;
    s32 n_cubes_z;
    m4 *matricies;
};

struct offscreen_buffer
{
    void *memory;
    s32 width;
    s32 height;
    s32 pitch;
    s32 bytes_per_pixel;
};

struct sound_output_buffer
{
    s32 samples_per_second;
    s32 sample_count;
    s16 *samples;
    s32 tone_hertz;
};

bool init(thread_context *thread, game_memory *memory);
void update(thread_context *thread, game_memory *memory, game_input input, f32 dt);
bool exit(thread_context *thread, game_memory *memory);

}  // namespace game
}  // namespace tom

#endif
