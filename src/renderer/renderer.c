#include "renderer.h"
#include <math.h>

Renderer renderer;

static void link_shader_ubo(u32 shader_index, u32 ubo_index, char *identifier);
static void link_shader_ssbo(u32 shader_index, u32 ssbo_index);
static void set_game_ssbo(void);
static void set_gui_ssbo(void);
static void set_constants_ubo(void);
static void set_outline_ubo(void);
static void message_callback();

void renderer_init(void) 
{
    //glEnable(GL_DEBUG_OUTPUT);
    //glDebugMessageCallback(message_callback, 0);
    glDepthFunc(GL_LESS);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_STENCIL_TEST);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_CULL_FACE); 
    glCullFace(GL_BACK);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    /* --------------------- */
    renderer.shaders = malloc(NUM_SHADERS * sizeof(Shader));
    renderer.shaders[TILE_SHADER]       = shader_create("src/renderer/shaders/tile/tile.vert", "src/renderer/shaders/tile/tile.frag", "src/renderer/shaders/tile/tile.geom");
    renderer.shaders[WALL_SHADER]       = shader_create("src/renderer/shaders/wall/wall.vert", "src/renderer/shaders/wall/wall.frag", "src/renderer/shaders/wall/wall.geom");
    renderer.shaders[ENTITY_SHADER]     = shader_create("src/renderer/shaders/entity/entity.vert", "src/renderer/shaders/entity/entity.frag", "src/renderer/shaders/entity/entity.geom");
    renderer.shaders[SHADOW_SHADER]     = shader_create("src/renderer/shaders/shadow/shadow.vert", "src/renderer/shaders/shadow/shadow.frag", "src/renderer/shaders/shadow/shadow.geom");
    renderer.shaders[HEALTHBAR_SHADER]  = shader_create("src/renderer/shaders/healthbar/healthbar.vert", "src/renderer/shaders/healthbar/healthbar.frag", "src/renderer/shaders/healthbar/healthbar.geom");
    renderer.shaders[PROJECTILE_SHADER] = shader_create("src/renderer/shaders/projectile/projectile.vert", "src/renderer/shaders/projectile/projectile.frag", "src/renderer/shaders/projectile/projectile.geom");
    renderer.shaders[GUI_SHADER]        = shader_create("src/renderer/shaders/gui/gui.vert", "src/renderer/shaders/gui/gui.frag", NULL);
    renderer.shaders[PARTICLE_SHADER]   = shader_create("src/renderer/shaders/particle/particle.vert", "src/renderer/shaders/particle/particle.frag", "src/renderer/shaders/particle/particle.geom");
    renderer.shaders[OBSTACLE_SHADER]   = shader_create("src/renderer/shaders/obstacle/obstacle.vert", "src/renderer/shaders/obstacle/obstacle.frag", "src/renderer/shaders/obstacle/obstacle.geom");
    renderer.shaders[PARJICLE_SHADER]   = shader_create("src/renderer/shaders/parjicle/parjicle.vert", "src/renderer/shaders/parjicle/parjicle.frag", "src/renderer/shaders/parjicle/parjicle.geom");
    renderer.shaders[PARSTACLE_SHADER]  = shader_create("src/renderer/shaders/parstacle/parstacle.vert", "src/renderer/shaders/parstacle/parstacle.frag", "src/renderer/shaders/parstacle/parstacle.geom");
    /* --------------------- */
    renderer.vaos = malloc(NUM_VAOS * sizeof(VAO));
    renderer.vaos[TILE_VAO]         = vao_create(GL_STATIC_DRAW, GL_POINTS, 2);
    renderer.vaos[WALL_VAO]         = vao_create(GL_STATIC_DRAW, GL_POINTS, 4);
    renderer.vaos[ENTITY_VAO]       = vao_create(GL_DYNAMIC_DRAW, GL_POINTS, 6);
    renderer.vaos[PROJECTILE_VAO]   = vao_create(GL_DYNAMIC_DRAW, GL_POINTS, 5);
    renderer.vaos[GUI_VAO]          = vao_create(GL_STATIC_DRAW, GL_TRIANGLES, 9);
    renderer.vaos[PARTICLE_VAO]     = vao_create(GL_DYNAMIC_DRAW, GL_POINTS, 4);
    renderer.vaos[OBSTACLE_VAO]     = vao_create(GL_STATIC_DRAW, GL_POINTS, 4);
    renderer.vaos[PARJICLE_VAO]     = vao_create(GL_DYNAMIC_DRAW, GL_POINTS, 5);
    renderer.vaos[PARSTACLE_VAO]    = vao_create(GL_STATIC_DRAW, GL_POINTS, 4);
    vao_attr(renderer.vaos[TILE_VAO]        , 0, 2, 0);
    vao_attr(renderer.vaos[WALL_VAO]        , 0, 3, 0);
    vao_attr(renderer.vaos[WALL_VAO]        , 1, 1, 3);
    vao_attr(renderer.vaos[ENTITY_VAO]      , 0, 3, 0);
    vao_attr(renderer.vaos[ENTITY_VAO]      , 1, 1, 3);
    vao_attr(renderer.vaos[ENTITY_VAO]      , 2, 1, 4);
    vao_attr(renderer.vaos[ENTITY_VAO]      , 3, 1, 5);
    vao_attr(renderer.vaos[PROJECTILE_VAO]  , 0, 3, 0);
    vao_attr(renderer.vaos[PROJECTILE_VAO]  , 1, 1, 3);
    vao_attr(renderer.vaos[PROJECTILE_VAO]  , 2, 1, 4);
    vao_attr(renderer.vaos[GUI_VAO]         , 0, 2, 0);
    vao_attr(renderer.vaos[GUI_VAO]         , 1, 2, 2);
    vao_attr(renderer.vaos[GUI_VAO]         , 2, 1, 4);
    vao_attr(renderer.vaos[GUI_VAO]         , 3, 4, 5);
    vao_attr(renderer.vaos[PARTICLE_VAO]    , 0, 3, 0);
    vao_attr(renderer.vaos[PARTICLE_VAO]    , 1, 1, 3);
    vao_attr(renderer.vaos[OBSTACLE_VAO]    , 0, 3, 0);
    vao_attr(renderer.vaos[OBSTACLE_VAO]    , 1, 1, 3);
    vao_attr(renderer.vaos[PARJICLE_VAO]    , 0, 3, 0);
    vao_attr(renderer.vaos[PARJICLE_VAO]    , 1, 1, 3);
    vao_attr(renderer.vaos[PARJICLE_VAO]    , 2, 1, 4);
    vao_attr(renderer.vaos[PARSTACLE_VAO]   , 0, 3, 0);
    vao_attr(renderer.vaos[PARSTACLE_VAO]   , 1, 1, 3);
    /* --------------------- */
    renderer.game_textures = malloc(NUM_GAME_TEXTURES * sizeof(Texture));
    renderer.game_textures[KNIGHT_DOWN_TEX]  = texture_create("assets/textures/game/knight/knight_down_1.png", GL_NEAREST);
    renderer.game_textures[KNIGHT_RIGHT_TEX] = texture_create("assets/textures/game/knight/knight_right_1.png", GL_NEAREST);
    renderer.game_textures[KNIGHT_UP_TEX]    = texture_create("assets/textures/game/knight/knight_up_1.png", GL_NEAREST);
    renderer.game_textures[KNIGHT_LEFT_TEX]  = texture_create("assets/textures/game/knight/knight_left_1.png", GL_NEAREST);
    renderer.game_textures[KNIGHT_SHOOT_DOWN_TEX]  = texture_create("assets/textures/game/knight/knight_shoot_down_1.png", GL_NEAREST);
    renderer.game_textures[KNIGHT_SHOOT_RIGHT_TEX] = texture_create("assets/textures/game/knight/knight_shoot_right_1.png", GL_NEAREST);
    renderer.game_textures[KNIGHT_SHOOT_UP_TEX]    = texture_create("assets/textures/game/knight/knight_shoot_up_1.png", GL_NEAREST);
    renderer.game_textures[KNIGHT_SHOOT_LEFT_TEX]  = texture_create("assets/textures/game/knight/knight_shoot_left_1.png", GL_NEAREST);
    renderer.game_textures[BULLET_TEX]       = texture_create("assets/textures/game/bullet.png", GL_NEAREST);
    renderer.game_textures[TILE_TEX]         = texture_create("assets/textures/game/tile.png", GL_NEAREST);
    renderer.game_textures[WALL_TOP_TEX]     = texture_create("assets/textures/game/wall_top.png", GL_NEAREST);
    renderer.game_textures[WALL_TEX]         = texture_create("assets/textures/game/wall.png", GL_NEAREST);
    renderer.game_textures[BUSH_TEX]         = texture_create("assets/textures/game/bush.png", GL_NEAREST);
    renderer.game_textures[ROCK_TEX]         = texture_create("assets/textures/game/rock.png", GL_NEAREST);
    /* --------------------- */
    renderer.gui_textures = malloc(NUM_GUI_TEXTURES * sizeof(Texture));
    renderer.gui_textures[NO_TEX]     = texture_create("assets/textures/gui/none.png", GL_LINEAR);
    renderer.gui_textures[EMPTY_TEX]  = texture_create("assets/textures/gui/empty.png", GL_LINEAR);
    renderer.gui_textures[A_TEX]      = texture_create("assets/textures/gui/text/A.png", GL_LINEAR);
    renderer.gui_textures[B_TEX]      = texture_create("assets/textures/gui/text/B.png", GL_LINEAR);
    renderer.gui_textures[BUTTON_TEX] = texture_create("assets/textures/gui/button.png", GL_NEAREST);
    /* --------------------- */
    renderer.ubos = malloc(NUM_UBOS * sizeof(UBO));
    renderer.ubos[MATRICES_UBO]     = ubo_create(32 * sizeof(f32));
    renderer.ubos[ZOOM_UBO]         = ubo_create(sizeof(f32));
    renderer.ubos[ASPECT_RATIO_UBO] = ubo_create(sizeof(f32));
    renderer.ubos[ROTATION_UBO]     = ubo_create(sizeof(f32));
    renderer.ubos[TILT_UBO]         = ubo_create(sizeof(f32));
    renderer.ubos[CONSTANTS_UBO]    = ubo_create(2 * sizeof(f32));
    renderer.ubos[OUTLINE_UBO]      = ubo_create(sizeof(f32));
    set_constants_ubo();
    set_outline_ubo();
    /* --------------------- */
    renderer.ssbos = malloc(NUM_SSBOS * sizeof(SSBO));
    renderer.ssbos[GAME_SSBO] = ssbo_create(NUM_GAME_TEXTURES * sizeof(u64));
    renderer.ssbos[GUI_SSBO] = ssbo_create(NUM_GUI_TEXTURES * sizeof(u64));
    set_game_ssbo();
    set_gui_ssbo();
    /* --------------------- */
    link_shader_ubo(TILE_SHADER, MATRICES_UBO, "Matrices");
    link_shader_ubo(WALL_SHADER, MATRICES_UBO, "Matrices");
    link_shader_ubo(ENTITY_SHADER, MATRICES_UBO, "Matrices");
    link_shader_ubo(ENTITY_SHADER, ASPECT_RATIO_UBO, "AspectRatio");
    link_shader_ubo(ENTITY_SHADER, ZOOM_UBO, "Zoom");
    link_shader_ubo(ENTITY_SHADER, OUTLINE_UBO, "OutlineThickness");
    link_shader_ubo(HEALTHBAR_SHADER, MATRICES_UBO, "Matrices");
    link_shader_ubo(HEALTHBAR_SHADER, ZOOM_UBO, "Zoom");
    link_shader_ubo(HEALTHBAR_SHADER, ASPECT_RATIO_UBO, "AspectRatio");
    link_shader_ubo(HEALTHBAR_SHADER, OUTLINE_UBO, "OutlineThickness");
    link_shader_ubo(PROJECTILE_SHADER, MATRICES_UBO, "Matrices");
    link_shader_ubo(PROJECTILE_SHADER, ZOOM_UBO, "Zoom");
    link_shader_ubo(PROJECTILE_SHADER, ASPECT_RATIO_UBO, "AspectRatio");
    link_shader_ubo(PROJECTILE_SHADER, ROTATION_UBO, "Rotation");
    link_shader_ubo(PROJECTILE_SHADER, TILT_UBO, "Tilt");
    link_shader_ubo(PROJECTILE_SHADER, CONSTANTS_UBO, "Constants");
    link_shader_ubo(SHADOW_SHADER, MATRICES_UBO, "Matrices");
    link_shader_ubo(PARTICLE_SHADER, MATRICES_UBO, "Matrices");
    link_shader_ubo(PARTICLE_SHADER, ASPECT_RATIO_UBO, "AspectRatio");
    link_shader_ubo(PARTICLE_SHADER, ZOOM_UBO, "Zoom");
    link_shader_ubo(PARTICLE_SHADER, OUTLINE_UBO, "OutlineThickness");
    link_shader_ubo(OBSTACLE_SHADER, MATRICES_UBO, "Matrices");
    link_shader_ubo(OBSTACLE_SHADER, ASPECT_RATIO_UBO, "AspectRatio");
    link_shader_ubo(OBSTACLE_SHADER, ZOOM_UBO, "Zoom");
    link_shader_ubo(OBSTACLE_SHADER, OUTLINE_UBO, "OutlineThickness");
    link_shader_ubo(PARJICLE_SHADER, MATRICES_UBO, "Matrices");
    link_shader_ubo(PARJICLE_SHADER, ASPECT_RATIO_UBO, "AspectRatio");
    link_shader_ubo(PARJICLE_SHADER, ZOOM_UBO, "Zoom");
    link_shader_ubo(PARJICLE_SHADER, ROTATION_UBO, "Rotation");
    link_shader_ubo(PARJICLE_SHADER, TILT_UBO, "Tilt");
    link_shader_ubo(PARJICLE_SHADER, CONSTANTS_UBO, "Constants");
    link_shader_ubo(PARJICLE_SHADER, OUTLINE_UBO, "OutlineThickness");
    link_shader_ubo(PARSTACLE_SHADER, MATRICES_UBO, "Matrices");
    link_shader_ubo(PARSTACLE_SHADER, ASPECT_RATIO_UBO, "AspectRatio");
    link_shader_ubo(PARSTACLE_SHADER, ZOOM_UBO, "Zoom");
    link_shader_ubo(PARSTACLE_SHADER, OUTLINE_UBO, "OutlineThickness");
    /* --------------------- */
    link_shader_ssbo(TILE_SHADER, GAME_SSBO);
    link_shader_ssbo(WALL_SHADER, GAME_SSBO);
    link_shader_ssbo(ENTITY_SHADER, GAME_SSBO);
    link_shader_ssbo(PROJECTILE_SHADER, GAME_SSBO);
    link_shader_ssbo(OBSTACLE_SHADER, GAME_SSBO);
    link_shader_ssbo(PARSTACLE_SHADER, GAME_SSBO);
    link_shader_ssbo(GUI_SHADER, GUI_SSBO);
    /* --------------------- */
    renderer.animations = malloc(NUM_ANIMATIONS * sizeof(Animation));
    animation_init_entities(&renderer.animations[ENTITY_ANIMATION]);
}

