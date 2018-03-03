/// <copyright file="frame_header.inl" company="Visualisierungsinstitut der Universit�t Stuttgart">
/// Copyright � 2018 Visualisierungsinstitut der Universit�t Stuttgart. Alle Rechte vorbehalten.
/// Copyright � 2017 SFB-TRR 161. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph M�ller</author>


/*
 * mmpld::read_frame_header
 */
template<class T> T& mmpld::read_frame_header(T& stream,
        const std::uint16_t version, frame_header& header) {
    unsigned int major, minor;
    mmpld::parse_version(version, major, minor);

    // Clear everything because some information is optional.
    detail::zero_memory(header);

    // Version 2 and above has a frame timestamp.
    if (minor >= 2) {
        detail::read(stream, header.timestamp);
    }

    // All versions have the number of particle lists to follow.
    detail::read(stream, header.lists);

    return stream;
}
