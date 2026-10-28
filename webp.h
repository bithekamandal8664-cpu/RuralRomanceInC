#ifndef WEBP_H
#define WEBP_H

#include <raylib.h>
#include <webp/demux.h>
#include <webp/decode.h>
#include <stdint.h>

typedef struct {
    WebPAnimDecoder *decoder;
    WebPAnimInfo info;
    Texture2D texture;
    uint8_t *pixels;

    // Keep encoded WebP data alive while decoder uses it
    unsigned char *fileData;
    int fileSize;

    int timestamp;
    double nextFrame;
    bool loaded;
} AnimatedWebP;

AnimatedWebP loadWebP(const char *image);
void drawWebP(AnimatedWebP *webp, int x, int y);
void unloadWebP(AnimatedWebP *webp);

#endif
