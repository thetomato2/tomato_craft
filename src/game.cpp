#include "game.hpp"
#include "shader.hpp"

namespace tom
{
namespace game
{

internal void on_resize(game_state *state, window_dims win_dims)
{
    state->vp.proj =
        mat::proj_persp(scast(f32, win_dims.width) / scast(f32, win_dims.height), state->fov);
}

bool init(thread_context *thread, game_memory *memory)
{
    memory->ogl_func_ptrs.is_init = false;

    memory->ogl_func_ptrs.is_init =
        ogl::init_func_ptrs(&memory->ogl_func_ptrs, memory->plat_io.ogl_get_func_ptr);

    if (memory->ogl_func_ptrs.is_init) {
        printf("Loaded OpenGL function pointers!\n");
    } else {
        printf("ERROR-> Failed to load OpenGL function pointers!\n");
        INVALID_CODE_PATH;
    }

    ogl::wgl_func_ptrs gfx = memory->ogl_func_ptrs;

    TOM_ASSERT(sizeof(game_state) <= memory->permanent_storage_size);
    game_state *state = (game_state *)memory->permanent_storage;
    szt game_size     = sizeof(game_state);

    init_arena(&state->arena, memory->permanent_storage_size - game_size,
               (byt *)memory->permanent_storage + game_size);

    state->clear_color = { 0.2f, 0.3f, 0.3f, 1.0f };

    state->line_mode = false;

    const char *vert_path = "./main.vert";
    const char *frag_path = "./main.frag";

    state->camera = PUSH_STRUCT(&state->arena, camera);
    new (state->camera) camera();  // NOTE: placment new

    state->main_shader = PUSH_STRUCT(&state->arena, shader);
    new (state->main_shader)  // NOTE: placment new
        shader(&memory->ogl_func_ptrs, memory->plat_io, vert_path, frag_path);

    TOM_ASSERT(state->main_shader);

    ogl::enable(GL_DEPTH_TEST);

    // clang-format off
        f32 verts[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
        };
        
        s32 inds[36];
        for (s32 i = 0; i < ARRAY_COUNT(inds); ++i) {
            inds[i] = i;
        }

    // clang-format on

    u32 vbo, vao, ebo;
    gfx.gen_vert_arr(1, &vao);
    gfx.gen_buffers(1, &vbo);
    gfx.gen_buffers(1, &ebo);
    gfx.bind_vert_arr(vao);

    gfx.bind_buffer(GL_ARRAY_BUFFER, vbo);
    gfx.buffer_data(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    gfx.bind_buffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    gfx.buffer_data(GL_ELEMENT_ARRAY_BUFFER, sizeof(inds), inds, GL_STATIC_DRAW);

    // position attribute
    gfx.vertex_attrib_ptr(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    gfx.enable_vert_attrib_array(0);
    // texture coord attribute
    gfx.vertex_attrib_ptr(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    gfx.enable_vert_attrib_array(1);

    // load and create a texture
    // -------------------------
    u32 texture1;
    // texture 1
    // ---------
    ogl::gen_tex(1, &texture1);
    ogl::bind_tex(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    ogl::tex_params_s32(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    ogl::tex_params_s32(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    ogl::tex_params_s32(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    ogl::tex_params_s32(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    s32 width, height, n_channels;
    stbi_set_flip_vertically_on_load(true);
    byt *data = stbi_load("../../assets/images/win11.png", &width, &height, &n_channels, 0);
    if (data) {
        ogl::tex_img_2d(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                        data);
        gfx.gen_mipmap(GL_TEXTURE_2D);
    } else {
        printf("Failed to load texture\n");
        INVALID_CODE_PATH;
    }
    stbi_image_free(data);

    state->vbo    = vbo;
    state->ebo    = ebo;
    state->vao    = vao;
    state->text_1 = texture1;

    state->main_shader->use();
    state->main_shader->set_s32("our_texture", 0);

    state->fov = 1.0f;

    state->camera->pos.z = 10.0f;
    state->camera->speed = 5.0f;

    state->scaler = 1.0f;

    state->clear_color = { 0.2f, 0.3f, 0.3f, 1.0f };

    return true;
}

void update(thread_context *thread, game_memory *memory, game_input input, f32 dt)
{
    game_state *state = (game_state *)memory->permanent_storage;
    if (memory->win_resize || state->fov_old < state->fov - math::eps_f32 ||
        state->fov_old > state->fov + math::eps_f32) {
        on_resize(state, memory->win_dims);
        memory->win_resize = false;
    }

    ogl::wgl_func_ptrs gfx = memory->ogl_func_ptrs;

    if (state->line_mode) {
        ogl::poly_mode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        ogl::poly_mode(GL_FRONT_AND_BACK, GL_FILL);
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    ogl::clear_color(state->clear_color.r, state->clear_color.g, state->clear_color.b,
                     state->clear_color.a);
    ogl::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    gfx.active_tex(GL_TEXTURE0);
    ogl::bind_tex(GL_TEXTURE_2D, state->text_1);

    gfx.use_program(state->main_shader->get_id());

    {
        ImGui::Begin("Scene");
        ImGui::ColorEdit4("Clear", (f32 *)&state->clear_color.e[0]);
        ImGui::SliderFloat("fov", &state->fov, 0.01f, 2.0f);
        ImGui::SliderFloat3("model loc", &state->model_loc.e[0], -10.0f, 10.0f);
        ImGui::SliderAngle("x rot", &state->model_rot.x);
        ImGui::SliderAngle("y rot", &state->model_rot.y);
        ImGui::SliderAngle("z rot", &state->model_rot.z);
        ImGui::SliderFloat("scale", &state->scaler, 0.1f, 3.0f);
        ImGui::SliderInt("inds", &state->inds, 0, 12);
        ImGui::End();
    }

    {
        ImGui::Begin("Camera");
        ImGui::SliderFloat("x", &state->camera->pos.x, -100.0f, 100.0f);
        ImGui::SliderFloat("y", &state->camera->pos.y, -100.0f, 100.0f);
        ImGui::SliderFloat("z", &state->camera->pos.z, -100.0f, 100.0f);
        ImGui::SliderFloat("speed", &state->camera->speed, -100.0f, 100.0f);
        ImGui::End();
    }

    local_persist f32 time_total = 0.0f;
    time_total += dt * 0.01f;

    m4 model = mat::identity();
    model    = mat::translate(model, state->model_loc);
    model    = mat::rot_x(model, state->model_rot.x);
    model    = mat::rot_y(model, state->model_rot.y);
    model    = mat::rot_z(model, state->model_rot.z);
    model    = mat::scale(model, state->scaler);

    state->vp.view = state->camera->get_view();

    if (input::is_key_up(input.keyboard.d4)) {
        mat::print_m4(state->vp.view);
    }

    if (input::is_key_down(input.keyboard.w)) {
        state->camera->move(camera::mov_dir::backward, dt);
    }
    if (input::is_key_down(input.keyboard.s)) {
        state->camera->move(camera::mov_dir::forward, dt);
    }
    if (input::is_key_down(input.keyboard.a)) {
        state->camera->move(camera::mov_dir::left, dt);
    }
    if (input::is_key_down(input.keyboard.d)) {
        state->camera->move(camera::mov_dir::right, dt);
    }
    if (input::is_key_down(input.keyboard.z)) {
        state->camera->move(camera::mov_dir::down, dt);
    }
    if (input::is_key_down(input.keyboard.c)) {
        state->camera->move(camera::mov_dir::up, dt);
    }

    m4 vp = state->vp.proj * state->vp.view;

    state->main_shader->set_mat4("model", model);
    state->main_shader->set_mat4("vp", vp);

    // gfx.bind_vert_arr(state->vao);
    gfx.bind_buffer(GL_ARRAY_BUFFER, state->vbo);
    gfx.bind_buffer(GL_ELEMENT_ARRAY_BUFFER, state->ebo);
    // position attribute
    gfx.enable_vert_attrib_array(0);
    gfx.vertex_attrib_ptr(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    // texture coord attribute
    gfx.enable_vert_attrib_array(1);
    gfx.vertex_attrib_ptr(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));

    local_persist bool ele_sw = true;

    if (input::is_key_up(input.keyboard.d1)) {
        ele_sw = !ele_sw;
    }

    if (ele_sw)
        ogl::draw_arrays(GL_TRIANGLES, 0, 36);
    else
        ogl::draw_elements(GL_TRIANGLES, state->inds * 3, GL_UNSIGNED_INT, 0);

    gfx.disable_vert_attrib_array(0);
    gfx.disable_vert_attrib_array(1);
    ImGui::Render();
    // NOTE: this is where ImGui is drawn
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

// NOTE: clean up here
bool exit(thread_context *thread, game_memory *memory)
{
    return true;
}

}  // namespace game
}  // namespace tom