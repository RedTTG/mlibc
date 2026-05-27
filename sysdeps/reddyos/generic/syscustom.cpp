#include <bits/syscall.h>
#include <reddyos/syscalls.h>
#include <reddyos/syscustom.h>

extern "C" int sys_term(char c) {
    return syscall(SYSCALL_TERM, c);
}