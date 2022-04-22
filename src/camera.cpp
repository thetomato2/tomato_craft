#include "camera.hpp"

namespace tom
{
camera::camera() :
    speed(1.0f), pos({ 0.0f, 0.0f, 0.0f }), target({ 0.0f, 0.0f, 1.0f }), up({ 0.0f, 1.0f, 0.0f })
{
}

camera::~camera()
{
}

void camera::move(const mov_dir dir, const f32 dt)
{
    switch (dir) {
        case mov_dir::forward: {
            pos += target * speed * dt;
        } break;
        case mov_dir::backward: {
            pos -= target * speed * dt;
        } break;
        case mov_dir::up: {
            pos.y += speed * dt;
        } break;
        case mov_dir::down: {
            pos.y -= speed * dt;
        } break;
        case mov_dir::right: {
            v3 res = vec::cross(up, target);
            res    = vec::normalize(res);
            res *= speed * dt;
            pos += res;

        } break;
        case mov_dir::left: {
            v3 res = vec::cross(target, up);
            res    = vec::normalize(res);
            res *= speed * dt;
            pos += res;
        } break;
        default: {
        } break;
    }
}

m4 camera::get_view() const
{
    m4 res = mat::cam_transform(target, up, pos);
    return res;
}

}  // namespace tom