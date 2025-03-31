// <copyright file="count.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "mmpld/file_header.h"
#include "mmpld/frame_header.h"
#include "mmpld/list_header.h"


namespace mmpld {

    /// <summary>
    /// Retreive the number of particles from the list.
    /// </summary>
    /// <typeparam name="T">The scalar type to express the size in. This is
    /// usually <c>size_t</c> when working on the CPU or <c>UINT</c> when
    /// working with Direct3D.</typeparam>
    /// <param name="header">The list header to get the size for.</param>
    /// <returns><see cref="mmpld::list_header::particles" />.</returns>
    template<class T> inline T count(const list_header &header) noexcept {
        return static_cast<T>(header.particles);
    }

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

} /* end namespace mmpld */

#include "mmpld/count.inl"
