/*
* Class for manipulating the save/loading frame
*/
#include "definitions.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string.h>
#include <iostream>
#include "predefined_frame.h"
#include "data_processing.h"
#include "table.h"


using namespace std;

//Constructor
FramePredefined::FramePredefined(){
    // Define shape of the menu
    background.x = 0;
    background.y = 0;
    background.w = SCREEN_W;
    background.h = SCREEN_H;

    option1.x = (SCREEN_W - 2*SIZE_BUTTON_W)/3;
    option1.y = SIZE_BUTTON_H;
    option1.w = SIZE_BUTTON_W;
    option1.h = SIZE_BUTTON_H;

    option2.x = (SCREEN_W - 2*SIZE_BUTTON_W)/3;
    option2.y = 3*SIZE_BUTTON_H;
    option2.w = SIZE_BUTTON_W;
    option2.h = SIZE_BUTTON_H;

    option3.x = (SCREEN_W - 2*SIZE_BUTTON_W)/3;
    option3.y = 5*SIZE_BUTTON_H;
    option3.w = SIZE_BUTTON_W;
    option3.h = SIZE_BUTTON_H;

    option4.x = 2*(SCREEN_W - 2*SIZE_BUTTON_W)/3 + SIZE_BUTTON_W;
    option4.y = SIZE_BUTTON_H;
    option4.w = SIZE_BUTTON_W;
    option4.h = SIZE_BUTTON_H;

    option5.x = 2*(SCREEN_W - 2*SIZE_BUTTON_W)/3 + SIZE_BUTTON_W;
    option5.y = 3*SIZE_BUTTON_H;
    option5.w = SIZE_BUTTON_W;
    option5.h = SIZE_BUTTON_H;

    option6.x = 2*(SCREEN_W - 2*SIZE_BUTTON_W)/3 + SIZE_BUTTON_W;
    option6.y = 5*SIZE_BUTTON_H;
    option6.w = SIZE_BUTTON_W;
    option6.h = SIZE_BUTTON_H;

    font = TTF_OpenFont("Raleway-Regular.ttf", 24);
    color = { 255, 255, 255 };
    surface_option1 = TTF_RenderText_Blended(font, "Seed 1", color);
    surface_option2 = TTF_RenderText_Blended(font, "Seed 2", color);
    surface_option3 = TTF_RenderText_Blended(font, "Seed 3", color);
    surface_option4 = TTF_RenderText_Blended(font, "Seed 4", color);
    surface_option5 = TTF_RenderText_Blended(font, "Seed 5", color);
    surface_option6 = TTF_RenderText_Blended(font, "Seed 6", color);

    texW_option1 = 0;
    texH_option1 = 0;
    texW_option2 = 0;
    texH_option2 = 0;
    texW_option3 = 0;
    texH_option3 = 0;
    texW_option4 = 0;
    texH_option4 = 0;
    texW_option5 = 0;
    texH_option5 = 0;
    texW_option6 = 0;
    texH_option6 = 0;

    initialized = false;

}

//Destructor
FramePredefined::~FramePredefined(){
    if (initialized) {
        SDL_DestroyTexture(texture_option1);
        SDL_DestroyTexture(texture_option2);
        SDL_DestroyTexture(texture_option3);
        SDL_DestroyTexture(texture_option4);
        SDL_DestroyTexture(texture_option5);
        SDL_DestroyTexture(texture_option6);
    }
    SDL_FreeSurface(surface_option1);
    SDL_FreeSurface(surface_option2);
    SDL_FreeSurface(surface_option3);
    SDL_FreeSurface(surface_option4);
    SDL_FreeSurface(surface_option5);
    SDL_FreeSurface(surface_option6);
}

