all:
	gcc -Isrc/Include -Lsrc/lib/libSDL2.a -o Shooter main.c scene.c textures.c entity.c -lSDL2main -lSDL2 -lSDL2_image
