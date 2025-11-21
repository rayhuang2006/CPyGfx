#ifndef CPYGFX_GEOMETRY_H
#define CPYGFX_GEOMETRY_H

/**
 * @brief 檢查兩個矩形是否重疊 (AABB 碰撞偵測)
 * * @param x1 矩形1 X
 * @param y1 矩形1 Y
 * @param w1 矩形1 寬
 * @param h1 矩形1 高
 * @param x2 矩形2 X
 * @param y2 矩形2 Y
 * @param w2 矩形2 寬
 * @param h2 矩形2 高
 * @return int 1 代表碰撞 (重疊), 0 代表無碰撞
 */
int check_collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);

#endif 
