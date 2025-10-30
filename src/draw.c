// 檔案名稱: CPyGfx/src/draw.c
#include "draw.h"
#include "display.h" // 需要 get_renderer()
#include <SDL.h>     // 需要 SDL_Rect

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

// --- 新增的函式 ---
void draw_rect(int x, int y, int w, int h, int r, int g, int b) {
    SDL_Renderer* renderer = get_renderer();
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    
    // SDL_Rect 是一個結構體，用來定義矩形
    SDL_Rect rect = { x, y, w, h };
    SDL_RenderDrawRect(renderer, &rect);
}

void draw_rect_filled(int x, int y, int w, int h, int r, int g, int b) {
    SDL_Renderer* renderer = get_renderer();
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    
    SDL_Rect rect = { x, y, w, h };
    SDL_RenderFillRect(renderer, &rect);
}