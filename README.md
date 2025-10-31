# CPyGfx (C-Python Graphics Engine)

這是一個從零打造的迷你 C 語言圖形引擎，使用 Python ctypes 封裝。

## 開發者設定 (macOS ARM64)

本專案需要 C 編譯環境和 Homebrew 來安裝系統依賴。

### 1. 安裝系統依賴 (System Dependencies)

請使用 Homebrew 安裝以下依賴：

```bash
brew install pkg-config sdl2 sdl2_ttf sdl2_image sdl2_mixer
```

#### 注意事項
1. 如果 `pkg-config` 找不到函式庫，你可能需要強制連結它們：
   ```bash
   brew link sdl2 --force
   brew link sdl2_ttf --force
   brew link sdl2_image --force
   brew link sdl2_mixer --force
   ```
2. 確保你的 Homebrew 是最新版本：
   ```bash
   brew update
   brew upgrade
   ```

3. 如果你使用的是 Apple Silicon (M1/M2)，請確認 Homebrew 安裝在正確的路徑 (`/opt/homebrew`)，並將其加入環境變數：
   ```bash
   export PATH="/opt/homebrew/bin:$PATH"
   export PKG_CONFIG_PATH="/opt/homebrew/lib/pkgconfig:$PKG_CONFIG_PATH"
   ```

### 2. 設定 Python 虛擬環境

從 `CPyGfx` 專案根目錄執行以下指令：

```bash
# 建立 .venv 虛擬環境
python3.11 -m venv .venv

# 啟動虛擬環境
source .venv/bin/activate
```

### 3. 從原始碼編譯並安裝 CPyGfx

在**已啟動**虛擬環境的狀態下，執行以下指令以編譯並安裝：

```bash
pip install -e .
```

`pip` 會自動讀取 `setup.py` 並呼叫 `clang` 和 `pkg-config` 來編譯 C 核心。

### 4. 測試安裝

執行以下指令以確認安裝是否成功：

```bash
python -c "import cpygfx; print('CPyGfx 安裝成功！')"
```

