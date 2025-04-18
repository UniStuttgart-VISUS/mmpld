﻿// <copyright file="enum_dispatch_list.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2016 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <array>
#include <tuple>


namespace mmpld {
namespace detail {

    /// <summary>
    /// Template for dispatch lists which allow for defining lists of enum
    /// values.
    /// </summary>
    /// <remarks>
    /// The intended use of this class is the definition of a dispatch list type
    /// for an enumeration type <c>et</c> like this
    /// <c>template&lt;et... V&gt; using et_list_t
    /// = enum_dispatch_list&lt;et, V...&gt;;</c>
    /// </remarks>
    /// <typeparam name="E">The type of the enumeration.</typeparam>
    /// <typeparam name="Vs">The enumeration values.</typeparam>
    template<class E, E... Vs> struct enum_dispatch_list { };

    /// <summary>
    /// Creates an array for all enum values in the dispatch list.
    /// </summary>
    /// <typeparam name="E">The type of the enumeration.</typeparam>
    /// <typeparam name="Vs">The enumeration values.</typeparam>
    /// <returns>An array holding all <typeparamref name="Vs" />.</returns>
    template<class E, E... Vs>
    inline constexpr std::array<E, sizeof...(Vs)> make_dispatch_array(
            enum_dispatch_list<E, Vs...>) {
        return { Vs... };
    }

    /// <summary>
    /// Creates a tuple for all enum values in the dispatch list.
    /// </summary>
    /// <typeparam name="E">The type of the enumeration.</typeparam>
    /// <typeparam name="Vs">The enumeration values.</typeparam>
    /// <returns>A tuple holding all <typeparamref name="Vs" />.</returns>
    template<class E, E... Vs>
    inline constexpr auto make_dispatch_tuple(enum_dispatch_list<E, Vs...>)
            -> decltype(std::make_tuple(Vs...)) {
        return std::make_tuple(Vs...);
    }

} /* end namespace detail */
} /* end namespace mmpld */
