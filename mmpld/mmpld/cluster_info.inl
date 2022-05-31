// <copyright file="cluster_info.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2019 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>


/*
 * mmpld::read_cluster_info
 */
template<class F> mmpld::cluster_info mmpld::read_cluster_info(F& file) {
    typedef detail::basic_io_traits<F> io_traits_type;
    std::uint32_t cnt = 0;
    std::uint64_t size = 0; // HAZARD: This is just a guess. The original code
                            // uses size_t, which has different sizes in 32-bit
                            // and 64-bit builds. However, we assume the author
                            // used 64-bit builds, because otherwise, it would
                            // have not made sense using different types for
                            // the list counter and the data size.
    cluster_info retval;

    detail::read(file, cnt);
    detail::read(file, size);

    retval._count = static_cast<std::size_t>(cnt);

    retval._data.resize(size);
    io_traits_type::read(file, retval._data.data(), retval._data.size());

    return retval;
}


/*
 * mmpld::skip_cluster_info
 */
template<class F> void mmpld::skip_cluster_info(F& file) {
    typedef detail::basic_io_traits<F> io_traits_type;
    std::uint32_t cnt = 0;
    std::uint64_t size = 0; // HAZARD: This is just a guess.
                            // Cf. read_cluster_info().

    detail::read(file, cnt);
    detail::read(file, size);

    auto offset = io_traits_type::tell(file);
    offset += size;
    io_traits_type::seek(file, offset);
}
