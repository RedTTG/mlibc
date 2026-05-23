#include <bits/ensure.h>
#include <mlibc/all-sysdeps.hpp>
#include <reddyos/syscalls.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>

namespace mlibc {
    int stub_syscall() {
        __ensure(!"STUB function was called");
        __builtin_unreachable();
    }
    int sys_read(int fd, void *buff, size_t count, ssize_t *bytes_read) {
        long ret = syscall(SYSCALL_READ, fd, (uint64_t)buff, count);
        if(ret < 0)
            return ret;
        *bytes_read = ret;
        return 0;
    }
    int sys_write(int fd, const void *buff, size_t count, ssize_t *bytes_written) {
        long ret = syscall(SYSCALL_WRITE, fd, (uint64_t)buff, count);
        if(ret < 0)
            return ret;
        *bytes_written = ret;
        return 0;
    }
    int sys_open(const char *pathname, int flags, mode_t mode, int *fd) {
        long ret = syscall(SYSCALL_OPEN, (uint64_t)pathname, flags, mode);
        if(ret < 0)
            return ret;
        *fd = ret;
        return 0;
    };
    int sys_close(int fd) {
        return syscall(SYSCALL_CLOSE, fd);
    }
    int sys_stat(const char* filename, struct stat* buffer) {
        return syscall(SYSCALL_STAT, (uint64_t)filename, (uint64_t)buffer);
    }
    int sys_fstat(int fd, struct stat* buffer) {
        return syscall(SYSCALL_FSTAT, fd, (uint64_t)buffer);
    }
    int sys_lseek(int fd, off_t offset, int whence, off_t *new_offset) {
        long ret = syscall(SYSCALL_LSEEK, fd, offset, whence);
        if(ret < 0)
            return ret;
        *new_offset = ret;
        return 0;
    }
    int sys_ioctl(int fd, uint64_t cmd, uint64_t arg) {
        return syscall(SYSCALL_IOCTL, fd, cmd, arg);
    }

    // TODO: STUBS
    int sys_anon_allocate(unsigned long, void**) {
        return stub_syscall();
    }
    int sys_anon_free(void*, unsigned long) {
        return stub_syscall();
    }
    int sys_clock_get(int, long*, long*) {
        return stub_syscall();
    }
    void sys_exit(int) {
        stub_syscall();
    }
    int sys_futex_wait(int*, int, timespec const*) {
        return stub_syscall();
    }
    int sys_futex_wake(int*) {
        return stub_syscall();
    }
    void sys_libc_log(char const*) {
        stub_syscall();
    }
    void sys_libc_panic() {
        stub_syscall();
    }
    int sys_seek(int, long, int, long*) {
        return stub_syscall();
    }
    int sys_tcb_set(void*) {
        return stub_syscall();
    }
    int sys_vm_map(void*, unsigned long, int, int, int, long, void**) {
        return stub_syscall();
    }
}