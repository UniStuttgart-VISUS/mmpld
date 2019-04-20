/// <copyright file="vertex_properties.h" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2019 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>

#pragma once

#include <stdexcept>

#include "mmpld/vertex_type.h"


namespace mmpld {

    /// <summary>
    /// Combines run-time information that can be obtained for a
    /// <see cref="vertex_type" />.
    /// </summary>
    struct vertex_properties {

        /// <summary>
        /// Indicates whether the data contain per-vertex radius information.
        /// </summary>
        bool has_radius;

        /// <summary>
        /// The offset of the radius in bytes from the begin of the vertex data.
        /// </summary>
        std::size_t radius_offset;

        /// <summary>
        /// The overall size of the position component in bytes.
        /// </summary>
        std::size_t size;
    };

namespace detail {

    /// <summary>
    /// Tests all members of <see cref="colour_dispatch_list" /> for the
    /// given runtime type and fills <paramref name="properties" /> if the type
    /// was found.
    /// </summary>
    template<vertex_type V, vertex_type... Vs>
    bool get_properties(enum_dispatch_list<vertex_type, V, Vs...>,
            const vertex_type type, vertex_properties& properties) {
        if (type == V) {
            typedef vertex_traits<V> traits_type;
            properties.has_radius = (traits_type::radius_offset
                < traits_type::size);
            properties.radius_offset = traits_type::radius_offset;
            properties.size = traits_type::size;

            return (type != vertex_type::none);

        } else {
            return get_properties(enum_dispatch_list<vertex_type, Vs...> {},
                type, properties);
        }
    }

    /// <summary>
    /// Recursion stop for <see cref="get_properties" />.
    /// </summary>
    inline bool get_properties(enum_dispatch_list<vertex_type>,
            const vertex_type, vertex_properties&) {
        throw std::runtime_error("The properties of the given vertex_type "
            "could not be retrieved. Make sure that the vertex_type is valid "
            "and that all valid vertex types have been registered in the "
            "enum_dispatch_list.");
    }

} /* end namespace detail */

    /// <summary>
    /// Retrieves the properties of the given <see cref="vertex_type" />.
    /// </summary>
    /// <param name="type">The identifier for the position component to retrieve
    /// the properties for.</param>
    /// <param name="properties">The structure receiving the result.</param>
    /// <returns><c>true</c> if <paramref name="type" /> is not
    /// <see cref="vertex_type::none" />, <c>false</c> otherwise.</returns>
    inline bool get_properties(const vertex_type type,
            vertex_properties& properties) {
        return detail::get_properties(detail::vertex_dispatch_list {},
            type, properties);
    }

} /* end namespace mmpld */
