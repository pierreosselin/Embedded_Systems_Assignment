#include "definitions.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string.h>


// Create Predefined Frame for renderer and window

#ifndef BAND_FRAME
#define BAND_FRAME

class BandFrame {
    public:
        BandFrame();
        ~BandFrame();
        void update_band(SDL_Renderer *ren, States& state);
        void destroy_font();

    private:
        SDL_Rect band, rec_esc, rec_return, rec_backspace;
        TTF_Font *font;
        SDL_Color color;
        bool initialized_esc, initialized_return, initialized_backspace;
        // How Many buttons? Esc, Return, Backspace
        SDL_Surface *surface_esc, *surface_return, *surface_backspace;
        SDL_Texture *texture_esc, *texture_return, *texture_backspace;
        int texW_esc, texH_esc, texW_return, texH_return, texW_backspace, texH_backspace;
};

#endif
