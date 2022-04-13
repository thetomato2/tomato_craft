#ifndef TOM_CAMERA_HPP_
#define TOM_CAMERA_HPP_

#include "common.hpp"

namespace tom
{
// Defines several possible options for camera movement. Used as abstraction to stay away from
// window-system specific input methods
enum camera_movement
{
    forward,
    backward,
    left,
    right
};

// Default camera values
constexpr f32 def_yaw     = -90.0f;
constexpr f32 def_pitch   = 0.0f;
constexpr f32 def_speed   = 2.5f;
constexpr f32 def_sens    = 0.1f;
constexpr f32 def_zoom    = 45.0f;
constexpr f32 scroll_sens = 2.0f;

#if 0
// An abstract camera class that processes input and calculates the corresponding Euler Angles,
// Vectors and Matrices for use in OpenGL
class camera
{
public:
    // camera Attributes
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 world_up;

    // euler Angles
    f32 yaw;
    f32 pitch;
    // camera options
    f32 mov_speed;
    f32 mouse_sens;
    f32 zoom;

    // constructor with vectors
    camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), f32 yaw = def_yaw, f32 pitch = def_pitch) :
        front(glm::vec3(0.0f, 0.0f, -1.0f)),
        mov_speed(def_speed),
        mouse_sens(def_sens),
        zoom(def_zoom)
    {
        this->position = position;
        this->world_up = up;
        this->yaw      = yaw;
        this->pitch    = pitch;
        update_camera_vectors();
    }
    // constructor with scalar values
    camera(f32 pos_x, f32 pos_y, f32 pos_z, f32 up_x, f32 up_y, f32 up_z, f32 yaw, f32 pitch) :
        front(glm::vec3(0.0f, 0.0f, -1.0f)), mov_speed(def_speed), mouse_sens(def_sens), zoom(zoom)
    {
        position = glm::vec3(pos_x, pos_y, pos_z);
        world_up = glm::vec3(up_x, up_y, up_z);
        yaw      = yaw;
        pitch    = pitch;
        update_camera_vectors();
    }

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 get_view_matrix() { return glm::lookAt(position, position + front, up); }
    glm::mat4 get_view_matrix(glm::vec3 look_at_pos)
    {
        return glm::lookAt(position, look_at_pos + front, up);
    }

    // processes input received from any keyboard-like input system. Accepts input parameter in the
    // form of camera defined ENUM (to abstract it from windowing systems)
    void process_keyboard(camera_movement dir, f32 dt)
    {
        f32 vel = mov_speed * dt;
        if (dir == camera_movement::forward) position += front * vel;
        if (dir == camera_movement::backward) position -= front * vel;
        if (dir == camera_movement::left) position -= right * vel;
        if (dir == camera_movement::right) position += right * vel;
    }

    // processes input received from a mouse input system. Expects the offset value in both the x
    // and y direction.
    void process_mouse_movement(f32 x_off, f32 y_off, bool constrain_pitch = true)
    {
        x_off *= mouse_sens;
        y_off *= mouse_sens;

        yaw += x_off;
        pitch += y_off;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrain_pitch) {
            if (pitch > 89.0f) pitch = 89.0f;
            if (pitch < -89.0f) pitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        update_camera_vectors();
    }

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical
    // wheel-axis
    void process_mouse_scroll(f32 y_off)
    {
        zoom -= (f32)y_off * scroll_sens;
        zoom = math::bounds(zoom, 1.0f, 110.0f);
    }

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void update_camera_vectors()
    {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front   = glm::normalize(front);
        // also re-calculate the Right and Up vector
        right = glm::normalize(glm::cross(
            front, world_up));  // normalize the vectors, because their length gets closer to 0 the
                                // more you look up or down which results in slower movement.
        up = glm::normalize(glm::cross(right, front));
    }
};

#endif
}  // namespace tom

#endif
