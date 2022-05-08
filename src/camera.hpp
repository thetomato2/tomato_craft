
#ifndef TOMATO_CAMERA_HPP_
#define TOMATO_CAMERA_HPP_

#include "core.hpp"
#include "input.hpp"

namespace tom
{

class camera
{
public:
    f32 speed;

    enum class mode
    {
        look_at,
        fps
    };

    enum class mov_dir
    {
        forward,
        backward,
        up,
        down,
        right,
        left,
    };

    camera();
    camera(v3 pos, v3 target, v3 up);
    ~camera();

    void move(mov_dir dir, f32 dt, bool distance = false);
    void mouse_look(input::mouse ms, window_dims win_dims);
    void orbit(input::keyboard kb, input::mouse ms, window_dims win_dims, f32 *dist = nullptr,
               v3 *target_pos = nullptr);
    void pan(mov_dir dir, f32 dt, bool distance = false);

    m4 get_view();
    v3 get_pos() const;
    void set_pos(v3 pos);

    // void mode(const camera::mode mode) { _mode = mode; }

private:
    // NOTE: in open_gl coords
    v3 _pos;
    f32 _angle_h;
    f32 _angle_v;
    v2 _mouse_pos;
    v3 _up;
    v3 _target;
    v3 _target_pos;
    // camera::mode _mode;

    void init_angle();
    void default_init();
};

}  // namespace tom

#endif  // !TOMATO_CAMERA_HPP_