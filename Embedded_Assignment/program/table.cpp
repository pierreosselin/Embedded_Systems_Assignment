/*
* Utilities for array / table manipulation
*/
#include <stdio.h>
#include <SDL.h>
#include "definitions.h"

using namespace std;


// Copy array 2 into array1
void copy_array(bool table1[N_TILES_H][N_TILES_W], bool table2[N_TILES_H][N_TILES_W]) {
    int i, j;
    for (i = 0; i < N_TILES_H; i++) {
        for (j = 0; j < N_TILES_W; j++) {
            table1[i][j] = table2[i][j];
        }
    }
}

void initialize_array(bool table1[N_TILES_H][N_TILES_W]) {
    int i, j;
    for (i = 0; i < N_TILES_H; i++) {
        for (j = 0; j < N_TILES_W; j++) {
            table1[i][j] = false;
        }
    }
}

void print_table(bool table[N_TILES_H][N_TILES_W]){
    int i,j;
    for(i = 0; i < N_TILES_H; i++){
        for(j = 0; j < N_TILES_W; j++){
            printf(" %d ", table[i][j]);
        }
        printf("\n");
    }
}

void update_frame(SDL_Renderer *ren, bool table[N_TILES_H][N_TILES_W], SDL_Rect rect_table[N_TILES_H][N_TILES_W]) {
    int i, j;
    SDL_RenderClear(ren);
    for(i = 0; i < N_TILES_H; i++){
        for(j = 0; j < N_TILES_W; j++){
            if (table[i][j]) {
                SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
            }
            else {
                SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
            }
            SDL_RenderFillRect(ren, &(rect_table[i][j]));
        }
    }
}

void update_table(bool table[N_TILES_H][N_TILES_W]){
    int aux_table[N_TILES_H][N_TILES_W] = {0};
    int i,j;

    //Corner
    aux_table[0][0] = table[1][0] + table[1][1] + table[0][1];
    aux_table[N_TILES_H - 1][0] = table[N_TILES_H - 1][1] + table[N_TILES_H - 2][0] + table[N_TILES_H - 2][1];
    aux_table[0][N_TILES_W - 1] = table[0][N_TILES_W - 2] + table[1][N_TILES_W - 2] + table[1][N_TILES_W - 1];
    aux_table[N_TILES_H - 1][N_TILES_W - 1] = table[N_TILES_H - 1][N_TILES_W - 2] + table[N_TILES_H - 2][N_TILES_W - 2] + table[N_TILES_H - 2][N_TILES_W - 1];

    //Border except Corner
    for (i = 1; i < N_TILES_H - 1; i++) {
        aux_table[i][0] = table[i - 1][0] + table[i - 1][1] + table[i][1] + table[i + 1][1] + table[i + 1][0];
        aux_table[i][N_TILES_W - 1] = table[i - 1][N_TILES_W - 1] + table[i - 1][N_TILES_W - 2] + table[i][N_TILES_W - 2] + table[i + 1][N_TILES_W - 2] + table[i + 1][N_TILES_W - 1];
    }

    for (j = 1; j < N_TILES_W - 1; j++) {
        aux_table[0][j] = table[0][j - 1] + table[1][j - 1] + table[1][j] + table[1][j + 1] + table[0][j + 1];
        aux_table[N_TILES_H - 1][j] = table[N_TILES_H - 1][j - 1] + table[N_TILES_H - 2][j - 1] + table[N_TILES_H - 2][j] + table[N_TILES_H - 2][j + 1] + table[N_TILES_H - 1][j + 1];
    }

    //Interior
    for(i = 1; i < N_TILES_H - 1; i++){
        for(j = 1; j < N_TILES_W - 1; j++){
            aux_table[i][j] = table[i-1][j-1] + table[i-1][j] + table[i-1][j+1] + table[i][j+1] + table[i+1][j+1] + table[i+1][j] + table[i+1][j-1] + table[i][j-1];
        }
    }

    //Update table
    for(i = 0; i < N_TILES_H; i++){
        for(j = 0; j < N_TILES_W; j++){
            table[i][j] = ((table[i][j] == 1) && (aux_table[i][j] <= 3) && (aux_table[i][j] >= 2)) || ((table[i][j] == 0) && (aux_table[i][j] == 3));
        }
    }
}

void initialize_board(SDL_Rect rect_table[N_TILES_H][N_TILES_W]){
    int i, j;
    for (i = 0; i < N_TILES_H; i++){
        for (j = 0; j < N_TILES_W; j++) {
            rect_table[i][j].x = SIZE_TILES*j;
            rect_table[i][j].y = SIZE_TILES*i;
            rect_table[i][j].w = SIZE_TILES;
            rect_table[i][j].h = SIZE_TILES;
        }
    }
}
