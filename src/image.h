#ifndef CPYGFX_IMAGE_H
#define CPYGFX_IMAGE_H

#include <SDL.h>

/**
 * @brief 初始化 IMG 引擎 (PNG, JPG)
 * @return 0 成功, -1 失敗
 */
int image_init();

/**
 * @brief 載入一個圖片檔案，並將其轉換為 GPU 紋理
 * @param image_path 圖片檔案的路徑
 * @return void* 指向 SDL_Texture 的指標。失敗則回傳 NULL。
 */
void* load_image(const char* image_path);

/**
 * @brief 繪製一個已載入的紋理 (圖片)
 * @param texture_ptr (void*) 之前由 load_image() 回傳的指標
 * @param x 螢幕 X 座標
 * @param y 螢幕 Y 座標
 */
void draw_image(void* texture_ptr, int x, int y);

/**
 * @brief (新增) 繪製圖片並縮放到指定大小
 * @param w 目標寬度
 * @param h 目標高度
 */
void draw_image_rect(void* texture_ptr, int x, int y, int w, int h);

/**
 * @brief 釋放一個紋理的記憶體
 * @param texture_ptr (void*) 之前由 load_image() 回傳的指標
 */
void free_image(void* texture_ptr);

/**
 * @brief 關閉 IMG 引擎
 */
void image_quit();

#endif