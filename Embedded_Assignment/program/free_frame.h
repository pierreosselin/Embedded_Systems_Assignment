#include <stdio.h>
#include <SDL.h>
#include "definitions.h"

void event_handler_free(SDL_Event *e, States& state, bool table[N_TILES_H][N_TILES_W], bool initial_table[N_TILES_H][N_TILES_W]);
