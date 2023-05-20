#include "structs.h"

SDL_Texture *loadTexture(Game_s game, char *filename) {
	SDL_Texture *texture;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	texture = IMG_LoadTexture(game.renderer, filename);

	return texture;
}

void blitAnimated(Game_s *game, Entity *player) {
	SDL_Rect src;  // Rect representing the source frame within the texture

	int textureWidth, textureHeight;
	SDL_QueryTexture(player->texture, NULL, NULL, &textureWidth, &textureHeight);

	player->w = textureWidth / player->numFrames; // Width of each frame
	player->h = textureHeight; // Height of each frame (assuming one row)

	src.x = player->currentFrame * player->w; // Calculate the source frame's x-coordinate
	src.y = 0;                         // Y-coordinate is 0 for a single row
	src.w = player->w;                // Width of the source frame
	src.h = player->h;               // Height of the source frame

	player->entityRect.x = player->x - game->camX;
	player->entityRect.y = player->y - game->camY;
	
	player->entityRect.w = src.w * player->scaling;
	player->entityRect.h = src.h * player->scaling;
	player->w *= player->scaling;
	player->h *= player->scaling;
	
	
	SDL_RenderCopy(game->renderer, player->texture, &src, &player->entityRect);

	//Shrinks hitbox to feet, decrease width
	player->entityRect.x += (player->entityRect.w / COLLISION_MARGIN);
	player->entityRect.w /= (COLLISION_MARGIN / 2);
	player->entityRect.y += player->entityRect.h - (player->entityRect.h / player->entityRect.h);
	player->entityRect.h /= player->entityRect.h;


}

bool checkCollision(SDL_Rect rectA, SDL_Rect rectB) {
	return (
	rectA.x + rectA.w >= rectB.x &&
	rectB.x + rectB.w >= rectA.x &&
	rectA.y + rectA.h >= rectB.y &&
	rectB.y + rectB.h >= rectA.y
	);
}

bool checkCollisionBottom(SDL_Rect rectA, SDL_Rect rectB) {
	return (
	rectA.x + rectA.w >= rectB.x &&
	rectB.x + rectB.w >= rectA.x &&
	rectA.y + rectA.h >= rectB.y &&
	rectB.y + rectB.h >= rectA.y
	);
}

