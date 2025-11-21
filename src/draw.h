#ifndef CPYGFX_DRAW_H
#define CPYGFX_DRAW_H

/**
 * @brief 使用指定顏色清除畫面
 */
void clear(int r, int g, int b);

/**
 * @brief 畫一個像素
 */
void draw_pixel(int x, int y, int r, int g, int b);

/**
 * @brief 畫一條線
 */
void draw_line(int x1, int y1, int x2, int y2, int r, int g, int b);

/**
 * @brief 畫一個空心矩形
 */
void draw_rect(int x, int y, int w, int h, int r, int g, int b);

/**
 * @brief 畫一個實心矩形
 */
void draw_rect_filled(int x, int y, int w, int h, int r, int g, int b);

#endif