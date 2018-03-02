/// <copyright file="list_header.h" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2018 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
/// Copyright © 2017 SFB-TRR 161. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>

#pragma once

#include <limits>

#include "mmpld/colour_type.h"
#include "mmpld/io.h"
#include "mmpld/particle_properties.h"
#include "mmpld/vertex_type.h"


namespace mmpld {

    /// <summary>
    /// The descriptor of the content of a particle list.
    /// </summary>
    struct list_header {

        /// <summary>
        /// The constant colour of the particles if
        /// <see cref="list_header::colour_type" /> is
        /// <see cref="colour_type::none" />.
        /// </summary>
        float colour[4];

        /// <summary>
        /// The type of per-vertex colours in the list.
        /// </summary>
        mmpld::colour_type colour_type;

        /// <summary>
        /// The maximum intensity found in the list if
        /// <see cref="list_header::colour_type" /> is
        /// <see cref="colour_type::float_i" />.
        /// </summary>
        float max_intensity;

        /// <summary>
        /// The minimum intensity found in the list if
        /// <see cref="list_header::colour_type" /> is
        /// <see cref="colour_type::float_i" />.
        /// </summary>
        float min_intensity;

        /// <summary>
        /// The number of particles in the list.
        /// </summary>
        std::uint64_t particles;

        /// <summary>
        /// The global radius of the particles in the list if no individual
        /// radius is given on a per-vertex basis.
        /// </summary>
        float radius;

        /// <summary>
        /// The type of position data per vertex.
        /// </summary>
        mmpld::vertex_type vertex_type;
    };

    /// <summary>
    /// Retrieve the particle properties of the list described by the given
    /// header.
    /// </summary>
    /// <tparam name="T">The type to return the bitmask as. This type must be
    /// at least as wide as <see cref="mmpld::particle_properties" />.</tparam>
    /// <param name="header">The list header to get the properties for.</param>
    /// <returns>A bitmask holding the particle properties.</returns>
    template<class T> T get_properties(const list_header& header);

    /// <summary>
    /// Compute the stride of the particles in the list described by the given
    /// header.
    /// </summary>
    /// <tparam name="T">The scalar type to express the stride in. This is
    /// usually <c>size_t</c> when working on the CPU or <c>UINT</c> when
    /// working with Direct3D.</tparam>
    /// <param name="header">The list header to get the stride for.</param>
    /// <returns>The stide of the particles in bytes.</returns>
    template<class T> T get_stride(const list_header& header);

    /// <summary>
    /// Reads an MMPLD list header fromt he current location in the stream.
    /// </summary>
    /// <tparam name="T">The type of stream, which can be an STL stream or a
    /// file descriptor or <see cref="FILE" /> handle.</tparam>
    /// <param name="stream">The stream to read the header from. The stream must
    /// be open and in binary mode.</param>
    /// <param name="header">Receives the header.</param>
    /// <returns><paramref name="stream" />.</returns>
    template<class T> T& read_list_header(T& stream, list_header& header);

} /* end namespace mmpld */

#include "mmpld/list_header.inl"
