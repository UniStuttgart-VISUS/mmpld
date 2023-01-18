// <copyright file="count.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

/*
 * mmpld::count
 */
template<class T, class F>
T mmpld::count(const frame_header& header, const std::uint16_t version,
        F& stream) {
    mmpld::list_header listHeader;
    const auto pos = detail::basic_io_traits<F>::tell(stream);
    auto retval = static_cast<T>(0);

    for (decltype(header.lists) i = 0; i < header.lists; ++i) {
        mmpld::read_list_header(stream, version, listHeader);
        retval += static_cast<T>(listHeader.particles);

        skip_particles(stream, listHeader);

        if (version == mmpld::make_version(1, 1)) {
            // MMPLD 1.1 needs to skip the cluster information block as well.
            mmpld::skip_cluster_info(stream);
        }
    }

    detail::basic_io_traits<F>::seek(stream, pos);

    return retval;
}