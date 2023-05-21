#include "structs.h"

void renderGameObjects(Game_s *game, Entity_s *player, Tile_s tileMap[MAP_HEIGHT][MAP_WIDTH]) {
	renderMap(game, player, tileMap);
	blitAnimated(game, player);
	SDL_RenderPresent(game->renderer);
	renderTexture(game, player);
}

SDL_Texture *loadTexture(Game_s game, char *filename) {
	SDL_Texture *texture;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	texture = IMG_LoadTexture(game.renderer, filename);

	return texture;
}

void initMap(Tile_s tileMap[MAP_HEIGHT][MAP_WIDTH]) {
	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			tileMap[y][x].type = 0;

			tileMap[y][x].rect.x = x * TILE_SIZE;
			tileMap[y][x].rect.y = y * TILE_SIZE;
			tileMap[y][x].rect.w = TILE_SIZE;
			tileMap[y][x].rect.h = TILE_SIZE;
		}
	}
}

void renderMap(Game_s *game, Entity_s *player, Tile_s tileMap[MAP_HEIGHT][MAP_WIDTH]) {
	player->isColliding = false;
	int collidingTiles = 0;

	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			Tile_s tile = tileMap[y][x];

			// Set the tile color based on its type
			SDL_Color color;
			if (tile.type == 0) {
				color = COLOR_WHITE;
			} 
			else if (tile.type == 2) {
				color = COLOR_BLACK;
			}
			else if (tile.type == 3) {
				color = COLOR_GREEN;
			}

			tile.rect.x -= (game->camX);
			tile.rect.y -= (game->camY);

			SDL_SetRenderDrawColor(game->renderer, color.r, color.g, color.b, color.a);
			SDL_RenderFillRect(game->renderer, &tile.rect);

			if (tile.type != 0 && checkCollision(player->entityRect, tile.rect)) {
				collidingTiles++;
				player->tile = tile.type;
				}
			else {
				player->isColliding = false;
			}
		}
	}
	if (collidingTiles > 0) {
		player->isColliding = true;

	}

	if (!player->isColliding) {
		player->y += FRAME_TIME;
	}
}

void renderTexture(Game_s *game, Entity_s *player) {
	if (game->left) {
		player->texture = player->runL;
		player->numFrames = 12;
		player->isLeft = true;
		}
	else if (player->isLeft) {
		player->texture = player->idleL;
		player->numFrames = 4;
	}
	if (game->right) {
		player->texture = player->runR;
		player->numFrames = 12;
		player->isLeft = false;
		}
	else if (!player->isLeft) {
		player->texture = player->idleR;
		player->numFrames = 4;
	}
	if (game->jump && player->isLeft) {
		player->texture = player->jumpL;
		player->numFrames = 5;
		}
	else if (game->jump) {
		player->texture = player->jumpR;
		player->numFrames = 5;
	}
}

// void readMap(Tile_s tileMap[MAP_HEIGHT][MAP_WIDTH], char level[20]) {
// 	FILE *file;
// 	int value, height = 0, width = 0;
//
//
// 	if (fopen_s(&file, level, "r") != 0) {
// 		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "UNABLE TO LOAD FILE %s\n", level);
// 		exit(1);
// 	}
// 	else {
// 		//fseek(file, 0L, SEEK_SET );
// 		while (fscanf_s(file, "%d%*c", &value, 1) != 0 && width < MAP_WIDTH && height < MAP_HEIGHT) {	
// 			if (width == MAP_WIDTH - 1) {
// 				width = 0;
// 				height++;
// 			}
// 			tileMap[height][width].type = value;
// 			SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading h: %d w: %d value %d\n", height, width, tileMap[height][width].type);
// 			width++;
// 		}
// 	}
// 	fclose(file);
// }
//
void readMap(Tile_s tileMap[MAP_HEIGHT][MAP_WIDTH], char level[]) {
	FILE *file = fopen(level, "r");
	char value;
	
	if (file == NULL) {
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "UNABLE TO LOAD FILE %s\n", level);
 		exit(1);
	}
	else {
		for (int y = 0; y < MAP_HEIGHT; y++) {
			for (int x = 0; x < MAP_WIDTH; x++) {
				fscanf(file, "%c ", &value);
				tileMap[y][x].type = ((int) value) - '0';
				/* SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading h: %d w: %d value %d\n", y, x, tileMap[y][x].type); */
			}
		}
	}
	fclose(file);
}

void testMap(Tile_s tileMap[MAP_HEIGHT][MAP_WIDTH]) {
	for (int x = 0; x < MAP_WIDTH; x++) {
		tileMap[MAP_HEIGHT - 1][x].type = 2;
	}
	tileMap[MAP_HEIGHT - 8][2].type = 2;
	tileMap[MAP_HEIGHT - 8][3].type = 2;
	tileMap[MAP_HEIGHT - 8][4].type = 2;
	tileMap[MAP_HEIGHT - 8][5].type = 2;
	tileMap[MAP_HEIGHT - 8][6].type = 2;

	tileMap[MAP_HEIGHT - 5][7].type = 2;

	tileMap[MAP_HEIGHT - 8][10].type = 2;
	tileMap[MAP_HEIGHT - 8][11].type = 2;
	tileMap[MAP_HEIGHT - 8][12].type = 2;

	tileMap[MAP_HEIGHT - 3][10].type = 2;
	tileMap[MAP_HEIGHT - 3][11].type = 2;
	tileMap[MAP_HEIGHT - 3][12].type = 2;
	tileMap[MAP_HEIGHT - 3][13].type = 2;
	tileMap[MAP_HEIGHT - 3][14].type = 2;
	tileMap[MAP_HEIGHT - 3][20].type = 2;
	tileMap[MAP_HEIGHT - 3][21].type = 2;
	tileMap[MAP_HEIGHT - 3][22].type = 2;
	tileMap[MAP_HEIGHT - 8][25].type = 3;
	tileMap[MAP_HEIGHT - 8][26].type = 3;
	tileMap[MAP_HEIGHT - 8][27].type = 3;
	tileMap[MAP_HEIGHT - 8][28].type = 3;
	tileMap[MAP_HEIGHT - 8][29].type = 3;

	tileMap[3][3].type = 2;
	tileMap[3][4].type = 2;
	tileMap[3][5].type = 2;
	tileMap[4][3].type = 2;
	tileMap[4][4].type = 2;
	tileMap[4][5].type = 2;
}

