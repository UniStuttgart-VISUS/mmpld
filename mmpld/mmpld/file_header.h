/// <copyright file="file_header.h" company="Visualisierungsinstitut der Universit�t Stuttgart">
/// Copyright � 2018 Visualisierungsinstitut der Universit�t Stuttgart. Alle Rechte vorbehalten.
/// Copyright � 2017 SFB-TRR 161. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph M�ller</author>

#pragma once

#include <cinttypes>
#include <cstdlib>
#include <stdexcept>
#include <vector>

#include "mmpld/io.h"


namespace mmpld {

#pragma pack(push, 1)
    /// <summary>
    /// The header at the beginning of any MMPLD file.
    /// </summary>
    struct file_header {

        /// <summary>
        /// A magic identifier for the MMPLD file type.
        /// </summary>
        char magic_identifier[6];

        /// <summary>
        /// The version of the MMPLD file type.
        /// </summary>
        std::uint16_t version;

        /// <summary>
        /// The number of frames stored in the file.
        /// </summary>
        std::uint32_t frames;

        /// <summary>
        /// The bounding box of the data in the file.
        /// </summary>
        /// <remarks>
        /// The order is: x-, y- and z-component of the begin of the bounding
        /// box followed by x-, y- and z-component of the end position.
        /// </remarks>
        float bounding_box[6];

        /// <summary>
        /// The suggested clipping box for the data in the file.
        /// </summary>
        /// <remarks>
        /// The order is: x-, y- and z-component of the begin of the bounding
        /// box followed by x-, y- and z-component of the end position.
        /// </remarks>
        float clipping_box[6];
    };
#pragma pack(pop)

    /// <summary>
    /// The seek table which contains the offsets (in bytes from the beginning
    /// of the file) of individual particle lists in the file.
    /// </summary>
    typedef std::vector<std::uint64_t> seek_table;

    /// <summary>
    /// Reads the MMPLD header and the seek table from the given stream (at its
    /// current location).
    /// </summary>
    /// <tparam name="T">The type of stream, which can be an STL stream or a
    /// file descriptor or <see cref="FILE" /> handle.</tparam>
    /// <param name="stream">The stream to read the header from. The stream must
    /// be open and in binary mode.</param>
    /// <param name="header">Receives the header.</param>
    /// <param name="seek_table">Receives the seek table.</param>
    /// <returns><paramref name="stream" />.</returns>
    template<class T>
    T& read_file_header(T& stream, file_header& header, seek_table& seek_table);

    /// <summary>
    /// Split a file version of an MMPLD file into major and minor version
    /// </summary>
    /// <param name="version">The version number to be split into their parts.
    /// </param>
    /// <param name="major">Receives the major version.</param>
    /// <param name="minor">Receives the minor version.</param>
    inline void parse_version(const std::uint16_t version, unsigned int& major,
            unsigned int& minor) {
        std::div_t v = std::div(version, 100);
        major = v.quot;
        minor = v.rem;
    }

} /* end namespace mmpld */

#include "mmpld/file_header.inl"
