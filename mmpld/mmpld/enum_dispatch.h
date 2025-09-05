// <copyright file="enum_dispatch.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2019 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_MMPLD_ENUM_DISPATCH_H)
#define _MMPLD_ENUM_DISPATCH_H
#pragma once

#include "mmpld/enum_dispatch_list.h"


MMPLD_DETAIL_NAMESPACE_BEGIN

template<class F, class E, E V, E... Vs>
auto enum_dispatch(enum_dispatch_list<E, V, Vs...>, const E value,
        F&& callback) -> decltype(callback()) {
    if (value == V) {
        return callback();
    } else {
        return enum_dispatch(enum_dispatch_list<E, Vs...> { }, value,
            std::forward<F>(callback));
    }
}

template<class F, class E>
auto enum_dispatch(enum_dispatch_list<E>, const E, F&& callback)
        -> decltype(callback()) {
    throw "TODO";
}

//template<class E, E... V>
//bool enum_dispatch(enum_dispatch_list<E, Es...>, const E value) {
//    if (traits_type<E>::name() == str) {
//        return E;
//    } else {
//        return enum_parse_helper::parse(list_type<Es...>(), str);
//    }
//}

///// <summary>
///// Terminates the template recursion of <c>enum_dispatch</c>.
///// </summary>
//inline bool enum_dispatch(enum_dispatch_list<E>, const E value) {
//    throw std::invalid_argument("The given enumeration value was not "
//        "found. Make sure that all valid enumeration values are listed "
//        "in the dispatch list for the enumeration.");
//}

MMPLD_DETAIL_NAMESPACE_END

#endif /* !defined(_MMPLD_ENUM_DISPATCH_H) */
