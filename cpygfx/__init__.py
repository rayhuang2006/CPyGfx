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
    
    # --- 新增 ---
    draw_rect,
    draw_rect_filled,
    get_mouse_clicked
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
    
    # --- 新增 ---
    "draw_rect",
    "draw_rect_filled",
    "get_mouse_clicked"
]