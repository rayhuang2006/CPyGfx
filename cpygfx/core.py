# 檔案名稱: CPyGfx/cpygfx/core.py
# (已升級支援 image 模組)
import ctypes
import os
import sys
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

# 輔助函式：Python str -> C bytes
def _to_c_string(py_str):
    if py_str is None:
        return None
    return py_str.encode(sys.getdefaultencoding())

# --- 2. 定義 C 函式原型 (Prototypes) ---

# Display / Event / Input
_lib.init_window.argtypes = [ctypes.c_int, ctypes.c_int]
_lib.init_window.restype = ctypes.c_int
_lib.poll_event.argtypes = []
_lib.poll_event.restype = ctypes.c_int
_lib.get_mouse_x.argtypes = []
_lib.get_mouse_x.restype = ctypes.c_int
_lib.get_mouse_y.argtypes = []
_lib.get_mouse_y.restype = ctypes.c_int
_lib.get_mouse_clicked.argtypes = []
_lib.get_mouse_clicked.restype = ctypes.c_int
_lib.update.argtypes = []
_lib.update.restype = None
_lib.close_window.argtypes = []
_lib.close_window.restype = None

# Draw
_lib.clear.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_int]
_lib.clear.restype = None
_lib.draw_pixel.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int]
_lib.draw_pixel.restype = None
_lib.draw_line.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int]
_lib.draw_line.restype = None
_lib.draw_rect.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int]
_lib.draw_rect.restype = None
_lib.draw_rect_filled.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int]
_lib.draw_rect_filled.restype = None

# Text (TTF)
_lib.text_init.argtypes = []
_lib.text_init.restype = ctypes.c_int
_lib.load_font.argtypes = [ctypes.c_char_p, ctypes.c_int]
_lib.load_font.restype = ctypes.c_int
_lib.draw_text.argtypes = [ctypes.c_char_p, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int]
_lib.draw_text.restype = None
_lib.text_quit.argtypes = []
_lib.text_quit.restype = None

# --- (新增) Image ---
_lib.image_init.argtypes = []
_lib.image_init.restype = ctypes.c_int
_lib.load_image.argtypes = [ctypes.c_char_p]
_lib.load_image.restype = ctypes.c_void_p  # <-- 回傳指標
_lib.draw_image.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.c_int] # <-- 接收指標
_lib.draw_image.restype = None
_lib.free_image.argtypes = [ctypes.c_void_p] # <-- 接收指標
_lib.free_image.restype = None
_lib.image_quit.argtypes = []
_lib.image_quit.restype = None
# --------------------

# --- 3. 將 C 函式包裝成 Python 函式 ---

# (init_window, poll_event, clear, draw_..., get_mouse_... 保持不變)
def init_window(w: int, h: int) -> bool:
    if _lib.init_window(w, h) != 0: return False
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
def update():
    _lib.update()
def close_window():
    _lib.close_window()
def draw_rect(x: int, y: int, w: int, h: int, r: int, g: int, b: int):
    _lib.draw_rect(x, y, w, h, r, g, b)
def draw_rect_filled(x: int, y: int, w: int, h: int, r: int, g: int, b: int):
    _lib.draw_rect_filled(x, y, w, h, r, g, b)
def get_mouse_clicked() -> bool:
    return _lib.get_mouse_clicked() == 1

# (text_init, load_font, draw_text, text_quit 保持不變)
def text_init() -> bool:
    if _lib.text_init() != 0: return False
    return True
def load_font(font_path: str, size: int) -> bool:
    if _lib.load_font(_to_c_string(font_path), size) != 0: return False
    return True
def draw_text(text: str, x: int, y: int, r: int, g: int, b: int):
    _lib.draw_text(_to_c_string(text), x, y, r, g, b)
def text_quit():
    _lib.text_quit()

# --- (新增) Image 函式 ---
def image_init() -> bool:
    """初始化圖片引擎。必須在 init_window 之後呼叫。"""
    if _lib.image_init() != 0:
        print("CPyGfx 核心：IMG 圖片引擎初始化失敗。")
        return False
    return True

def load_image(image_path: str) -> ctypes.c_void_p:
    """
    載入圖片檔案。
    回傳一個指向紋理的指標 (ctypes.c_void_p)。
    如果失敗，回傳 None。
    """
    c_path = _to_c_string(image_path)
    ptr = _lib.load_image(c_path)
    if ptr is None:
        print(f"CPyGfx 核心：載入圖片 {image_path} 失敗。")
    return ptr

def draw_image(texture_ptr: ctypes.c_void_p, x: int, y: int):
    """在 (x, y) 處繪製圖片 (紋理指標)。"""
    if texture_ptr:
        _lib.draw_image(texture_ptr, x, y)
    else:
        print("CPyGfx 錯誤：試圖繪製一個 None 圖片指標。")

def free_image(texture_ptr: ctypes.c_void_p):
    """釋放圖片 (紋理指標) 的記憶體。"""
    if texture_ptr:
        _lib.free_image(texture_ptr)

def image_quit():
    """關閉圖片引擎。"""
    _lib.image_quit()
# -------------------------