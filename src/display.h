// 檔案名稱: src/display.h
#ifndef CPYGFX_DISPLAY_H
#define CPYGFX_DISPLAY_H

#include <SDL.h> // 需要 SDL_Renderer 的定義

/**
 * @brief 初始化視窗和渲染器
 * @return 0 成功, -1 失敗
 */
int init_window(int w, int h);

/**
 * @brief 關閉並清理資源
 */
void close_window();

/**
 * @brief 將後台緩衝區的內容更新到螢幕上
 */
void update();

/**
 * @brief (內部函式) 取得全域的渲染器
 * @return SDL_Renderer*
 */
SDL_Renderer* get_renderer();

#endif // CPYGFX_DISPLAY_H