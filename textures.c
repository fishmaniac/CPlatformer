#include "structs.h"

SDL_Texture *loadTexture(Game_s game, char *filename) {
	SDL_Texture *texture;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	texture = IMG_LoadTexture(game.renderer, filename);

	return texture;
}

void blitAnimated(Game_s *game, Entity *player) {
	SDL_Rect src;  // Rect representing the source frame within the texture
	SDL_Rect dest; // Rect representing the destination position on the screen

	int textureWidth, textureHeight;
	SDL_QueryTexture(player->texture, NULL, NULL, &textureWidth, &textureHeight);

	player->w = textureWidth / player->numFrames; // Width of each frame
	player->h = textureHeight; // Height of each frame (assuming one row)

	src.x = player->currentFrame * player->w; // Calculate the source frame's x-coordinate
	src.y = 0;                         // Y-coordinate is 0 for a single row
	src.w = player->w;                // Width of the source frame
	src.h = player->h;               // Height of the source frame

	dest.x = player->x - game->camX;
	dest.y = player->y - game->camY;

	dest.w = src.w * player->scaling;
	dest.h = src.h * player->scaling;
	player->w *= player->scaling;
	player->h *= player->scaling;

	SDL_RenderCopy(game->renderer, player->texture, &src, &dest);
}

bool checkCollision(Entity *rect1, Entity *rect2) {
	if (rect1->x < rect2->x + rect2->w &&
		rect1->x + rect1->w > rect2->x &&
		rect1->y < rect2->y + rect2->h &&
		rect1->y + rect1->h > rect2->y) {
		// rects are colliding
		return true;
	}
	// rects are not colliding
	return false;
}

void handleCollisions(Entity *player, Entity *environment, int numEntities) {
	for (int i = 0; i < numEntities; i++) {
		//SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Colliding with %d entities", numEntities);
		if (checkCollision(player, &environment[i])) {
			player->y -= FRAME_TIME; //OR GRAVITY
			player->isColliding = true;
		}
		else {
			player->y += FRAME_TIME;
			player->isColliding = false;
		}
	}
}


