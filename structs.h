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
	bool up, down, left, right, jump, fire; 
	int jumpDuration, camX, camY;
} Game_s;

typedef struct {
	int x, y, jY, w, h, health;
	float scaling, vX, vY;
	bool isJumping, isColliding;
	Uint32 currentFrame, numFrames, animationDelay;
	SDL_Texture *texture;
	SDL_Color color;
} Entity;

typedef struct {
    int type;
    SDL_Rect rect;
} Tile;

Game_s initScene(Game_s game);
void prepareScene(SDL_Renderer *renderer);
void addSquare(Game_s* game, int x, int y, int width, int height, SDL_Color color, Entity *square);
void updateCamera(Game_s *game, Entity *player);
void renderGameObjects(Game_s *game, Entity *player, Tile tileMap[MAP_HEIGHT][MAP_WIDTH]);

SDL_Texture *loadTexture(Game_s game, char *filename);
// void blit(Game_s *game, Entity *player);
void blitAnimated(Game_s *game, Entity *player);
bool checkCollision(Entity *rect1, Entity *rect2);
void handleCollisions(Entity *player, Entity *environment, int numEntities);


void doInput(Game_s *game, Entity *player);
void doKeyDown(Game_s *game, Entity *player, SDL_KeyboardEvent *event);
void doKeyUp(Game_s *game, Entity *player, SDL_KeyboardEvent *event);
void cleanupGame(Game_s game);

void initMap(Tile tileMap[MAP_HEIGHT][MAP_WIDTH]);
void renderMap(SDL_Renderer* renderer, Tile tileMap[MAP_HEIGHT][MAP_WIDTH]);

#endif
