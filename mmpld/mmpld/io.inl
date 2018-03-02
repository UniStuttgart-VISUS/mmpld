/// <copyright file="io.inl" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2018 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
/// Copyright © 2017 SFB-TRR 161. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>


/*
 * mmpld::detail::open
 */
template<class C, class T>
void mmpld::detail::open(const C *path, std::basic_ifstream<C, T>& stream) {
    if (path == nullptr) {
        std::invalid_argument("The path must not be nullptr.");
    }

    stream.open(path, std::ios::binary);
}


/*
 * mmpld::detail::open
 */
template<class C> void mmpld::detail::open(const C *path, int& stream) {
    if (path == nullptr) {
        std::invalid_argument("The path must not be nullptr.");
    }

    stream = io_traits<C>::open(path, O_BINARY | O_RDONLY);
    if (stream == -1) {
        throw std::system_error(errno, std::system_category());
    }
}


/*
 * mmpld::detail::open
 */
template<class C> void mmpld::detail::open(const C *path, FILE *& stream) {
    if (path == nullptr) {
        std::invalid_argument("The path must not be nullptr.");
    }

    stream = io_traits<C>::fopen(path, MMPLD_TPL_LITERAL(C, "rb"));
    if (stream == nullptr) {
        throw std::system_error(errno, std::system_category());
    }
}


/*
 * mmpld::detail::read
 */
template<class T> T& mmpld::detail::read(int handle, T& retval) {
    auto dst = reinterpret_cast<std::uint8_t *>(&retval);
    auto rem = sizeof(retval);

    while (rem > 0) {
#if defined(WIN32)
        auto cnt = ::_read(handle, dst, rem);
#else /* defined(WIN32) */
        auto cnt = ::read(handle, dst, rem);
#endif /* defined(WIN32) */
        if (cnt == -1) {
            throw std::system_error(errno, std::system_category());
        }
        dst += cnt;
        rem -= cnt;
    }

    return retval;
}


/*
 * mmpld::detail::read
 */
template<class T> T& mmpld::detail::read(FILE *handle, T& retval) {
    auto dst = reinterpret_cast<std::uint8_t *>(&retval);
    auto rem = sizeof(retval);

    while (rem > 0) {
        auto cnt = ::fread(dst, rem, 1, handle);
        if (::ferror(handle)) {
            throw std::system_error(errno, std::system_category());
        }
        dst += cnt;
        rem -= cnt;
    }

    return retval;
}
