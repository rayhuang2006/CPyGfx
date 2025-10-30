# 檔案名稱: CPyGfx/setup.py
# (已升級為支援 SDL2_ttf)
import os
import subprocess
from setuptools import setup, Extension, find_packages

# --- 自動偵測 SDL2 旗標 (flags) ---
def get_c_flags(pkg_name):
    """執行 pkg-config 或 sdl2-config 來取得編譯旗標"""
    config_tool = "sdl2-config" if pkg_name == "SDL2" else "pkg-config"
    
    # 檢查工具是否存在
    if os.system(f"which {config_tool} > /dev/null") != 0:
        if pkg_name == "SDL2_ttf":
            # 如果是 ttf 找不到，可能是 brew link 沒做
            raise EnvironmentError(
                f"找不到 `{config_tool}`。請嘗試 `brew install {pkg_name}` "
                f"和 `brew link {pkg_name} --force`"
            )
        raise EnvironmentError(f"找不到 `{config_tool}`。請確保 {pkg_name} 已安裝。")
    
    # 執行指令
    try:
        command = [config_tool, "--cflags", pkg_name] if pkg_name != "SDL2" else [config_tool, "--cflags"]
        cflags = subprocess.check_output(command).decode("utf-8").strip().split()
        return cflags
    except subprocess.CalledProcessError:
        raise EnvironmentError(f"使用 `{config_tool}` 取得 {pkg_name} cflags 失敗。")

def get_c_libs(pkg_name):
    """執行 pkg-config 或 sdl2-config 來取得連結旗標"""
    config_tool = "sdl2-config" if pkg_name == "SDL2" else "pkg-config"
    
    try:
        command = [config_tool, "--libs", pkg_name] if pkg_name != "SDL2" else [config_tool, "--libs"]
        libs = subprocess.check_output(command).decode("utf-8").strip().split()
        return libs
    except subprocess.CalledProcessError:
        raise EnvironmentError(f"使用 `{config_tool}` 取得 {pkg_name} libs 失敗。")

# --- 取得所有函式庫的旗標 ---
# 我們需要 SDL2 和 SDL2_ttf
# set() 用來自動處理重複的旗標 (例如 -L/opt/homebrew/lib)
all_cflags = list(set(get_c_flags("SDL2") + get_c_flags("SDL2_ttf")))
all_libs = list(set(get_c_libs("SDL2") + get_c_libs("SDL2_ttf")))

print(f"--- 偵測到的 C 旗標 (CFlags) ---")
print(" ".join(all_cflags))
print(f"--- 偵測到的 C 連結 (Libs) ---")
print(" ".join(all_libs))
print("-------------------------------")


# --- 定義 C Extension 模組 ---
cpygfx_core_module = Extension(
    name='cpygfx._cpygfx_core', 
    
    # C 原始碼檔案列表
    sources=[
        'src/display.c',
        'src/draw.c',
        'src/event.c',
        'src/input.c',
        'src/text.c'  # <-- 1. 加入新的 text.c
    ],
    
    # 2. 更新編譯旗標
    extra_compile_args=all_cflags,
    
    # 3. 更新連結旗標
    extra_link_args=all_libs
)

# --- 主要的 setup() 函式 ---
setup(
    name='cpygfx',
    version='0.1.0',
    description='A mini C-based graphics library for Python (similar to pygame)',
    author='Ray Huang', 
    packages=find_packages(),
    ext_modules=[cpygfx_core_module],
    zip_safe=False 
)