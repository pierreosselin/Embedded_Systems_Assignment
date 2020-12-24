#include "definitions.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string.h>


//using namespace std;

// Create Menu frame for renderer and window

#ifndef MENUFRAME
#define MENUFRAME

class FrameMenu {
    public:
        FrameMenu();
        ~FrameMenu();
        void create_menu(SDL_Renderer *ren);
        void destroy_font();

    private:
        SDL_Rect background, free_seed, predefined_seed, quit;
        TTF_Font * font;
        SDL_Color color;
        SDL_Surface *surface_free, *surface_load, *surface_quit;
        SDL_Texture *texture_free, *texture_load, *texture_quit;
        int texW_free, texH_free, texW_load, texH_load, texW_quit, texH_quit;
};

#endif


void event_handler_menu(SDL_Event *e, States& state);
