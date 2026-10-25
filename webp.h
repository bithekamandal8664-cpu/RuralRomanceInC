
#ifndef WEBP_H
#define WEBP_H

#include <raylib.h>
#include <webp/demux.h>
#include <webp/decode.h>

typedef struct {
    WebPAnimDecoder *decoder;
    WebPAnimInfo info;
    Texture2D texture;
    uint8_t *pixels;
    int timestamp;
    double nextFrame;
    bool loaded;
} AnimatedWebP;

AnimatedWebP loadWebP(const char *image);
void drawWebP(AnimatedWebP *webp, int x, int y);
void unloadWebP(AnimatedWebP *webp);

#endif

