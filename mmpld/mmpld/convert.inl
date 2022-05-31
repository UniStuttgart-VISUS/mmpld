// <copyright file="convert.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2018 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>


namespace mmpld {
namespace detail {

    /// <summary>
    /// If <paramref name="offset" /> is not <paramref name="invalid" />, return
    /// a pointer <paramref name="offset" /> bytes after
    /// <paramref name="base" />.
    /// </summary>
    template<class P, class O> inline const void *apply_offset(const P *base,
            const O offset, const O invalid) {
        auto retval = (offset != invalid) ? base + offset : nullptr;
        return static_cast<const void *>(retval);
    }

    /// <summary>
    /// Convert <paramref name="colour" /> to grey-scale.
    /// </summary>
    template<class O, class I> O to_grey(const I *colour, const size_t cnt) {
        typedef typename std::conditional<std::is_floating_point<O>::value,
            O, float>::type intermediate_type;
        intermediate_type retval = 0;

        switch (cnt) {
            case 0:
                // No source colour, return black.
                retval = 0.0f;
                break;

            case 1:
                // Source is already grey.
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
            const I *input, const size_t cnt_in, void *output,
            const size_t cnt_out) {
        if (cnt_out == 0) {
            // Nothing to do.

        } else if (cnt_out == 1) {
            // Convert output to grey-scale.
            *static_cast<O *>(output) = to_grey<O>(input, cnt_in);

        } else {
            // Create or convert colour.
            constexpr const auto float_in = std::is_floating_point<I>::value;
            constexpr const auto float_out = std::is_floating_point<O>::value;

            for (size_t i = 0; i < cnt_out; ++i) {
                if (float_in && !float_out) {
                    // Input is floating point, but output is not: Scale values
                    // to maximum of output type.
                    auto w = static_cast<I>(1);
                    auto b = static_cast<I>(0);
                    auto f = (i == 3) ? w : b;  // Alpha fallback 1, other 0.
                    auto c = (i < cnt_in) ? input[i] : f;
                    c *= static_cast<I>((std::numeric_limits<O>::max)());
                    static_cast<O *>(output)[i] = static_cast<O>(c);

                } else if (!float_in && float_out) {
                    // Input is no floating point, but output is: Scale values
                    // to maximum of input type.
                    auto w = static_cast<O>((std::numeric_limits<I>::max)());
                    auto b = static_cast<O>(0);
                    auto f = (i == 3) ? w : b;  // Alpha fallback 1, other 0.
                    auto c = (i < cnt_in) ? static_cast<O>(input[i]) : f;
                    c /= w;
                    static_cast<O *>(output)[i] = c;

                } else {
                    // Input and output are of the same type (integral or
                    // floating point): Just cast it.
                    auto w = float_out
                        ? static_cast<O>(1)
                        : (std::numeric_limits<O>::max)();
                    auto b = static_cast<O>(0);
                    auto f = (i == 3) ? w : b;  // Alpha fallback 1, other 0.
                    auto c = (i < cnt_in) ? static_cast<O>(input[i]) : f;
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
        const I *input, const size_t cnt_in, void *output,
        const size_t cnt_out) { }

} /* end namespace detail */
} /* end namespace mmpld */


/*
 * mmpld::convert
 */
template<class T>
size_t mmpld::convert(const void *src, const list_header& header, void *dst,
        const size_t cnt) {
    typedef T dst_view;
    typedef typename dst_view::vertex_value_type dst_vertex_scalar;

    const auto retval = (std::min)(static_cast<size_t>(header.particles), cnt);
    const auto dst_channels = dst_view::colour_traits::channels;
    const auto dst_colour = dst_view::colour_traits::colour_type;
    const auto dst_stride = dst_view::stride();
    const auto dst_vertex = dst_view::vertex_traits::vertex_type;
    const auto src_stride = get_stride<size_t>(header);
    auto d = static_cast<std::uint8_t *>(dst);
    auto s = static_cast<const std::uint8_t *>(src);

    if ((header.vertex_type == dst_vertex)
            && (header.colour_type == dst_colour)) {
        /* Source and destination types are the same, copy at once. */
        assert(dst_stride == src_stride);
        ::memcpy(d, s, retval * dst_stride);

    } else {
        /* Convert one particle at a time. */
        size_t src_col_offset, src_pos_offset, src_rad_offset;
        const auto invalid = get_offsets<size_t>(header, src_pos_offset,
            src_rad_offset, src_col_offset);

        for (size_t i = 0; i < retval; ++i) {
            auto dst_pos = dst_view::position(d);
            auto dst_rad = dst_view::radius(d);
            auto dst_col = static_cast<void *>(dst_view::colour(d));
            auto src_pos = detail::apply_offset(s, src_pos_offset, invalid);
            auto src_rad = detail::apply_offset(s, src_rad_offset, invalid);
            auto src_col = detail::apply_offset(s, src_col_offset, invalid);

            // Initialise the output particle with zeros.
            dst_view::clear(d);

            if ((dst_pos != nullptr) && (src_pos != nullptr)) {
                // We need to write a position and we have one (this should be
                // true for all valid data sets).
                switch (header.vertex_type) {
                    case mmpld::vertex_type::float_xyz:
                    case mmpld::vertex_type::float_xyzr:
                        dst_pos[0] = static_cast<dst_vertex_scalar>(
                            *(static_cast<const float *>(src_pos) + 0));
                        dst_pos[1] = static_cast<dst_vertex_scalar>(
                            *(static_cast<const float *>(src_pos) + 1));
                        dst_pos[2] = static_cast<dst_vertex_scalar>(
                            *(static_cast<const float *>(src_pos) + 2));
                        break;

                    case mmpld::vertex_type::short_xyz:
                        dst_pos[0] = static_cast<dst_vertex_scalar>(
                            *(static_cast<const std::int16_t *>(src_pos) + 0));
                        dst_pos[1] = static_cast<dst_vertex_scalar>(
                            *(static_cast<const std::int16_t *>(src_pos) + 1));
                        dst_pos[2] = static_cast<dst_vertex_scalar>(
                            *(static_cast<const std::int16_t *>(src_pos) + 2));
                        break;

                    case mmpld::vertex_type::double_xyz:
                        dst_pos[0] = static_cast<dst_vertex_scalar>(
                            *(static_cast<const double *>(src_pos) + 0));
                        dst_pos[1] = static_cast<dst_vertex_scalar>(
                            *(static_cast<const double *>(src_pos) + 1));
                        dst_pos[2] = static_cast<dst_vertex_scalar>(
                            *(static_cast<const double *>(src_pos) + 2));
                        break;

                    default:
                        throw std::logic_error("An invalid source vertex type "
                            "which cannot be converted was specified.");
                }
            }

            if (dst_rad != nullptr) {
                if (src_rad == nullptr) {
                    // We have no valid offset for the source radius, so we
                    // need to copy the global radius to each particle.
                    *dst_rad = static_cast<dst_vertex_scalar>(header.radius);
                } else {
                    // We know that all radii are float, so we can reinterpret
                    // the source pointer.
                    *dst_rad = *static_cast<const dst_vertex_scalar *>(src_rad);
                }
            }

            if (dst_col != nullptr) {
                typedef typename dst_view::colour_value_type dst_type;

                if (src_col == nullptr) {
                    // We have no valid offset for the source colour, so we
                    // need to use the global colour from the header.
                    detail::convert_colour<dst_type>(header.colour, 4,
                        dst_col, dst_channels);

                } else {
                    // There is a per-vertex colour that needs to be converted.
                    switch (header.colour_type) {
                        case mmpld::colour_type::intensity:
                            detail::convert_colour<dst_type>(
                                static_cast<const float *>(src_col), 1,
                                dst_col, dst_channels);
                            break;

                        case mmpld::colour_type::rgb32:
                            detail::convert_colour<dst_type>(
                                static_cast<const float *>(src_col), 3,
                                dst_col, dst_channels);
                            break;

                        case mmpld::colour_type::rgb8:
                            detail::convert_colour<dst_type>(
                                static_cast<const std::uint8_t *>(src_col), 3,
                                dst_col, dst_channels);
                            break;

                        case mmpld::colour_type::rgba32:
                            detail::convert_colour<dst_type>(
                                static_cast<const float *>(src_col), 4,
                                dst_col, dst_channels);
                            break;

                        case mmpld::colour_type::rgba8:
                            detail::convert_colour<dst_type>(
                                static_cast<const std::uint8_t *>(src_col), 4,
                                dst_col, dst_channels);
                            break;

                        case mmpld::colour_type::rgba16:
                            detail::convert_colour<dst_type>(
                                static_cast<const std::uint16_t *>(src_col), 4,
                                dst_col, dst_channels);
                            break;

                        case mmpld::colour_type::intensity64:
                            detail::convert_colour<dst_type>(
                                static_cast<const double *>(src_col), 1,
                                dst_col, dst_channels);
                            break;

                        default:
                            throw std::logic_error("An invalid source colour"
                                "type which cannot be converted was "
                                "specified.");
                    }
                }
            }

            s += src_stride;
            d += dst_stride;
        }
    }

    return retval;
}
