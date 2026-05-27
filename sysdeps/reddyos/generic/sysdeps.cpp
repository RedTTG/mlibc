#include <bits/ensure.h>
#include <bits/syscall.h>
#include <abi-bits/errno.h>
#include "mlibc/tcb.hpp"
#include <mlibc/all-sysdeps.hpp>
#include <mlibc/sysdeps.hpp>
#include <reddyos/terminal.h>
#include <reddyos/syscalls.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <mlibc/fsfd_target.hpp>


// ANCHOR: stub
#define STUB()                                                                                     \
	({                                                                                             \
		__ensure(!"STUB function was called");                                                     \
		__builtin_unreachable();                                                                   \
	})
// ANCHOR_END: stub

namespace mlibc {

void Sysdeps<LibcPanic>::operator()() {
    STUB();
}

void Sysdeps<LibcLog>::operator()(const char *msg) {
    terminal_write("libc log: ");
    terminal_write(msg);
    terminal_write("\n");
}

int Sysdeps<Isatty>::operator()(int fd) {
    STUB();
}

int Sysdeps<Write>::operator()(int fd, void const *buf, size_t size, ssize_t *bytes_written) {
	long result = syscall(SYSCALL_WRITE, fd, (uint64_t) buf, size);
	if (result < 0)
		return result;
	*bytes_written = result;
	return 0;
}

int Sysdeps<TcbSet>::operator()(void *pointer) {
    STUB();
}

int Sysdeps<AnonAllocate>::operator()(size_t size, void **pointer) {
    long ret = syscall(SYSCALL_MMAP, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (ret < 0)
        return ENOMEM;
    *pointer = (void*)ret;
    return 0;
}

int Sysdeps<AnonFree>::operator()(void *, unsigned long) {
    STUB();
} // no-op

int Sysdeps<Seek>::operator()(int fd, off_t offset, int whence, off_t *new_offset) {
	long result = syscall(SYSCALL_LSEEK, fd, offset, whence);
	if (result < 0)
		return result;
	*new_offset = result;
	return 0;
}

// int Sysdeps<Stat>::operator()(mlibc::fsfd_target fsfdt, int fd, const char *path, int flags, struct stat *statbuf) {
// 	if (fsfdt == mlibc::fsfd_target::path) {
// 		// sys_stat behavior
// 		return syscall(SYSCALL_STAT, (uint64_t) path, (uint64_t) statbuf);
// 	} else if (fsfdt == mlibc::fsfd_target::fd) {
// 		// sys_fstat behavior
// 		return syscall(SYSCALL_FSTAT, fd, (uint64_t) statbuf);
// 	}
// 	// fd_path: for now, use fd if available, otherwise fall back to path
// 	if (fd >= 0) {
// 		return syscall(SYSCALL_FSTAT, fd, (uint64_t) statbuf);
// 	} else if (path) {
// 		return syscall(SYSCALL_STAT, (uint64_t) path, (uint64_t) statbuf);
// 	}
// 	return -1;
// }

void Sysdeps<Exit>::operator()(int status) {
    STUB();
}

int Sysdeps<Close>::operator()(int fd) {
	return syscall(SYSCALL_CLOSE, fd);
}

int Sysdeps<FutexWake>::operator()(int *, bool) {
	STUB();
}
int Sysdeps<FutexWait>::operator()(int *, int, timespec const *) {
	STUB();
}
int Sysdeps<Read>::operator()(int fd, void *buf, unsigned long count, long *bytes_read) {
	long result = syscall(SYSCALL_READ, fd, (uint64_t) buf, count);
	if (result < 0)
		return result;
	*bytes_read = result;
	return 0;
}
int Sysdeps<Open>::operator()(const char *pathname, int flags, unsigned int mode, int *fd) {
	long result = syscall(SYSCALL_OPEN, (uint64_t) pathname, flags, mode);
	if (result < 0)
		return result;
	*fd = result;
	return 0;
}
int Sysdeps<VmMap>::operator()(void *, size_t, int, int, int, off_t, void **) {
	STUB();
}
int Sysdeps<VmUnmap>::operator()(void *, size_t) {
	STUB();
}
int Sysdeps<ClockGet>::operator()(int, time_t *, long *) {
	STUB();
}

// int Sysdeps<Ioctl>::operator()(int fd, unsigned long request, void *arg, int *result) {
// 	long ret = syscall(SYSCALL_IOCTL, fd, request, (uint64_t) arg);
// 	if (ret < 0)
// 		return ret;
// 	*result = ret;
// 	return 0;
// }

} // namespace mlibc
