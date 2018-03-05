/// <copyright file="io.h" company="Visualisierungsinstitut der Universit�t Stuttgart">
/// Copyright � 2018 Visualisierungsinstitut der Universit�t Stuttgart. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph M�ller</author>

#pragma once

#include <cassert>
#include <cerrno>
#include <cinttypes>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <stdexcept>
#include <system_error>

#include <fcntl.h>

#include <sys/stat.h>
#include <sys/types.h>

#if defined(_WIN32)
#include <io.h>
#include <share.h>
#include <tchar.h>
#include <Windows.h>
#else /* defined(_WIN32) */
#include <unistd.h>
#endif /* defined(_WIN32) */

#include "mmpld/literal.h"


namespace mmpld {
namespace detail {

    template<class F> struct basic_io_traits { };

    template<class F, class C> struct io_traits : public basic_io_traits<F> { };

    template<> struct basic_io_traits<std::ifstream> {
        typedef std::ifstream file_type;
        typedef std::ifstream::streamoff size_type;

        static inline void close(file_type& file) {
            file.close();
        }

        static inline size_type read(file_type& file, void *dst,
                const size_type cnt) {
            auto begin = file.tellg();
            file.read(static_cast<std::ifstream::char_type *>(dst), cnt);
            return (file.tellg() - begin);
        }

        static inline void seek(file_type& file, const size_type offset) {
            file.seekg(offset);
        }

        static inline size_type tell(file_type& file) {
            return file.tellg();
        }
    };

    template<> struct io_traits<std::ifstream, char>
            : public basic_io_traits<std::ifstream> {
        typedef char char_type;
        typedef basic_io_traits<std::ifstream>::file_type file_type;
        typedef basic_io_traits<std::ifstream>::size_type size_type;

        static inline void open(const char_type *path, file_type& file) {
            file.open(path, std::ios::binary);
        }
    };

    template<> struct basic_io_traits<FILE *> {
        typedef FILE *file_type;
#if defined(_WIN32)
        typedef __int64 size_type;
#else /* defined(_WIN32) */
        typedef long size_type;
#endif /* defined(_WIN32) */

        static inline void close(file_type& file) {
            if (file != nullptr) {
                ::fclose(file);
                file = nullptr;
            }
        }

        // Note: must be inline to prevent code generation in library.
        static inline size_type read(file_type& file, void *dst,
            const size_type cnt);

        static inline void seek(file_type& file, const size_type offset) {
#if defined(_WIN32)
            ::_fseeki64(file, static_cast<std::int64_t>(offset), SEEK_SET);
#else /* defined(_WIN32) */
            ::fseek(file, static_cast<int>(offset), SEEK_SET);
#endif /* defined(_WIN32) */
        }

        static inline size_type tell(file_type& file) {
#if defined(_WIN32)
            return ::_ftelli64(file);
#else /* defined(_WIN32) */
            return ::ftell(file);
#endif /* defined(_WIN32) */
        }
    };

    template<> struct io_traits<FILE *, char> : public basic_io_traits<FILE *> {
        typedef char char_type;
        typedef basic_io_traits<FILE *>::file_type file_type;
        typedef basic_io_traits<FILE *>::size_type size_type;

        static inline void open(const char_type *path, file_type& file) {
            static const char_type *const MODE = "rb";
#if defined(_WIN32)
            if (::fopen_s(&file, path, MODE) != 0) {
                file = nullptr;
                throw std::system_error(errno, std::system_category());
            }
#else /* defined(_WIN32) */
            if ((file = ::fopen(path, MODE)) == nullptr) {
                throw std::system_error(errno, std::system_category());
            }
#endif /* defined(_WIN32) */
        }
    };

#if defined(_WIN32)
    template<> struct io_traits<FILE *, wchar_t>
            : public basic_io_traits<FILE *> {
        typedef wchar_t char_type;
        typedef basic_io_traits<FILE *>::file_type file_type;
        typedef basic_io_traits<FILE *>::size_type size_type;

        static inline void open(const char_type *path, file_type& file) {
            static const char_type *const MODE = L"rb";
            if (::_wfopen_s(&file, path, MODE) != 0) {
                file = nullptr;
                throw std::system_error(errno, std::system_category());
            }
        }
    };
#endif /* defined(_WIN32) */

