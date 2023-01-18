// <copyright file="list_header.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2018 - 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// Copyright © 2017 SFB-TRR 161. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <limits>
#include <type_traits>
#include <vector>

#include "mmpld/colour_properties.h"
#include "mmpld/colour_type.h"
#include "mmpld/enum_dispatch.h"
#include "mmpld/io.h"
#include "mmpld/particle_properties.h"
#include "mmpld/vertex_properties.h"
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
    /// <typeparam name="T">An element in the input layout. This can be one of
    /// <see cref="D3D10_INPUT_ELEMENT_DESC" />,
    /// <see cref="D3D11_INPUT_ELEMENT_DESC" />,
    /// <see cref="D3D12_INPUT_ELEMENT_DESC" /> or any compatible layout.
    /// </typeparam>
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
    /// <typeparam name="T">The scalar type to express the offsets in. If this is
    /// a signed type, invalid offsets will be negative. Otherwise, the maximum
    /// value of the type is used to express invalid offsets.</typeparam>
    /// <param name="pos">Receives the offset of the position in bytes.</param>
    /// <param name="rad">Receives the offset of the radius in bytes.</param>
    /// <param name="col">Receives the offset of the colour in bytes.</param>
    /// <returns>The value that is used to express invalid offsets.</returns>
    template<class T>
    T get_offsets(const list_header& header, T& pos, T& rad, T& col) noexcept;

    /// <summary>
    /// Retrieve the particle properties of the list described by the given
    /// header.
    /// </summary>
    /// <typeparam name="T">The type to return the bitmask as. This type must be
    /// at least as wide as <see cref="mmpld::particle_properties" />. Using a
    /// template here allows the caller to decide whether the return value
    /// should by the <c>enum class</c> used by the library or another type
    /// which can be used to perform computations.</typeparam>
    /// <param name="header">The list header to get the properties for.</param>
    /// <returns>A bitmask holding the particle properties.</returns>
    template<class T> T get_properties(const list_header& header) noexcept;

    /// <summary>
    /// Compute the stride of the particles with the specified vertex and colour
    /// types.
    /// </summary>
    /// <typeparam name="T">The scalar type to express the stride in. This is
    /// usually <c>size_t</c> when working on the CPU or <c>UINT</c> when
    /// working with Direct3D.</typeparam>
    /// <param name="vertexType">The type of the positional data.</param>
    /// <param name="colourType">The type of the colour data.</param>
    /// <returns>The stide of the particles in bytes.</returns>
    template<class T> T get_stride(const vertex_type vertexType,
        const colour_type colourType) noexcept;

    /// <summary>
    /// Compute the stride of the particles in the list described by the given
    /// header.
    /// </summary>
    /// <typeparam name="T">The scalar type to express the stride in. This is
    /// usually <c>size_t</c> when working on the CPU or <c>UINT</c> when
    /// working with Direct3D.</typeparam>
    /// <param name="header">The list header to get the stride for.</param>
    /// <returns>The stide of the particles in bytes.</returns>
    template<class T> inline T get_stride(const list_header& header) noexcept {
        return get_stride<T>(header.vertex_type, header.colour_type);
    }

    /// <summary>
    /// Compute the size of the raw particle data in the list.
    /// </summary>
    /// <typeparam name="T">The scalar type to express the size in. This is
    /// usually <c>size_t</c> when working on the CPU or <c>UINT</c> when
    /// working with Direct3D.</typeparam>
    /// <param name="header">The list header to get the size for.</param>
    /// <returns>The total size of the particles in bytes.</returns>
    template<class T> inline T get_size(const list_header& header) noexcept {
        return static_cast<T>(header.particles) * get_stride<T>(header);
    }

    /// <summary>
    /// Answer whether the particle format of the given two lists is the same
    /// wrt. vertex format and colour format.
    /// </summary>
    /// <param name="lhs">A particle list header.</param>
    /// <param name="rhs">Another particle list header.</param>
    /// <returns><c>true</c> if <paramref name="lhs" /> and
    /// <paramref name="rhs" /> share the same particle format, <c>false</c>
    /// otherwise.</returns>
    inline bool is_same_format(const list_header& lhs,
            const list_header& rhs) noexcept {
        return ((lhs.vertex_type == rhs.vertex_type)
            && (lhs.colour_type == rhs.colour_type));
    }

    /// <summary>
    /// Reads an MMPLD list header from the current location in the stream.
    /// </summary>
    /// <typeparam name="T">The type of stream, which can be an STL stream or a
    /// file descriptor or <see cref="FILE" /> handle.</typeparam>
    /// <param name="stream">The stream to read the header from. The stream must
    /// be open and in binary mode.</param>
    /// <param name="fileVersion">The version of the MMPLD file, which is
    /// required to handle different formats of the list header.</param>
    /// <param name="header">Receives the header.</param>
    /// <returns><paramref name="stream" />.</returns>
    template<class T>
    T& read_list_header(T& stream, const std::uint16_t fileVersion,
        list_header& header);

    /// <summary>
    /// Advance the stream such that all particles of the given list are
    /// skipped.
    /// </summary>
    /// <remarks>
    /// <para>This function only requires the file pointer in
    /// <paramref name="stream" /> to point to the first particle of the list
    /// described by <paramref name="header" />. If this precondition is not
    /// met, the effect of the function is undefined.</para>
    /// <para>Please note that an <se cref="mmpld::cluster_info" /> block after
    /// the particles will <i>not</i> be skipped. The caller is responsible
    /// for handling this if the file version is 1.1.</para>
    /// </remarks>
    /// <typeparam name="T">The type of stream, which can be an STL stream or a
    /// file descriptor or <see cref="FILE" /> handle.</typeparam>
    /// <param name="stream">The stream to read the header from. The stream must
    /// be open and in binary mode.</param>
    /// <param name="header">The description of the list to be skipped.</param>
    /// <returns><paramref name="stream" />.</returns>
    template<class T>
    inline T& skip_particles(T& stream, const list_header& header) {
        detail::skip(stream, get_size<std::size_t>(header));
        return stream;
    }

    /// <summary>
    /// Writes and MMPLD list header to the current location in the stream.
    /// </summary>
    /// <typeparam name="T">The type of stream, which can be an STL stream or a
    /// file descriptor or <see cref="FILE" /> handle.</typeparam>
    /// <param name="header">The header to be written.</param>
    /// <param name="fileVersion">The MMPLD file version that is being written,
    /// which causes the header to being layouted differently in the file.
    /// </param>
    /// <param name="stream">The stream to write to.</param>
    /// <returns><paramref name="stream" />.</returns>
    template<class T>
    T& write_list_header(const list_header& header,
        const std::uint16_t fileVersion, T& stream);

} /* end namespace mmpld */

#include "mmpld/list_header.inl"
