// <copyright file="convert.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2018 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <algorithm>
#include <stdexcept>

#include "mmpld/io.h"
#include "mmpld/list_header.h"
#include "mmpld/particle_traits.h"
#include "mmpld/particle_view.h"


namespace mmpld {

    /// <summary>
    /// Convert <paramref name="cnt" /> particles of the type described in
    /// <paramref name="header" /> starting at <paramref name="src" /> into the
    /// type defined by the <see cref="mmpld::particle_view" />
    /// <tparamref name="T" />.
    /// </summary>
    /// <tparam name="T">A particle view describing the desired output type.
    /// </tparam>
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
    /// at least <paramref name="cnt" /> * <tparamref name="T">::size bytes
    /// wide.</param>
    /// <param name="cnt">The number of particles to be converted. If this is
    /// larger than the list size in <paramref name="header" />, the conversion
    /// stops after the smaller list size has been processed.</param>
    /// <returns>The number of particles acutally converted.</returns>
    template<class T>
    size_t convert(const void *src, const list_header& header, void *dst,
        const size_t cnt);

} /* end namespace mmpld */

#include "mmpld/convert.inl"
