# 檔案名稱: CPyGfx/cpygfx/__init__.py

from .core import (
    init_window,
    poll_event,
    clear,
    draw_pixel,
    update,
    close_window,
    draw_line,
    get_mouse_x,
    get_mouse_y,
    draw_rect,
    draw_rect_filled,
    get_mouse_clicked,
    text_init,
    load_font,
    draw_text,
    text_quit
)

__all__ = [
    "init_window",
    "poll_event",
    "clear",
    "draw_pixel",
    "update",
    "close_window",
    "draw_line",
    "get_mouse_x",
    "get_mouse_y",
    "draw_rect",
    "draw_rect_filled",
    "get_mouse_clicked",
    "text_init",
    "load_font",
    "draw_text",
    "text_quit"
]