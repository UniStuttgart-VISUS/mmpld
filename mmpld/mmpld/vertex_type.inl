﻿// <copyright file="vertex_type.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2018 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * mmpld::to_string
 */
template<class C>
std::basic_string<C> mmpld::to_string(const vertex_type value) {
#define __MMPLD_TO_STRING_CASE(v) case mmpld::vertex_type::v:\
    return MMPLD_TPL_LITERAL(C, #v);

    switch (value) {
        __MMPLD_TO_STRING_CASE(none);
        __MMPLD_TO_STRING_CASE(float_xyz);
        __MMPLD_TO_STRING_CASE(float_xyzr);
        __MMPLD_TO_STRING_CASE(short_xyz);
        __MMPLD_TO_STRING_CASE(double_xyz);

        default:
            return MMPLD_TPL_LITERAL(C, "unknown");
    }

#undef __MMPLD_TO_STRING_CASE
}
