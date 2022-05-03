#include "game.hpp"

namespace tom
{
namespace game
{

internal void on_resize(game_state *state, window_dims win_dims)
{
    f32 aspect = scast(f32, win_dims.width) / scast(f32, win_dims.height);
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
    new (&state->main_shader) shader(&memory->ogl_func_ptrs, memory->plat_io, vert_path, frag_path);

    new (&state->camera) camera();

    ogl::enable(GL_DEPTH_TEST);

    model::data_paths cube_paths = { .name   = "cube",
                                     .mesh   = "../../../assets/mesh/cube.obj",
                                     .albedo = "../../../assets/images/red.png",
                                     .normal = nullptr };

    model::data_paths cone_paths = { .name   = "cone",
                                     .mesh   = "../../../assets/mesh/cone.obj",
                                     .albedo = "../../../assets/images/green.png",
                                     .normal = nullptr };

    model::data_paths sphere_paths = { .name   = "sphere",
                                     .mesh   = "../../../assets/mesh/sphere.obj",
                                     .albedo = "../../../assets/images/blue.png",
                                     .normal = nullptr };

    model::data_paths tomato_paths = { .name   = "tomato",
                                       .mesh   = "../../../assets/mesh/tomato.obj",
                                       .albedo = "../../../assets/images/tomato.png",
                                       .normal = nullptr };

    model::data_paths monkey_paths = { .name   = "monkey",
                                       .mesh   = "../../../assets/mesh/monkey.obj",
                                       .albedo = "../../../assets/images/pika.png",
                                       .normal = nullptr };

    // FIXME: the memory block gets cleard and probably leaks the original models vector
    new (&state->models) vector<model>();

    state->models.emplace_back(gfx, memory->plat_io, cube_paths);
    state->models.emplace_back(gfx, memory->plat_io, cone_paths);
    state->models.emplace_back(gfx, memory->plat_io, sphere_paths);
    state->models.emplace_back(gfx, memory->plat_io, tomato_paths);
    state->models.emplace_back(gfx, memory->plat_io, monkey_paths);

    state->main_shader.use();
    state->main_shader.set_s32("our_texture", 0);

    state->fov = 1.0f;

    state->camera.pos.z = 10.0f;
    state->camera.speed = 5.0f;

    state->scaler = 1.0f;

    state->max_cubes = 100;
    state->n_cubes   = 1;
    state->n_cubes_z = 1;

    state->clear_color = { 0.2f, 0.3f, 0.3f, 1.0f };

    s32 total_cubes  = math::cube(state->max_cubes);
    state->matricies = (m4 *)push_size(&state->arena, sizeof(m4) * total_cubes);

    s32 n_tex_units = 0;
    ogl::get_int4(GL_MAX_TEXTURE_UNITS, &n_tex_units);
    printf("Max Texture Units: %d\n", n_tex_units);

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

    if (input::is_key_up(input.keyboard.d2)) state->line_mode = !state->line_mode;

    state->main_shader.use();

    {
        ImGui::Begin("Scene");
        ImGui::ColorEdit4("Clear", (f32 *)&state->clear_color.e[0]);
        ImGui::SliderFloat("fov", &state->fov, 0.01f, 3.0f);
        ImGui::SliderFloat3("model loc", &state->model_loc.e[0], -10.0f, 10.0f);
        ImGui::SliderAngle("x rot", &state->model_rot.x);
        ImGui::SliderAngle("y rot", &state->model_rot.y);
        ImGui::SliderAngle("z rot", &state->model_rot.z);
        ImGui::SliderFloat("scale", &state->scaler, 0.1f, 3.0f);
        ImGui::SliderInt("num cubes", &state->n_cubes, 1, 100);
        ImGui::SliderInt("num cubes z", &state->n_cubes_z, 1, 100);
        ImGui::End();
    }

    {
        ImGui::Begin("Camera");
        ImGui::SliderFloat("x", &state->camera.pos.x, -100.0f, 100.0f);
        ImGui::SliderFloat("y", &state->camera.pos.y, -100.0f, 100.0f);
        ImGui::SliderFloat("z", &state->camera.pos.z, -100.0f, 100.0f);
        ImGui::SliderFloat("speed", &state->camera.speed, -100.0f, 100.0f);
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

    if (input::is_key_up(input.keyboard.d4)) {
        mat::print_m4(state->vp.view);
    }

    if (input::is_key_up(input.keyboard.z)) {
        f32 dist      = (scast(f32, state->n_cubes) * 0.9f) + 1.0f;
        v3 target_pos = { scast(f32, state->n_cubes / 2), scast(f32, state->n_cubes_z / 2),
                          scast(f32, state->n_cubes / 2) };
        state->camera.orbit(input.keyboard, input.mouse, memory->win_dims, &dist, &target_pos);
    } else {
        state->camera.orbit(input.keyboard, input.mouse, memory->win_dims);
    }

    state->vp.view = state->camera.get_view();
    m4 vp          = state->vp.proj * state->vp.view;

    state->main_shader.set_m4("vp", vp);

    for (auto &ml : state->models) {
        state->main_shader.set_m4("model", model);
        ml.draw();
        model = mat::translate(model, { 3.0f, 0.0f, 0.0f });
    }

    ImGui::Render();
    // NOTE: this is where ImGui is drawn
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

// NOTE: clean up here
bool exit(thread_context *thread, game_memory *memory)
{
    game_state *state = (game_state *)memory->permanent_storage;

    return true;
}

}  // namespace game
}  // namespace tom