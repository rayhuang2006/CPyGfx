// src/sound.c
#include "sound.h"

#include <stdio.h>
#include <string.h>

#include <SDL.h>
#include <SDL_mixer.h>

#ifndef MAX_CHANNELS
#define MAX_CHANNELS 64
#endif

static int g_audio_inited = 0;
static Mix_Chunk* g_channel_chunks[MAX_CHANNELS] = {0};

static void on_channel_finished(int channel) {
    if (channel >= 0 && channel < MAX_CHANNELS) {
        if (g_channel_chunks[channel]) {
            Mix_FreeChunk(g_channel_chunks[channel]);
            g_channel_chunks[channel] = NULL;
        }
    }
}

int sound_init() {
    if (g_audio_inited) return 0;

    // 確保 SDL Audio subsystem 已初始化（display.c 只 init VIDEO）:contentReference[oaicite:1]{index=1}
    if ((SDL_WasInit(SDL_INIT_AUDIO) & SDL_INIT_AUDIO) == 0) {
        if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) {
            fprintf(stderr, "無法初始化 SDL Audio: %s\n", SDL_GetError());
            return -1;
        }
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "Mix_OpenAudio 失敗: %s\n", Mix_GetError());
        return -1;
    }

    Mix_AllocateChannels(MAX_CHANNELS);
    Mix_ChannelFinished(on_channel_finished);

    g_audio_inited = 1;
    return 0;
}

void sound_quit() {
    if (!g_audio_inited) return;

    // 清掉仍在佔用的 chunk
    for (int i = 0; i < MAX_CHANNELS; i++) {
        if (g_channel_chunks[i]) {
            Mix_FreeChunk(g_channel_chunks[i]);
            g_channel_chunks[i] = NULL;
        }
    }

    Mix_CloseAudio();
    g_audio_inited = 0;
}

int play_sound(const char* wav_path, int loops) {
    if (!wav_path || wav_path[0] == '\0') return -1;

    if (sound_init() != 0) return -1;

    Mix_Chunk* chunk = Mix_LoadWAV(wav_path);
    if (!chunk) {
        fprintf(stderr, "Mix_LoadWAV 失敗 (%s): %s\n", wav_path, Mix_GetError());
        return -1;
    }

    int channel = Mix_PlayChannel(-1, chunk, loops);
    if (channel < 0) {
        fprintf(stderr, "Mix_PlayChannel 失敗: %s\n", Mix_GetError());
        Mix_FreeChunk(chunk);
        return -1;
    }

    if (channel >= 0 && channel < MAX_CHANNELS) {
        // 若該 channel 之前殘留，就先釋放
        if (g_channel_chunks[channel]) {
            Mix_FreeChunk(g_channel_chunks[channel]);
        }
        g_channel_chunks[channel] = chunk;
    } else {
        // 理論上不會，但保底：避免 leak
        Mix_FreeChunk(chunk);
    }

    return 0;
}

