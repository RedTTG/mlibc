#pragma once

#include <stddef.h>
#include <stdint.h>

#define SYSCALL_READ 0
#define SYSCALL_WRITE 1
#define SYSCALL_OPEN 2
#define SYSCALL_CLOSE 3
#define SYSCALL_STAT 4
#define SYSCALL_FSTAT 5
#define SYSCALL_LSEEK 8
#define SYSCALL_MMAP 9
#define SYSCALL_IOCTL 16
#define SYSCALL_TERM 100
#define SYSCALL_STUB 999



#ifndef __MLIBC_ABI_ONLY

static long syscall(long func, uint64_t p1 = 0, uint64_t p2 = 0, uint64_t p3 = 0, uint64_t p4 = 0, uint64_t p5 = 0, uint64_t p6 = 0) {
    volatile long ret;
    register uint64_t r10 asm("r10") = p4;
    register uint64_t r8 asm("r8") = p5;
    register uint64_t r9 asm("r9") = p6;

    asm volatile (
        "syscall"
        : "=a"(ret)
        : "a"(func),
          "D"(p1),
          "S"(p2),
          "d"(p3),
          "r"(r10),
          "r"(r8),
          "r"(r9)
        : "rcx", "r11", "memory"
    );
    return ret;
}

#endif /* !__MLIBC_ABI_ONLY */