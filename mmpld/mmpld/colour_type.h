/// <copyright file="colour_type.h" company="Visualisierungsinstitut der Universität Stuttgart">
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

} /* end namespace mmpld */

#include "mmpld/colour_type.inl"
