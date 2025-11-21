#include "image.h"
#include "display.h"
#include <SDL_image.h>
#include <stdio.h>

static SDL_Renderer* renderer = NULL;

int image_init() {
    int flags = IMG_INIT_PNG | IMG_INIT_JPG;
    if ((IMG_Init(flags) & flags) != flags) {
        fprintf(stderr, "無法初始化 SDL_image (PNG, JPG): %s\n", IMG_GetError());
        return -1;
    }
    
    renderer = get_renderer();
    if (renderer == NULL) {
        fprintf(stderr, "Image 模組無法取得渲染器\n");
        return -1;
    }
    return 0;
}

void* load_image(const char* image_path) {
    SDL_Surface* surface = IMG_Load(image_path);
    if (surface == NULL) {
        fprintf(stderr, "無法載入圖片 %s: %s\n", image_path, IMG_GetError());
        return NULL;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_FreeSurface(surface);

    if (texture == NULL) {
        fprintf(stderr, "無法從圖片建立紋理: %s\n", SDL_GetError());
        return NULL;
    }
    
    return (void*)texture;
}

void draw_image(void* texture_ptr, int x, int y) {
    if (texture_ptr == NULL) return;

    SDL_Texture* texture = (SDL_Texture*)texture_ptr;

    int w, h;
    if (SDL_QueryTexture(texture, NULL, NULL, &w, &h) != 0) {
        fprintf(stderr, "無法查詢紋理: %s\n", SDL_GetError());
        return;
    }
    
    SDL_Rect dst_rect = { x, y, w, h };

    SDL_RenderCopy(renderer, texture, NULL, &dst_rect);
}

void free_image(void* texture_ptr) {
    if (texture_ptr != NULL) {
        SDL_DestroyTexture((SDL_Texture*)texture_ptr);
    }
}

void image_quit() {
    IMG_Quit();
}