/// <copyright file="vertex_type.h" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2018 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
/// Copyright © 2017 SFB-TRR 161. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>

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

} /* end namespace mmpld */
