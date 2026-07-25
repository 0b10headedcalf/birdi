LINKS = -lraylib

build:  
	gcc src/birdi.c -o birdi.bin $(LINKS) -std=gnu99 -O3 -Wall -fsanitize=address

debug:
	gcc src/birdi.c -o birdi.bin $(LINKS) -std=gnu99 -O0 -Wall -Wextra -fsanitize=address 
