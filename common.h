#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define PROJECT_NAME "SdlGame"
#define MAX_ENTITIES 10
#define FRAME_TIME 16
#define GRAVITY 5
#define SPRINT_SCALAR 2

#define PLAYER_SPEED 10
#define PLAYER_STAMINA 100
#define CAMERA_SPEED 10
#define JUMP_HEIGHT 32
#define MAX_JUMP_DURATION 16

#define MAP_WIDTH 200
#define MAP_HEIGHT 30
#define TILE_SIZE 32
#define COLLISION_MARGIN 6

#define COLOR_WHITE (SDL_Color){255, 255, 255, 255}
#define COLOR_BLACK (SDL_Color){0, 0, 0, 255}
#define COLOR_BLUE (SDL_Color){101, 189, 255, 255}
#define COLOR_GREEN (SDL_Color){24, 175, 0, 255}