void FramePredefined::create_predefined(SDL_Renderer *ren) {

    initialized = true;

    texture_option1 = SDL_CreateTextureFromSurface(ren, surface_option1);
    texture_option2 = SDL_CreateTextureFromSurface(ren, surface_option2);
    texture_option3 = SDL_CreateTextureFromSurface(ren, surface_option3);
    texture_option4 = SDL_CreateTextureFromSurface(ren, surface_option4);
    texture_option5 = SDL_CreateTextureFromSurface(ren, surface_option5);
    texture_option6 = SDL_CreateTextureFromSurface(ren, surface_option6);

    SDL_QueryTexture(texture_option1, NULL, NULL, &texW_option1, &texH_option1);
    SDL_QueryTexture(texture_option2, NULL, NULL, &texW_option2, &texH_option2);
    SDL_QueryTexture(texture_option3, NULL, NULL, &texW_option3, &texH_option3);
    SDL_QueryTexture(texture_option4, NULL, NULL, &texW_option4, &texH_option4);
    SDL_QueryTexture(texture_option5, NULL, NULL, &texW_option5, &texH_option5);
    SDL_QueryTexture(texture_option6, NULL, NULL, &texW_option6, &texH_option6);

    SDL_Rect dstrect_option1 = { (SCREEN_W - 2*SIZE_BUTTON_W)/3 + (SIZE_BUTTON_W - texW_option1)/2, SIZE_BUTTON_H + (SIZE_BUTTON_H - texH_option1)/2, texW_option1, texH_option1};
    SDL_Rect dstrect_option2 = { (SCREEN_W - 2*SIZE_BUTTON_W)/3 + (SIZE_BUTTON_W - texW_option2)/2, 3*SIZE_BUTTON_H + (SIZE_BUTTON_H - texH_option2)/2, texW_option2, texH_option2};
    SDL_Rect dstrect_option3 = { (SCREEN_W - 2*SIZE_BUTTON_W)/3 + (SIZE_BUTTON_W - texW_option3)/2, 5*SIZE_BUTTON_H + (SIZE_BUTTON_H - texH_option3)/2, texW_option3, texH_option3 };
    SDL_Rect dstrect_option4 = { 2*(SCREEN_W - 2*SIZE_BUTTON_W)/3 + SIZE_BUTTON_W + (SIZE_BUTTON_W - texW_option4)/2, SIZE_BUTTON_H + (SIZE_BUTTON_H - texH_option4)/2, texW_option4, texH_option4 };
    SDL_Rect dstrect_option5 = { 2*(SCREEN_W - 2*SIZE_BUTTON_W)/3 + SIZE_BUTTON_W + (SIZE_BUTTON_W - texW_option5)/2, 3*SIZE_BUTTON_H + (SIZE_BUTTON_H - texH_option5)/2, texW_option5, texH_option5 };
    SDL_Rect dstrect_option6 = { 2*(SCREEN_W - 2*SIZE_BUTTON_W)/3 + SIZE_BUTTON_W + (SIZE_BUTTON_W - texW_option6)/2, 5*SIZE_BUTTON_H + (SIZE_BUTTON_H - texH_option6)/2, texW_option6, texH_option6 };

    // Update Renderer
    SDL_RenderClear(ren);
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    SDL_RenderFillRect(ren, &background);
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderFillRect(ren, &option1);
    SDL_RenderFillRect(ren, &option2);
    SDL_RenderFillRect(ren, &option3);
    SDL_RenderFillRect(ren, &option4);
    SDL_RenderFillRect(ren, &option5);
    SDL_RenderFillRect(ren, &option6);
    SDL_RenderCopy(ren, texture_option1, NULL, &dstrect_option1);
    SDL_RenderCopy(ren, texture_option2, NULL, &dstrect_option2);
    SDL_RenderCopy(ren, texture_option3, NULL, &dstrect_option3);
    SDL_RenderCopy(ren, texture_option4, NULL, &dstrect_option4);
    SDL_RenderCopy(ren, texture_option5, NULL, &dstrect_option5);
    SDL_RenderCopy(ren, texture_option6, NULL, &dstrect_option6);
}

void FramePredefined::destroy_font() {
    TTF_CloseFont(font);
}

void load_options(int n, bool table[N_TILES_H][N_TILES_W]) {
    string options[6] = {"option1", "option2", "option3", "option4", "option5", "option6"};
    load_data(table, options[n]);
}

void save_options(int n, bool table[N_TILES_H][N_TILES_W]) {
    string options[6] = {"option1", "option2", "option3", "option4", "option5", "option6"};
    save_data(table, options[n]);
}

