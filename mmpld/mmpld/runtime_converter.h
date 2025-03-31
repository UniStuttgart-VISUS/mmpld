// <copyright file="runtime_converter.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2018 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once


namespace mmpld {
namespace detail {

    /// <summary>
    /// Generic base class for converting positions and colours.
    /// </summary>
    /// <remarks>
    /// <para>This is the fallback that should never be used. There need to be
    /// valid specialisations for all possible conversions in order to make the
    /// runtime conversion table compile.</para>
    /// <para>The main reason for this class existing is that we need to be able
    /// to drop data, which then will have a target type of <c>void</c>. In
    /// order for this to be legal, there need to be template specialiations
    /// that are empty and do not cause instances of <c>void</c> to be created.
    /// </para>
    /// </remarks>
    /// <typeparam name="E">The type of the enumeration determining what
    /// conversion needs to be performed.</typeparam>
    /// <typeparam name="O">The output type to convert to.</typeparam>
    /// <typeparam name="I">The input type to convert from.</typeparam>
    template<class E, E O, E I> struct runtime_converter { };

} /* end namespace detail */
} /* end namespace mmpld */
