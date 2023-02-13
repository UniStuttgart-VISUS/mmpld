// <copyright file="frame_header.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2018 - 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// Copyright © 2017 SFB-TRR 161. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>


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
