﻿// <copyright file="file_header.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2018 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Copyright © 2017 SFB-TRR 161.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * mmpld::read_file_header
 */
template<class T> T& mmpld::read_file_header(T& stream, file_header& header,
        seek_table& seek_table) {
    std::uint64_t offset = 0;

    // Read and check the header.
    detail::read(stream, header);
    if (::strcmp(header.magic_identifier, "MMPLD") != 0) {
        throw std::runtime_error("The given stream does not start with a valid "
            "MMPLD header.");
    }

    // Read the seek table.
    seek_table.clear();
    seek_table.reserve(header.frames);
    for (decltype(header.frames) i = 0; i < header.frames; ++i) {
        detail::read(stream, offset);
        seek_table.push_back(offset);
    }

    return stream;
}


/*
 * mmpld::write_file_header
 */
template<class T>
T& mmpld::write_file_header(const file_header& header, T& stream) {
    detail::write(header, stream);
    return stream;
}


/*
 * mmpld::write_file_header
 */
template<class T>
T& mmpld::write_file_header(const file_header& header,
        const seek_table& seek_table, T& stream) {
    write_file_header(header, stream);

    for (decltype(header.frames) i = 0; i < header.frames; ++i) {
        detail::write(seek_table[i], stream);
    }

    return stream;
}

