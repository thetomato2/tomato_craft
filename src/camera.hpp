
#ifndef TOMATO_CAMERA_HPP_
#define TOMATO_CAMERA_HPP_

#include "common.hpp"
#include "math.hpp"
#include "input.hpp"

namespace tom
{
struct camera
{
    f32 speed;
    f32 angle_h;
    f32 angle_v;
    v2 mouse_pos;
    v3 pos;
    v3 target;
    v3 up;
};

enum class camera_mode
{
    look_at,
    fps
};

enum class camera_mov_dir
{
    forward,
    backward,
    up,
    down,
    right,
    left,
};

camera camera_init();
camera camera_init(v3 pos, v3 target, v3 up);
void camera_move(camera &cam, camera_mov_dir dir, f32 dt, bool distance = false);
void camera_mouse_look(camera &cam, input::mouse ms, window_dims win_dims);
void camera_look_at(camera &cam, v3 &target_pos, input::keyboard kb, input::mouse ms,
                    window_dims win_dims, f32 *dist = nullptr);
m4 camera_get_view(camera cam);

}  // namespace tom

#endif  // !TOMATO_CAMERA_HPP_