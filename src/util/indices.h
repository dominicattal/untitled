#ifndef INDICES_H
#define INDICES_H

#define DOWN  0
#define RIGHT 1
#define UP    2
#define LEFT  3

#define FALSE 0
#define TRUE 1

#pragma region UBOS
#define NUM_UBOS         7
#define MATRICES_UBO     0
#define ZOOM_UBO         1
#define ASPECT_RATIO_UBO 2
#define ROTATION_UBO     3
#define TILT_UBO         4
#define CONSTANTS_UBO    5
#define OUTLINE_UBO      6
#pragma endregion

#pragma region SSBOS
#define NUM_SSBOS 2
#define GAME_SSBO 0
#define GUI_SSBO  1
#pragma endregion

#pragma region SHADERS
#define NUM_SHADERS       11
#define TILE_SHADER       0
#define WALL_SHADER       1
#define ENTITY_SHADER     2
#define PROJECTILE_SHADER 3
#define GUI_SHADER        4
#define SHADOW_SHADER     5
#define HEALTHBAR_SHADER  6
#define PARTICLE_SHADER   7
#define OBSTACLE_SHADER   8
#define PARJICLE_SHADER   9
#define PARSTACLE_SHADER  10
#pragma endregion

#pragma region VAOS
#define NUM_VAOS       9
#define TILE_VAO       0
#define WALL_VAO       1
#define ENTITY_VAO     2
#define PROJECTILE_VAO 3
#define GUI_VAO        4
#define PARTICLE_VAO   5
#define OBSTACLE_VAO   6
#define PARJICLE_VAO   7
#define PARSTACLE_VAO  8
#pragma endregion

#pragma region GAME_TEXTURES
#define NUM_GAME_TEXTURES 14
#define KNIGHT_DOWN_TEX   0
#define BULLET_TEX        1
#define TILE_TEX          2
#define WALL_TOP_TEX      3
#define WALL_TEX          4
#define BUSH_TEX          5
#define ROCK_TEX          6
#define KNIGHT_RIGHT_TEX  7
#define KNIGHT_UP_TEX     8
#define KNIGHT_LEFT_TEX   9
#define KNIGHT_SHOOT_LEFT_TEX 10
#define KNIGHT_SHOOT_RIGHT_TEX 11
#define KNIGHT_SHOOT_DOWN_TEX 12
#define KNIGHT_SHOOT_UP_TEX 13
#pragma endregion

#pragma region GUI_TEXTURES
#define NUM_GUI_TEXTURES 5
#define NO_TEX           0
#define EMPTY_TEX        1
#define A_TEX            2
#define B_TEX            3
#define BUTTON_TEX       4
#pragma endregion

#pragma region ANIMATIONS
#define NUM_ANIMATIONS 1
#define ENTITY_ANIMATION 0
#pragma endregion

#pragma region ENTITY_IDS
#define MAX_ENTITY_ID 2
#define KNIGHT 0
#define ENEMY  1
#pragma endregion

#pragma region ENTITY_STATES
#define KNIGHT_STATES 2
#define KNIGHT_IDLE   0
#define KNIGHT_SHOOT  1
#define ENEMY_STATES 2
#define ENEMY_IDLE   0
#define ENEMY_SHOOT  1
#pragma endregion

#endif