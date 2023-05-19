#include <SDL2/SDL.h>
#include "structs.h"

Game_s testShape(Game_s game);
void gameLoop(Game_s *game, Entity *player, Entity *environment, Tile tileMap[MAP_HEIGHT][MAP_WIDTH]);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	
	Tile tileMap[MAP_HEIGHT][MAP_WIDTH];
	Game_s game;
	Entity player;
	Entity environment[MAX_ENTITIES];

	memset(&game, 0, sizeof(Game_s));
	memset(&player, 0, sizeof(Entity));
	game = initScene(game);
	initMap(tileMap);

	player.x = SCREEN_WIDTH / 2;
	player.y = SCREEN_HEIGHT - 200;
	player.scaling = 2.5;
	player.numFrames = 4;
	player.animationDelay = 128;
	player.texture = loadTexture(game, "assets/gothicvania/Gothic-hero-Files/PNG/gothic-hero-idle.png");
	player.isJumping = false;

	
	

	gameLoop(&game, &player, environment, tileMap);
	

	cleanupGame(game);
	return 0;
}

void gameLoop(Game_s *game, Entity *player, Entity *environment, Tile tileMap[MAP_HEIGHT][MAP_WIDTH]) {
	Uint32 lastFrameTime = SDL_GetTicks();
/* 	SDL_Color color = {255, 0, 0, 255}; */

	while (1) {
		prepareScene(game->renderer);
		doInput(game, player);

		if (game->jump) {
/* 			player->y -= 50; */
			if (game->jumpDuration > 0) {
				player->y -= JUMP_HEIGHT;
				game->jumpDuration--;
				if (game->jumpDuration == 0) {
					player->isJumping = false;
				}
			}
			else {
				game->jump = 0;
				player->texture = loadTexture(*game, "assets/gothicvania/Gothic-hero-Files/PNG/gothic-hero-idle.png");
				player->numFrames = 4;
			}
		}
		//MAYBE TURN TO ELSE IFS
		if (game->left) {
			player->x -= PLAYER_SPEED;
		}
		if (game->right) {
			player->x += PLAYER_SPEED;
		}
		
		
		Uint32 currentFrameTime = SDL_GetTicks();
		Uint32 frameDuration = currentFrameTime - lastFrameTime;

		if (frameDuration >= player->animationDelay) {
			player->currentFrame = (player->currentFrame + 1) % player->numFrames;
			lastFrameTime = currentFrameTime;
		}
		
		// addSquare(game, 100, 400, 2000, 100, color, &environment[0]);
		// addSquare(game, 300, 300, 400, 100, color, &environment[1]);

/* 		handleCollisions(player, &environment[0], 2); */
		updateCamera(game, player);
		renderGameObjects(game, player, tileMap);
		
		//SDL_RenderClear(game->renderer);
		

		//SETS GAME LOOP FRAME RATE
		Uint32 elapsedTime = SDL_GetTicks() - currentFrameTime;
		if (elapsedTime < FRAME_TIME) {
			SDL_Delay(FRAME_TIME - elapsedTime);
		}
	}
}