    template<> struct basic_io_traits<int> {
        typedef int file_type;
#if defined(_WIN32)
        typedef __int64 size_type;
#else /* defined(_WIN32) */
        typedef off_t size_type;
#endif /* defined(_WIN32) */

        static inline void close(file_type& file) {
#if defined(_WIN32)
            ::_close(file);
#else /* defined(_WIN32) */
            ::close(file);
#endif /* defined(_WIN32) */
        }

        // Note: must be inline to prevent code generation in library.
        static inline size_type read(file_type& file, void *dst,
            const size_type cnt);

        static inline void seek(file_type& file, const size_type offset) {
#if defined(_WIN32)
            ::_lseeki64(file, static_cast<std::int64_t>(offset), SEEK_SET);
#else /* defined(_WIN32) */
            ::lseek(file, static_cast<int>(offset), SEEK_SET);
#endif /* defined(_WIN32) */
        }

        static inline size_type tell(file_type& file) {
#if defined(_WIN32)
            return ::_telli64(file);
#else /* defined(_WIN32) */
            return ::tell(file);
#endif /* defined(_WIN32) */
        }
    };

    template<> struct io_traits<int, char> : public basic_io_traits<int> {
        typedef char char_type;
        typedef basic_io_traits<int>::file_type file_type;
        typedef basic_io_traits<int>::size_type size_type;

        static inline void open(const char_type *path, file_type& file) {
#if defined(_WIN32)
            if (::_sopen_s(&file, path, _O_BINARY | _O_RDONLY,
                    _SH_DENYWR, _S_IREAD) != 0) {
                file = -1;
                throw std::system_error(errno, std::system_category());
            }
#else /* defined(_WIN32) */
            if ((file = ::open(path, O_BINARY | O_RDONLY)) != 0) {
                throw std::system_error(errno, std::system_category());
            }
#endif /* defined(_WIN32) */
        }
    };

#if defined(_WIN32)
    template<> struct io_traits<int, wchar_t> : public basic_io_traits<int> {
        typedef wchar_t char_type;
        typedef basic_io_traits<int>::file_type file_type;
        typedef basic_io_traits<int>::size_type size_type;

        static inline void open(const char_type *path, file_type& file) {
            if (::_wsopen_s(&file, path, _O_BINARY | _O_RDONLY,
                    _SH_DENYWR, _S_IREAD) != 0) {
                file = -1;
                throw std::system_error(errno, std::system_category());
            }
        }
    };
#endif /* defined(_WIN32) */

#if defined(_WIN32)
    template<> struct basic_io_traits<HANDLE> {
        typedef HANDLE file_type;
        typedef decltype(LARGE_INTEGER::QuadPart) size_type;

        static inline void close(file_type& file) {
            ::CloseHandle(file);
        }

        // Note: must be inline to prevent code generation in library.
        static inline size_type read(file_type& file, void *dst,
            const size_type cnt);

        static inline void seek(file_type& file, const size_type offset) {
            LARGE_INTEGER o;
            o.QuadPart = offset;
            if (!::SetFilePointerEx(file, o, nullptr, FILE_BEGIN)) {
                throw std::system_error(::GetLastError(),
                    std::system_category());
            }
        }

        static inline size_type tell(file_type& file) {
            LARGE_INTEGER o, c;
            o.QuadPart = 0;
            if (!::SetFilePointerEx(file, o, &c, FILE_CURRENT)) {
                throw std::system_error(::GetLastError(),
                    std::system_category());
            }
            return c.QuadPart;
        }
    };

    template<> struct io_traits<HANDLE, char> : public basic_io_traits<HANDLE> {
        typedef char char_type;
        typedef basic_io_traits<HANDLE>::file_type file_type;
        typedef basic_io_traits<HANDLE>::size_type size_type;

        static inline void open(const char_type *path, file_type& file) {
            if ((file = ::CreateFileA(path, GENERIC_READ, FILE_SHARE_READ,
                    nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL))
                    == INVALID_HANDLE_VALUE) {
                throw std::system_error(::GetLastError(),
                    std::system_category());
            }
        }
    };
    
    template<> struct io_traits<HANDLE, wchar_t>
            : public basic_io_traits<HANDLE> {
        typedef wchar_t char_type;
        typedef basic_io_traits<HANDLE>::file_type file_type;
        typedef basic_io_traits<HANDLE>::size_type size_type;

        static inline void open(const char_type *path, file_type& file) {
            if ((file = ::CreateFileW(path, GENERIC_READ, FILE_SHARE_READ,
                    nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL))
                    == INVALID_HANDLE_VALUE) {
                throw std::system_error(::GetLastError(),
                    std::system_category());
            }
        }
    };
#endif /* defined(_WIN32) */

    template<class F, class T> inline T& read(F& handle, T& retval) {
        basic_io_traits<F>::read(handle, &retval, sizeof(retval));
        return retval;
    }

    template<class T> inline void zero_memory(T& memory) {
        ::memset(&memory, 0, sizeof(memory));
    }

} /* end namespace detail */
} /* end namespace mmpld */

#include "mmpld/io.inl"
