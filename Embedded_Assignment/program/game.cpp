/*
* Event handler in the simulation of the game
*/

#include <stdio.h>
#include <SDL.h>
#include <fstream>
#include "table.h"
#include "definitions.h"

using namespace std;

void event_handler_game(SDL_Event *e, States& state, bool table[N_TILES_H][N_TILES_W], bool initial_table[N_TILES_H][N_TILES_W], SDL_Rect rect_table[N_TILES_H][N_TILES_W]) {
    if (e->type == SDL_KEYDOWN){
        if ( (e->key).keysym.sym == SDLK_ESCAPE) {
            copy_array(table, initial_table);
            state = FREE;
        }
    }
}

void update_game(SDL_Renderer *ren, bool table[N_TILES_H][N_TILES_W], SDL_Rect rect_table[N_TILES_H][N_TILES_W]) {
    static int iterations = 0;

    iterations = iterations + 1;

    SDL_RenderClear(ren);

    update_frame(ren, table, rect_table);

    update_table(table);
}
