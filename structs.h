//scene.c
//textures.c
//entity.c

#ifndef INIT_H
#define INIT_H

#include "common.h"

typedef struct {
	SDL_Renderer *renderer;
	SDL_Window *window;
	SDL_Rect camera;
	bool down, left, right, jump, sprint, fire; 
	float jumpDuration;
	int camX, camY;
} Game_s;

typedef struct {
	int x, y, w, h, tile, speed, stamina, health;
	float scaling;
	bool isJumping, isColliding, isLeft;
	Uint32 currentFrame, numFrames, animationDelay;
	SDL_Texture *texture, *idleL, *idleR, *runL, *runR, *jumpL, *jumpR;
	SDL_Rect entityRect;
} Entity;

typedef struct {
    int type;
    SDL_Rect rect;
} Tile;
//scene.c
Game_s initScene(Game_s game);
void prepareScene(SDL_Renderer *renderer);
void updateCamera(Game_s *game, Entity *player);
void cleanupGame(Game_s game);
void doInput(Game_s *game, Entity *player);
void doKeyDown(Game_s *game, Entity *player, SDL_KeyboardEvent *event);
void doKeyUp(Game_s *game, Entity *player, SDL_KeyboardEvent *event);
void handleMovement(Game_s *game, Entity *player);

//textures.c
void renderGameObjects(Game_s *game, Entity *player, Tile tileMap[MAP_HEIGHT][MAP_WIDTH]);
SDL_Texture *loadTexture(Game_s game, char *filename);
void initMap(Tile tileMap[MAP_HEIGHT][MAP_WIDTH]);
void renderMap(Game_s *game, Entity *player, Tile tileMap[MAP_HEIGHT][MAP_WIDTH]);
void renderTexture(Game_s *game, Entity *player);
void readMap(Tile tileMap[MAP_HEIGHT][MAP_WIDTH], char level[20]);
void testMap(Tile tileMap[MAP_HEIGHT][MAP_WIDTH]);

//entity.c
void blitAnimated(Game_s *game, Entity *player);
bool checkCollision(SDL_Rect rectA, SDL_Rect rectB);
void initPlayer(Entity *player, Game_s *game);

#endif
