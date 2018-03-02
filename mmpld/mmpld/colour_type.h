/// <copyright file="colour_type.h" company="Visualisierungsinstitut der Universit�t Stuttgart">
/// Copyright � 2018 Visualisierungsinstitut der Universit�t Stuttgart. Alle Rechte vorbehalten.
/// Copyright � 2017 SFB-TRR 161. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph M�ller</author>

#pragma once

#include <cinttypes>


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

} /* end namespace mmpld */
