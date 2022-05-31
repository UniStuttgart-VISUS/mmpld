// <copyright file="colour_type.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2018 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>


/*
 * mmpld::to_string
 */
template<class C>
std::basic_string<C> mmpld::to_string(const colour_type value) {
#define __MMPLD_TO_STRING_CASE(v) case mmpld::colour_type::v:\
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

