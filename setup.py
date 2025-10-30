# 檔案名稱: setup.py
import os
import subprocess
from setuptools import setup, Extension, find_packages

# --- 自動偵測 SDL2 旗標 (flags) ---
# 我們再次使用 sdl2-config，但這次是在 setup.py 裡！
def get_sdl2_flags():
    """執行 sdl2-config 來取得編譯和連結旗標"""
    if os.system("which sdl2-config > /dev/null") != 0:
        # 如果找不到 sdl2-config (例如 Windows)，提供一個備用方案
        # 這裡我們為了 macOS 簡化，假設它一定存在
        raise EnvironmentError("找不到 `sdl2-config`。請確保 SDL2 已安裝並在 PATH 中。")
    
    # --cflags 會給出 include 路徑
    cflags = subprocess.check_output(["sdl2-config", "--cflags"]).decode("utf-8").strip().split()
    
    # --libs 會給出 library 路徑和 library 名稱
    libs = subprocess.check_output(["sdl2-config", "--libs"]).decode("utf-8").strip().split()
    
    return cflags, libs

sdl_cflags, sdl_libs = get_sdl2_flags()

# --- 定義 C Extension 模組 ---
# 這是 setup.py 的核心
# 我們告訴 setuptools：「嘿，這裡有一堆 C 程式碼，請幫我編譯」
cpygfx_core_module = Extension(
    # 1. 模組的名稱 (Python import 時的路徑)
    # 'cpygfx._cpygfx_core' 意思是它會被放在 cpygfx 資料夾下
    # 並命名為 _cpygfx_core.so (或 .dylib)
    name='cpygfx._cpygfx_core', 
    
    # 2. C 原始碼檔案列表
    sources=[
        'src/display.c',
        'src/draw.c',
        'src/event.c',
        'src/input.c'
    ],
    
    # 3. 編譯旗標 (例如 -I/opt/homebrew/include/SDL2)
    extra_compile_args=sdl_cflags,
    
    # 4. 連結旗標 (例如 -L/opt/homebrew/lib -lSDL2)
    extra_link_args=sdl_libs
)

# --- 主要的 setup() 函式 ---
setup(
    name='cpygfx',
    version='0.1.0',
    description='A mini C-based graphics library for Python (similar to pygame)',
    author='Ray Huang', # <-- 你可以改成你的名字
    
    # 告訴 setuptools 去哪裡找 Python 套件
    # find_packages() 會自動找到 'cpygfx' 資料夾
    packages=find_packages(),
    
    # 告訴 setuptools 這是一個包含 C Extension 的套件
    ext_modules=[cpygfx_core_module],
    
    # 確保 C 函式庫和 Python 程式碼一起安裝
    # 這樣 cpygfx/core.py 才能找到 _cpygfx_core.so
    zip_safe=False 
)