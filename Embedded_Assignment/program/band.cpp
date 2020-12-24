/*
* Class for manipulating the band element
*/

#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string.h>
#include "definitions.h"
#include "band.h"

using namespace std;

//Constructor
BandFrame::BandFrame(){
    // Define shape of the menu
    band.x = 0;
    band.y = SCREEN_H;
    band.w = SCREEN_W;
    band.h = BAND_H;

    font = TTF_OpenFont("Raleway-Regular.ttf", 24);
    color = { 0, 0, 0 };

    initialized_esc = false;
    initialized_return = false;
    initialized_backspace = false;

    texW_esc = 0;
    texH_esc = 0;
    texW_return = 0;
    texH_return = 0;
    texW_backspace = 0;
    texH_backspace = 0;
}

//Destructor
BandFrame::~BandFrame(){
    if (initialized_esc) {
        SDL_DestroyTexture(texture_esc);
        SDL_FreeSurface(surface_esc);
    }
    if (initialized_return) {
        SDL_DestroyTexture(texture_return);
        SDL_FreeSurface(surface_return);
    }
    if (initialized_backspace) {
        SDL_DestroyTexture(texture_backspace);
        SDL_FreeSurface(surface_backspace);
    }
}

void BandFrame::update_band(SDL_Renderer *ren, States& state) {

    // Update Renderer
    SDL_SetRenderDrawColor(ren, 120, 120, 120, 255);
    SDL_RenderFillRect(ren, &band);

    if (state == MENU) {
        surface_esc = TTF_RenderText_Blended(font, "ESC : Quit", color);
        texture_esc = SDL_CreateTextureFromSurface(ren, surface_esc);
        SDL_QueryTexture(texture_esc, NULL, NULL, &texW_esc, &texH_esc);
        SDL_Rect dstrect_esc = {(SCREEN_W - texW_esc)/2, SCREEN_H + (BAND_H - texH_esc)/2, texW_esc, texH_esc};
        SDL_RenderCopy(ren, texture_esc, NULL, &dstrect_esc);
        initialized_esc = true;
    }
    else if (state == FREE) {
        surface_esc = TTF_RenderText_Blended(font, "ESC : Menu", color);
        surface_return = TTF_RenderText_Blended(font, "RETURN : Start Simulation", color);
        surface_backspace = TTF_RenderText_Blended(font, "BACKSPACE : Save Config", color);
        texture_esc = SDL_CreateTextureFromSurface(ren, surface_esc);
        texture_return = SDL_CreateTextureFromSurface(ren, surface_return);
        texture_backspace = SDL_CreateTextureFromSurface(ren, surface_backspace);
        SDL_QueryTexture(texture_esc, NULL, NULL, &texW_esc, &texH_esc);
        SDL_QueryTexture(texture_return, NULL, NULL, &texW_return, &texH_return);
        SDL_QueryTexture(texture_backspace, NULL, NULL, &texW_backspace, &texH_backspace);
        SDL_Rect dstrect_esc = {(SCREEN_W/2 - texW_esc)/2, SCREEN_H + (BAND_H/2 - texH_esc)/2, texW_esc, texH_esc};
        SDL_Rect dstrect_return = { SCREEN_W/2 + (SCREEN_W/2 - texW_return)/2, SCREEN_H + (BAND_H/2 - texH_return)/2, texW_return, texH_return};
        SDL_Rect dstrect_backspace = { (SCREEN_W - texW_backspace)/2, SCREEN_H + BAND_H/2 + (BAND_H/2 - texH_backspace)/2, texW_backspace, texH_backspace };
        SDL_RenderCopy(ren, texture_esc, NULL, &dstrect_esc);
        SDL_RenderCopy(ren, texture_return, NULL, &dstrect_return);
        SDL_RenderCopy(ren, texture_backspace, NULL, &dstrect_backspace);
        initialized_esc = true;
        initialized_return = true;
        initialized_backspace = true;
    }
    else if (state == SAVE) {
        surface_esc = TTF_RenderText_Blended(font, "ESC : Return to free seed", color);
        texture_esc = SDL_CreateTextureFromSurface(ren, surface_esc);
        SDL_QueryTexture(texture_esc, NULL, NULL, &texW_esc, &texH_esc);
        SDL_Rect dstrect_esc = { (SCREEN_W - texW_esc)/2, SCREEN_H + (BAND_H - texH_esc)/2, texW_esc, texH_esc};
        SDL_RenderCopy(ren, texture_esc, NULL, &dstrect_esc);
        initialized_esc = true;
    }
    else if (state == GAME) {
        surface_esc = TTF_RenderText_Blended(font, "ESC : Return to free seed", color);
        texture_esc = SDL_CreateTextureFromSurface(ren, surface_esc);
        SDL_QueryTexture(texture_esc, NULL, NULL, &texW_esc, &texH_esc);
        SDL_Rect dstrect_esc = { (SCREEN_W - texW_esc)/2, SCREEN_H + (BAND_H - texH_esc)/2, texW_esc, texH_esc};
        SDL_RenderCopy(ren, texture_esc, NULL, &dstrect_esc);
        initialized_esc = true;
    }
    else if(state == PREDEFINED) {
        surface_esc = TTF_RenderText_Blended(font, "ESC : Menu", color);
        texture_esc = SDL_CreateTextureFromSurface(ren, surface_esc);
        SDL_QueryTexture(texture_esc, NULL, NULL, &texW_esc, &texH_esc);
        SDL_Rect dstrect_esc = { (SCREEN_W - texW_esc)/2, SCREEN_H + (BAND_H - texH_esc)/2, texW_esc, texH_esc};
        SDL_RenderCopy(ren, texture_esc, NULL, &dstrect_esc);
        initialized_esc = true;
    }
}

void BandFrame::destroy_font() {
    TTF_CloseFont(font);
}
