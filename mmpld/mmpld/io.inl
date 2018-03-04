/// <copyright file="io.inl" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2018 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>


/*
 * mmpld::detail::basic_io_traits<FILE *>::read
 */
void mmpld::detail::basic_io_traits<FILE *>::read(file_type& file, void *dst,
        const size_type cnt) {
    assert(cnt < (std::numeric_limits<unsigned int>::max)());
    auto ptr = reinterpret_cast<std::uint8_t *>(dst);
    auto rem = static_cast<size_t>(cnt);

    while (rem > 0) {
        auto cnt = ::fread(ptr, 1, rem, file);
        if (::ferror(file)) {
            throw std::system_error(errno, std::system_category());
        }
        ptr += cnt;
        rem -= cnt;
    }
}


/*
 * mmpld::detail::basic_io_traits<int>::read
 */
void mmpld::detail::basic_io_traits<int>::read(file_type& file, void *dst,
        const size_type cnt) {
    auto ptr = reinterpret_cast<std::uint8_t *>(dst);
    auto rem = cnt;

    while (rem > 0) {
#if defined(_WIN32)
        assert(rem < (std::numeric_limits<unsigned int>::max)());
        auto cnt = ::_read(file, ptr, static_cast<unsigned int>(rem));
#else /* defined(_WIN32) */
        auto cnt = ::read(file, ptr, rem);
#endif /* defined(_WIN32) */
        if (cnt == -1) {
            throw std::system_error(errno, std::system_category());
        }
        ptr += cnt;
        rem -= cnt;
    }
}


#if defined(_WIN32)
/*
 * mmpld::detail::basic_io_traits<HANDLE>::read
 */
void mmpld::detail::basic_io_traits<HANDLE>::read(file_type& file, void *dst,
        const size_type cnt) {
    assert(cnt < (std::numeric_limits<DWORD>::max)());
    auto ptr = reinterpret_cast<std::uint8_t *>(dst);
    auto rem = static_cast<DWORD>(cnt);

    while (rem > 0) {
        DWORD cnt = 0;
        if (!::ReadFile(file, ptr, rem, &cnt, nullptr)) {
            throw std::system_error(::GetLastError(), std::system_category());
        }
        ptr += cnt;
        rem -= cnt;
    }
}
#endif /* defined(_WIN32) */