void renderer_malloc(u32 vao, u32 length)
{
    if (renderer.vaos[vao].mode == GL_POINTS)
        length *= renderer.vaos[vao].length;
    vao_malloc(renderer.vaos[vao], length);
}

void renderer_update(u32 vao, u32 offset, u32 length, f32* buffer)
{
    if (renderer.vaos[vao].mode == GL_POINTS)
        length *= renderer.vaos[vao].length;
    vao_update(renderer.vaos[vao], offset, length, buffer);
}

void renderer_render(void)
{
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    shader_use(renderer.shaders[TILE_SHADER]);
    vao_draw(renderer.vaos[TILE_VAO]);
    shader_use(renderer.shaders[SHADOW_SHADER]);
    vao_draw(renderer.vaos[PROJECTILE_VAO]);
    vao_draw(renderer.vaos[OBSTACLE_VAO]);
    vao_draw(renderer.vaos[PARSTACLE_VAO]);
    vao_draw(renderer.vaos[ENTITY_VAO]);
    glEnable(GL_DEPTH_TEST);
    shader_use(renderer.shaders[WALL_SHADER]);
    vao_draw(renderer.vaos[WALL_VAO]);
    shader_use(renderer.shaders[ENTITY_SHADER]);
    vao_draw(renderer.vaos[ENTITY_VAO]);
    shader_use(renderer.shaders[PARTICLE_SHADER]);
    vao_draw(renderer.vaos[PARTICLE_VAO]);
    shader_use(renderer.shaders[PARJICLE_SHADER]);
    vao_draw(renderer.vaos[PARJICLE_VAO]);
    shader_use(renderer.shaders[PROJECTILE_SHADER]);
    vao_draw(renderer.vaos[PROJECTILE_VAO]);
    shader_use(renderer.shaders[OBSTACLE_SHADER]);
    vao_draw(renderer.vaos[OBSTACLE_VAO]);
    shader_use(renderer.shaders[PARSTACLE_SHADER]);
    vao_draw(renderer.vaos[PARSTACLE_VAO]);
    //glDepthFunc(GL_ALWAYS);
    shader_use(renderer.shaders[HEALTHBAR_SHADER]);
    vao_draw(renderer.vaos[ENTITY_VAO]);
    //glDepthFunc(GL_LESS);
    glDisable(GL_DEPTH_TEST);
    shader_use(renderer.shaders[GUI_SHADER]);
    vao_draw(renderer.vaos[GUI_VAO]);
}

