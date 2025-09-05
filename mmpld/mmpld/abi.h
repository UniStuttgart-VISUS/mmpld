// <copyright file="abi.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_MMPLD_ABI_H)
#define _MMPLD_ABI_H
#pragma once

#include <cinttypes>

#define MMPLD_ABI_MAJOR 1
#define MMPLD_ABI_MINOR 18
#define MMPLD_ABI_PATCH 0


#define __MMPLD_CONCAT(l, r) l ## r
#define _MMPLD_CONCAT(l, r) __MMPLD_CONCAT(l, r)


/// <summary>
/// Creates the full ABI versison string.
/// </summary>
/// <param name="mj">The major version of the ABI.</param>
/// <param name="mn">The minor version of the ABI.</param>
#define MMPLD_ABI_VERSION(mj, mn) _MMPLD_CONCAT(mj, _MMPLD_CONCAT(_, mn))


/// <summary>
/// Creates the name of the namespace for the specified ABI version.
/// </summary>
/// <param name="mj">The major version of the ABI.</param>
/// <param name="mn">The minor version of the ABI.</param>
#define MMPLD_ABI_NAMESPACE(mj, mn) _MMPLD_CONCAT(v, MMPLD_ABI_VERSION(mj, mn))


/// <summary>
/// Creates the name of the current ABI namespace.
/// </summary>
#define MMPLD_NAMESPACE mmpld::MMPLD_ABI_NAMESPACE(MMPLD_ABI_MAJOR,\
    MMPLD_ABI_MINOR)


/// <summary>
/// Marks the begin of the current ABI namespace.
/// </summary>
#define MMPLD_NAMESPACE_BEGIN namespace mmpld {\
    inline namespace MMPLD_ABI_NAMESPACE(MMPLD_ABI_MAJOR, MMPLD_ABI_MINOR) {


/// <summary>
/// Marks the end of the current ABI namespace.
/// </summary>
#define MMPLD_NAMESPACE_END } }


/// <summary>
/// Create the name of the current namespace for implementation details
/// </summary>
#define MMPLD_DETAIL_NAMESPACE MMPLD_NAMESPACE::detail


/// <summary>
/// Marks the begin of the current namespace for implementation details.
/// </summary>
#define MMPLD_DETAIL_NAMESPACE_BEGIN MMPLD_NAMESPACE_BEGIN\
    namespace detail {


/// <summary>
/// Marks the end of the current namespace for implementation details.
/// </summary>
#define MMPLD_DETAIL_NAMESPACE_END } MMPLD_NAMESPACE_END

#endif /* !defined(_MMPLD_ABI_H) */
