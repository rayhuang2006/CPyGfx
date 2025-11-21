#include "geometry.h"

int check_collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {    
    // 1. 檢查 R1 是否在 R2 左側
    if (x1 + w1 <= x2) return 0;
    
    // 2. 檢查 R1 是否在 R2 右側
    if (x1 >= x2 + w2) return 0;
    
    // 3. 檢查 R1 是否在 R2 上方
    if (y1 + h1 <= y2) return 0;
    
    // 4. 檢查 R1 是否在 R2 下方
    if (y1 >= y2 + h2) return 0;
    
    // 5. 如果都不是，那就是重疊了
    return 1;
}