#include <bits/ensure.h>
#include <abi-bits/errno.h>
#include <mlibc/all-sysdeps.hpp>
#include <reddyos/terminal.h>
#include <reddyos/syscalls.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>

namespace mlibc {
    int stub_syscall(const char *name) {
        return syscall(SYSCALL_STUB, (uint64_t) name);
    }

    int sys_read(int fd, void *buff, size_t count, ssize_t *bytes_read) {
        long ret = syscall(SYSCALL_READ, fd, (uint64_t) buff, count);
        if (ret < 0)
            return ret;
        *bytes_read = ret;
        return 0;
    }

    int sys_write(int fd, const void *buff, size_t count, ssize_t *bytes_written) {
        long ret = syscall(SYSCALL_WRITE, fd, (uint64_t) buff, count);
        if (ret < 0)
            return ret;
        *bytes_written = ret;
        return 0;
    }

    int sys_open(const char *pathname, int flags, mode_t mode, int *fd) {
        long ret = syscall(SYSCALL_OPEN, (uint64_t) pathname, flags, mode);
        if (ret < 0)
            return ret;
        *fd = ret;
        return 0;
    };

    int sys_close(int fd) {
        return syscall(SYSCALL_CLOSE, fd);
    }

    int sys_stat(const char *filename, struct stat *buffer) {
        return syscall(SYSCALL_STAT, (uint64_t) filename, (uint64_t) buffer);
    }

    int sys_fstat(int fd, struct stat *buffer) {
        return syscall(SYSCALL_FSTAT, fd, (uint64_t) buffer);
    }

    int sys_lseek(int fd, off_t offset, int whence, off_t *new_offset) {
        long ret = syscall(SYSCALL_LSEEK, fd, offset, whence);
        if (ret < 0)
            return ret;
        *new_offset = ret;
        return 0;
    }

    int sys_ioctl(int fd, uint64_t cmd, uint64_t arg) {
        return syscall(SYSCALL_IOCTL, fd, cmd, arg);
    }

    // TODO: STUBS
    int sys_anon_allocate(size_t size, void **pointer) {
        long ret = syscall(SYSCALL_MMAP, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        if (ret < 0)
            return ENOMEM;
        *pointer = (void*)ret;
        return 0;
    }

    int sys_anon_free(void *, unsigned long) {
        return stub_syscall("sys_anon_free");
    }

    int sys_clock_get(int, long *, long *) {
        return stub_syscall("sys_clock_get");
    }

    void sys_exit(int) {
        stub_syscall("sys_exit");
    }

    int sys_futex_wait(int *, int, timespec const *) {
        return stub_syscall("sys_futex_wait");
    }

    int sys_futex_wake(int *) {
        return stub_syscall("sys_futex_wake");
    }

    void sys_libc_log(char const *log) {
        terminal_write("libc log: ");
        terminal_write(log);
        terminal_write("\n");
    }

    void sys_libc_panic() {
        stub_syscall("sys_libc_panic");
    }

    int sys_seek(int, long, int, long *) {
        return stub_syscall("sys_seek");
    }

    int sys_tcb_set(void *) {
        return stub_syscall("sys_tcb_set");
    }

    int sys_vm_map(void *, unsigned long, int, int, int, long, void **) {
        return stub_syscall("sys_vm_map");
    }
}
