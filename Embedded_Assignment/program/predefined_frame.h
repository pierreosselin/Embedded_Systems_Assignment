#include "definitions.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string.h>


// Create Predefined Frame for renderer and window

#ifndef PREDEFINED_FRAME
#define PREDEFINED_FRAME

class FramePredefined {
    public:
        FramePredefined();
        ~FramePredefined();
        void create_predefined(SDL_Renderer *ren);
        void destroy_font();

    private:
        SDL_Rect background, option1, option2, option3, option4, option5, option6;
        TTF_Font *font;
        SDL_Color color;
        bool initialized;
        SDL_Surface *surface_option1, *surface_option2, *surface_option3, *surface_option4, *surface_option5, *surface_option6;
        SDL_Texture *texture_option1, *texture_option2, *texture_option3, *texture_option4, *texture_option5, *texture_option6;
        int texW_option1, texH_option1, texW_option2, texH_option2, texW_option3, texH_option3, texW_option4, texH_option4, texW_option5, texH_option5, texW_option6, texH_option6;
};

#endif

void event_handler_predefined(SDL_Event *e, States& state, bool table[N_TILES_H][N_TILES_W], bool initial_table[N_TILES_H][N_TILES_W]);
void event_handler_save(SDL_Event *e, States& state, bool table[N_TILES_H][N_TILES_W]);
void load_options(int n, bool table[N_TILES_H][N_TILES_W]);
void save_options(int n, bool table[N_TILES_H][N_TILES_W]);
