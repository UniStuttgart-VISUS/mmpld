// <copyright file="count.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * MMPLD_NAMESPACE::count
 */
template<class T, class F>
T MMPLD_NAMESPACE::count(const frame_header& header,
        const std::uint16_t version,
        F& stream) {
    list_header listHeader;
    const auto pos = detail::basic_io_traits<F>::tell(stream);
    auto retval = static_cast<T>(0);

    for (decltype(header.lists) i = 0; i < header.lists; ++i) {
        read_list_header(stream, version, listHeader);
        retval += static_cast<T>(listHeader.particles);

        skip_particles(stream, listHeader);

        if (version == make_version(1, 1)) {
            // MMPLD 1.1 needs to skip the cluster information block as well.
            skip_cluster_info(stream);
        }
    }

    detail::basic_io_traits<F>::seek(stream, pos);

    return retval;
}
