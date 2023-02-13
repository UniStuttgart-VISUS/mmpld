// <copyright file="frame_header.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2018 - 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// Copyright © 2017 SFB-TRR 161. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>
#include <istream>

#include "file_header.h"
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
    /// Retreive the overall number of particles in the lists of the frame.
    /// </summary>
    /// <remarks>
    /// <para>This function requires the file pointer in
    /// <paramref name="stream" /> to point to the first particle list of the
    /// frame described by <paramref name="header" />. The behaviour of the
    /// function is undefined if this precondition is not met.</para>
    /// <para>The function will seek through all lists in the frame and tally
    /// the overall particles of the frame. Before the function returns
    /// successfully, the file pointer will be restored to the location it
    /// was when the function was entered. The position of the file pointer
    /// is undefined if the function fails. Callers must seek to the begin
    /// of a frame manually in this case.</para>
    /// </remarks>
    /// <typeparam name="T">The scalar type to express the size in. This is
    /// usually <c>size_t</c> when working on the CPU or <c>UINT</c> when
    /// working with Direct3D.</typeparam>
    /// <typeparam name="F">The representation of the file.</typeparam>
    /// <param name="header">The frame header to get the size for.</param>
    /// <param name="version">The file format version obtained from the
    /// <see cref="mmpld::file_header" />.</param>
    /// <param name="stream">The stream containing the lists. The file pointer
    /// must stand at the position after the frame header, ie on the list
    /// header of the first list in the frame. The method will reset
    /// the position before it returns.</para>
    /// <returns>The total number of particles in all lists of the frame.
    /// </returns>
    template<class T, class F>
    T count(const frame_header& header, const std::uint16_t version,
        F& stream);

    /// <summary>
    /// Reads the frame header (of the specified file version) from the current
    /// position in the file.
    /// </summary>
    /// <typeparam name="T">The type of stream, which can be an STL stream or a
    /// file descriptor or <see cref="FILE" /> handle.</typeparam>
    /// <param name="stream">The stream to read from. The stream must be open
    /// and in binary mode and must point to the frame header.</param>
    /// <param name="header">Receives the frame header.</param>
    /// <param name="version">The file format version obtained from the
    /// <see cref="mmpld::file_header" />.</param>
    /// <returns><paramref name="stream" />.</returns>
    template<class T> T& read_frame_header(T& stream, const std::uint16_t version,
        frame_header& header);

    /// <summary>
    /// Writes the given frame header assuming the given file format version to
    /// the current position in the file.
    /// </summary>
    /// <typeparam name="T">The type of stream, which can be an STL stream or a
    /// file descriptor or <see cref="FILE" /> handle.</typeparam>
    /// <param name="header">The frame header to be written.</param>
    /// <param name="version">The file format version obtained from the
    /// <see cref="mmpld::file_header" />.</param>
    /// <param name="stream">The stream to read from. The stream must be open
    /// and in binary mode and must point to the frame header.</param>
    /// <returns><paramref name="stream" />.</returns>
    template<class T> T& write_frame_header(const frame_header& header,
        const std::uint16_t version, T& stream);

} /* end namespace mmpld */

#include "mmpld/frame_header.inl"
