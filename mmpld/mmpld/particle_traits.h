// <copyright file="particle_traits.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2018 -2022 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cassert>
#include <memory>

#include "mmpld/list_header.h"

namespace mmpld {

    /// <summary>
    /// This structure allows for creating a view on particle data at compile
    /// time.
    /// </summary>
    /// <remarks>
    /// <para>The particle traits are mostly used if an application needs to
    /// impose a specific view on the data which might require conversion.
    /// </para>
    /// <para><see cref="mmpld::particle_view" /> is the runtime equivalent of
    /// this structure.</para>
    /// <para>Be aware that all pointer-based operations are unchecked!</para>
    /// </remarks>
    /// <typeparam name="V">The type of the positional data.</typeparam>
    /// <typeparam name="C">The type of the colour data.</typeparam>
    template<vertex_type V, colour_type C> struct particle_traits {

        /// <summary>
        /// The type and sizing information about the colour of the particle.
        /// </summary>
        typedef mmpld::colour_traits<C> colour_traits;

        /// <summary>
        /// The type of the colour components.
        /// </summary>
        typedef typename colour_traits::value_type colour_value_type;

        /// <summary>
        /// The type and sizing information about the position and size of the
        /// particle.
        /// </summary>
        typedef mmpld::vertex_traits<V> vertex_traits;

        /// <summary>
        /// The type of the position components.
        /// </summary>
        typedef typename vertex_traits::value_type vertex_value_type;

        /// <summary>
        /// Advances the given pointer by the stride of one particle.
        /// </summary>
        /// <param name="data">The pointer to be advanced.</param>
        /// <returns>The advanced pointer.</returns>
        static inline const void *advance(const void *data) noexcept {
            auto retval = static_cast<const std::uint8_t *>(data);
            retval += particle_traits::stride();
            return static_cast<void *>(retval);
        }

        /// <summary>
        /// Zero the memory of one particle starting at
        /// <paramref name="data" />.
        /// </summary>
        /// <param name="data">The pointer to the particle.</param>
        static inline void clear(void *data) noexcept {
            ::memset(data, 0, particle_traits::stride());
        }

        /// <summary>
        /// Provide access to the first colour component if any.
        /// </summary>
        /// <param name="data">A pointer to the begin of a particle.</param>
        /// <returns>The first colour component or <c>nullptr</c>.</returns>
        static inline const colour_value_type *colour(
                const void *data) noexcept {
            auto c = (colour_traits::size > 0)
                ? static_cast<const std::uint8_t *>(data) + vertex_traits::size
                : nullptr;
            return reinterpret_cast<const colour_value_type *>(c);
        }

        /// <summary>
        /// Provide access to the first colour component if any.
        /// </summary>
        /// <param name="data">A pointer to the begin of a particle.</param>
        /// <returns>The first colour component or <c>nullptr</c>.</returns>
        static inline colour_value_type *colour(void *data) noexcept {
            auto c = (colour_traits::size > 0)
                ? static_cast<std::uint8_t *>(data) + vertex_traits::size
                : nullptr;
            return reinterpret_cast<colour_value_type *>(c);
        }

        /// <summary>
        /// Answer the type of the colour data.
        /// </summary>
        /// <returns>The type of the colour data.</returns>
        static inline mmpld::colour_type colour_type(void) noexcept {
            return particle_traits::colour_traits::colour_type;
        }

        /// <summary>
        /// Provide access to the first position component.
        /// </summary>
        /// <param name="data">A pointer to the begin of a particle.</param>
        /// <returns>The first position component.</returns>
        static inline const vertex_value_type *position(
                const void *data) noexcept {
            assert(vertex_traits::size > 0);
            return (vertex_traits::size > 0)
                ? static_cast<const vertex_value_type *>(data)
                : nullptr;
        }

        /// <summary>
        /// Provide access to the first position component.
        /// </summary>
        /// <param name="data">A pointer to the begin of a particle.</param>
        /// <returns>The first position component.</returns>
        static inline vertex_value_type *position(void *data) noexcept {
            assert(vertex_traits::size > 0);
            return (vertex_traits::size > 0)
                ? static_cast<vertex_value_type *>(data)
                : nullptr;
        }

        /// <summary>
        /// Answer the type of the vertex data.
        /// </summary>
        /// <returns>The type of the vertex data.</returns>
        static inline mmpld::vertex_type position_type(void) noexcept {
            return particle_traits::vertex_type();
        }

        /// <summary>
        /// Provide access to the per-particle radius if any.
        /// </summary>
        /// <param name="data">A pointer to the begin of a particle.</param>
        /// <returns>The radius or <c>nullptr</c>.</returns>
        static inline  const vertex_value_type *radius(const void *data) {
            auto cnt = vertex_traits::size / sizeof(vertex_value_type);
            return (cnt == 4)
                ? (static_cast<const vertex_value_type *>(data) + 3)
                : nullptr;
        }

        /// <summary>
        /// Provide access to the per-particle radius if any.
        /// </summary>
        /// <param name="data">A pointer to the begin of a particle.</param>
        /// <returns>The radius or <c>nullptr</c>.</returns>
        static inline vertex_value_type *radius(void *data) {
            auto cnt = vertex_traits::size / sizeof(vertex_value_type);
            return (cnt == 4)
                ? (static_cast<vertex_value_type *>(data) + 3)
                : nullptr;
        }

        /// <summary>
        /// Answer the size in bytes of <paramref name="cnt" /> particles of
        /// this type.
        /// </summary>
        /// <param name="cnt">The number of particles to compute the size for.
        /// </param>
        /// <returns>The size of <paramref name="cnt" /> particles.</returns>
        static inline std::size_t size(
                const decltype(list_header::particles) cnt) noexcept {
            return cnt * particle_traits::stride();
        }

        /// <summary>
        /// Gets the particle stride.
        /// </summary>
        /// <returns>The particle stride in bytes.</returns>
        static inline std::size_t stride(void) noexcept {
            return (vertex_traits::size + colour_traits::size);
        }

        /// <summary>
        /// Answer the type of the vertex data.
        /// </summary>
        /// <returns>The type of the vertex data.</returns>
        static inline mmpld::vertex_type vertex_type(void) noexcept {
            return particle_traits::vertex_traits::value;
        }
    };


