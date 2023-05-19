#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//^^REPLACE WITH WIN32 MAIN FUNCTION

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define PROJECT_NAME "SdlGame"
#define MAX_ENTITIES 10
#define PLAYER_SPEED 10
#define JUMP_HEIGHT 10
#define MAX_JUMP_DURATION 80
#define FRAME_TIME 16
#define GRAVITY 5

#define MAP_WIDTH 200
#define MAP_HEIGHT 30
#define TILE_SIZE 32

#define CAMERA_SPEED 10
