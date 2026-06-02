#include <bits/syscall.h>
#include <reddyos/syscalls.h>
#include <mlibc/sysdeps.hpp>
#include <mlibc/all-sysdeps.hpp>

extern "C" int ioctl(int fd, unsigned long request, void *arg) {
    int result;
    mlibc::sysdep<Ioctl>(fd, request, arg, &result);
    return result;
}