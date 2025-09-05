// <copyright file="convert_colour.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2018 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_MMPLD_CONVERT_COLOUR_H)
#define _MMPLD_CONVERT_COLOUR_H
#pragma once

#include "mmpld/colour_properties.h"
#include "mmpld/list_header.h"
#include "mmpld/runtime_converter.h"


namespace mmpld {
namespace detail {

    /// <summary>
    /// Normalise the given intensity to the range of [0, 1].
    /// </summary>
    template<class T> inline T normalise_intensity(const T intensity,
            const float min_intensity, const float max_intensity) {
        const auto mi = static_cast<T>(min_intensity);
        const auto ma = static_cast<T>(max_intensity);
        return intensity / (ma - mi) + mi;
    }

    /// <summary>
    /// Normalise the given intensity to the range of [0, 1] if the total number
    /// of channels is one and the type is a floating-point number.
    /// </summary>
    template<class T> inline T normalise_intensity(const T intensity,
            const std::size_t cur_channel, const std::size_t cnt_channels,
            const float min_intensity, const float max_intensity) {
        if (std::is_floating_point<T>::value && (cnt_channels == 1)
                && valid_intensity_range(min_intensity, max_intensity)
                && (cur_channel < 3)) {
            return normalise_intensity(intensity, min_intensity, max_intensity);
        } else {
            return intensity;
        }
    }

    /// <summary>
    /// Convert <paramref name="colour" /> to a floating-point grey-scale value.
    /// </summary>
    template<class O, class I>
    O to_intensity(const I *colour, const size_t cnt) {
        typedef typename std::conditional<std::is_floating_point<O>::value,
            O, float>::type intermediate_type;
        intermediate_type retval = 0;

        switch (cnt) {
            case 0:
                // No source colour, return black.
                retval = 0.0f;
                break;

            case 1:
                // Source is already grey, just cast to intermediate type. We
                // do not scale the range (from [min_intensity, max_intensity]
                // to [0, 1]) here, because we are converting between floats
                // and the target header has already copied the correct range.
                retval = static_cast<intermediate_type>(*colour);
                break;

            case 3:
            case 4:
                // Source is colour.
                retval = static_cast<intermediate_type>(0.21)
                    * static_cast<intermediate_type>(colour[0])
                    + static_cast<intermediate_type>(0.72)
                    * static_cast<intermediate_type>(colour[1])
                    + static_cast<intermediate_type>(0.07f)
                    * static_cast<intermediate_type>(colour[2]);
                break;

            default:
                throw std::logic_error("More than four colour channels are "
                    "not supported.");
        }

        if (!std::is_floating_point<O>::value) {
            // We compute the grey-scale data as float as the formula requires
            // us to do so. However, if the requested output is not a
            // floating-point type, we need to scale it to the maximum valid
            // value to prevent everything from becoming black.
            retval *= static_cast<float>((std::numeric_limits<O>::max)());
        }

        return static_cast<O>(retval);
    }

