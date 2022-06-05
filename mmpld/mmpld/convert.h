// <copyright file="convert.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2018 - 2022 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <algorithm>
#include <functional>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

#include "mmpld/io.h"
#include "mmpld/list_header.h"
#include "mmpld/particle_traits.h"
#include "mmpld/particle_view.h"


namespace mmpld {

    /// <summary>
    /// Convert at most <paramref name="cnt" /> particles of the type described
    /// in <paramref name="header" /> starting at <paramref name="src" /> into
    /// the type defined by the <see cref="mmpld::particle_traits" />
    /// <typeparamref name="T" />.
    /// </summary>
    /// <typeparam name="T">A particle view describing the desired output type.
    /// </typeparam>
    /// <param name="src">A pointer to the source particles. Note that this must
    /// not necessarily the begin of the list, but could be any of the particles
    /// in the list provided that at least <paramref name="cnt" /> valid
    /// particles remain.</param>
    /// <param name="header">The header describing the source particle list. If
    /// the destination type requires per-vertex radii and the input does not
    /// have such, the radius from the header is used. The same holds for
    /// per-vertex colour data.</param>
    /// <param name="dst">A pointer to the destination buffer, which must be
    /// at least <paramref name="cnt" /> * <typeparamref name="T">::size bytes
    /// wide.</param>
    /// <param name="cnt">The number of particles to be converted. If this is
    /// larger than the list size in <paramref name="header" />, the conversion
    /// stops after the smaller list size has been processed.</param>
    /// <returns>The number of particles acutally converted.</returns>
    template<class T>
    std::size_t convert(const void *src, const list_header& header, void *dst,
        const std::size_t cnt);

    /// <summary>
    /// Convert at most <paramref name="cnt" /> particles from
    /// <paramref name="src" /> into the format of <paramref name="dst" />.
    /// </summary>
    /// <typeparam name="T">A particle view describing the desired output type.
    /// </typeparam>
    /// <param name="src">A pointer to the source particles. Note that this must
    /// not necessarily the begin of the list, but could be any of the particles
    /// in the list provided that at least <paramref name="cnt" /> valid
    /// particles remain.</param>
    /// <param name="header">The header describing the source particle list. If
    /// the destination type requires per-vertex radii and the input does not
    /// have such, the radius from the header is used. The same holds for
    /// per-vertex colour data.</param>
    /// <param name="dst">The destination data, which must be a good
    /// <see cref="particle_view" />.</param>
    /// <returns>The number of particles acutally converted.</returns>
    template<class T>
    std::size_t convert(const void *src, const list_header& header,
        particle_view<T>& dst, const std::size_t cnt);

    //template<class T, class F>
    //decltype(list_header::particles) read_as(F& file,
    //    const list_header& src_header,
    //    particle_view<T>& dst,
    //    const decltype(list_header::particles) cnt,
    //    decltype(list_header::particles) cnt_buffer = 0);

    template<class F>
    decltype(list_header::particles) read_as(F& file,
        const list_header& src_header, void *dst, list_header& dst_header,
        decltype(list_header::particles) cnt_buffer = 0);

    /// <summary>
    /// Read the particle list described by <paramref name="header" /> from the
    /// current position in <paramref name="file" /> and convert the data on the
    /// fly to the format of <see cref="particle_traits" />
    /// <typeparamref name="T" />.
    /// </summary>
    /// <remarks>
    /// <para>The method will read the input in batches and convert them via a
    /// temporary buffer holding <paramref name="cnt_buffer" /> particles to the
    /// requested output format. If no buffer size is specified, the whole data
    /// are read at once.</para>
    /// <para>If the requested output format matches the actual format of the
    /// input, the data are read directly into the output buffer and no
    /// intermediate buffer is allocated.</para>
    /// </remarks>
    /// <typeparam name="T">The target particle traits to convert to.</typeparam>
    /// <typeparam name="F">The type of the file handle.</typeparam>
    /// <param name="file">An open file handle with the file pointer standing at
    /// the begin of the list described by <paramref name="header" />.</param>
    /// <param name="header">The description of the list to be read.</param>
    /// <param name="dst">A buffer to hold at least <paramref name="cnt" />
    /// particles of the size defined by <typeparamref name="T" />.</param>
    /// <param name="cnt">The maximum number of particles to be read.</param>
    /// <param name="cnt_buffer">The number of particles to be converted at
    /// once. If this value is zero, which is its default, the method will
    /// allocate a conversion buffer to hold all of the particles in the input
    /// at once.</param>
    /// <returns>The number of particles actually read, which might be less than
    /// <paramref name="cnt" /> if the input was smaller.</returns>
    template<class T, class F>
    decltype(list_header::particles) read_as(F& file, const list_header& header,
        void *dst, const decltype(list_header::particles) cnt,
        decltype(list_header::particles) cnt_buffer = 0);

} /* end namespace mmpld */

#include "mmpld/convert.inl"
