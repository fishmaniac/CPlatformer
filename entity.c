#include "structs.h"

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

	//After drawing, shrinks hitbox to feet, decrease width
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

void initPlayer(Entity *player, Game_s *game) {
	player->x = 0;
	player->y = SCREEN_HEIGHT - (MAP_HEIGHT * TILE_SIZE);
	player->speed = PLAYER_SPEED;
	player->stamina = PLAYER_STAMINA;
	player->scaling = 2.5;
	player->numFrames = 4;
	player->animationDelay = 128;
	player->isJumping = false;
	player->idleR = loadTexture(*game, "assets/gothicvania/Gothic-hero-Files/PNG/gothic-hero-idle.png");
	player->idleL = loadTexture(*game, "assets/gothicvania/Gothic-hero-Files/PNG/gothic-hero-idle-left.png");
	player->runL = loadTexture(*game, "assets/gothicvania/Gothic-hero-Files/PNG/gothic-hero-run-left.png");
	player->runR = loadTexture(*game, "assets/gothicvania/Gothic-hero-Files/PNG/gothic-hero-run.png");
	player->jumpL = loadTexture(*game, "assets/gothicvania/Gothic-hero-Files/PNG/gothic-hero-jump-left.png");
	player->jumpR = loadTexture(*game, "assets/gothicvania/Gothic-hero-Files/PNG/gothic-hero-jump.png");

	player->texture = player->idleR;
}
