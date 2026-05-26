#pragma once

#define FB_IOCTL_FLIP   0x46420001
#define FB_IOCTL_CLEAR  0x46420002
#define FB_IOCTL_GET_INFO 0x46420003
#include "stddef.h"
#include "stdint.h"

typedef struct fb_info {
    uint64_t width;
    uint64_t height;
    uint64_t pitch;
    uint16_t bpp;
    size_t size;
} fb_info_t;
