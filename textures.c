#include "structs.h"

void renderGameObjects(Game_s *game, Entity *player, Tile tileMap[MAP_HEIGHT][MAP_WIDTH]) {
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



void initMap(Tile tileMap[MAP_HEIGHT][MAP_WIDTH]) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            tileMap[y][x].type = 0; // Set all tiles initially as empty

            // Set the position and size of the tile
            tileMap[y][x].rect.x = x * TILE_SIZE;
            tileMap[y][x].rect.y = y * TILE_SIZE;
            tileMap[y][x].rect.w = TILE_SIZE;
            tileMap[y][x].rect.h = TILE_SIZE;
        }
    }

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

    // Example: Set some tiles as tiles
    tileMap[3][3].type = 2;
    tileMap[3][4].type = 2;
    tileMap[3][5].type = 2;
    tileMap[4][3].type = 2;
    tileMap[4][4].type = 2;
    tileMap[4][5].type = 2;
}

void renderMap(Game_s *game, Entity *player, Tile tileMap[MAP_HEIGHT][MAP_WIDTH]) {
    player->isColliding = false;
    int collidingTiles = 0;

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            Tile tile = tileMap[y][x];

            // Set the tile color based on its type
            SDL_Color color;
            if (tile.type == 0) {
                color = COLOR_WHITE;
            } else if (tile.type == 2) {
                color = COLOR_BLACK;
            }

            tile.rect.x -= (game->camX);
            tile.rect.y -= (game->camY);
            
            SDL_SetRenderDrawColor(game->renderer, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(game->renderer, &tile.rect);

            if (tile.type != 0 && checkCollision(player->entityRect, tile.rect)) {
                collidingTiles++;

/*                 SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Colliding with entity: %d %d\nPlayer height: %d", y, x, player->y); */
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

void renderTexture(Game_s *game, Entity *player) {
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
