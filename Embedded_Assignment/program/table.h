#include <SDL.h>
#include "definitions.h"

void initialize_board(SDL_Rect rect_table[N_TILES_H][N_TILES_W]);
void print_table(bool table[N_TILES_H][N_TILES_W]);
void update_frame(SDL_Renderer *ren, bool table[N_TILES_H][N_TILES_W], SDL_Rect rect_table[N_TILES_H][N_TILES_W]);
void update_table(bool table[N_TILES_H][N_TILES_W]);
void copy_array(bool table1[N_TILES_H][N_TILES_W], bool table2[N_TILES_H][N_TILES_W]);
void initialize_array(bool table1[N_TILES_H][N_TILES_W]);
void initialize_band(SDL_Rect *band);
void update_band(SDL_Renderer *ren, SDL_Rect *band, States& state);
