# Compiler flags
CFLAGS := -Isrc/Include
LDFLAGS := -Lsrc/lib -lSDL2main -lSDL2 -lSDL2_image

# Target and source files
TARGET := Shooter
SOURCES := main.c scene.c textures.c entity.c

# Default target
all: $(TARGET)

# Rule to build the target
$(TARGET): $(SOURCES)
	gcc $(CFLAGS) -o $@ $^ $(LDFLAGS)
