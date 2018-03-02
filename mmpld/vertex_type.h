/// <copyright file="vertex_type.h" company="Visualisierungsinstitut der Universit�t Stuttgart">
/// Copyright � 2018 Visualisierungsinstitut der Universit�t Stuttgart. Alle Rechte vorbehalten.
/// Copyright � 2017 SFB-TRR 161. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph M�ller</author>

#pragma once

#include <cinttypes>


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
        /// Floating-point 3D position only.
        /// </summary>
        float_xyz = 1,

        /// <summary>
        /// 3D position and radius.
        /// </summary>
        float_xyzr = 2,

        /// <summary>
        /// 16-bit 3D position without radius.
        /// </summary>
        short_xyz = 3
    };

} /* end namespace mmpld */
