#include "input.h"

static int mouse_x = 0;
static int mouse_y = 0;
static int mouse_clicked_flag = 0; 

void _input_reset_flags() {
    mouse_clicked_flag = 0;
}

void _input_handle_event(SDL_Event* event) {
    if (event->type == SDL_MOUSEMOTION) {
        mouse_x = event->motion.x;
        mouse_y = event->motion.y;
    }
    
    if (event->type == SDL_MOUSEBUTTONDOWN) {
        if (event->button.button == SDL_BUTTON_LEFT) {
            mouse_clicked_flag = 1;
        }
    }
    
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

int is_key_down(int scancode) {

    const Uint8* state = SDL_GetKeyboardState(NULL);
    
    if (scancode < 0 || scancode >= SDL_NUM_SCANCODES) {
        return 0;
    }
    
    return state[scancode];
}