#include "structs.h"

Game_s initScene(Game_s game) {
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);

	// Create a window
	game.window = SDL_CreateWindow(PROJECT_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN);
	game.renderer = SDL_CreateRenderer(game.window, -1, SDL_RENDERER_ACCELERATED);
	
	prepareScene(game.renderer);

	return game;
}

void prepareScene(SDL_Renderer *renderer) {
	// Set the renderer color
	SDL_SetRenderDrawColor(renderer, 101, 189, 255, 255);
	SDL_RenderClear(renderer);
}

void updateCamera(Game_s *game, Entity *player) {
	game->camX = player->x - (SCREEN_WIDTH / 2);
	game->camY = player->y - (SCREEN_HEIGHT / 2);
}


void renderGameObjects(Game_s *game, Entity *player, Tile tileMap[MAP_HEIGHT][MAP_WIDTH]) {
	renderMap(game, player, tileMap);
	blitAnimated(game, player);
	SDL_RenderPresent(game->renderer);
}
