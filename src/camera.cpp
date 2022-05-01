#include "camera.hpp"

namespace tom
{

camera::camera()
{
    default_init();
    init_angle();
}

camera::camera(v3 pos, v3 target, v3 up)
{
    default_init();
    this->pos = pos;
    // NOTE: can't assume passed in vectors are normalized
    _target = vec::normalize(target);
    _up     = vec::normalize(up);
    init_angle();
}

void camera::init_angle()
{
    v3 h_target = vec::normalize({ _target.x, 0.0f, _target.z });
    f32 angle   = math::to_degree(asin(abs(h_target.z)));

    if (h_target.z >= 0.0f) {
        if (h_target.x >= 0.0f)
            _angle_h = 360.0f - angle;
        else
            _angle_h = 180.0f + angle;
    } else {
        if (h_target.x >= 0.0f)
            _angle_h = angle;
        else
            _angle_h = 180.0f - angle;
    }

    _angle_v = -math::to_degree(asin(_target.y));
}

void camera::default_init()
{
    speed       = 1.0f;
    _angle_h    = 0.0f;
    _angle_v    = 0.0f;
    pos         = { 0.0f, 0.0f, 0.0f };
    _up         = { 0.0f, 1.0f, 0.0f };
    _target     = { 0.0f, 0.0f, 1.0f };
    _target_pos = {};
}

void camera::move(const mov_dir dir, const f32 dt, bool distance)
{
    f32 new_speed = speed;
    if (distance) {
        new_speed = 1.0f;
    }

    switch (dir) {
        case mov_dir::forward: {
            pos += _target * new_speed * dt;
        } break;
        case mov_dir::backward: {
            pos -= _target * new_speed * dt;
        } break;
        case mov_dir::up: {
            pos.y += new_speed * dt;
        } break;
        case mov_dir::down: {
            pos.y -= new_speed * dt;
        } break;
        case mov_dir::right: {
            v3 res = vec::cross(_up, _target);
            res    = vec::normalize(res);
            res *= new_speed * dt;
            pos += res;

        } break;
        case mov_dir::left: {
            v3 res = vec::cross(_target, _up);
            res    = vec::normalize(res);
            res *= new_speed * dt;
            pos += res;
        } break;
        default: {
        } break;
    }
}

void camera::pan(const mov_dir dir, const f32 dt, bool distance)
{
    f32 new_speed = speed / 2.0f;
    if (distance) {
        new_speed = 1.0f;
    }

    switch (dir) {
        case mov_dir::forward: {
            pos += _target * new_speed * dt;
            _target_pos += _target * new_speed * dt;
        } break;
        case mov_dir::backward: {
            pos -= _target * new_speed * dt;
            _target_pos -= _target * new_speed * dt;
        } break;
        case mov_dir::up: {
            pos.y += new_speed * dt;
            _target_pos.y += new_speed * dt;
        } break;
        case mov_dir::down: {
            pos.y -= new_speed * dt;
            _target_pos.y -= new_speed * dt;
        } break;
        case mov_dir::right: {
            v3 res = vec::cross(_up, _target);
            res    = vec::normalize(res);
            res *= new_speed * dt;
            pos += res;
            _target_pos += res;

        } break;
        case mov_dir::left: {
            v3 res = vec::cross(_target, _up);
            res    = vec::normalize(res);
            res *= speed * dt;
            pos += res;
            _target_pos += res;
        } break;
        default: {
        } break;
    }
}

void camera::mouse_look(const input::mouse ms, const window_dims win_dims)
{
    v2 ms_delta = ms.get_delta();
    if (ms.pos.x < 0.0f || ms.pos.x > scast(f32, win_dims.width) || ms.pos.u < 0.0f ||
        ms.pos.y > scast(f32, win_dims.height))
        ms_delta = {};

    f32 angle_h = ms_delta.x / 20.0f;
    f32 angle_v = ms_delta.y / 20.0f;

    v3 n = vec::normalize(_target);
    v3 u = vec::normalize(vec::cross(_up, n));
    v3 v = vec::cross(n, u);

    if (input::is_key_down(ms.l)) {
        _target = qua::rotate(_target, u, angle_v);
        _target = qua::rotate(_target, _up, angle_h);
    }
    // cam.target = qua::rotate(cam.target, cam.up, 1.0f);
}

void camera::orbit(input::keyboard kb, input::mouse ms, window_dims win_dims, f32 *dist,
                   v3 *target_pos)
{
    if (target_pos) _target_pos = *target_pos;

    v2 ms_delta = ms.get_delta();
    if (ms.pos.x < 0.0f || ms.pos.x > scast(f32, win_dims.width) || ms.pos.u < 0.0f ||
        ms.pos.y > scast(f32, win_dims.height))
        ms_delta = {};

    f32 d1;
    if (dist) {
        d1 = *dist;
    } else {
        d1 = vec::distance(pos, _target_pos);
    }

    f32 mouse_sens  = 0.0005f / (1 / d1);
    f32 scroll_sens = 50.0f;

    // to keep a constant orbit

    if (input::is_key_down(ms.m)) {
        if (ms_delta.x > 0.0f) {
            f32 spd     = abs(ms_delta.x) * mouse_sens;
            mov_dir dir = mov_dir::left;
            input::is_key_down(kb.left_shift) ? pan(dir, spd) : move(dir, spd);
        }

        if (ms_delta.x < 0.0f) {
            f32 spd     = abs(ms_delta.x) * mouse_sens;
            mov_dir dir = mov_dir::right;
            input::is_key_down(kb.left_shift) ? pan(dir, spd) : move(dir, spd);
        }

        if (ms_delta.y > 0.0f) {
            f32 spd     = abs(ms_delta.y) * mouse_sens;
            mov_dir dir = mov_dir::up;
            input::is_key_down(kb.left_shift) ? pan(dir, spd) : move(dir, spd);
        }

        if (ms_delta.y < 0.0f) {
            f32 spd     = abs(ms_delta.y) * mouse_sens;
            mov_dir dir = mov_dir::down;
            input::is_key_down(kb.left_shift) ? pan(dir, spd) : move(dir, spd);
        }
    }
    _target = vec::normalize(pos - _target_pos);
    f32 d2  = vec::distance(pos, _target_pos);
    // moved away
    if (d1 > d2) {
        move(mov_dir::forward, d1 - d2, true);
    }
    // moved toward
    if (d1 < d2) {
        move(mov_dir::backward, d2 - d1, true);
    }
    if (ms.scroll > 0) {
        f32 spd = scroll_sens * mouse_sens;
        move(mov_dir::backward, spd);
    }

    if (ms.scroll < 0) {
        f32 spd = scroll_sens * mouse_sens;
        move(mov_dir::forward, spd);
    }
}

m4 camera::get_view()
{
    return mat::get_uvn(_target, _up, pos);
}
}  // namespace tom