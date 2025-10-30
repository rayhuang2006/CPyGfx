// 檔案名稱: CPyGfx/src/text.c
#include "text.h"
#include "display.h" // 需要 get_renderer()
#include <SDL_ttf.h>
#include <stdio.h>

// 靜態全域變數，用來儲存已載入的字型
static TTF_Font* font = NULL;
// 靜態全域變數，用來儲存渲染器 (方便使用)
static SDL_Renderer* renderer = NULL;

int text_init() {
    if (TTF_Init() == -1) {
        fprintf(stderr, "無法初始化 SDL_ttf: %s\n", TTF_GetError());
        return -1;
    }
    // 順便取得並儲存渲染器
    renderer = get_renderer();
    if (renderer == NULL) {
        fprintf(stderr, "Text 模組無法取得渲染器\n");
        return -1;
    }
    return 0;
}

int load_font(const char* font_path, int size) {
    // 如果已經載入過字型，先釋放
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
    
    // 1. 渲染文字到一個 "Surface" (CPU 記憶體)
    SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);
    if (surface == NULL) {
        fprintf(stderr, "無法渲染文字: %s\n", TTF_GetError());
        return;
    }

    // 2. 將 "Surface" 轉換為 "Texture" (GPU 紋理)
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) {
        fprintf(stderr, "無法建立文字紋理: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }

    // 3. 準備目標繪製矩形
    SDL_Rect dst_rect = { x, y, surface->w, surface->h };

    // 4. 繪製紋理
    SDL_RenderCopy(renderer, texture, NULL, &dst_rect);

    // 5. 釋放資源 (非常重要)
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void text_quit() {
    if (font != NULL) {
        TTF_CloseFont(font);
        font = NULL;
    }
    TTF_Quit();
}