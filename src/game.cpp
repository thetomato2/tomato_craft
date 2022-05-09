#include "game.hpp"

namespace tom
{
namespace game
{

internal void on_resize(game_state *state, window_dims win_dims)
{
    f32 aspect = scast(f32, win_dims.width) / scast(f32, win_dims.height);
    state->wvp.proj =
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

    state->line_mode = false;

    new (&state->obj_shader)
        shader(&memory->ogl_func_ptrs, memory->plat_io, "./main.vert", "./main.frag");
    new (&state->light_shader)
        shader(&memory->ogl_func_ptrs, memory->plat_io, "./light.vert", "./light.frag");

    new (&state->cam_main) camera();
    new (&state->cam2) camera();

    gfx.enable(GL_DEPTH_TEST);

    model::data_paths cube_paths = { .name   = "cube",
                                     .mesh   = "../../../assets/mesh/cube.obj",
                                     .albedo = nullptr,
                                     .normal = nullptr };

    model::data_paths cone_paths = { .name   = "cone",
                                     .mesh   = "../../../assets/mesh/cone.obj",
                                     .albedo = nullptr,
                                     .normal = nullptr };

    model::data_paths sphere_paths = { .name   = "sphere",
                                       .mesh   = "../../../assets/mesh/sphere.obj",
                                       .albedo = nullptr,
                                       .normal = nullptr };

    model::data_paths tomato_paths = { .name   = "tomato",
                                       .mesh   = "../../../assets/mesh/tomato.obj",
                                       .albedo = "../../../assets/images/tomato.png",
                                       .normal = nullptr };

    model::data_paths monkey_paths = { .name   = "monkey",
                                       .mesh   = "../../../assets/mesh/monkey.obj",
                                       .albedo = "../../../assets/images/pika.png",
                                       .normal = nullptr };

    model::data_paths elf_paths = { .name   = "elf",
                                    .mesh   = "../../../assets/mesh/elf.obj",
                                    .albedo = "../../../assets/images/skin.png",
                                    .normal = nullptr };

    // FIXME: the memory block gets cleared (in the platform layer????) and probably leaks the
    // original models vector data block
    // NOTE: manually call the desctuctor!! duh, but still there has to be a better way
    // otherwise why bother with a dedicated memory block
    state->models.~vector();
    state->lights.~vector();
    new (&state->models) vector<model>();
    new (&state->lights) vector<light>();

    state->models.emplace_back(gfx, memory->plat_io, cone_paths);
    state->models.emplace_back(gfx, memory->plat_io, cube_paths);
    state->models.emplace_back(gfx, memory->plat_io, sphere_paths);
    // state->models.emplace_back(gfx, memory->plat_io, elf_paths);
    // state->models.emplace_back(gfx, memory->plat_io, tomato_paths);
    // state->models.emplace_back(gfx, memory->plat_io, monkey_paths);

    state->models[0].color = { 1.0, 0.0f, 0.0f };
    state->models[1].color = { 0.0, 1.0f, 0.0f };
    state->models[2].color = { 0.0, 0.0f, 1.0f };

    state->lights.emplace_back(gfx, memory->plat_io, sphere_paths.mesh);
#if Z_UP
    state->lights[0].pos.z = 5.0f;
    state->cam_pos.y       = -10.0f;
#else
    state->lights[0].pos.y = 5.0f;
    state->cam_pos.z       = 10.0f;
#endif
    state->fov = 1.0f;

    state->cam_main.set_pos(state->cam_pos);
    state->cam_main.speed = 5.0f;

    f32 tp          = 10.0f;
    state->cam2_pos = { -tp, -tp, tp };
    state->cam2.set_pos(state->cam2_pos);
    state->cam2.orbit(state->keyboard, state->mouse, memory->win_dims, nullptr, {});

    state->cur_cam = 1;

    state->scaler = 1.0f;
    state->spec   = 32.0f;

    state->max_cubes = 100;
    state->n_cubes   = 1;
    state->n_cubes_z = 1;

    state->clear_color = { 0.1f, 0.1f, 0.1f, 1.0f };

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
        gfx.poly_mode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        gfx.poly_mode(GL_FRONT_AND_BACK, GL_FILL);
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    gfx.clear_color(state->clear_color.r, state->clear_color.g, state->clear_color.b,
                    state->clear_color.a);
    gfx.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (input::is_key_up(input.keyboard.t)) state->line_mode = !state->line_mode;

    {
        ImGui::Begin("Scene");
        ImGui::SliderFloat("fov", &state->fov, 0.01f, 3.0f);
        ImGui::ColorEdit4("Clear", (f32 *)&state->clear_color.e[0]);
        ImGui::ColorEdit3("Light", (f32 *)&state->lights[0].color.e[0]);
        ImGui::SliderFloat3("light loc", &state->lights[0].pos.e[0], -10.0f, 10.0f);
        ImGui::SliderFloat("spec", &state->spec, 1.0f, 256.0f);
        // ImGui::SliderFloat3("model loc", &state->model_loc.e[0], -10.0f, 10.0f);
        // ImGui::SliderAngle("x rot", &state->model_rot.x);
        // ImGui::SliderAngle("y rot", &state->model_rot.y);
        // ImGui::SliderAngle("z rot", &state->model_rot.z);
        // ImGui::SliderFloat("scale", &state->scaler, 0.1f, 3.0f);
        ImGui::End();
    }

    state->cam_pos = state->cam_main.get_pos();
    {
        ImGui::Begin("Camera");
        ImGui::SliderFloat("x", &state->cam_pos.x, -100.0f, 100.0f);
        ImGui::SliderFloat("y", &state->cam_pos.y, -100.0f, 100.0f);
        ImGui::SliderFloat("z", &state->cam_pos.z, -100.0f, 100.0f);
        ImGui::SliderFloat("speed", &state->cam_main.speed, -100.0f, 100.0f);
        ImGui::End();
    }
    state->cam_main.set_pos(state->cam_pos);

    local_persist f32 time_total = 0.0f;
    time_total += dt * 0.01f;

    if (input::is_key_up(input.keyboard.d4)) {
        mat::print_m4(state->wvp.view);
    }

    if (input::is_key_up(input.keyboard.d1)) {
        state->cur_cam = 1;
    }
    if (input::is_key_up(input.keyboard.d2)) {
        state->cur_cam = 2;
    }

    if (state->cur_cam == 1) {
        if (input::is_key_up(input.keyboard.z)) {
            f32 dist      = (scast(f32, state->n_cubes) * 0.9f) + 1.0f;
            v3 target_pos = { scast(f32, state->n_cubes / 2), scast(f32, state->n_cubes_z / 2),
                              scast(f32, state->n_cubes / 2) };
            state->cam_main.orbit(input.keyboard, input.mouse, memory->win_dims, &dist,
                                  &target_pos);
        } else {
            state->cam_main.orbit(input.keyboard, input.mouse, memory->win_dims);
        }
    }

#if Z_UP
    state->wvp.world = mat::y_up_to_z_up();
#else
    state->wvp.world       = mat::identity();
#endif
    camera *cam;
    switch (state->cur_cam) {
        case 1: {
            cam = &state->cam_main;
        } break;
        case 2: {
            cam = &state->cam2;
        } break;
        default: {
            cam = &state->cam_main;
        }
    }

    state->wvp.view = cam->get_view();
    m4 wvp          = state->wvp.proj * state->wvp.view * state->wvp.world;

    local_persist constexpr f32 model_x_increment = 3.0f;

    light *light = &state->lights[0];
    m4 light_m4  = mat::translate(light->pos);
    light_m4     = mat::scale(light_m4, 0.5f);
    state->light_shader.use();
    state->light_shader.set_m4("model", light_m4);
    state->light_shader.set_m4("wvp", wvp);
    state->light_shader.set_v3("light_col", light->color);
    light->draw();

    state->obj_shader.use();
    state->obj_shader.set_m4("wvp", wvp);
    state->obj_shader.set_m4("model", light_m4);
    state->obj_shader.set_f32("shiny", state->spec);
    state->obj_shader.set_v3("view_pos", cam->get_pos());
    state->obj_shader.set_v3("light_col", light->color);
    state->obj_shader.set_v3("light_pos", light->pos);

    f32 cur_x = -model_x_increment;

    for (auto &ml : state->models) {
        m4 model_m4 = mat::translate({ cur_x, 0.0f, 0.0f });
        cur_x += model_x_increment;

        state->obj_shader.set_m4("model", model_m4);
        state->obj_shader.set_v3("obj_col", ml.color);

        ml.draw();
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