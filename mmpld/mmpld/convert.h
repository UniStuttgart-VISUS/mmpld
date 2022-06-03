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
    /// per-vertex colour data.
    /// </param>
    /// <param name="void">A pointer to the destination buffer, which must be
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
    /// Convert <paramref name="cnt" /> particles from <paramref name="src" />
    /// into the format of <paramref name="dst" />.
    /// </summary>
    /// <typeparam name="T">A particle view describing the desired output type.
    /// </typeparam>
    /// <typeparam name="S">A particle view describing the desired input type.
    /// </typeparam>
    /// <param name="src">The source data, which must be a good
    /// <see cref="particle_view" />.</param>
    /// <param name="dst">The destination data, which must be a good
    /// <see cref="particle_view" />.</param>
    template<class T, class S>
    void convert(const particle_view<T>& src, const particle_view<T>& dst,
        const std::size_t cnt);

} /* end namespace mmpld */

#include "mmpld/convert.inl"