void renderer_destroy(void)
{
    i32 i;
    for (i = 0; i < NUM_VAOS; i++)
        vao_destroy(renderer.vaos[i]);
    free(renderer.vaos);

    for (i = 0; i < NUM_SHADERS; i++)
        shader_destroy(renderer.shaders[i]);
    free(renderer.shaders);

    for (i = 0; i < NUM_UBOS; i++)
        ubo_destroy(renderer.ubos[i]);
    free(renderer.ubos);

    for (i = 0; i < NUM_GAME_TEXTURES; i++)
        texture_destroy(renderer.game_textures[i]);
    free(renderer.game_textures);

    for (i = 0; i < NUM_GUI_TEXTURES; i++)
        texture_destroy(renderer.gui_textures[i]);
    free(renderer.gui_textures);

    for (i = 0; i < NUM_SSBOS; i++)
        ssbo_destroy(renderer.ssbos[i]);
    free(renderer.ssbos);

    animation_destroy_entities(&renderer.animations[ENTITY_ANIMATION]);
}

void renderer_uniform_update_view(f32 *mat) {
    ubo_update(renderer.ubos[MATRICES_UBO], 0, 16 * sizeof(f32), mat);
}

void renderer_uniform_update_proj(f32 *mat) {
    ubo_update(renderer.ubos[MATRICES_UBO], 16 * sizeof(f32), 16 * sizeof(f32), mat);
}

