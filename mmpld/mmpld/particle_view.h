/// <copyright file="particle_traits.h" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2018 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>

#pragma once

#include <cassert>

#include "mmpld/colour_type.h"
#include "mmpld/vertex_type.h"


namespace mmpld {

    /// <summary>
    /// This structure allows for creating a view on particle data at comile
    /// time.
    /// </summary>
    template<vertex_type V, colour_type C> struct particle_view {

        /// <summary>
        /// The type and sizing information about the colour of the particle.
        /// </summary>
        typedef mmpld::colour_traits<C> colour_traits;

        /// <summary>
        /// The type of the colour components.
        /// </summary>
        typedef typename colour_traits::value_type colour_type;

        /// <summary>
        /// The type and sizing information about the position and size of the
        /// particle.
        /// </summary>
        typedef mmpld::vertex_traits<V> vertex_traits;

        /// <summary>
        /// The type of the position components.
        /// </summary>
        typedef typename vertex_traits::value_type vertex_type;

        /// <summary>
        /// Provide access to the first colour component if any.
        /// </summary>
        /// <param name="data">A pointer to the begin of a particle.</param>
        /// <returns>The first colour component or <c>nullptr</c>.</returns>
        static const colour_type *colour(const void *data) {
            auto c = (colour_traits::size > 0)
                ? static_cast<const std::uint8_t *>(data) + vertex_traits::size
                : nullptr;
            return reinterpret_cast<const colour_type *>(c);
        }

        /// <summary>
        /// Provide access to the first colour component if any.
        /// </summary>
        /// <param name="data">A pointer to the begin of a particle.</param>
        /// <returns>The first colour component or <c>nullptr</c>.</returns>
        static colour_type *colour(void *data) {
            auto c = (colour_traits::size > 0)
                ? static_cast<std::uint8_t *>(data) + vertex_traits::size
                : nullptr;
            return reinterpret_cast<colour_type *>(c);
        }

        /// <summary>
        /// Provide access to the first position component.
        /// </summary>
        /// <param name="data">A pointer to the begin of a particle.</param>
        /// <returns>The first position component.</returns>
        static const vertex_type *position(const void *data) {
            assert(vertex_traits::size > 0);
            return (vertex_traits::size > 0)
                ? static_cast<const vertex_type *>(data)
                : nullptr;
        }

        /// <summary>
        /// Provide access to the first position component.
        /// </summary>
        /// <param name="data">A pointer to the begin of a particle.</param>
        /// <returns>The first position component.</returns>
        static vertex_type *position(void *data) {
            assert(vertex_traits::size > 0);
            return (vertex_traits::size > 0)
                ? static_cast<vertex_type *>(data)
                : nullptr;
        }

        /// <summary>
        /// Provide access to the per-particle radius if any.
        /// </summary>
        /// <param name="data">A pointer to the begin of a particle.</param>
        /// <returns>The radius or <c>nullptr</c>.</returns>
        static const vertex_type *radius(const void *data) {
            auto cnt = vertex_traits::size / sizeof(vertex_type);
            return (cnt == 4)
                ? (static_cast<const vertex_type *>(data) + 3)
                : nullptr;
        }

        /// <summary>
        /// Provide access to the per-particle radius if any.
        /// </summary>
        /// <param name="data">A pointer to the begin of a particle.</param>
        /// <returns>The radius or <c>nullptr</c>.</returns>
        static vertex_type *radius(void *data) {
            auto cnt = vertex_traits::size / sizeof(vertex_type);
            return (cnt == 4)
                ? (static_cast<vertex_type *>(data) + 3)
                : nullptr;
        }

        /// <summary>
        /// Gets the particle stride.
        /// </summary>
        /// <returns>The particle stride in bytes.</returns>
        static const size_t stride(void) {
            return (vertex_traits::size + colour_traits::size);
        }
    };

} /* end namespace mmpld */
