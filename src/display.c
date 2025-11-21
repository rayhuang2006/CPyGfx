#include "display.h"
#include <stdio.h>

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;

int init_window(int w, int h) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "無法初始化 SDL: %s\n", SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow(
        "CPyGfx (Modular)", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        w, h, 
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        fprintf(stderr, "無法建立視窗: %s\n", SDL_GetError());
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        fprintf(stderr, "無法建立渲染器: %s\n", SDL_GetError());
        return -1;
    }

    return 0;
}

void close_window() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void update() {
    SDL_RenderPresent(renderer);
}

// 實作這個內部函式
SDL_Renderer* get_renderer() {
    return renderer;
}