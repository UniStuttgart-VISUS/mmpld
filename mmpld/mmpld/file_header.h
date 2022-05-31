// <copyright file="file_header.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2018 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// Copyright © 2017 SFB-TRR 161. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

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
    /// Creates a a file version from the given major and minor version.
    /// </summary>
    /// <param name="major">The major version.</param>
    /// <param name="minor">The minor version.</param>
    /// <returns>The version number as it appears in an MMPLD file.</returns>
    inline std::uint16_t make_version(const std::uint16_t major,
            const std::uint16_t minor) {
        assert(minor < 100);
        return (major * 100) + minor;
    }

    /// <summary>
    /// Reads the MMPLD header and the seek table from the given stream (at its
    /// current location).
    /// </summary>
    /// <typeparam name="T">The type of stream, which can be an STL stream or a
    /// file descriptor or <see cref="FILE" /> handle.</typeparam>
    /// <param name="stream">The stream to read the header from. The stream must
    /// be open and in binary mode.</param>
    /// <param name="header">Receives the header.</param>
    /// <param name="seek_table">Receives the seek table.</param>
    /// <returns><paramref name="stream" />.</returns>
    template<class T>
    T& read_file_header(T& stream, file_header& header, seek_table& seek_table);

    /// <summary>
    /// Split a file version of an MMPLD file into major and minor version.
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

    /// <summary>
    /// Writes the given MMPLD file header to the current location in the given
    /// stream.
    /// </summary>
    /// <typeparam name="T">The type of stream, which can be an STL stream or a
    /// file descriptor or <see cref="FILE" /> handle.</typeparam>
    /// <param name="header">The file header to be written.</param>
    /// <param name="stream">The stream to read the header from. The stream must
    /// be open and in binary mode.</param>
    /// <returns><paramref name="stream" />.</returns>
    template<class T>
    T& write_file_header(const file_header& header, T& stream);

    /// <summary>
    /// Writes the given MMPLD file header and seek table to the current
    /// location in the given stream.
    /// </summary>
    /// <typeparam name="T">The type of stream, which can be an STL stream or a
    /// file descriptor or <see cref="FILE" /> handle.</typeparam>
    /// <param name="header">The file header to be written.</param>
    /// <param name="seek_table">The seek table to be added after the header.
    /// </param>
    /// <param name="stream">The stream to read the header from. The stream must
    /// be open and in binary mode.</param>
    /// <returns><paramref name="stream" />.</returns>
    template<class T>
    T& write_file_header(const file_header& header,
        const seek_table& seek_table, T& stream);

} /* end namespace mmpld */

#include "mmpld/file_header.inl"
