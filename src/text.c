#include "text.h"
#include "display.h"
#include <SDL_ttf.h>
#include <stdio.h>

static TTF_Font* font = NULL;
static SDL_Renderer* renderer = NULL;

int text_init() {
    if (TTF_Init() == -1) {
        fprintf(stderr, "無法初始化 SDL_ttf: %s\n", TTF_GetError());
        return -1;
    }
    renderer = get_renderer();
    if (renderer == NULL) {
        fprintf(stderr, "Text 模組無法取得渲染器\n");
        return -1;
    }
    return 0;
}

int load_font(const char* font_path, int size) {
    if (font != NULL) {
        TTF_CloseFont(font);
    }
    
    font = TTF_OpenFont(font_path, size);
    if (font == NULL) {
        fprintf(stderr, "無法載入字型 %s: %s\n", font_path, TTF_GetError());
        return -1;
    }
    return 0;
}

void draw_text(const char* text, int x, int y, int r, int g, int b) {
    if (font == NULL) {
        fprintf(stderr, "錯誤: 尚未載入字型\n");
        return;
    }

    SDL_Color color = { (Uint8)r, (Uint8)g, (Uint8)b, 255 };
    
    SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);
    if (surface == NULL) {
        fprintf(stderr, "無法渲染文字: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) {
        fprintf(stderr, "無法建立文字紋理: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect dst_rect = { x, y, surface->w, surface->h };

    SDL_RenderCopy(renderer, texture, NULL, &dst_rect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void get_text_size(const char* text, int* w, int* h) {
    if (font == NULL || text == NULL) {
        if (w) *w = 0;
        if (h) *h = 0;
        return;
    }
    TTF_SizeText(font, text, w, h);
}

void text_quit() {
    if (font != NULL) {
        TTF_CloseFont(font);
        font = NULL;
    }
    TTF_Quit();
}