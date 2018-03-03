/// <copyright file="io.h" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2018 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>

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

    template<class F, class C> struct io_traits {
        typedef C char_type;
        typedef F file_type;
    };

    template<class T> inline void read_all(std::istream& stream, T *dst,
            const size_t cnt) {
        stream.read(reinterpret_cast<char *>(dst), cnt * sizeof(T));
    }

    template<> struct io_traits<std::ifstream, char> {
        typedef char char_type;
        typedef std::ifstream file_type;

        static inline void close(file_type& file) {
            file.close();
        }

        static inline void open(const char_type *path, file_type& file) {
            file.open(path, std::ios::binary);
        }

        static inline void read(file_type& file, void *dst, const size_t cnt) {
            file.read(static_cast<char_type *>(dst), cnt);
        }

        static inline void seek(file_type& file, const size_t offset) {
            file.seekg(offset);
        }
    };

    template<class T> void read_all(FILE *file, T *dst, const size_t cnt);

    template<> struct io_traits<FILE *, char> {
        typedef char char_type;
        typedef FILE *file_type;

        static inline void close(file_type& file) {
            if (file != nullptr) {
                ::fclose(file);
                file = nullptr;
            }
        }

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

        static inline void read(file_type& file, void *dst, const size_t cnt) {
            read_all(file, static_cast<std::uint8_t *>(dst), cnt);
        }

        static inline void seek(file_type& file, const size_t offset) {
#if defined(_WIN32)
            ::_fseeki64(file, static_cast<std::int64_t>(offset), SEEK_SET);
#else /* defined(_WIN32) */
            ::fseek(file, static_cast<int>(offset), SEEK_SET);
#endif /* defined(_WIN32) */
        }
    };

#if defined(_WIN32)
    template<> struct io_traits<FILE *, wchar_t> {
        typedef wchar_t char_type;
        typedef FILE *file_type;

        static inline void close(file_type& file) {
            if (file != nullptr) {
                ::fclose(file);
                file = nullptr;
            }
        }

        static inline void open(const char_type *path, file_type& file) {
            static const char_type *const MODE = L"rb";
            if (::_wfopen_s(&file, path, MODE) != 0) {
                file = nullptr;
                throw std::system_error(errno, std::system_category());
            }
        }

        static inline void read(file_type& file, void *dst, const size_t cnt) {
            read_all(file, static_cast<std::uint8_t *>(dst), cnt);
        }

        static inline void seek(file_type& file, const size_t offset) {
            ::_fseeki64(file, static_cast<std::int64_t>(offset), SEEK_SET);
        }
    };
#endif /* defined(_WIN32) */

    template<class T> void read_all(int file, T *dst, const size_t cnt);

    template<> struct io_traits<int, char> {
        typedef char char_type;
        typedef int file_type;

        static inline void close(file_type& file) {
#if defined(_WIN32)
            ::_close(file);
#else /* defined(_WIN32) */
            ::close(file);
#endif /* defined(_WIN32) */
        }

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

        static inline void read(file_type& file, void *dst, const size_t cnt) {
            read_all(file, static_cast<std::uint8_t *>(dst), cnt);
        }

        static inline void seek(file_type& file, const size_t offset) {
#if defined(_WIN32)
            ::_lseeki64(file, static_cast<std::int64_t>(offset), SEEK_SET);
#else /* defined(_WIN32) */
            ::lseek(file, static_cast<int>(offset), SEEK_SET);
#endif /* defined(_WIN32) */
        }
    };

#if defined(_WIN32)
    template<> struct io_traits<int, wchar_t> {
        typedef wchar_t char_type;
        typedef int file_type;

        static inline void close(file_type& file) {
            ::_close(file);
        }

        static inline void open(const char_type *path, file_type& file) {
            if (::_wsopen_s(&file, path, _O_BINARY | _O_RDONLY,
                    _SH_DENYWR, _S_IREAD) != 0) {
                file = -1;
                throw std::system_error(errno, std::system_category());
            }
        }

        static inline void read(file_type& file, void *dst, const size_t cnt) {
            read_all(file, static_cast<std::uint8_t *>(dst), cnt);
        }
        static inline void seek(file_type& file, const size_t offset) {
            ::_lseeki64(file, static_cast<std::int64_t>(offset), SEEK_SET);
        }
    };
#endif /* defined(_WIN32) */

#if defined(_WIN32)
    template<class T> void read_all(HANDLE file, T *dst, const size_t cnt);
#endif /* defined(_WIN32) */

#if defined(_WIN32)
    template<> struct io_traits<HANDLE, char> {
        typedef char char_type;
        typedef HANDLE file_type;

        static inline void close(file_type& file) {
            ::CloseHandle(file);
        }

        static inline void open(const char_type *path, file_type& file) {
            if ((file = ::CreateFileA(path, GENERIC_READ, FILE_SHARE_READ,
                    nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL))
                    == INVALID_HANDLE_VALUE) {
                throw std::system_error(::GetLastError(),
                    std::system_category());
            }
        }

        static inline void read(file_type& file, void *dst, const size_t cnt) {
            read_all(file, static_cast<std::uint8_t *>(dst), cnt);
        }

        static inline void seek(file_type& file, const size_t offset) {
            LARGE_INTEGER o;
            o.QuadPart = offset;
            if (!::SetFilePointerEx(file, o, nullptr, FILE_BEGIN)) {
                throw std::system_error(::GetLastError(),
                    std::system_category());
            }
        }
    };
#endif /* defined(_WIN32) */

#if defined(_WIN32)
    template<> struct io_traits<HANDLE, wchar_t> {
        typedef wchar_t char_type;
        typedef HANDLE file_type;

        static inline void close(file_type& file) {
            ::CloseHandle(file);
        }

        static inline void open(const char_type *path, file_type& file) {
            if ((file = ::CreateFileW(path, GENERIC_READ, FILE_SHARE_READ,
                    nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL))
                    == INVALID_HANDLE_VALUE) {
                throw std::system_error(::GetLastError(),
                    std::system_category());
            }
        }

        static inline void read(file_type& file, void *dst, const size_t cnt) {
            read_all(file, static_cast<std::uint8_t *>(dst), cnt);
        }

        static inline void seek(file_type& file, const size_t offset) {
            LARGE_INTEGER o;
            o.QuadPart = offset;
            if (!::SetFilePointerEx(file, o, nullptr, FILE_BEGIN)) {
                throw std::system_error(::GetLastError(),
                    std::system_category());
            }
        }
    };
#endif /* defined(_WIN32) */

    template<class F, class T> inline T& read(F& handle, T& retval) {
        read_all(handle, &retval, 1);
        return retval;
    }

    template<class T> inline void zero_memory(T& memory) {
        ::memset(&memory, 0, sizeof(memory));
    }

} /* end namespace detail */
} /* end namespace mmpld */

#include "mmpld/io.inl"
