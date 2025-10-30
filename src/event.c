// 檔案名稱: CPyGfx/src/event.c
#include "event.h" 
#include "input.h" // 包含 input 模組
#include <SDL.h>

static SDL_Event event; 

int poll_event() {
    
    // --- 關鍵修改 ---
    // 在處理新事件前，先重置 input 的「單次點擊」旗標
    _input_reset_flags();
    // ------------------

    while (SDL_PollEvent(&event)) {
        
        // 把事件餵給 input 模組去處理
        _input_handle_event(&event); 
        
        // 處理關閉事件
        if (event.type == SDL_QUIT) {
            return 1; 
        }
    }
    return 0; 
}