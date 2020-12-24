/*
* Class for manipulating the menu graphical element
*/
#include "definitions.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string.h>
#include <iostream>
#include "menu_frame.h"

using namespace std;

//Constructor
FrameMenu::FrameMenu(){
    // Define shape of the menu
    background.x = 0;
    background.y = 0;
    background.w = SCREEN_W;
    background.h = SCREEN_H;


    free_seed.x = (SCREEN_W - SIZE_BUTTON_W)/2;
    free_seed.y = SIZE_BUTTON_H;
    free_seed.w = SIZE_BUTTON_W;
    free_seed.h = SIZE_BUTTON_H;

    predefined_seed.x = (SCREEN_W - SIZE_BUTTON_W)/2;
    predefined_seed.y = 3*SIZE_BUTTON_H;
    predefined_seed.w = SIZE_BUTTON_W;
    predefined_seed.h = SIZE_BUTTON_H;

    quit.x = (SCREEN_W - SIZE_BUTTON_W)/2;
    quit.y = 5*SIZE_BUTTON_H;
    quit.w = SIZE_BUTTON_W;
    quit.h = SIZE_BUTTON_H;

    //font = TTF_OpenFont("OpenSans-Regular.ttf", 24);
    font = TTF_OpenFont("Raleway-Regular.ttf", 24);
    color = { 255, 255, 255 };
    surface_free = TTF_RenderText_Blended(font, "Free Initial Seed", color);
    surface_load = TTF_RenderText_Blended(font, "Load Initial Seed", color);
    surface_quit = TTF_RenderText_Blended(font, "Quit Simulator", color);

    texW_free = 0;
    texH_free = 0;
    texW_load = 0;
    texH_load = 0;
    texW_quit = 0;
    texH_quit = 0;

}

//Destructor
FrameMenu::~FrameMenu(){
    SDL_DestroyTexture(texture_free);
    SDL_DestroyTexture(texture_load);
    SDL_DestroyTexture(texture_quit);
    SDL_FreeSurface(surface_free);
    SDL_FreeSurface(surface_load);
    SDL_FreeSurface(surface_quit);
}

void FrameMenu::create_menu(SDL_Renderer *ren) {

    texture_free = SDL_CreateTextureFromSurface(ren, surface_free);
    texture_load = SDL_CreateTextureFromSurface(ren, surface_load);
    texture_quit = SDL_CreateTextureFromSurface(ren, surface_quit);

    SDL_QueryTexture(texture_free, NULL, NULL, &texW_free, &texH_free);
    SDL_QueryTexture(texture_load, NULL, NULL, &texW_load, &texH_load);
    SDL_QueryTexture(texture_quit, NULL, NULL, &texW_quit, &texH_quit);

    SDL_Rect dstrect_free = { (SCREEN_W - SIZE_BUTTON_W)/2 + (SIZE_BUTTON_W - texW_free)/2, SIZE_BUTTON_H + (SIZE_BUTTON_H - texH_free)/2, texW_free, texH_free };
    SDL_Rect dstrect_load = { (SCREEN_W - SIZE_BUTTON_W)/2 + (SIZE_BUTTON_W - texW_load)/2, 3*SIZE_BUTTON_H + (SIZE_BUTTON_H - texH_load)/2, texW_load, texH_load };
    SDL_Rect dstrect_quit = { (SCREEN_W - SIZE_BUTTON_W)/2 + (SIZE_BUTTON_W - texW_quit)/2, 5*SIZE_BUTTON_H + (SIZE_BUTTON_H - texH_quit)/2, texW_quit, texH_quit };

    // Update Renderer
    SDL_RenderClear(ren);
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    SDL_RenderFillRect(ren, &background);
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderFillRect(ren, &free_seed);
    SDL_RenderFillRect(ren, &predefined_seed);
    SDL_RenderFillRect(ren, &quit);
    SDL_RenderCopy(ren, texture_free, NULL, &dstrect_free);
    SDL_RenderCopy(ren, texture_load, NULL, &dstrect_load);
    SDL_RenderCopy(ren, texture_quit, NULL, &dstrect_quit);
}

void FrameMenu::destroy_font() {
    TTF_CloseFont(font);
}

void event_handler_menu(SDL_Event *e, States& state) {
    if (e->type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        // Three possibilities to check in the menu
        if ((x >= (SCREEN_W - SIZE_BUTTON_W)/2) && (x <= (SCREEN_W + SIZE_BUTTON_W)/2)){
            if ((y >= SIZE_BUTTON_H) && (y <= 2 *SIZE_BUTTON_H) ){
                state = FREE;
            }
            else if ((y >= 3*SIZE_BUTTON_H) && (y <= 4*SIZE_BUTTON_H)) {
                state = PREDEFINED;
            }
            else if ((y >= 5*SIZE_BUTTON_H) && (y <= 6*SIZE_BUTTON_H)) {
                state = QUIT;
            }
        }
    }
    else if (e->type == SDL_KEYDOWN){
        if ( (e->key).keysym.sym == SDLK_ESCAPE) {
            state = QUIT;
        }
    }
}
