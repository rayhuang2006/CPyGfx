# 檔案名稱: CPyGfx/cpygfx/core.py
# (已修正，加回 update 和 close_window)
import ctypes
import os
import importlib.util  

spec = importlib.util.find_spec("cpygfx._cpygfx_core")

if spec is None or spec.origin is None:
    raise ImportError("無法找到 CPyGfx 的核心 C 函式庫。請確保專案已正確編譯。")

lib_path = spec.origin

try:
    _lib = ctypes.CDLL(lib_path)
except OSError as e:
    print(f"載入 C 函式庫失敗: {e}")
    raise

# --- 2. 定義 C 函式原型 (Prototypes) ---
_lib.init_window.argtypes = [ctypes.c_int, ctypes.c_int]
_lib.init_window.restype = ctypes.c_int

_lib.poll_event.argtypes = []
_lib.poll_event.restype = ctypes.c_int

_lib.clear.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_int]
_lib.clear.restype = None

_lib.draw_pixel.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int]
_lib.draw_pixel.restype = None

_lib.draw_line.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int]
_lib.draw_line.restype = None

_lib.get_mouse_x.argtypes = []
_lib.get_mouse_x.restype = ctypes.c_int

_lib.get_mouse_y.argtypes = []
_lib.get_mouse_y.restype = ctypes.c_int

# --- (遺漏的函式綁定已加回) ---
_lib.update.argtypes = []
_lib.update.restype = None

_lib.close_window.argtypes = []
_lib.close_window.restype = None
# ------------------------------

_lib.draw_rect.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int]
_lib.draw_rect.restype = None

_lib.draw_rect_filled.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int]
_lib.draw_rect_filled.restype = None

_lib.get_mouse_clicked.argtypes = []
_lib.get_mouse_clicked.restype = ctypes.c_int

# --- 3. 將 C 函式包裝成 Python 函式 ---
def init_window(w: int, h: int) -> bool:
    if _lib.init_window(w, h) != 0:
        print("CPyGfx 核心：初始化失敗。")
        return False
    return True

def poll_event() -> bool:
    return _lib.poll_event() == 1

def clear(r: int, g: int, b: int):
    _lib.clear(r, g, b)

def draw_pixel(x: int, y: int, r: int, g: int, b: int):
    _lib.draw_pixel(x, y, r, g, b)

def draw_line(x1: int, y1: int, x2: int, y2: int, r: int, g: int, b: int):
    _lib.draw_line(x1, y1, x2, y2, r, g, b)

def get_mouse_x() -> int:
    return _lib.get_mouse_x()

def get_mouse_y() -> int:
    return _lib.get_mouse_y()

# --- (遺漏的 Python 函式已加回) ---
def update():
    """更新螢幕顯示。"""
    _lib.update()

def close_window():
    """關閉視窗並結束 SDL。"""
    _lib.close_window()
# ---------------------------------

def draw_rect(x: int, y: int, w: int, h: int, r: int, g: int, b: int):
    """畫一個 (r, g, b) 顏色的空心矩形。"""
    _lib.draw_rect(x, y, w, h, r, g, b)

def draw_rect_filled(x: int, y: int, w: int, h: int, r: int, g: int, b: int):
    """畫一個 (r, g, b) 顏色的實心矩形。"""
    _lib.draw_rect_filled(x, y, w, h, r, g, b)

def get_mouse_clicked() -> bool:
    """檢查「這一幀」滑鼠左鍵是否「剛被按下」"""
    return _lib.get_mouse_clicked() == 1