# CPyGfx (C-Python Graphics Engine)
[繁體中文版本](https://github.com/rayhuang2006/CPyGfx/blob/main/README_tw.md)

This is a mini C graphics engine built from scratch, wrapped using Python's `ctypes`.

## Developer Setup (macOS ARM64)

This project requires a C compiler and Homebrew to install system dependencies.

### 1. Install System Dependencies

Use Homebrew to install the following dependencies:

```bash
brew install pkg-config sdl2 sdl2_ttf sdl2_image sdl2_mixer
```

#### Notes
1. If `pkg-config` cannot find the libraries, you may need to force-link them:
   ```bash
   brew link sdl2 --force
   brew link sdl2_ttf --force
   brew link sdl2_image --force
   brew link sdl2_mixer --force
   ```
2. Ensure your Homebrew is up to date:
   ```bash
   brew update
   brew upgrade
   ```

3. If you are using Apple Silicon (M1/M2), make sure Homebrew is installed in the correct path (`/opt/homebrew`) and add it to your environment variables:
   ```bash
   export PATH="/opt/homebrew/bin:$PATH"
   export PKG_CONFIG_PATH="/opt/homebrew/lib/pkgconfig:$PKG_CONFIG_PATH"
   ```

### 2. Set Up Python Virtual Environment

From the root directory of the `CPyGfx` project, run the following commands:

```bash
# Create a .venv virtual environment
python3.11 -m venv .venv

# Activate the virtual environment
source .venv/bin/activate
```

### 3. Build and Install CPyGfx from Source

With the virtual environment **activated**, run the following command to build and install:

```bash
pip install -e .
```

`pip` will automatically read `setup.py` and use `clang` and `pkg-config` to compile the C core.

### 4. Test Installation

Run the following command to verify the installation:

```bash
python -c "import cpygfx; print('CPyGfx installed successfully!')"
```