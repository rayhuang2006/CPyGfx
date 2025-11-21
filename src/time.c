#include "time.h"
#include <SDL.h>

uint32_t get_ticks() {
    return SDL_GetTicks();
}

void delay(uint32_t ms) {
    SDL_Delay(ms);
}