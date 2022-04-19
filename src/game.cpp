#include "game.hpp"
#include "shader.hpp"

#include "imgui_style.h"

namespace tom
{
namespace game
{

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

    state->main_shader = PUSH_STRUCT(&state->arena, shader);
    new (state->main_shader)  // NOTE: placment new
        shader(&memory->ogl_func_ptrs, memory->plat_io, vert_path, frag_path);

    TOM_ASSERT(state->main_shader);

    ogl::enable(GL_DEPTH_TEST);

    // clang-format off
        float verts[] = {
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
    // clang-format on

    // NOTE: this is stupid
    f32 *ptr_1 = &state->verts[0];
    f32 *ptr_2 = &verts[0];
    for (s32 i = 0; i < 180; ++i) {
        *ptr_1++ = *ptr_2++;
    }

    u32 vbo, vao;
    gfx.gen_vert_arr(1, &vao);
    gfx.gen_buffers(1, &vbo);
    gfx.bind_vert_arr(vao);

    gfx.bind_buffer(GL_ARRAY_BUFFER, vbo);
    gfx.buffer_data(GL_ARRAY_BUFFER, sizeof(state->verts), state->verts, GL_STATIC_DRAW);

    // position attribute
    gfx.vertex_attrib_ptr(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    gfx.enable_vertex_attrib_array(0);
    // texture coord attribute
    gfx.vertex_attrib_ptr(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    gfx.enable_vertex_attrib_array(1);

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
    state->vao    = vao;
    state->text_1 = texture1;

    state->main_shader->use();
    state->main_shader->set_s32("our_texture", 0);

    state->vp.view = mat::translate(mat::identity(), { 0.0f, 0.0f, -100.0f });

    state->vp.proj = mat::proj_persp(
        scast(f32, memory->win_dims.width) / scast(f32, memory->win_dims.height), 55.0f);

    state->clear_color = { 0.2f, 0.3f, 0.3f, 1.0f };

    return true;
}

void update(thread_context *thread, game_memory *memory, game_input input, f32 dt)
{
    game_state *state = (game_state *)memory->permanent_storage;

    ogl::wgl_func_ptrs gfx = memory->ogl_func_ptrs;

    // glClearColor(state->clear_color.r, state->clear_color.g, state->clear_color.b,
    //              state->clear_color.a);
    // ogl::draw_arrays(GL_TRIANGLES, 0, 3);

    if (state->line_mode) {
        ogl::poly_mode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        ogl::poly_mode(GL_FRONT_AND_BACK, GL_FILL);
    }

    // ImGui_ImplOpenGL3_NewFrame();
    // ImGui_ImplGlfw_NewFrame();
    // ImGui::NewFrame();

    ogl::clear_color(state->clear_color.r, state->clear_color.g, state->clear_color.b,
                     state->clear_color.a);
    ogl::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    gfx.active_tex(GL_TEXTURE0);
    ogl::bind_tex(GL_TEXTURE_2D, state->text_1);

    gfx.use_program(state->main_shader->get_id());

#if 0
    f32 rot  = (sin(time) / 2.0f) + 0.5f;
    f32 tran = (sin(time) / 2.0f);
    rot *= 5;

    constexpr f32 zoom_speed = 0.1f;
    local_persist f32 z_loc  = 10.0f;
    if (state->keyboard.w.ended_down) {
        state->cam.process_keyboard(camera_movement::forward, dt);
    } else if (state->keyboard.s.ended_down) {
        state->cam.process_keyboard(camera_movement::backward, dt);
    }
    if (state->keyboard.a.ended_down) {
        state->cam.process_keyboard(camera_movement::left, dt);
    } else if (state->keyboard.d.ended_down) {
        state->cam.process_keyboard(camera_movement::right, dt);
    }

    {
        ImGui::Begin("Blurp");
        ImGui::ColorEdit4("Clear", (f32 *)&state->clear_color[0]);
        ImGui::SliderFloat4("Cam Pos", (f32 *)&state->cam.position[0], -10.0f, 10.0f);
        ImGui::SliderFloat("Cam Zoom", &state->cam.zoom, 0.0f, 100.0f);
        ImGui::End();
    }

    constexpr f32 focal_speed   = 1.0f;
    local_persist f32 focal_len = 10.0f;

    f32 angle = 20.0f * time;
    // glm::mat4 model =
    //     glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(1.0f, 0.0f, 1.0f));
    state->vp.view = state->cam.get_view_matrix();

    state->vp.proj =
        glm::perspective(glm::radians(state->cam.zoom), (f32)g_width / (f32)g_height, 0.1f, 100.0f);
#endif

    local_persist f32 time_total = 0.0f;
    time_total += dt * 0.05f;

    m4 model = mat::identity();
    model    = model * mat::rot_x(45.0f);
    model    = model * mat::rot_z(45.0f * time_total);
    state->main_shader->set_mat4("model", model);
    state->main_shader->set_mat4("view", state->vp.view);
    state->main_shader->set_mat4("proj", state->vp.proj);

    gfx.bind_vert_arr(state->vao);
    ogl::draw_arrays(GL_TRIANGLES, 0, 36);

    // ImGui::Render();
    // // NOTE: this is where ImGui is drawn
    // ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

// NOTE: clean up here
bool exit(thread_context *thread, game_memory *memory)
{
    return true;
}

}  // namespace game
}  // namespace tom