/// <copyright file="colour_type.h" company="Visualisierungsinstitut der Universit�t Stuttgart">
/// Copyright � 2018 Visualisierungsinstitut der Universit�t Stuttgart. Alle Rechte vorbehalten.
/// Copyright � 2017 SFB-TRR 161. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph M�ller</author>

#pragma once

#include <cinttypes>
#include <string>

#include "mmpld/literal.h"


namespace mmpld {

    /// <summary>
    /// The type of the colour data stored in an MMPLD file.
    /// </summary>
    enum class colour_type : std::uint8_t {

        /// <summary>
        /// No colour information is associated with a vertex.
        /// </summary>
        none = 0,

        /// <summary>
        /// Colour in three 8-bit channels.
        /// </summary>
        rgb8 = 1,

        /// <summary>
        /// Colour in four 8-bit channels.
        /// </summary>
        rgba8 = 2,

        /// <summary>
        /// A single floating-point intensity value.
        /// </summary>
        intensity = 3,

        /// <summary>
        /// Colour in three 32-bit channels.
        /// </summary>
        rgb32 = 4,

        /// <summary>
        /// Colour in four 32-bit channels.
        /// </summary>
        rgba32 = 5
    };

    /// <summary>
    /// Convert the given colour type to a human-readable representation.
    /// </summary>
    /// <tparam name="C>The character type of the string to create.</tparam>
    /// <param name="value">The value to be converted.</param>
    /// <returns>A string representation of <paramref name="value" />.</returns>
    template<class C> std::basic_string<C> to_string(const colour_type value);

    /// <summary>
    /// The colour traits allow for compile-time reflection on the colour type.
    /// </summary>
    /// <tparam name="C">The <see cref="colour_type" /> to be reflected.
    /// </tparam>
    template<colour_type C> struct colour_traits { };

    /// <summary>
    /// Specialisation for <see cref="colour_type::none" />.
    /// </summary>
    template<> struct colour_traits<colour_type::none> {
        /// <summary>
        /// The type of a single colour component.
        /// </summary>
        typedef void value_type;

        /// <summary>
        /// The number of colour channels.
        /// </summary>
        static const size_t channels = 0;

        /// <summary>
        /// The enumeration value being reflected.
        /// </summary>
        static const mmpld::colour_type colour_type = mmpld::colour_type::none;

        /// <summary>
        /// The total size of the colour components in bytes.
        /// </summary>
        static const size_t size = 0;
    };

    /// <summary>
    /// Specialisation for <see cref="colour_type::rgb8" />.
    /// </summary>
    template<> struct colour_traits<colour_type::rgb8> {
        /// <summary>
        /// The type of a single colour component.
        /// </summary>
        typedef std::uint8_t value_type;

        /// <summary>
        /// The number of colour channels.
        /// </summary>
        static const size_t channels = 3;

        /// <summary>
        /// The enumeration value being reflected.
        /// </summary>
        static const mmpld::colour_type colour_type = mmpld::colour_type::rgb8;

        /// <summary>
        /// The total size of the colour components in bytes.
        /// </summary>
        static const size_t size = channels * sizeof(value_type);
    };

    /// <summary>
    /// Specialisation for <see cref="colour_type::rgba8" />.
    /// </summary>
    template<> struct colour_traits<colour_type::rgba8> {
        /// <summary>
        /// The type of a single colour component.
        /// </summary>
        typedef std::uint8_t value_type;

        /// <summary>
        /// The number of colour channels.
        /// </summary>
        static const size_t channels = 4;

        /// <summary>
        /// The enumeration value being reflected.
        /// </summary>
        static const mmpld::colour_type colour_type = mmpld::colour_type::rgba8;

        /// <summary>
        /// The total size of the colour components in bytes.
        /// </summary>
        static const size_t size = channels * sizeof(value_type);
    };

    /// <summary>
    /// Specialisation for <see cref="colour_type::intensity" />.
    /// </summary>
    template<> struct colour_traits<colour_type::intensity> {
        /// <summary>
        /// The type of a single colour component.
        /// </summary>
        typedef float value_type;

        /// <summary>
        /// The number of colour channels.
        /// </summary>
        static const size_t channels = 1;

        /// <summary>
        /// The enumeration value being reflected.
        /// </summary>
        static const mmpld::colour_type colour_type
            = mmpld::colour_type::intensity;

        /// <summary>
        /// The total size of the colour components in bytes.
        /// </summary>
        static const size_t size = channels * sizeof(value_type);
    };

    /// <summary>
    /// Specialisation for <see cref="colour_type::rgb32" />.
    /// </summary>
    template<> struct colour_traits<colour_type::rgb32> {
        /// <summary>
        /// The type of a single colour component.
        /// </summary>
        typedef float value_type;

        /// <summary>
        /// The number of colour channels.
        /// </summary>
        static const size_t channels = 3;

        /// <summary>
        /// The enumeration value being reflected.
        /// </summary>
        static const mmpld::colour_type colour_type
            = mmpld::colour_type::rgb32;

        /// <summary>
        /// The total size of the colour components in bytes.
        /// </summary>
        static const size_t size = channels * sizeof(value_type);
    };

    /// <summary>
    /// Specialisation for <see cref="colour_type::rgba32" />.
    /// </summary>
    template<> struct colour_traits<colour_type::rgba32> {
        /// <summary>
        /// The type of a single colour component.
        /// </summary>
        typedef float value_type;

        /// <summary>
        /// The number of colour channels.
        /// </summary>
        static const size_t channels = 4;

        /// <summary>
        /// The enumeration value being reflected.
        /// </summary>
        static const mmpld::colour_type colour_type
            = mmpld::colour_type::rgba32;

        /// <summary>
        /// The total size of the colour components in bytes.
        /// </summary>
        static const size_t size = channels * sizeof(value_type);
    };

} /* end namespace mmpld */

#include "mmpld/colour_type.inl"
