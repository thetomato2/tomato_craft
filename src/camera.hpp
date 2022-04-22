
#ifndef TOMATO_CAMERA_HPP_
#define TOMATO_CAMERA_HPP_

#include "common.hpp"
#include "math.hpp"

namespace tom
{
struct camera
{
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
    ~camera();

    void move(mov_dir dir, f32 dt);

    m4 get_view() const;

    f32 speed;
    v3 pos;
    v3 target;
    v3 up;
};

}  // namespace tom

#endif  // !TOMATO_CAMERA_HPP_