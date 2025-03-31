// <copyright file="convert_position.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2018 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "mmpld/runtime_converter.h"
#include "mmpld/vertex_properties.h"


namespace mmpld {
namespace detail {

    /// <summary>
    /// Perform a radius conversion in cases where, both, input and output have
    /// an radius specified according to their type.
    /// </summary>
    template<class O, class I>
    typename std::enable_if<!std::is_void<I>::value
        && !std::is_void<O>::value>::type
    convert_radius(const I *input, const float global_radius, O *output) {
        if (output != nullptr) {
            if (input == nullptr) {
                // We have no valid offset for the source radius, so we
                // need to copy the global radius to each particle.
                *output = static_cast<O>(global_radius);
            } else {
                // We know that all radii are float, so we can just cast.
                *output = static_cast<O>(*input);
            }
        }
    }

    /// <summary>
    /// Apply the global radius in lack of a per-vertex input.
    /// </summary>
    template<class O>
    typename std::enable_if<!std::is_void<O>::value>::type
    convert_radius(const void *input, const float global_radius, O *output) {
        if (output != nullptr) {
            // As we have no input, we must use the global radius.
            *output = static_cast<O>(global_radius);
        }
    }

    /// <summary>
    /// Do nothing if no radius is requested in output.
    /// </summary>
    template<class I>
    inline void convert_radius(const I *input, const float global_radius,
            void *output) {
        // As we have no output, there is nothing to do.
    }

    /// <summary>
    /// Specialised conversion for positions, which just casts the individual
    /// components.
    /// </summary>
    template<vertex_type O, vertex_type I>
    struct runtime_converter<vertex_type, O, I> {
        typedef vertex_traits<O> output_traits;
        typedef vertex_traits<I> input_traits;

        static inline void convert(const void *src, void *dst) {
            auto d = static_cast<typename output_traits::value_type *>(dst);
            auto s = static_cast<const typename input_traits::value_type *>(src);
            d[0] = static_cast<typename output_traits::value_type>(s[0]);
            d[1] = static_cast<typename output_traits::value_type>(s[1]);
            d[2] = static_cast<typename output_traits::value_type>(s[2]);
        }
    };

    /// <summary>
    /// Further specialisation for conversion of no position.
    /// </summary>
    template<> struct runtime_converter<vertex_type, vertex_type::none,
            vertex_type::none> {
        static inline void convert(const void *src, void *dst) { }
    };

    /// <summary>
    /// Further specialisation for discarding the position.
    /// </summary>
    template<vertex_type I>
    struct runtime_converter<vertex_type, vertex_type::none, I> {
        static inline void convert(const void *src, void *dst) { }
    };

    /// <summary>
    /// Further specialisation generating the origin for missing position input.
    /// </summary>
    template<vertex_type O>
    struct runtime_converter<vertex_type, O, vertex_type::none> {
        typedef vertex_traits<O> output_traits;

        static inline void convert(const void *src, void *dst) {
            auto d = static_cast<typename output_traits::value_type *>(dst);
            d[0] = static_cast<typename output_traits::value_type>(0);
            d[1] = static_cast<typename output_traits::value_type>(0);
            d[2] = static_cast<typename output_traits::value_type>(0);
        }
    };

} /* end namespace detail */
} /* end namespace mmpld */
