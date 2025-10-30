// 檔案名稱: CPyGfx/src/input.c
#include "input.h"

// 靜態變數，只在這個檔案中可見
static int mouse_x = 0;
static int mouse_y = 0;
static int mouse_clicked_flag = 0; // 我們的「單次點擊」旗標

// 在每一幀的事件處理開始前，重置這個旗標
void _input_reset_flags() {
    mouse_clicked_flag = 0;
}

void _input_handle_event(SDL_Event* event) {
    // 檢查事件是否為滑鼠移動
    if (event->type == SDL_MOUSEMOTION) {
        mouse_x = event->motion.x;
        mouse_y = event->motion.y;
    }
    
    // 檢查事件是否為滑鼠「按下」
    if (event->type == SDL_MOUSEBUTTONDOWN) {
        if (event->button.button == SDL_BUTTON_LEFT) {
            mouse_clicked_flag = 1; // 設定旗標
        }
    }
    
    // (我們暫時不處理 SDL_MOUSEBUTTONUP)
}

int get_mouse_x() {
    return mouse_x;
}

int get_mouse_y() {
    return mouse_y;
}

int get_mouse_clicked() {
    return mouse_clicked_flag;
}