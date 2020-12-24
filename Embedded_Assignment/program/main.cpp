#include <stdio.h>
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <fstream>
#include <string.h>
#include "table.h"
#include "definitions.h"
#include "data_processing.h"
#include "menu_frame.h"
#include "free_frame.h"
#include "game.h"
#include "band.h"
#include "predefined_frame.h"

using namespace std;


int main(int argc, char* args[]) {

    if (SDL_Init(SDL_INIT_VIDEO) != 0){
            cout << "SDL_Init Error: " << SDL_GetError() << endl;
	return 0;
    }

    SDL_Window *win = SDL_CreateWindow("The Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H + BAND_H, SDL_WINDOW_SHOWN);
    if (win == nullptr){
        cout << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
        SDL_Quit();
        return 0;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr){
        SDL_DestroyWindow(win);
        cout << "SDL_CreateRenderer Error: " << SDL_GetError() << endl;
        SDL_Quit();
        return 0;
    }
    if( TTF_Init() == -1 ){
            printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
            return 0;
        }

    //Initialize Menu and filename
    States state = MENU;

    int iterations = 0;
    FrameMenu menuFrame;
    FramePredefined predefinedFrame;
    BandFrame bandFrame;

    //Initialize board (Possibly load it)
    bool table[N_TILES_H][N_TILES_W] = {0};
    bool initial_table[N_TILES_H][N_TILES_W] = {0};
    SDL_Rect rect_table[N_TILES_H][N_TILES_W];
    SDL_Rect band;

    initialize_board(rect_table);

    //Initialize font menu
    menuFrame.create_menu(ren);
    bandFrame.update_band(ren, state);

    //Render Window
    SDL_RenderPresent(ren);

    SDL_Event e;
    while (state != QUIT){
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                state = QUIT;
            }
            if (state == MENU){
                event_handler_menu(&e, state);
                if (state == PREDEFINED) {
                    SDL_RenderClear(ren);
                    predefinedFrame.create_predefined(ren);
                }
                else if (state == FREE){
                    initialize_array(table);
                }
            }
            else if (state == FREE) {
                event_handler_free(&e, state, table, initial_table);
                update_frame(ren, table, rect_table);
                if (state == MENU){
                    menuFrame.create_menu(ren);
                }
                else if (state == SAVE){
                    predefinedFrame.create_predefined(ren);
                }
            }
            else if (state == PREDEFINED) {
                event_handler_predefined(&e, state, table, initial_table);
                if (state == MENU){
                    SDL_RenderClear(ren);
                    menuFrame.create_menu(ren);
                }
            }
            else if (state == SAVE) {
                event_handler_save(&e, state, table);
                if (state == GAME){
                    SDL_RenderClear(ren);
                }
            }
            else if (state == GAME) {
                event_handler_game(&e, state, table, initial_table, rect_table);
            }
        }
        if (state == GAME) {
            update_game(ren, table, rect_table);
        }
        bandFrame.update_band(ren, state);
        SDL_RenderPresent(ren);
        SDL_Delay(FRAME_RATE);
    }

    SDL_DestroyWindow(win);
    menuFrame.destroy_font();
    predefinedFrame.destroy_font();
    TTF_Quit();
    SDL_Quit();
    return 0;
}
