// <copyright file="frame_header.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2018 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// Copyright © 2017 SFB-TRR 161. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>
#include <istream>

#include "mmpld/io.h"


namespace mmpld {

    /// <summary>
    /// The descriptor of a frame, which might comprise multiple lists.
    /// </summary>
    struct frame_header {
        /// <summary>
        /// The number of lists in the frame.
        /// </summary>
        std::int32_t lists;

        /// <summary>
        /// The (optional) timestamp of the frame.
        /// </summary>
        float timestamp;
    };

    /// <summary>
    /// Reads the frame header (of the specified file version) from the current
    /// position in the file.
    /// </summary>
    /// <tparam name="T">The type of stream, which can be an STL stream or a
    /// file descriptor or <see cref="FILE" /> handle.</tparam>
    /// <param name="stream">The stream to read from. The stream must be open
    /// and in binary mode and must point to the frame header.</param>
    /// <param name="header">Receives the frame header.</param>
    /// <param name="version">The file format version obtained from the
    /// <see cref="mmpld::file_header" />.</param>
    /// <returns><paramref name="stream" />.</returns>
    template<class T> T& read_frame_header(T& stream, const std::uint16_t version,
        frame_header& header);

} /* end namespace mmpld */

#include "mmpld/frame_header.inl"
