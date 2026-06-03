#include <reddyos/fb.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#include "../include/reddyos/terminal.h"

extern "C" FRAMEBUFFER* fb_get(const char* path) {
    FRAMEBUFFER* fb = (FRAMEBUFFER*)malloc(sizeof(FRAMEBUFFER));
    if (!fb)
        goto fail;

    memset(fb, 0, sizeof(FRAMEBUFFER));

    fb->file = fopen(path, "r+b");
    if (!fb->file)
        goto fail;
    fb->file_fd = fileno(fb->file);
    if (ioctl(fb->file_fd, FB_IOCTL_GET_INFO, &fb->info) != 0)
        goto fail;
    fb->back = (uint32_t*)mmap(
        NULL,
        fb->info.size,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        fb->file_fd,
        0
    );
    if (!fb->back)
        goto fail;
    return fb;

fail:
    if (fb) {
        if (fb->file)
            fclose(fb->file);
        if (fb->back)
            munmap(fb->back, fb->info.size);
        free(fb);
    }
    return NULL;
}

extern "C" void fb_close(FRAMEBUFFER* fb) {
    if (fb->file)
        fclose(fb->file);
    if (fb->back)
        munmap(fb->back, fb->info.size);
    free(fb);
}

extern "C" void fb_flip(FRAMEBUFFER* fb) {
    ioctl(fb->file_fd, FB_IOCTL_FLIP, NULL);
}

extern "C" void fb_clear(FRAMEBUFFER *fb, uint32_t color) {
    ioctl(fb->file_fd, FB_IOCTL_CLEAR, color);
}

void fb_clamp_v(FRAMEBUFFER* fb, int& v, int min, int max) {
    switch (fb->clamp) {
        case FB_CLAMP_EDGES:
            if (v < min) v = min;
            if (v >= max) v = max -1;
            break;
        case FB_CLAMP_WRAP:
            if (v < min) v = max - (min - v) % (max - min);
            if (v >= max) v = min + (v - min) % (max - min);
            break;
    }
}

void fb_clamp_x(FRAMEBUFFER* fb, int& x) {
    fb_clamp_v(fb, x, 0, fb->info.width);
}

void fb_clamp_y(FRAMEBUFFER* fb, int& y) {
    fb_clamp_v(fb, y, 0, fb->info.height);
}

void fb_clamp_x_y(FRAMEBUFFER* fb, int& x, int& y) {
    fb_clamp_x(fb, x);
    fb_clamp_y(fb, y);
}

extern "C" void fb_draw_pixel(FRAMEBUFFER* fb, int x, int y, uint32_t color) {
    fb_clamp_x_y(fb, x, y);
    fb->back[FB(fb, x, y)] = color;
}

extern "C" void fb_draw_rect(FRAMEBUFFER* fb, int x, int y, int w, int h, uint32_t color, uint16_t width) {
    if (width == 0) {
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                fb_draw_pixel(fb, x + j, y + i, color);
            }
        }
        return;
    }
    x -= width / 2;
    y -= width / 2;
    w += width;
    h += width;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if ((j < width || j > w - width) || (i < width || i > h - width)) {
                fb_draw_pixel(fb, x + j, y + i, color);
            }
        }
    }
}

extern "C" void fb_draw_line(FRAMEBUFFER* fb, int x, int y, int w, int h, uint32_t color, uint16_t width) {

}

extern "C" void fb_draw_circle(FRAMEBUFFER* fb, int x, int y, int w, int h, uint32_t color, uint16_t width) {

}
