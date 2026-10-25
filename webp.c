
#include "webp.h"

AnimatedWebP loadWebP(const char *image) {
    AnimatedWebP a = {0};
    int size = 0;
    unsigned char *file = LoadFileData(image, &size);
    if (!file || size <= 0) return a;

    WebPData data = {file, (size_t)size};
    WebPAnimDecoderOptions opt;
    WebPAnimDecoderOptionsInit(&opt);
    opt.color_mode = MODE_RGBA;

    a.decoder = WebPAnimDecoderNew(&data, &opt);
    if (!a.decoder || !WebPAnimDecoderGetInfo(a.decoder, &a.info))
        goto fail;

    if (!WebPAnimDecoderGetNext(a.decoder, &a.pixels, &a.timestamp))
        goto fail;

    Image img = {
        a.pixels, (int)a.info.canvas_width,
        (int)a.info.canvas_height, 1,
        PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
    };

    a.texture = LoadTextureFromImage(img);
    a.nextFrame = GetTime() + 0.1;
    a.loaded = IsTextureValid(a.texture);
    UnloadFileData(file);
    return a;

fail:
    if (a.decoder) WebPAnimDecoderDelete(a.decoder);
    UnloadFileData(file);
    return a;
}

void drawWebP(AnimatedWebP *a, int x, int y) {
    if (!a || !a->loaded) return;

    if (GetTime() >= a->nextFrame) {
        if (!WebPAnimDecoderHasMoreFrames(a->decoder))
            WebPAnimDecoderReset(a->decoder);

        if (WebPAnimDecoderGetNext(a->decoder, &a->pixels,
                                   &a->timestamp))
            UpdateTexture(a->texture, a->pixels);

        a->nextFrame = GetTime() + 0.1;
    }

    DrawTexture(a->texture, x, y, WHITE);
}

void unloadWebP(AnimatedWebP *a) {
    if (!a) return;
    if (a->loaded) UnloadTexture(a->texture);
    if (a->decoder) WebPAnimDecoderDelete(a->decoder);
    *a = (AnimatedWebP){0};
}

