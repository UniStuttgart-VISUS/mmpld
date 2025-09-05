// <copyright file="colour_type.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2018 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * MMPLD_NAMESPACE::to_string
 */
template<class C>
std::basic_string<C> MMPLD_NAMESPACE::to_string(const colour_type value) {
#define __MMPLD_TO_STRING_CASE(v) case colour_type::v:\
    return MMPLD_TPL_LITERAL(C, #v);

    switch (value) {
        __MMPLD_TO_STRING_CASE(none);
        __MMPLD_TO_STRING_CASE(rgb8);
        __MMPLD_TO_STRING_CASE(rgba8);
        __MMPLD_TO_STRING_CASE(intensity);
        __MMPLD_TO_STRING_CASE(rgb32);
        __MMPLD_TO_STRING_CASE(rgba32);
        __MMPLD_TO_STRING_CASE(rgba16);
        __MMPLD_TO_STRING_CASE(intensity64);

        default:
            return MMPLD_TPL_LITERAL(C, "unknown");
    }

#undef __MMPLD_TO_STRING_CASE
}
