#include "state.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

extern Window window;
extern Renderer renderer;
extern Camera camera;
extern Game game;

static void link_camera_gfx(void) 
{
    camera.aspect_ratio = (float) window.size.x / window.size.y;
    camera.viewID = renderer_uniform_location("view");
    camera.projID = renderer_uniform_location("proj");
    camera_update_view();
    camera_update_proj();
}

static void link_camera_game(void)
{
    game.rotation = camera.yaw;
    game.view_angle = camera.pitch;
}

static void process_input(void)
{
    i32 rotation_magnitude = 0;
    vec2i move_direction = vec2i_create(0, 0);
    if (window_key_pressed(GLFW_KEY_ESCAPE))
        window_close();
    if (window_key_pressed(GLFW_KEY_Q))
        rotation_magnitude++;
    if (window_key_pressed(GLFW_KEY_E))
        rotation_magnitude--;
    if (window_key_pressed(GLFW_KEY_W))
        move_direction.x++;
    if (window_key_pressed(GLFW_KEY_S))
        move_direction.x--;
    if (window_key_pressed(GLFW_KEY_A))
        move_direction.y--;
    if (window_key_pressed(GLFW_KEY_D))
        move_direction.y++;

    if (move_direction.x != 0 || move_direction.y != 0)
        game_set_target(camera_move(move_direction, window.dt));
    if (rotation_magnitude != 0)
        game_set_rotation(camera_rotate(rotation_magnitude, window.dt));
}

void state_init(void) 
{
    gfx_init();
    camera_init();
    game_init();
    link_camera_gfx();
    link_camera_game();
}

void state_loop(void)
{
    while (!window_closed()) 
    {
        process_input();
        renderer_update(game.buffer_length * sizeof(f32), game.buffer);
        renderer_render();
        window_poll_events();
        window_swap_buffers();
        window_calc_dt();
    }
}

void state_exit(void)
{
    renderer_destroy();
    game_destroy();
}