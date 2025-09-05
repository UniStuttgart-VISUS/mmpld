// <copyright file="literal.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2017 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_MMPLD_LITERAL_H)
#define _MMPLD_LITERAL_H
#pragma once

#include "mmpld/abi.h"

MMPLD_DETAIL_NAMESPACE_BEGIN

template<class T> struct literal_selector {
    typedef T char_type;
};

template<> struct literal_selector<char> {
    typedef char char_type;
    static inline constexpr const char_type select(const char n,
            const wchar_t) noexcept {
        return n;
    }
    static inline constexpr const char_type *select(const char *n,
            const wchar_t *) noexcept {
        return n;
    }
};

template<> struct literal_selector<wchar_t> {
    typedef wchar_t char_type;
    static inline constexpr const char_type select(const char,
            const wchar_t w) noexcept {
        return w;
    }
    static inline constexpr const char_type *select(const char *,
            const wchar_t *w) noexcept {
        return w;
    }
};

MMPLD_DETAIL_NAMESPACE_END

#define MMPLD_TPL_LITERAL(T, l)\
    MMPLD_DETAIL_NAMESPACE::literal_selector<T>::select(l, L##l)

#endif /* !defined(_MMPLD_LITERAL_H) */
