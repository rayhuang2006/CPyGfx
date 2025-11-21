import os
import subprocess
from setuptools import setup, Extension, find_packages

def get_c_flags(pkg_name):
    """執行 pkg-config 或 sdl2-config 來取得編譯旗標"""
    config_tool = "sdl2-config" if pkg_name == "SDL2" else "pkg-config"
    
    if os.system(f"which {config_tool} > /dev/null") != 0:
        if pkg_name != "SDL2":
            raise EnvironmentError(
                f"找不到 `{config_tool}`。請嘗試 `brew install pkg-config {pkg_name}` "
                f"和 `brew link {pkg_name} --force`"
            )
        raise EnvironmentError(f"找不到 `{config_tool}`。請確保 {pkg_name} 已安裝。")
    
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

all_cflags = list(set(
    get_c_flags("SDL2") + 
    get_c_flags("SDL2_ttf") +
    get_c_flags("SDL2_image")
))
all_libs = list(set(
    get_c_libs("SDL2") + 
    get_c_libs("SDL2_ttf") +
    get_c_libs("SDL2_image")
))

print(f"--- 偵測到的 C 旗標 (CFlags) ---")
print(" ".join(all_cflags))
print(f"--- 偵測到的 C 連結 (Libs) ---")
print(" ".join(all_libs))
print("-------------------------------")


cpygfx_core_module = Extension(
    name='cpygfx._cpygfx_core', 
    
    # C 原始碼檔案列表
    sources=[
        'src/display.c',
        'src/draw.c',
        'src/event.c',
        'src/input.c',
        'src/text.c',
        'src/image.c',
        'src/time.c',
        'src/geometry.c'
    ],
    
    extra_compile_args=all_cflags,
    
    extra_link_args=all_libs
)

setup(
    name='cpygfx',
    version='0.2.0',
    description='A mini C-based graphics library for Python (similar to pygame)',
    author='Ray Huang', 
    packages=find_packages(),
    ext_modules=[cpygfx_core_module],
    zip_safe=False 
)