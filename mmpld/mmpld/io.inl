/// <copyright file="io.inl" company="Visualisierungsinstitut der Universit�t Stuttgart">
/// Copyright � 2018 Visualisierungsinstitut der Universit�t Stuttgart. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph M�ller</author>


/*
 * mmpld::detail::basic_io_traits<FILE *>::read
 */
mmpld::detail::basic_io_traits<FILE *>::size_type
mmpld::detail::basic_io_traits<FILE *>::read(file_type& file, void *dst,
        const size_type cnt) {
    assert(cnt < (std::numeric_limits<unsigned int>::max)());
    auto ptr = reinterpret_cast<std::uint8_t *>(dst);
    auto rem = static_cast<size_t>(cnt);

    while (rem > 0) {
        auto read = ::fread(ptr, 1, rem, file);
        if (::ferror(file)) {
            throw std::system_error(errno, std::system_category());
        }
        ptr += read;
        rem -= read;
        if (::feof(file)) {
            break;
        }
    }

    return (cnt - rem);
}


/*
 * mmpld::detail::basic_io_traits<int>::read
 */
mmpld::detail::basic_io_traits<int>::size_type
mmpld::detail::basic_io_traits<int>::read(file_type& file, void *dst,
        const size_type cnt) {
    auto ptr = reinterpret_cast<std::uint8_t *>(dst);
    auto rem = cnt;

    while (rem > 0) {
#if defined(_WIN32)
        assert(rem < (std::numeric_limits<unsigned int>::max)());
        auto read = ::_read(file, ptr, static_cast<unsigned int>(rem));
#else /* defined(_WIN32) */
        auto cnt = ::read(file, ptr, rem);
#endif /* defined(_WIN32) */
        if (read == -1) {
            throw std::system_error(errno, std::system_category());
        }
        if (read == 0) {
            // EOF
            break;
        }
        ptr += read;
        rem -= read;
    }

    return (cnt - rem);
}


#if defined(_WIN32)
/*
 * mmpld::detail::basic_io_traits<HANDLE>::read
 */
mmpld::detail::basic_io_traits<HANDLE>::size_type
mmpld::detail::basic_io_traits<HANDLE>::read(file_type& file, void *dst,
        const size_type cnt) {
    assert(cnt < (std::numeric_limits<DWORD>::max)());
    auto ptr = reinterpret_cast<std::uint8_t *>(dst);
    auto rem = static_cast<DWORD>(cnt);

    while (rem > 0) {
        DWORD read = 0;
        if (!::ReadFile(file, ptr, rem, &read, nullptr)) {
            throw std::system_error(::GetLastError(), std::system_category());
        }
        if (read == 0) {
            // EOF
            break;
        }
        ptr += read;
        rem -= read;
    }

    return (cnt - rem);
}
#endif /* defined(_WIN32) */
