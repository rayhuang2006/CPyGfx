#ifndef CPYGFX_TIME_H
#define CPYGFX_TIME_H

#include <stdint.h>

/**
 * @brief 取得自 SDL 初始化以來的毫秒數
 * @return uint32_t 毫秒 (大約 49 天後會溢位歸零，對小遊戲夠用了)
 */
uint32_t get_ticks();

/**
 * @brief 暫停程式執行指定的毫秒數
 * @param ms 毫秒
 */
void delay(uint32_t ms);

#endif