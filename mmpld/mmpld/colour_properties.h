// <copyright file="colour_properties.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2019 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <stdexcept>

#include "mmpld/colour_type.h"


namespace mmpld {

    /// <summary>
    /// Combines run-time information that can be obtained for a
    /// <see cref="colour_type" />.
    /// </summary>
    struct colour_properties {

        /// <summary>
        /// The number of colour channels.
        /// </summary>
        std::size_t channels;

        /// <summary>
        /// Indicates whether the colour type uses floating point numbers or
        /// not.
        /// </summary>
        bool is_float;

        /// <summary>
        /// The overall size of the colour component in bytes.
        /// </summary>
        std::size_t size;
    };

namespace detail {

    /// <summary>
    /// Tests all members of <see cref="colour_dispatch_list" /> for the
    /// given runtime type and fills <paramref name="properties" /> if the type
    /// was found.
    /// </summary>
    template<colour_type C, colour_type... Cs>
    bool get_properties(enum_dispatch_list<colour_type, C, Cs...>,
            const colour_type type, colour_properties& properties) {
        if (type == C) {
            typedef colour_traits<C> traits_type;
            properties.channels = traits_type::channels;
            properties.is_float = std::is_floating_point<
                typename traits_type::value_type>::value;
            properties.size = traits_type::size;

            return (type != colour_type::none);

        } else {
            return get_properties(enum_dispatch_list<colour_type, Cs...> {},
                type, properties);
        }
    }

    /// <summary>
    /// Recursion stop for <see cref="get_properties" />.
    /// </summary>
    inline bool get_properties(enum_dispatch_list<colour_type>,
            const colour_type, colour_properties&) {
        throw std::runtime_error("The properties of the given colour_type "
            "could not be retrieved. Make sure that the colour_type is valid "
            "and that all valid colour types have been registered in the "
            "enum_dispatch_list.");
    }

} /* end namespace detail */

    /// <summary>
    /// Retrieves the properties of the given <see cref="colour_type" />.
    /// </summary>
    /// <param name="type">The identifier for the colour component to retrieve
    /// the properties for.</param>
    /// <param name="properties">The structure receiving the result.</param>
    /// <returns><c>true</c> if <paramref name="type" /> is not
    /// <see cref="colour_type::none" />, <c>false</c> otherwise.</returns>
    inline bool get_properties(const colour_type type,
            colour_properties& properties) {
        return detail::get_properties(detail::colour_dispatch_list {},
            type, properties);
    }

} /* end namespace mmpld */