    /// <summary>
    /// Perform a colour conversion.
    /// </summary>
    template<class O, class I>
    typename std::enable_if<!std::is_void<O>::value>::type convert_colour(
            const I *input, const size_t cnt_in,
            void *output, const size_t cnt_out,
            const float min_intensity, const float max_intensity) {
        if (cnt_out == 0) {
            // Nothing to do.

        } else if (cnt_out == 1) {
            // Convert output to grey-scale.
            *static_cast<O *>(output) = to_intensity<O>(input, cnt_in);

        } else {
            // Create or convert colour.
            constexpr auto float_in = std::is_floating_point<I>::value;
            constexpr auto float_out = std::is_floating_point<O>::value;
            constexpr auto float_to_int = float_in && !float_out;
            constexpr auto int_to_float = !float_in && float_out;

            for (size_t i = 0; i < cnt_out; ++i) {
                if (float_to_int) {
                    // Input is floating point, but output is not: Scale values
                    // to maximum of output type.
                    auto w = static_cast<I>(1);
                    auto b = static_cast<I>(0);
                    // Determine the fallback colour 'f': For alpha (i == 3),
                    // use white 'w', otherwise splat the grey value 'g', which
                    // is black if we have no grey value from the input.
                    auto g = (cnt_in == 1) ? input[0] : b;
                    auto f = (i == 3) ? w : g;
                    auto c = (i < cnt_in) ? input[i] : f;
                    c = normalise_intensity(c, i, cnt_in, min_intensity,
                        max_intensity);
                    c *= static_cast<I>((std::numeric_limits<O>::max)());
                    static_cast<O *>(output)[i] = static_cast<O>(c);

                } else if (int_to_float) {
                    // Input is no floating point, but output is: Scale values
                    // to maximum of input type.
                    auto w = static_cast<O>((std::numeric_limits<I>::max)());
                    auto b = static_cast<O>(0);
                    // Determine the fallback colour: For alpha (i == 3), use
                    // white, otherwise splat the grey value or use black.
                    auto g = (cnt_in == 1) ? static_cast<O>(input[0]) : b;
                    auto f = (i == 3) ? w : g;
                    auto c = (i < cnt_in) ? static_cast<O>(input[i]) : f;
                    // No intensity scaling here, because intensities are all
                    // float and therefore this code path cannot be reached for
                    // this kind of data.
                    c /= w;
                    static_cast<O *>(output)[i] = c;

                } else {
                    // Input and output are of the same type (integral or
                    // floating point): Just cast it.
                    auto w = float_out
                        ? static_cast<O>(1)
                        : (std::numeric_limits<O>::max)();
                    auto b = static_cast<O>(0);
                    // Determine the fallback colour: For alpha (i == 3), use
                    // white, otherwise splat the grey value or use black.
                    auto g = (cnt_in == 1) ? static_cast<O>(input[0]) : b;
                    auto f = (i == 3) ? w : g;
                    auto c = (i < cnt_in) ? static_cast<O>(input[i]) : f;
                    c = normalise_intensity(c, i, cnt_in, min_intensity,
                        max_intensity);
                    static_cast<O *>(output)[i] = c;
                }
            } /* end for (size_t i = 0; i < cnt_out; ++i) */
        } /* end if (cnt_out == 0) */
    }

    /// <summary>
    /// Convert nothing if the output type is invalid (<c>void</c>).
    /// </summary>
    template<class O, class I>
    typename std::enable_if<std::is_void<O>::value>::type convert_colour(
        const I *, const size_t,
        void *, const size_t,
        const float, const float) { }

    /// <summary>
    /// Specialised conversion for colours, which redirects the conversion to
    /// <see cref="convert_colour" />.
    /// </summary>
    template<colour_type O, colour_type I>
    struct runtime_converter<colour_type, O, I> {
        typedef colour_traits<O> output_traits;
        typedef colour_traits<I> input_traits;

        static inline void convert(const void *src, void *dst,
                const float min_intensity, const float max_intensity) {
            auto s = static_cast<const typename input_traits::value_type *>(src);
            convert_colour<typename output_traits::value_type>(
                s, input_traits::channels,
                dst, output_traits::channels,
                min_intensity, max_intensity);
        }
    };

    /// <summary>
    /// Further specialisation for conversion of no colour.
    /// </summary>
    template<> struct runtime_converter<colour_type, colour_type::none,
            colour_type::none> {
        static inline void convert(const void *, void *,
            const float, const float) { }
    };

    /// <summary>
    /// Further specialisation generating a medium grey for missing colour
    /// input.
    /// </summary>
    template<colour_type O>
    struct runtime_converter<colour_type, O, colour_type::none> {
        typedef colour_traits<O> output_traits;

        static inline void convert(const void *, void *dst, const float,
                const float) {
            static constexpr std::array<std::uint8_t, 4> GREY {
                128, 128, 128, 255
            };
            convert_colour<typename output_traits::value_type>(GREY.data(),
                GREY.size(), dst, output_traits::channels, 0.0f, 0.0f);
        }
    };

} /* end namespace detail */
} /* end namespace mmpld */

#endif /* !defined(_MMPLD_CONVERT_COLOUR_H) */
