#include "structs.h"

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
			player->texture = player->runL;
			player->numFrames = 12;
		}
		if (event->keysym.scancode == SDL_SCANCODE_D) {
			game->right = 1;
			player->texture = player->runR;
			player->numFrames = 12;
		}
		if (event->keysym.scancode == SDL_SCANCODE_SPACE) {
			game->jump = 1;
			game->jumpDuration = MAX_JUMP_DURATION;
			if (player->texture == player->idleR || player->texture == player->runR) {
				player->texture = player->jumpR;
			}
			else {
				player->texture = player->jumpL;
			}
			player->numFrames = 5;
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
			player->texture = player->idleL;
			player->numFrames = 4;
		}
		if (event->keysym.scancode == SDL_SCANCODE_D) {
			game->right = 0;
			player->texture = player->idleR;
			player->numFrames = 4;
		}
	}
}

void cleanupGame(Game_s game) {
	SDL_DestroyRenderer(game.renderer);
	SDL_DestroyWindow(game.window);
	SDL_Quit();
}
