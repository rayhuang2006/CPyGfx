// src/sound.h
#pragma once

int sound_init();
void sound_quit();

/**
 * 播放 WAV 音效
 * loops: 0=播放一次, 1=再播一次(共2次), -1=無限循環
 * return: 0=成功, -1=失敗
 */
int play_sound(const char* wav_path, int loops);
