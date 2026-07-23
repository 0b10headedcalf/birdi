CFLAGS = -O -Wall
RAYLIB = -lraylib

birdi: src/birdi.c
	clang src/birdi.c -o build/birdi.bin $(CFLAGS) $(RAYLIB)
