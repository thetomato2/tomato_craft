#include "game.hpp"

#include "imgui_style.h"

namespace tom
{
namespace game
{
#if 0
internal void render(game_state *state)
{
    local_persist bool is_init = false;

    if (!is_init) {
        g_line_mode = false;

        state->main_shader = std::make_unique<shader>("./main.vert", "./main.frag");
        TOM_ASSERT(state->main_shader);

        // clang-format off
        float vertices[] = {
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

        u32 vbo, vao;
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                              (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // load and create a texture
        // -------------------------
        u32 texture1;
        // texture 1
        // ---------
        glGenTextures(1, &texture1);
        glBindTexture(GL_TEXTURE_2D, texture1);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        s32 width, height, n_channels;
        stbi_set_flip_vertically_on_load(
            true);  // tell stb_image.h to flip loaded texture's on the y-axis.
        unsigned char *data =
            stbi_load("../../assets/images/win11.png", &width, &height, &n_channels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                         data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cout << "Failed to load texture\n";
            INVALID_CODE_PATH;
        }
        stbi_image_free(data);

        state->vbo    = vbo;
        state->vao    = vao;
        state->text_1 = texture1;

        state->main_shader->use();
        state->main_shader->set_s32("our_texture", 0);

        state->cam     = { glm::vec3(0.0f, 0.0f, 2.5f) };
        state->vp.view = glm::mat4(1.0f);
        state->vp.proj = glm::mat4(1.0f);
        state->vp.proj =
            glm::perspective(glm::radians(45.0f), (f32)g_width / (f32)g_height, 0.1f, 100.0f);

        g_size_changed = false;

        state->time_last = 0.0f;

        state->clear_color = { 0.2f, 0.3f, 0.3f, 1.0f };

        for (s32 i = 0; i < 100; ++i) {
            for (s32 j = 0; j < 100; ++j) {
                state->cube_pos.push_back(glm::vec3(scast(f32, i), scast(f32, j), 0.0f));
            }
        }

        std::cout << "Successfully initialized memory.\n";

        is_init = true;
    }

    if (g_size_changed) {
        g_size_changed = false;
    }

    if (g_line_mode) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    glClearColor(state->clear_color.r, state->clear_color.g, state->clear_color.b,
                 state->clear_color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, state->text_1);

    glUseProgram(state->main_shader->get_id());

    // TODO: pull this out somewhere?
    f32 time         = glfwGetTime();
    f32 dt           = time - state->time_last;
    state->time_last = time;

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

    state->main_shader->set_mat4("view", state->vp.view);
    state->main_shader->set_mat4("proj", state->vp.proj);

    glBindVertexArray(state->vao);

    for (auto v3 : state->cube_pos) {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), v3);
        state->main_shader->set_mat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    ImGui::Render();
    // NOTE: this is where ImGui is drawn
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(win);
}

#endif

bool init(thread_context *thread, game_memory *memory)
{
    return true;
}

void update(thread_context *thread, game_memory *memory, game_input input, f32 dt)
{
}

// NOTE: clean up here
bool exit(thread_context *thread, game_memory *memory)
{
    return true;
}

}  // namespace game
}  // namespace tom