#pragma once
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
#define SYSCALL_PRCTL 158
#define SYSCALL_STUB 999