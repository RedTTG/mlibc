#pragma once

#define FB_IOCTL_FLIP   0x46420001
#define FB_IOCTL_CLEAR  0x46420002
#define FB_IOCTL_GET_INFO 0x46420003
#include "stddef.h"
#include "stdint.h"
#include "stdio.h"

typedef enum fb_clamp {
    FB_CLAMP_EDGES,
    FB_CLAMP_WRAP
} fb_clamp_t;

typedef struct fb_info {
    uint64_t width;
    uint64_t height;
    uint64_t pitch;
    uint16_t bpp;
    size_t size;
} fb_info_t;


typedef struct fb {
    fb_info_t info;
    FILE* file;
    int file_fd;
    uint32_t* back;
    fb_clamp_t clamp;
} FRAMEBUFFER;


#ifdef __cplusplus
extern "C" {
#endif


// Initialization functions
FRAMEBUFFER* fb_get(const char* path);
void fb_close(FRAMEBUFFER* fb);
void fb_flip(FRAMEBUFFER* fb);

// Draw functions
void fb_clear(FRAMEBUFFER* fb, uint32_t color);
void fb_draw_pixel(FRAMEBUFFER* fb, int x, int y, uint32_t color);
void fb_draw_rect(FRAMEBUFFER* fb, int x, int y, int w, int h, uint32_t color, uint16_t width);
void fb_draw_line(FRAMEBUFFER* fb, int x, int y, int w, int h, uint32_t color, uint16_t width);
void fb_draw_circle(FRAMEBUFFER* fb, int x, int y, int w, int h, uint32_t color, uint16_t width);


#define FB(fb, x, y) ((y) * ((fb)->info.pitch / 4) + (x))


#ifdef __cplusplus
}
#endif