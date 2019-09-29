/// <copyright file="enum_dispatch_list.h" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2018 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
/// Copyright © 2016 - 2018 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>

#pragma once


namespace mmpld {
namespace detail {

    /// <summary>
    /// Template for dispatch lists which allow for defining lists of enum
    /// values.
    /// </summary>
    /// <remarks>
    /// The intended use of this class is the definition of a dispatch list type
    /// for an enumeration type <c>et</c> like this
    /// <c>template<et... V> using et_list_t = enum_dispatch_list<et, V...>;</c>
    /// </remarks>
    /// <typeparam name="E">The type of the enumeration.</typeparam>
    /// <typeparam name="V">The enumeration values.</typeparam>
    template<class E, E... V> struct enum_dispatch_list { };

} /* end namespace detail */
} /* end namespace mmpld */