void renderer_uniform_update_zoom(f32 zoom) {
    ubo_update(renderer.ubos[ZOOM_UBO], 0, sizeof(f32), &zoom);
}

void renderer_uniform_update_rotation(f32 rotation) {
    ubo_update(renderer.ubos[ROTATION_UBO], 0, sizeof(f32), &rotation);
}

void renderer_uniform_update_tilt(f32 tilt) {
    ubo_update(renderer.ubos[TILT_UBO], 0, sizeof(f32), &tilt);
}

void renderer_uniform_update_aspect_ratio(f32 ar) {
    ubo_update(renderer.ubos[ASPECT_RATIO_UBO], 0, sizeof(f32), &ar);
}

void link_shader_ubo(u32 shader_index, u32 ubo_index, char *identifier)
{
    shader_bind_uniform_block(renderer.shaders[shader_index], ubo_index, identifier);
    ubo_bind_buffer_base(renderer.ubos[ubo_index], ubo_index);
}

void link_shader_ssbo(u32 shader_index, u32 ssbo_index)
{
    shader_use(renderer.shaders[shader_index]);
    ssbo_bind_buffer_base(renderer.ssbos[ssbo_index], ssbo_index);
}

void set_game_ssbo(void)
{
    u64 *handles = malloc(NUM_GAME_TEXTURES * sizeof(u64));
    for (i32 i = 0; i < NUM_GAME_TEXTURES; i++)
        handles[i] = renderer.game_textures[i].handle;
    ssbo_update(renderer.ssbos[GAME_SSBO], 0, NUM_GAME_TEXTURES * sizeof(u64), handles);
    free(handles);
}

void set_gui_ssbo(void)
{
    u64 *handles = malloc(NUM_GUI_TEXTURES * sizeof(u64));
    for (i32 i = 0; i < NUM_GUI_TEXTURES; i++)
        handles[i] = renderer.gui_textures[i].handle;
    ssbo_update(renderer.ssbos[GUI_SSBO], 0, NUM_GUI_TEXTURES * sizeof(u64), handles);
    free(handles);
}

void set_constants_ubo(void)
{
    f32 pi, sqrt2;
    pi = PI;
    sqrt2 = SQRT2;
    ubo_update(renderer.ubos[CONSTANTS_UBO], 0, sizeof(f32), &pi);
    ubo_update(renderer.ubos[CONSTANTS_UBO], sizeof(f32), sizeof(f32), &sqrt2);
}

void set_outline_ubo(void)
{
    f32 outline_thickness = 1 / 32.0f;
    ubo_update(renderer.ubos[OUTLINE_UBO], 0, sizeof(f32), &outline_thickness);
}

void GLAPIENTRY message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
   printf("GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n", ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ), type, severity, message);
}