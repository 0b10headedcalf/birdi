LINKS = -lraylib 
FILE ?= none

build:  
	gcc src/birdi.c -g -std=gnu11 -O3 -Wall -Wextra -fsanitize=address -o birdi.bin $(LINKS)

debug:
	gcc src/birdi.c -g -std=gnu11 -O0 -Wall -Wextra -fsanitize=address -o birdi.bin $(LINKS)

example:
	gcc lib/examples/$(FILE).c -g -std=gnu11 -O0 -fPIC -Wall -Wextra -fsanitize=address -shared -o examples/$(FILE).so 
