#ifndef CPYGFX_TEXT_H
#define CPYGFX_TEXT_H

/**
 * @brief 初始化 TTF 引擎
 * @return 0 成功, -1 失敗
 */
int text_init();

/**
 * @brief 載入一個字型檔案
 * @param font_path 字型檔的路徑 (例如 "Roboto.ttf")
 * @param size 字型大小 (例如 24)
 * @return 0 成功 (代表字型已載入), -1 失敗
 */
int load_font(const char* font_path, int size);

/**
 * @brief 繪製文字
 * @param text 要繪製的 C 字串
 * @param x 螢幕 X 座標
 * @param y 螢幕 Y 座標
 * @param r, g, b 顏色
 */
void draw_text(const char* text, int x, int y, int r, int g, int b);

/**
 * @brief [新增] 測量文字的寬度與高度
 * @param text 要測量的字串
 * @param w 輸出寬度指標
 * @param h 輸出高度指標
 */
void get_text_size(const char* text, int* w, int* h);

/**
 * @brief 關閉 TTF 引擎並釋放資源
 */
void text_quit();

#endif