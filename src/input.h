// 檔案名稱: CPyGfx/src/input.h
#ifndef CPYGFX_INPUT_H
#define CPYGFX_INPUT_H

#include <SDL.h> // 需要 SDL_Event 的定義

/**
 * @brief (內部) 由 event 模組呼叫，用來更新滑鼠狀態
 */
void _input_handle_event(SDL_Event* event);

/**
 * @brief (內部) 在 event poll 迴圈開始前呼叫，重置單次觸發的旗標
 */
void _input_reset_flags();

/**
 * @brief (公開) 取得目前的滑鼠 X 座標
 */
int get_mouse_x();

/**
 * @brief (公開) 取得目前的滑鼠 Y 座標
 */
int get_mouse_y();

/**
 * @brief (公開) 檢查「這一幀」滑鼠左鍵是否「剛被按下」
 * @return 1 (是), 0 (否)
 */
int get_mouse_clicked();

#endif // CPYGFX_INPUT_H