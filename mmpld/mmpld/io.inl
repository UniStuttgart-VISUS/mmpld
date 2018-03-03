/// <copyright file="io.inl" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2018 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>


/*
 * mmpld::detail::read_all
 */
template<class T>
void mmpld::detail::read_all(FILE *file, T *dst, const size_t cnt) {
    auto ptr = reinterpret_cast<std::uint8_t *>(dst);
    auto rem = cnt * sizeof(T);

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
 * mmpld::detail::read_all
 */
template<class T>
void mmpld::detail::read_all(int file, T *dst, const size_t cnt) {
    auto ptr = reinterpret_cast<std::uint8_t *>(dst);
    auto rem = static_cast<unsigned int>(cnt * sizeof(T));

    while (rem > 0) {
#if defined(_WIN32)
        auto cnt = ::_read(file, ptr, rem);
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
 * mmpld::detail::read_all
 */
template<class T>
void mmpld::detail::read_all(HANDLE file, T *dst, const size_t cnt) {
    auto ptr = reinterpret_cast<std::uint8_t *>(dst);
    auto rem = static_cast<DWORD>(cnt * sizeof(T));

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
