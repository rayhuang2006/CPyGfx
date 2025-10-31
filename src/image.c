// 檔案名稱: CPyGfx/src/image.c
#include "image.h"
#include "display.h" // 需要 get_renderer()
#include <SDL_image.h>
#include <stdio.h>

static SDL_Renderer* renderer = NULL;

int image_init() {
    // 初始化 PNG 和 JPG 載入器
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
    // 1. 從檔案載入到 Surface (CPU 記憶體)
    SDL_Surface* surface = IMG_Load(image_path);
    if (surface == NULL) {
        fprintf(stderr, "無法載入圖片 %s: %s\n", image_path, IMG_GetError());
        return NULL;
    }

    // 2. 從 Surface 建立 Texture (GPU 紋理)
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    // 3. 釋放 Surface (不再需要)
    SDL_FreeSurface(surface);

    if (texture == NULL) {
        fprintf(stderr, "無法從圖片建立紋理: %s\n", SDL_GetError());
        return NULL;
    }
    
    // 4. 回傳指向紋理的「void 指標」
    return (void*)texture;
}

void draw_image(void* texture_ptr, int x, int y) {
    if (texture_ptr == NULL) return;

    // 1. 將「void 指標」轉型 (cast) 回「紋理指標」
    SDL_Texture* texture = (SDL_Texture*)texture_ptr;

    // 2. 查詢紋理的寬度和高度
    int w, h;
    if (SDL_QueryTexture(texture, NULL, NULL, &w, &h) != 0) {
        fprintf(stderr, "無法查詢紋理: %s\n", SDL_GetError());
        return;
    }
    
    // 3. 設定目標矩形
    SDL_Rect dst_rect = { x, y, w, h };

    // 4. 繪製
    SDL_RenderCopy(renderer, texture, NULL, &dst_rect);
}

void free_image(void* texture_ptr) {
    if (texture_ptr != NULL) {
        // 釋放 GPU 紋理
        SDL_DestroyTexture((SDL_Texture*)texture_ptr);
    }
}

void image_quit() {
    IMG_Quit();
}