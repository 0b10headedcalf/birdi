LINKS = -lraylib

build:  
	gcc src/birdi.c -o birdi.bin $(LINKS) -O3 -Wall -fsanitize=address

debug:
	gcc src/birdi.c -o birdi.bin $(LINKS) -O0 -Wall -Wextra -fsanitize=address 
