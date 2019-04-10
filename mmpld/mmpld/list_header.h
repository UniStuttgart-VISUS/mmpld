/// <copyright file="list_header.h" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2018 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
/// Copyright © 2017 SFB-TRR 161. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>

#pragma once

#include <limits>
#include <type_traits>
#include <vector>

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
        /// The bounding box of the data in the list.
        /// </summary>
        /// <remarks>
        /// <para>This member is only set for file version 1.3 or above.
        /// Otherwise, all members will be zero.</para>
        /// <para>The order is: x-, y- and z-component of the begin of the
        /// bounding box followed by x-, y- and z-component of the end position.
        /// </para>
        /// </remarks>
        float bounding_box[6];

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

#if defined(MMPLD_WITH_DIRECT3D)
    /// <summary>
    /// Gets the Direct3D input layout elements for the given particle list.
    /// </summary>
    /// <remarks>
    /// <para>Direct3D 10, Direct3D 11 and Direct3D 12 use a similarly layouted
    /// structure for describing the input layout. You can use any structure
    /// with and identical memory layout (that can be initialises with the same
    /// initialiser list) as output parameter.</para>
    /// </remarks>
    /// <tparam name="T">An element in the input layout. This can be one of
    /// <see cref="D3D10_INPUT_ELEMENT_DESC" />,
    /// <see cref="D3D11_INPUT_ELEMENT_DESC" />,
    /// <see cref="D3D12_INPUT_ELEMENT_DESC" /> or any compatible layout.
    /// </tparam>
    /// <param name="header">The list header to get the layout for.</param>
    /// <returns>A vector describing the input layout.</returns>
    /// <exception cref="std::runtime_error">If the particle list is not
    /// compliant with the alignment requirements for Direct3D. As of version
    /// 1.2 of MMPLD, incompatible layouts are the ones using
    /// <see cref="mmpld::vertex_type::short_xyz" /> and/or
    /// <see cref="mmpld::colour_type::rgb8" />.</exception>
    template<class T>
    std::vector<T> get_input_layout(const list_header& header);
#endif /* defined(MMPLD_WITH_DIRECT3D) */

    /// <summary>
    /// Gets the offsets of the individual components of a particle in the
    /// given list.
    /// </summary>
    /// <tparam name="T">The scalar type to express the offsets in. If this is
    /// a signed type, invalid offsets will be negative. Otherwise, the maximum
    /// value of the type is used to express invalid offsets.</tparam>
    /// <param name="pos">Receives the offset of the position in bytes.</param>
    /// <param name="rad">Receives the offset of the radius in bytes.</param>
    /// <param name="col">Receives the offset of the colour in bytes.</param>
    /// <returns>The value that is used to express invalid offsets.</returns>
    template<class T>
    T get_offsets(const list_header& header, T& pos, T& rad, T& col);

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
    /// Compute the size of the raw particle data in the list.
    /// </summary>
    /// <tparam name="T">The scalar type to express the size in. This is
    /// usually <c>size_t</c> when working on the CPU or <c>UINT</c> when
    /// working with Direct3D.</tparam>
    /// <param name="header">The list header to get the size for.</param>
    /// <returns>The total size of the particles in bytes.</returns>
    template<class T> inline T get_size(const list_header& header) {
        return static_cast<T>(header.particles) * get_stride<T>(header);
    }

    /// <summary>
    /// Reads an MMPLD list header fromt he current location in the stream.
    /// </summary>
    /// <tparam name="T">The type of stream, which can be an STL stream or a
    /// file descriptor or <see cref="FILE" /> handle.</tparam>
    /// <param name="stream">The stream to read the header from. The stream must
    /// be open and in binary mode.</param>
    /// <param name="fileVersion">The version of the MMPLD file, which is
    /// required to handle different formats of the list header.</param>
    /// <param name="header">Receives the header.</param>
    /// <returns><paramref name="stream" />.</returns>
    template<class T>
    T& read_list_header(T& stream, const std::uint16_t fileVersion,
        list_header& header);

} /* end namespace mmpld */

#include "mmpld/list_header.inl"
