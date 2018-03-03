/// <copyright file="particle_properties.h" company="Visualisierungsinstitut der Universit�t Stuttgart">
/// Copyright � 2018 Visualisierungsinstitut der Universit�t Stuttgart. Alle Rechte vorbehalten.
/// Copyright � 2017 SFB-TRR 161. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph M�ller</author>

#pragma once

#include <cstdint>
#include <type_traits>


namespace mmpld {

    /// <summary>
    /// A bitmask which allows for identifying certain properties of a particle
    /// data set.
    /// </summary>
    enum class particle_properties : std::uint32_t {
        /// <summary>
        /// There is a global colour and radius for all particles. The particle
        /// itself has no information except for its position.
        /// </summary>
        none = 0,

        /// <summary>
        /// There is a separate colour for each particle.
        /// </summary>
        per_particle_colour = 0x00000001,

        /// <summary>
        /// There is a separate radius for each particle.
        /// </summary>
        per_particle_radius = 0x00000002,

        /// <summary>
        /// There is a separate intensity value per particle which needs to be
        /// transformed using a transfer function.
        /// </summary>
        per_particle_intensity = 0x00000004,

        /// <summary>
        /// The colours are in a floating point format.
        /// </summary>
        /// <remarks>
        /// This flag can only be set if
        /// <see cref="particle_properties::per_particle_colour" /> is also set.
        /// </remarks>
        float_colour = 0x00000008
    };

    /// <summary>
    /// Allows for combining two <see cref="particle_properties" />.
    /// </summary>
    inline particle_properties operator |(const particle_properties lhs,
            const particle_properties rhs) {
        typedef std::underlying_type<particle_properties>::type type;
        return static_cast<particle_properties>(
            static_cast<type>(lhs) | static_cast<type>(rhs));
    }

    /// <summary>
    /// Allows for combining two <see cref="particle_properties" />.
    /// </summary>
    inline particle_properties& operator |=(particle_properties& lhs,
            const particle_properties rhs) {
        lhs = lhs | rhs;
        return lhs;
    }

    /// <summary>
    /// Allows for testing two <see cref="particle_properties" />.
    /// </summary>
    inline particle_properties operator &(const particle_properties lhs,
            const particle_properties rhs) {
        typedef std::underlying_type<particle_properties>::type type;
        return static_cast<particle_properties>(
            static_cast<type>(lhs) & static_cast<type>(rhs));
    }

    /// <summary>
    /// Allows for testing two <see cref="particle_properties" />.
    /// </summary>
    inline particle_properties& operator &=(particle_properties& lhs,
            const particle_properties rhs) {
        lhs = lhs & rhs;
        return lhs;
    }
}
