/// <copyright file="vertex_type.h" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2018 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
/// Copyright © 2017 SFB-TRR 161. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>
#include <string>

#include "mmpld/literal.h"


namespace mmpld {

    /// <summary>
    /// The type of the per-vertex data stored in an MMPLD file
    /// </summary>
    enum class vertex_type : std::uint8_t {

        /// <summary>
        /// No positions are available on a per-vertex base.
        /// </summary>
        none = 0,

        /// <summary>
        /// 3D position.
        /// </summary>
        float_xyz = 1,

        /// <summary>
        /// 3D position and radius.
        /// </summary>
        float_xyzr = 2,

        /// <summary>
        /// 16-bit 3D position.
        /// </summary>
        short_xyz = 3
    };

    /// <summary>
    /// Convert the given vertex format to a human-readable representation.
    /// </summary>
    /// <tparam name="C>The character type of the string to create.</tparam>
    /// <param name="value">The value to be converted.</param>
    /// <returns>A string representation of <paramref name="value" />.</returns>
    template<class C> std::basic_string<C> to_string(const vertex_type value);

    /// <summary>
    /// The vertex traits allow for compile-time reflection on the vertex type.
    /// </summary>
    /// <tparam name="C">The <see cref="vertex_type" /> to be reflected.
    /// </tparam>
    template<vertex_type V> struct vertex_traits { };

    /// <summary>
    /// Specialisation for <see cref="vertex_type::none" />.
    /// </summary>
    template<> struct vertex_traits<vertex_type::none> {
        /// <summary>
        /// The type of a single  component.
        /// </summary>
        typedef void value_type;

        /// <summary>
        /// The enumeration value being reflected.
        /// </summary>
        static const mmpld::vertex_type vertex_type = mmpld::vertex_type::none;

        /// <summary>
        /// The total size of the whole positional parameters in bytes.
        /// </summary>
        static const size_t size = 0;
    };

    /// <summary>
    /// Specialisation for <see cref="vertex_type::float_xyz" />.
    /// </summary>
    template<> struct vertex_traits<vertex_type::float_xyz> {
        /// <summary>
        /// The type of a single  component.
        /// </summary>
        typedef float value_type;

        /// <summary>
        /// The enumeration value being reflected.
        /// </summary>
        static const mmpld::vertex_type vertex_type
            = mmpld::vertex_type::float_xyz;

        /// <summary>
        /// The total size of the whole positional parameters in bytes.
        /// </summary>
        static const size_t size = 3 * sizeof(value_type);
    };

    /// <summary>
    /// Specialisation for <see cref="vertex_type::float_xyzr" />.
    /// </summary>
    template<> struct vertex_traits<vertex_type::float_xyzr> {
        /// <summary>
        /// The type of a single  component.
        /// </summary>
        typedef float value_type;

        /// <summary>
        /// The enumeration value being reflected.
        /// </summary>
        static const mmpld::vertex_type vertex_type
            = mmpld::vertex_type::float_xyzr;

        /// <summary>
        /// The total size of the whole positional parameters in bytes.
        /// </summary>
        static const size_t size = 4 * sizeof(value_type);
    };

    /// <summary>
    /// Specialisation for <see cref="vertex_type::short_xyz" />.
    /// </summary>
    template<> struct vertex_traits<vertex_type::short_xyz> {
        /// <summary>
        /// The type of a single  component.
        /// </summary>
        typedef std::int16_t value_type;

        /// <summary>
        /// The enumeration value being reflected.
        /// </summary>
        static const mmpld::vertex_type vertex_type
            = mmpld::vertex_type::short_xyz;

        /// <summary>
        /// The total size of the whole positional parameters in bytes.
        /// </summary>
        static const size_t size = 3 * sizeof(value_type);
    };

} /* end namespace mmpld */

#include "mmpld/vertex_type.inl"
