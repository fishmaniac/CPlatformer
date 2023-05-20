#include "structs.h"

Game_s initScene(Game_s game) {
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);

	game.window = SDL_CreateWindow(PROJECT_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN);
	game.renderer = SDL_CreateRenderer(game.window, -1, SDL_RENDERER_PRESENTVSYNC);
	
	prepareScene(game.renderer);

	return game;
}

void prepareScene(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, COLOR_BLUE.r, COLOR_BLUE.g, COLOR_BLUE.b, COLOR_BLUE.a);
	SDL_RenderClear(renderer);
}

void updateCamera(Game_s *game, Entity *player) {
	game->camX = player->x - (SCREEN_WIDTH / 2);
	game->camY = player->y - (SCREEN_HEIGHT / 2);
}

void doInput(Game_s *game, Entity *player) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				exit(0);
				break;
			case SDL_KEYDOWN:
				doKeyDown(game, player, &event.key);
				break;
			case SDL_KEYUP:
				doKeyUp(game, player, &event.key);
				break;
			default:
				break;
		}
	}
}

void doKeyDown(Game_s *game, Entity *player, SDL_KeyboardEvent *event) {
	if (event->repeat == 0) {
		if (event->keysym.scancode == SDL_SCANCODE_A) {
			game->left = 1;
		}
		if (event->keysym.scancode == SDL_SCANCODE_D) {
			game->right = 1;
		}
		if (event->keysym.scancode == SDL_SCANCODE_SPACE && player->isColliding) {
			game->jump = 1;
			game->jumpDuration = MAX_JUMP_DURATION;
		}
		if (event->keysym.scancode == SDL_SCANCODE_Q) {
			exit(0);
		}
	}

}

void doKeyUp(Game_s *game, Entity *player, SDL_KeyboardEvent *event) {
	if (event->repeat == 0) {
		if (event->keysym.scancode == SDL_SCANCODE_A) {
			game->left = 0;
			// player->texture = player->idleL;
			// player->numFrames = 4;
		}
		if (event->keysym.scancode == SDL_SCANCODE_D) {
			game->right = 0;
			// player->texture = player->idleR;
			// player->numFrames = 4;
		}
	}
}

void cleanupGame(Game_s game) {
	SDL_DestroyRenderer(game.renderer);
	SDL_DestroyWindow(game.window);
	SDL_Quit();
}
