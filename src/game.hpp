#ifndef TOMATO_GAME_HPP_
#define TOMATO_GAME_HPP_
#include <stb_image.h>

#include "common.hpp"
#include "shader.hpp"
// #include "camera.hpp"
#include "input.hpp"
#include "opengl.hpp"

namespace tom
{

struct read_file_result
{
    szt content_size;
    void *contents;
};

using platform_free_file_memory  = void (*)(thread_context *, void *);
using platform_read_entire_file  = read_file_result (*)(thread_context *, const char *);
using platform_write_entire_file = b32 (*)(thread_context *, const char *, u64, void *);

#if TOM_OPENGL
using platform_get_ogl_func_ptr = void *(*)(const char *);
#endif

namespace game
{
struct game_memory
{
    bool is_initialized;
    u64 permanent_storage_size;
    void *permanent_storage;  // NOTE: required to be cleared to 0!

    u64 transient_storage_size;
    void *transient_storage;  // NOTE: required to be cleared to 0!

    platform_free_file_memory platform_free_file_memory;
    platform_read_entire_file platform_read_entire_file;
    platform_write_entire_file platform_write_entire_file;

#if TOM_OPENGL
    platform_get_ogl_func_ptr ogl_get_func_ptr;
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
    bool g_running;
    bool g_line_mode;

    input::keyboard keyboard;
    // camera cam;
    input::mouse mouse;
    struct
    {
        m4 view;
        m4 proj;
    } vp;

    f32 time_last;

    v4 clear_color;
    u32 vbo, vao, ebo, text_1;

    shader main_shader;
    f32 verts[6];
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
