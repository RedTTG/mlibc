#pragma once
#include <stdint.h>

#include "stdio.h"
#include "reddyos/terminal.h"

#define SYSCALL_READ 0
#define SYSCALL_WRITE 1
#define SYSCALL_OPEN 2
#define SYSCALL_CLOSE 3
#define SYSCALL_STAT 4
#define SYSCALL_FSTAT 5
#define SYSCALL_LSEEK 8
#define SYSCALL_MMAP 9
#define SYSCALL_MUNMAP 11
#define SYSCALL_IOCTL 16
#define SYSCALL_NANOSLEEP 35
#define SYSCALL_TERM 100
#define SYSCALL_PRCTL 158
#define SYSCALL_CLOCK_GETTIME 228
#define SYSCALL_STUB 999

namespace mlibc
{
    inline int sc_error(long ret) {
        if (ret < 0) {
            return (int)-ret;
        }
        return 0;
    }
}