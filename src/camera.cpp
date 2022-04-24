#include "camera.hpp"

namespace tom
{

internal m4 get_uvn(v3 target, v3 up, v3 pos)
{
    v3 n = vec::normalize(target);
    v3 u = vec::normalize(vec::cross(up, n));
    v3 v = vec::cross(n, u);

    m4 res = mat::row_3x3(u, v, n) * mat::translate(-pos);

    return res;
}

internal camera camera_init_angle(camera cam)
{
    v3 h_target = vec::normalize({ cam.target.x, 0.0f, cam.target.z });
    f32 angle   = math::to_degree(asin(abs(h_target.z)));

    if (h_target.z >= 0.0f) {
        if (h_target.x >= 0.0f)
            cam.angle_h = 360.0f - angle;
        else
            cam.angle_h = 180.0f + angle;
    } else {
        if (h_target.x >= 0.0f)
            cam.angle_h = angle;
        else
            cam.angle_h = 180.0f - angle;
    }

    cam.angle_v = -math::to_degree(asin(cam.target.y));

    return cam;
}

internal camera camera_default_init()
{
    camera res;

    res.speed   = 1.0f;
    res.angle_h = 0.0f;
    res.angle_v = 0.0f;
    res.pos     = { 0.0f, 0.0f, 0.0f };
    res.target  = { 0.0f, 0.0f, 1.0f };
    res.up      = { 0.0f, 1.0f, 0.0f };

    return res;
}

camera camera_init()
{
    camera res = camera_default_init();
    res        = camera_init_angle(res);
    return res;
}

camera camera_init(v3 pos, v3 target, v3 up)
{
    camera res = camera_default_init();

    res.pos = pos;
    // NOTE: can't assume passed in vectors are normalized
    res.target = vec::normalize(target);
    res.up     = vec::normalize(up);
    res        = camera_init_angle(res);

    return res;
}

void camera_move(camera &cam, const camera_mov_dir dir, const f32 dt, bool distance)
{
    f32 speed = cam.speed;
    if (distance) {
        speed = 1.0f;
    }

    switch (dir) {
        case camera_mov_dir::forward: {
            cam.pos += cam.target * speed * dt;
        } break;
        case camera_mov_dir::backward: {
            cam.pos -= cam.target * speed * dt;
        } break;
        case camera_mov_dir::up: {
            cam.pos.y += speed * dt;
        } break;
        case camera_mov_dir::down: {
            cam.pos.y -= speed * dt;
        } break;
        case camera_mov_dir::right: {
            v3 res = vec::cross(cam.up, cam.target);
            res    = vec::normalize(res);
            res *= speed * dt;
            cam.pos += res;

        } break;
        case camera_mov_dir::left: {
            v3 res = vec::cross(cam.target, cam.up);
            res    = vec::normalize(res);
            res *= speed * dt;
            cam.pos += res;
        } break;
        default: {
        } break;
    }
}

void camera_mouse_look(camera &cam, const input::mouse ms, const window_dims win_dims)
{
    v2 ms_delta = ms.get_delta();
    if (ms.pos.x < 0.0f || ms.pos.x > scast(f32, win_dims.width) || ms.pos.u < 0.0f ||
        ms.pos.y > scast(f32, win_dims.height))
        ms_delta = {};

    f32 angle_h = ms_delta.x / 20.0f;
    f32 angle_v = ms_delta.y / 20.0f;

    v3 n = vec::normalize(cam.target);
    v3 u = vec::normalize(vec::cross(cam.up, n));
    v3 v = vec::cross(n, u);

    if (input::is_key_down(ms.l)) {
        cam.target = qua::rotate(cam.target, u, angle_v);
        cam.target = qua::rotate(cam.target, cam.up, angle_h);
    }
    // cam.target = qua::rotate(cam.target, cam.up, 1.0f);
}

void camera_look_at(camera &cam, v3 target_pos, input::mouse ms, window_dims win_dims)
{
    v2 ms_delta = ms.get_delta();
    if (ms.pos.x < 0.0f || ms.pos.x > scast(f32, win_dims.width) || ms.pos.u < 0.0f ||
        ms.pos.y > scast(f32, win_dims.height))
        ms_delta = {};

    f32 d1 = vec::distance(cam.pos, target_pos);

    f32 mouse_sens  = 0.0005f / (1 / d1);
    f32 scroll_sens = 50.0f;

    // to keep a constant orbit

    if (input::is_key_down(ms.l)) {
        if (ms_delta.x > 0.0f) {
            f32 spd = abs(ms_delta.x) * mouse_sens;
            camera_move(cam, camera_mov_dir::left, spd);
        }

        if (ms_delta.x < 0.0f) {
            f32 spd = abs(ms_delta.x) * mouse_sens;
            camera_move(cam, camera_mov_dir::right, spd);
        }

        if (ms_delta.y > 0.0f) {
            f32 spd = abs(ms_delta.y) * mouse_sens;
            camera_move(cam, camera_mov_dir::up, spd);
        }

        if (ms_delta.y < 0.0f) {
            f32 spd = abs(ms_delta.y) * mouse_sens;
            camera_move(cam, camera_mov_dir::down, spd);
        }
    }
    printf("%d\n", ms.scroll);


    cam.target = vec::normalize(cam.pos - target_pos);
    f32 d2     = vec::distance(cam.pos, target_pos);
    // moved away
    if (d1 > d2) {
        camera_move(cam, camera_mov_dir::forward, d1 - d2, true);
    }
    // moved toward
    if (d1 < d2) {
        camera_move(cam, camera_mov_dir::backward, d2 - d1, true);
    }

    if (ms.scroll > 0) {
        f32 spd = scroll_sens * mouse_sens;
        camera_move(cam, camera_mov_dir::backward, spd);
    }

    if (ms.scroll < 0) {
        f32 spd = scroll_sens * mouse_sens;
        camera_move(cam, camera_mov_dir::forward, spd);
    }
}

m4 camera_get_view(const camera cam)
{
    m4 res = get_uvn(cam.target, cam.up, cam.pos);
    return res;
}
}  // namespace tom