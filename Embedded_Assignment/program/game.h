#include <stdio.h>
#include <SDL.h>
#include "definitions.h"

using namespace std;

void update_game(SDL_Renderer *ren, bool table[N_TILES_H][N_TILES_W], SDL_Rect rect_table[N_TILES_H][N_TILES_W]);
void event_handler_game(SDL_Event *e, States& state, bool table[N_TILES_H][N_TILES_W], bool initial_table[N_TILES_H][N_TILES_W], SDL_Rect rect_table[N_TILES_H][N_TILES_W]);
