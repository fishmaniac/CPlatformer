#include "structs.h"

Game_s initScene(Game_s game) {
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);

	// Create a window
	game.window = SDL_CreateWindow(PROJECT_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	game.renderer = SDL_CreateRenderer(game.window, -1, SDL_RENDERER_ACCELERATED);
	
	prepareScene(game.renderer);

	return game;
}

void prepareScene(SDL_Renderer *renderer) {
	// Set the renderer color
	SDL_SetRenderDrawColor(renderer, 101, 189, 255, 255);
	SDL_RenderClear(renderer);
}

void addSquare(Game_s *game, int x, int y, int width, int height, SDL_Color color, Entity *square) {
	square->x = x;
	square->y = y;
	square->w = width;
	square->h = height;
	square->color = color;

	SDL_SetRenderDrawColor(game->renderer, square->color.r, square->color.g, square->color.b, square->color.a);
	SDL_Rect rect = {square->x, square->y, square->w, square->h};
	SDL_RenderFillRect(game->renderer, &rect);
}

void updateCamera(Game_s *game, Entity *player) {
	game->camX = player->x - (SCREEN_WIDTH / 2);
	game->camY = player->y - (SCREEN_HEIGHT / 2);

	if (game->camX < 0) {
		game->camX = 0;
	}
	if (game->camY < 0) {
		game->camY = 0;
	}
	if (game->camX > (MAP_WIDTH * TILE_SIZE) - SCREEN_WIDTH) {
		game->camX = (MAP_WIDTH * TILE_SIZE) - SCREEN_WIDTH;
	}
	if (game->camY > (MAP_WIDTH * TILE_SIZE) - SCREEN_WIDTH) {
		game->camY = (MAP_WIDTH * TILE_SIZE) - SCREEN_WIDTH;
	}
}

void renderGameObjects(Game_s *game, Entity *player, Tile tileMap[MAP_HEIGHT][MAP_WIDTH]) {
	renderMap(game->renderer, tileMap);
	blitAnimated(game, player);
	SDL_RenderPresent(game->renderer);
}
