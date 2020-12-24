/*
* Event handler when state of designing the initial seed
*/
#include <stdio.h>
#include <SDL.h>
#include <fstream>
#include "table.h"
#include "definitions.h"

using namespace std;

void event_handler_free(SDL_Event *e, States& state, bool table[N_TILES_H][N_TILES_W], bool initial_table[N_TILES_H][N_TILES_W]) {
    static int previous_x = -1, previous_y = -1;
    static bool button_press = false;
    if (e->type == SDL_MOUSEBUTTONDOWN) {
        button_press = true;
    }
    else if (e->type == SDL_MOUSEBUTTONUP) {
        button_press = false;
    }
    else if (e->type == SDL_KEYDOWN){
        if ( (e->key).keysym.sym == SDLK_RETURN) {
            copy_array(initial_table, table);
            state = GAME;
        }
        else if ( (e->key).keysym.sym == SDLK_ESCAPE) {
            state = MENU;
        }
        else if ( (e->key).keysym.sym == SDLK_BACKSPACE) {
            state = SAVE;
        }
    }
    if (button_press){
        int x, y, coordinate_x, coordinate_y;
        SDL_GetMouseState(&x, &y);

        coordinate_x = x / (SIZE_TILES);
        coordinate_y = y / (SIZE_TILES);

        // Check if previously up then ok, is previously down, change only if different coordinate
        if ((!button_press) || !((previous_x == coordinate_x) && (previous_y == coordinate_y))) {
            table[coordinate_y][coordinate_x] = !(table[coordinate_y][coordinate_x]);
            previous_x = coordinate_x;
            previous_y = coordinate_y;
        }
    }
}
