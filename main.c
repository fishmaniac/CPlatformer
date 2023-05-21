#include <SDL2/SDL.h>
#include "structs.h"

Game_s testShape(Game_s game);
void gameLoop(Game_s *game, Entity_s *player, Entity_s *environment, Tile_s tileMap[MAP_HEIGHT][MAP_WIDTH]);

#ifdef _WIN32
#ifdef _WIN64
#define SDL_MAIN_HANDLED

int WinMain(int argc, char* argv[]) {
    SDL_SetMainReady();
    return main(argc, argv);
}
#endif
#endif

int main(int argc, char* argv[]) {
	Tile_s tileMap[MAP_HEIGHT][MAP_WIDTH];
	Game_s game;
	Entity_s player;
	Entity_s environment[MAX_ENTITIES];

	game = initScene(game);
	initMap(tileMap);
	//testMap(tileMap);
	readMap(tileMap, "level0.txt");

	initPlayer(&player, &game);

	game.camX = (SCREEN_WIDTH / 2);
	game.camY = (SCREEN_HEIGHT / 2);

	gameLoop(&game, &player, environment, tileMap);
	

	cleanupGame(game);
	return 0;
}

void gameLoop(Game_s *game, Entity_s *player, Entity_s *environment, Tile_s tileMap[MAP_HEIGHT][MAP_WIDTH]) {
	Uint32 lastFrameTime = SDL_GetTicks();

	while (1) {
		prepareScene(game->renderer);
		doInput(game, player);
		handleMovement(game, player);
		
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Player speed: %d\nPlayer stamina: %d\n", player->speed, player->stamina);
		Uint32 currentFrameTime = SDL_GetTicks();
		Uint32 frameDuration = currentFrameTime - lastFrameTime;

		if (frameDuration >= player->animationDelay) {
			player->currentFrame = (player->currentFrame + 1) % player->numFrames;
			lastFrameTime = currentFrameTime;
		}
		
		
		renderGameObjects(game, player, tileMap);
		updateCamera(game, player);

		
		SDL_RenderClear(game->renderer);
		

		//SETS GAME LOOP FRAME RATE
		Uint32 elapsedTime = SDL_GetTicks() - currentFrameTime;
		if (elapsedTime < FRAME_TIME) {
			SDL_Delay(FRAME_TIME - elapsedTime);
		}
	}
}