    /// <summary>
    /// Answer whether two <see cref="particle_traits" /> describe the same
    /// particle format wrt. vertex type and colour type.
    /// </summary>
    /// <typeparam name="S">An instance of <see cref="particle_traits" />.
    /// </typeparam>
    /// <typeparam name="T">Another instance of <see cref="particle_traits" />.
    /// </typeparam>
    /// <returns><c>true</c> if <typeparamref name="S" /> and
    /// <typeparamref name="T" /> describe the same particle format,
    /// <c>false</c> otherwise.</returns>
    template<class S, class T>
    inline constexpr bool is_same_format(void) noexcept {
        typedef typename S::colour_traits cl_t;
        typedef typename T::colour_traits cr_t;
        typedef typename S::vertex_traits vl_t;
        typedef typename T::vertex_traits vr_t;
        return ((vl_t::value == vr_t::value) && (cl_t::value == cr_t::value));
    }

    /// <summary>
    /// Answer whether a <see cref="particle_traits" /> describes the particle
    /// format of a <see cref="list_header" />.
    /// </summary>
    /// <typeparam name="T">An instance of <see cref="particle_traits" />.
    /// </typeparam>
    /// <param name="header">The description of the particle list to be
    /// compared.</param>
    /// <returns><c>true</c> if <typeparamref name="T" /> describes the particle
    /// format of <paramref name="header" />, <c>false</c> otherwise.</returns>
    template<class T>
    inline bool is_same_format(const list_header& header) noexcept {
        typedef typename T::colour_traits c_t;
        typedef typename T::vertex_traits v_t;
        return ((v_t::value == header.vertex_type)
            && (c_t::value == header.colour_type));
    }

} /* end namespace mmpld */
