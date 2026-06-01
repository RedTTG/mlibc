#pragma once

#include <mlibc/sysdep-signatures.hpp>

namespace mlibc {

    struct ReddyOSSysdepTags :
        LibcPanic,
        LibcLog,
        Isatty,
        Write,
        TcbSet,
        AnonAllocate,
        AnonFree,
        Seek,
        Exit,
        Close,
        FutexWake,
        FutexWait,
        Read,
        Open,
        VmMap,
        VmUnmap,
        ClockGet,
        Ioctl
    {};

    template<typename Tag>
    using Sysdeps = SysdepOf<ReddyOSSysdepTags, Tag>;

} // namespace mlibc