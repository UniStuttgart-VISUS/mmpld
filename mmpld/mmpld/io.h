/// <copyright file="io.h" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2018 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
/// Copyright © 2017 SFB-TRR 161. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>

#pragma once

#include <cerrno>
#include <cinttypes>
#include <cstdio>
#include <cstring>
#include <istream>
#include <stdexcept>
#include <system_error>

#include <sys/stat.h>
#include <sys/types.h>

#if defined(WIN32)
#include <io.h>
#include <share.h>
#include <tchar.h>
#else /* defined(WIN32) */
#include <unistd.h>
#endif /* defined(WIN32) */

#include "mmpld/literal.h"


namespace mmpld {
namespace detail {

    template<class T> struct io_traits {
        typedef T char_type;
    };

    template<> struct io_traits<char> {
        typedef char char_type;

        static inline FILE *fopen(const char_type *path,
                const char_type *mode) {
#if defined(WIN32)
            FILE *retval = nullptr;
            return (::fopen_s(&retval, path, mode) == 0) ? retval : nullptr;
#else /* defined(WIN32) */
            return ::fopen(path, mode);
#endif /* defined(WIN32) */
        }

        static inline int open(const char_type *path, const int flags) {
#if defined(WIN32)
            int retval = -1;
            return (::_sopen_s(&retval, path, flags, _SH_DENYWR, _S_IREAD) == 0)
                ? retval : -1;
#else /* defined(WIN32) */
            return ::open(path, flags);
#endif /* defined(WIN32) */
        }
    };

#if defined(WIN32)
    template<> struct io_traits<wchar_t> {
        typedef wchar_t char_type;

        static inline FILE *fopen(const char_type *path,
                const char_type *mode) {
            FILE *retval = nullptr;
            return (::_wfopen_s(&retval, path, mode) == 0) ? retval : nullptr;
        }

        static inline int open(const char_type *path, const int flags) {
            int retval = -1;
            return (::_wsopen_s(&retval, path, flags, _SH_DENYWR, _S_IREAD) == 0)
                ? retval : -1;
        }
    };
#endif /* defined(WIN32) */

    template<class C, class T>
    inline void close(std::basic_ifstream<C, T>& stream) {
        stream.close();
    }

    inline void close(int stream) {
#if defined(WIN32)
        ::_close(stream);
#else /* defined(WIN32) */
        ::close(stream);
#endif /* defined(WIN32) */
    }

    inline void close(FILE *stream) {
        ::fclose(stream);
    }

    template<class C, class T>
    void open(const C *path, std::basic_ifstream<C, T>& stream);

    template<class C> void open(const C *path, int& stream);

    template<class C> void open(const C *path, FILE *& stream);

    template<class T, class C, class A>
    inline T& read(std::basic_istream<C, A>& stream, T& retval) {
        static_assert((sizeof(T) % sizeof(C)) == 0, "Number of bytes to be read "
            "must be divisible by character size.");
        auto cnt = sizeof(T) / sizeof(C);
        stream.read(reinterpret_cast<C *>(&retval), cnt);
        return retval;
    }

    template<class T> T& read(int handle, T& retval);

    template<class T> T& read(FILE *handle, T& retval);

    template<class T> inline void zero_memory(T& memory) {
        ::memset(&memory, 0, sizeof(memory));
    }

} /* end namespace detail */
} /* end namespace mmpld */

#include "mmpld/io.inl"
