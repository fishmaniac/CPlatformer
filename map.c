#include "structs.h"

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

    // Example: Set some tiles as tiles
    tileMap[3][3].type = 2;
    tileMap[3][4].type = 2;
    tileMap[3][5].type = 2;
    tileMap[4][3].type = 2;
    tileMap[4][4].type = 2;
    tileMap[4][5].type = 2;
}

void renderMap(Game_s *game, Entity *player, Tile tileMap[MAP_HEIGHT][MAP_WIDTH]) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            Tile tile = tileMap[y][x];

            // Set the tile color based on its type
            SDL_Color color;
            if (tile.type == 0) {
                color = (SDL_Color){255, 255, 255, 255}; // White for empty
            } else if (tile.type == 2) {
                color = (SDL_Color){0, 0, 0, 255}; // Black for empty tiles
            }

            // Render relative to camera
            // (&tile.rect)->x = player->x;
            // (&tile.rect)->y = player->y;
            tile.rect.x -= (game->camX);
            tile.rect.y -= (game->camY);
            SDL_SetRenderDrawColor(game->renderer, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(game->renderer, &tile.rect);
        }
    }
}
