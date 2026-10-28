
#include "webp.h"

AnimatedWebP loadWebP(const char *image) {
    AnimatedWebP a = {0};
    int size = 0;

    a.fileData = LoadFileData(image, &size);
    a.fileSize = size;
    if (!a.fileData || size <= 0) goto fail;

    WebPData data = {a.fileData, (size_t)size};
    WebPAnimDecoderOptions opt;
    WebPAnimDecoderOptionsInit(&opt);
    opt.color_mode = MODE_RGBA;

    a.decoder = WebPAnimDecoderNew(&data, &opt);
    if (!a.decoder ||
        !WebPAnimDecoderGetInfo(a.decoder, &a.info))
        goto fail;

    if (!WebPAnimDecoderGetNext(a.decoder, &a.pixels,
                                &a.timestamp))
        goto fail;

    Image img = {
        .data = a.pixels,
        .width = (int)a.info.canvas_width,
        .height = (int)a.info.canvas_height,
        .mipmaps = 1,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
    };

    a.texture = LoadTextureFromImage(img);
    a.loaded = IsTextureValid(a.texture);
    a.nextFrame = GetTime() + 0.1;

    if (!a.loaded) goto fail;
    return a;

fail:
    if (a.decoder) WebPAnimDecoderDelete(a.decoder);
    if (a.fileData) UnloadFileData(a.fileData);
    if (a.loaded) UnloadTexture(a.texture);
    return (AnimatedWebP){0};
}

void drawWebP(AnimatedWebP *a, int x, int y) {
    if (!a || !a->loaded) return;

    if (GetTime() >= a->nextFrame) {
        if (!WebPAnimDecoderHasMoreFrames(a->decoder))
            WebPAnimDecoderReset(a->decoder);

        if (WebPAnimDecoderGetNext(a->decoder, &a->pixels,
                                   &a->timestamp)) {
            UpdateTexture(a->texture, a->pixels);
        }

        a->nextFrame = GetTime() + 0.1;
    }

    DrawTexture(a->texture, x, y, WHITE);
}

void unloadWebP(AnimatedWebP *a) {
    if (!a) return;

    if (a->loaded) UnloadTexture(a->texture);
    if (a->decoder) WebPAnimDecoderDelete(a->decoder);
    if (a->fileData) UnloadFileData(a->fileData);

    *a = (AnimatedWebP){0};
}
