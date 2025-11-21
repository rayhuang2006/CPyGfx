#include "event.h" 
#include "input.h"
#include <SDL.h>

static SDL_Event event; 

int poll_event() {   

    _input_reset_flags();

    while (SDL_PollEvent(&event)) {
        
        _input_handle_event(&event); 
        
        if (event.type == SDL_QUIT) {
            return 1; 
        }
    }
    return 0; 
}