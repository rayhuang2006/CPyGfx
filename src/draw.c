#include "draw.h"
#include "display.h" 
#include <SDL.h> 

void clear(int r, int g, int b) {
    SDL_Renderer* renderer = get_renderer(); 
    SDL_SetRenderDrawColor(renderer, r, g, b, 255); 
    SDL_RenderClear(renderer);
}

void draw_pixel(int x, int y, int r, int g, int b) {
    SDL_Renderer* renderer = get_renderer(); 
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderDrawPoint(renderer, x, y);
}

void draw_line(int x1, int y1, int x2, int y2, int r, int g, int b) {
    SDL_Renderer* renderer = get_renderer(); 
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void draw_rect(int x, int y, int w, int h, int r, int g, int b) {
    SDL_Renderer* renderer = get_renderer();
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    
    SDL_Rect rect = { x, y, w, h };
    SDL_RenderDrawRect(renderer, &rect);
}

void draw_rect_filled(int x, int y, int w, int h, int r, int g, int b) {
    SDL_Renderer* renderer = get_renderer();
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    
    SDL_Rect rect = { x, y, w, h };
    SDL_RenderFillRect(renderer, &rect);
}