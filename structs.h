//structs.c
//textures.c
//scene.c
//map.c

#ifndef INIT_H
#define INIT_H

#include "common.h"

typedef struct {
	SDL_Renderer *renderer;
	SDL_Window *window;
	SDL_Rect camera;
	bool up, down, left, right, jump, fire; 
	int jumpDuration, camX, camY;
} Game_s;

typedef struct {
	int x, y, jY, pY, w, h, health;
	float scaling, vX, vY;
	bool isJumping, isColliding;
	Uint32 currentFrame, numFrames, animationDelay;
	SDL_Texture *texture;
	SDL_Color color;
	SDL_Rect entityRect;
} Entity;

typedef struct {
    int type;
    SDL_Rect rect;
} Tile;

Game_s initScene(Game_s game);
void prepareScene(SDL_Renderer *renderer);
void updateCamera(Game_s *game, Entity *player);
void renderGameObjects(Game_s *game, Entity *player, Tile tileMap[MAP_HEIGHT][MAP_WIDTH]);

SDL_Texture *loadTexture(Game_s game, char *filename);
// void blit(Game_s *game, Entity *player);
void blitAnimated(Game_s *game, Entity *player);
bool checkCollision(SDL_Rect rectA, SDL_Rect rectB);
bool checkCollisionBottom(SDL_Rect rectA, SDL_Rect rectB);
void handleCollisions(Entity *player, Tile *tileMap);


void doInput(Game_s *game, Entity *player);
void doKeyDown(Game_s *game, Entity *player, SDL_KeyboardEvent *event);
void doKeyUp(Game_s *game, Entity *player, SDL_KeyboardEvent *event);
void cleanupGame(Game_s game);

void initMap(Tile tileMap[MAP_HEIGHT][MAP_WIDTH]);
void renderMap(Game_s *game, Entity *player, Tile tileMap[MAP_HEIGHT][MAP_WIDTH]);

#endif
