// <copyright file="frame_header.inl" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2018 - 2023 Visualisierungsinstitut der Universit�t Stuttgart. Alle Rechte vorbehalten.
// Copyright � 2017 SFB-TRR 161. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph M�ller</author>


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


/*
 * mmpld::read_frame_header
 */
template<class T> T& mmpld::read_frame_header(T& stream,
        const std::uint16_t version, frame_header& header) {
    unsigned int major, minor;
    mmpld::parse_version(version, major, minor);

    // Clear everything because some information is optional.
    detail::zero_memory(header);

    // Version 1.2 and above has a frame timestamp.
    if ((major > 1) || (minor >= 2)) {
        detail::read(stream, header.timestamp);
    }

    // All versions have the number of particle lists to follow.
    detail::read(stream, header.lists);

    return stream;
}


/*
 * mmpld::write_frame_header
 */
template<class T> T& mmpld::write_frame_header(const frame_header& header,
        const std::uint16_t version, T& stream) {
    unsigned int major, minor;
    mmpld::parse_version(version, major, minor);

    // Version 1.2 and above has a frame timestamp.
    if ((major > 1) || (minor >= 2)) {
        detail::write(header.timestamp, stream);
    }

    detail::write(header.lists, stream);

    return stream;
}
