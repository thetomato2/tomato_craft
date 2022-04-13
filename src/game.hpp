#ifndef TOMATO_GAME_HPP_
#define TOMATO_GAME_HPP_
#include <stb_image.h>

#include "common.hpp"
// #include "shader.hpp"
// #include "camera.hpp"
#include "input.hpp"

namespace tom
{

#ifdef TOM_INTERNAL
typedef struct debug_read_file_result
{
    u32 content_size;
    void *contents;
} debug_read_file_result;

    #define DEBUG_PLATFORM_FREE_FILE_MEMORY(name) void name(thread_context *thread, void *memory)
typedef DEBUG_PLATFORM_FREE_FILE_MEMORY(debug_platform_free_file_memory);

    #define DEBUG_PLATFORM_READ_ENTIRE_FILE(name) \
        debug_read_file_result name(thread_context *thread, const char *file_name)
typedef DEBUG_PLATFORM_READ_ENTIRE_FILE(debug_platform_read_entire_file);

    #define DEBUG_PLATFORM_WRITE_ENTIRE_FILE(name) \
        b32 name(thread_context *thread, const char *file_name, u64 memory_size, void *memory)
typedef DEBUG_PLATFORM_WRITE_ENTIRE_FILE(debug_platform_write_entire_file);
#endif

namespace game
{


typedef struct game_memory
{
    bool is_initialized;
    u64 permanent_storage_size;
    void *permanent_storage;  // NOTE: required to be cleared to 0!

    u64 transient_storage_size;
    void *transient_storage;  // NOTE: required to be cleared to 0!

#ifdef TOM_INTERNAL
    debug_platform_free_file_memory *platform_free_file_memory;
    debug_platform_read_entire_file *platform_read_entire_file;
    debug_platform_write_entire_file *platform_write_entire_file;
#endif
} game_memory;

struct game_input
{
    global_var constexpr u32 controller_cnt = 4;

    input::mouse mouse;
    input::keyboard keyboard;
    input::controller controllers[controller_cnt];
};

struct game_state
{
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

    m4 clear_color;
    u32 vbo, vao, ebo, text_1;
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