void event_handler_predefined(SDL_Event *e, States& state, bool table[N_TILES_H][N_TILES_W], bool initial_table[N_TILES_H][N_TILES_W]) {
    if (e->type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        //printf("Coordinates : x = %d, y = %d", x, y);
        //printf(" Quit is x = [%d, %d], y = [%d, %d] \n", (SCREEN_W - SIZE_BUTTON_W)/2, (SCREEN_W + SIZE_BUTTON_W)/2, 5*SIZE_BUTTON_H, 6*SIZE_BUTTON_H);

        // Three possibilities to check in the menu
        if ((x >= (SCREEN_W - 2*SIZE_BUTTON_W)/3) && (x <= (SCREEN_W - 2*SIZE_BUTTON_W)/3 + SIZE_BUTTON_W)){
            if ((y >= SIZE_BUTTON_H) && (y <= 2 *SIZE_BUTTON_H) ){
                load_options(0, table);
                copy_array(initial_table, table);
                state = FREE;
            }
            else if ((y >= 3*SIZE_BUTTON_H) && (y <= 4*SIZE_BUTTON_H)) {
                load_options(1, table);
                copy_array(initial_table, table);
                state = FREE;
            }
            else if ((y >= 5*SIZE_BUTTON_H) && (y <= 6*SIZE_BUTTON_H)) {
                load_options(2, table);
                copy_array(initial_table, table);
                state = FREE;
            }
        }
        else if ((x >= 2*(SCREEN_W - 2*SIZE_BUTTON_W)/3 + SIZE_BUTTON_W) && (x <= 2*(SCREEN_W - 2*SIZE_BUTTON_W)/3 + 2*SIZE_BUTTON_W)) {
            if ((y >= SIZE_BUTTON_H) && (y <= 2 *SIZE_BUTTON_H) ){
                load_options(3, table);
                copy_array(initial_table, table);
                state = FREE;
            }
            else if ((y >= 3*SIZE_BUTTON_H) && (y <= 4*SIZE_BUTTON_H)) {
                load_options(4, table);
                copy_array(initial_table, table);
                state = FREE;
            }
            else if ((y >= 5*SIZE_BUTTON_H) && (y <= 6*SIZE_BUTTON_H)) {
                load_options(5, table);
                copy_array(initial_table, table);
                state = FREE;
            }
        }
    }
    else if (e->type == SDL_KEYDOWN){
        if ( (e->key).keysym.sym == SDLK_ESCAPE) {
            state = MENU;
        }
    }
}

void event_handler_save(SDL_Event *e, States& state, bool table[N_TILES_H][N_TILES_W]) {
    if (e->type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        //printf("Coordinates : x = %d, y = %d", x, y);
        //printf(" Quit is x = [%d, %d], y = [%d, %d] \n", (SCREEN_W - SIZE_BUTTON_W)/2, (SCREEN_W + SIZE_BUTTON_W)/2, 5*SIZE_BUTTON_H, 6*SIZE_BUTTON_H);

        // Three possibilities to check in the menu
        if ((x >= (SCREEN_W - 2*SIZE_BUTTON_W)/3) && (x <= (SCREEN_W - 2*SIZE_BUTTON_W)/3 + SIZE_BUTTON_W)){
            if ((y >= SIZE_BUTTON_H) && (y <= 2 *SIZE_BUTTON_H) ){
                save_options(0, table);
                state = FREE;
            }
            else if ((y >= 3*SIZE_BUTTON_H) && (y <= 4*SIZE_BUTTON_H)) {
                save_options(1, table);
                state = FREE;
            }
            else if ((y >= 5*SIZE_BUTTON_H) && (y <= 6*SIZE_BUTTON_H)) {
                save_options(2, table);
                state = FREE;
            }
        }
        else if ((x >= 2*(SCREEN_W - 2*SIZE_BUTTON_W)/3 + SIZE_BUTTON_W) && (x <= 2*(SCREEN_W - 2*SIZE_BUTTON_W)/3 + 2*SIZE_BUTTON_W)) {
            if ((y >= SIZE_BUTTON_H) && (y <= 2 *SIZE_BUTTON_H) ){
                save_options(3, table);
                state = FREE;
            }
            else if ((y >= 3*SIZE_BUTTON_H) && (y <= 4*SIZE_BUTTON_H)) {
                save_options(4, table);
                state = FREE;
            }
            else if ((y >= 5*SIZE_BUTTON_H) && (y <= 6*SIZE_BUTTON_H)) {
                save_options(5, table);
                state = FREE;
            }
        }
    }
    else if (e->type == SDL_KEYDOWN){
        if ( (e->key).keysym.sym == SDLK_ESCAPE) {
            state = FREE;
        }
    }
}
