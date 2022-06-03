// <copyright file="convert.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2018 - 2022 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>


/// <summary>
/// Hash specialisation for pairs of <see cref="mmpld::vertex_type" />, which
/// are used to identify conversions.
/// </summary>
template<>
struct std::hash<std::pair<mmpld::vertex_type, mmpld::vertex_type>> {

    typedef std::pair<mmpld::vertex_type, mmpld::vertex_type> value_type;

    inline std::size_t operator ()(const value_type& value) const noexcept {
        static_assert(std::is_same< value_type::first_type,
            value_type::second_type>::value, "Both types of the conversion "
            "map must be identical.");
        static constexpr std::hash<value_type::first_type> hash;
        return (hash(value.first) ^ hash(value.second));
    }
};


/// <summary>
/// Hash specialisation for pairs of <see cref="mmpld::colour_type" />, which
/// are used to identify conversions.
/// </summary>
template<>
struct std::hash<std::pair<mmpld::colour_type, mmpld::colour_type>> {

    typedef std::pair<mmpld::colour_type, mmpld::colour_type> value_type;

    inline std::size_t operator ()(const value_type& value) const noexcept {
        static_assert(std::is_same< value_type::first_type,
            value_type::second_type>::value, "Both types of the conversion "
            "map must be identical.");
        static constexpr std::hash<value_type::first_type> hash;
        return (hash(value.first) ^ hash(value.second));
    }
};


namespace mmpld {
namespace detail {

    /// <summary>
    /// The identifier of a vertex conversion functor.
    /// </summary>
    typedef std::pair<vertex_type, vertex_type> vertex_conversion_id;

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


    //template<class C, C... Vs>
    //inline auto make_conversions_to(enum_dispatch_list<C, Vs...>, C output)
    //        -> decltype(std::tuple_cat(std::make_tuple(
    //        std::make_pair(output, Vs))...)) {
    //    return std::tuple_cat(std::make_tuple(std::make_pair(output, Vs))...);
    //}

    //template<class C, C... Vs>
    //inline auto make_conversions(enum_dispatch_list<C, Vs...>)
    //        -> decltype(std::tuple_cat(make_conversions_to(
    //        enum_dispatch_list<C, Vs...>{}, Vs)...)) {
    //    return std::tuple_cat(make_conversions_to(
    //        enum_dispatch_list<C, Vs...>{}, Vs)...);
    //}

    /// <summary>
    /// Generic base class for converting positions and colours.
    /// </summary>
    /// <remarks>
    /// This is the fallback that should never be used. There need to be valid
    /// specialisations for all possible conversions in order to make the
    /// runtime conversion table compile
    /// </remarks>
    /// <typeparam name="E">The type of the enumeration determining what
    /// conversion needs to be performed.</typeparam>
    /// <typeparam name="O">The output type to convert to.</typeparam>
    /// <typeparam name="I">The input type to convert from.</typeparam>
    template<class E, E O, E I> struct runtime_converter { };

    /// <summary>
    /// Specialised conversion for positions, which just casts the individual
    /// components.
    /// </summary>
    template<vertex_type O, vertex_type I>
    struct runtime_converter<vertex_type, O, I> {
        typedef vertex_traits<O> output_traits;
        typedef vertex_traits<I> input_traits;

        static inline void convert(void *dst, const void *src) {
            auto d = static_cast<output_traits::value_type *>(dst);
            auto s = static_cast<const input_traits::value_type *>(src);
            d[0] = static_cast<output_traits::value_type>(d[0]);
            d[1] = static_cast<output_traits::value_type>(d[1]);
            d[2] = static_cast<output_traits::value_type>(d[2]);
        }
    };

    /// <summary>
    /// Further specialisation for conversion no position.
    /// </summary>
    template<>
    struct runtime_converter<vertex_type, vertex_type::none,
            vertex_type::none> {
        static inline void convert(void *dst, const void *src) { }
    };

    /// <summary>
    /// Further specialisation for converting to a target type without a
    /// position.
    /// </summary>
    template<vertex_type I>
    struct runtime_converter<vertex_type, vertex_type::none, I> {
        static inline void convert(void *dst, const void *src) { }
    };

    /// <summary>
    /// Further specialisation generating the origin for missing position input.
    /// </summary>
    template<vertex_type O>
    struct runtime_converter<vertex_type, O, vertex_type::none> {
        typedef vertex_traits<O> output_traits;

        static inline void convert(void *dst, const void *src) {
            auto d = static_cast<output_traits::value_type *>(dst);
            d[0] = static_cast<output_traits::value_type>(0);
            d[1] = static_cast<output_traits::value_type>(0);
            d[2] = static_cast<output_traits::value_type>(0);
        }
    };


    /// <summary>
    /// Generates the conversion function pointers for converting from any of
    /// <c><typeparamref name="Is" />::value</c> to
    /// <c><typeparamref name="O" />::value</c>.
    /// </summary>
    /// <typeparam name="O">The traits type for the target of the conversion.
    /// This traits type must have a static <c>value</c> member with the
    /// enumeration value of the target type. If furthermore needs to define
    /// <c>value_type</c>, which must be the type of the data that are being
    /// converted.</typeparam>
    /// <typeparam name="Is">The traits types for the source of the conversion.
    /// These traits types must fulfil the same conditions as
    /// <typeparamref name="O" />.</typeparam>
    /// <returns>A tuple with all conversions to <typeparamref name="O" />. The
    /// keys are pairs holding the enumeration values of the source and target
    /// types, the values are pointers to
    /// <see cref="runtime_converter::convert" />.</returns>
    template<class O, class... Is>
    inline auto make_conversion_table5()
            -> decltype(std::tuple_cat(std::make_tuple(
            std::make_pair(std::make_pair(O::value, Is::value),
            runtime_converter<typename std::decay<decltype(O::value)>::type,
            O::value, Is::value>::convert))...)) {
            //    1))...)) {
        return std::tuple_cat(std::make_tuple(
            std::make_pair(std::make_pair(O::value, Is::value),
            runtime_converter<typename std::decay<decltype(O::value)>::type,
            O::value, Is::value>::convert))...);
    }

    /// <summary>
    /// Generates the conversion function pointers for performing arbitrary
    /// conversions between any of the types
    /// <c><typeparamref name="Ts" />::value</c>.
    /// </summary>
    /// <typeparam name="Ts">The traits types for the values to generate the
    /// conversion fro. This type must have a static <c>value</c> member holding
    /// the actual enum value. It furthermore needs to define <c>value_type</c>,
    /// which must be the type of the data that are being converted.</typeparam>
    /// <returns>A tuple holding all conversions between
    /// <typeparamref name="Ts" />. The keys are pairs holding the enumeration
    /// values of the source and target types, the values are pointers to
    /// <see cref="runtime_converter::convert" />.</returns>
    template<class... Ts>
    inline auto make_conversion_table4() -> decltype(
            std::tuple_cat(make_conversion_table5<Ts, Ts...>()...)) {
        return std::tuple_cat(make_conversion_table5<Ts, Ts...>()...);
    }

    /// <summary>
    /// Generates the conversion table for the members of the enumeration
    /// <typeparamref name="E" /> using the traits class
    /// <typeparamref name="T" />.
    /// </summary>
    /// <typeparam name="E">The type of the enumeration identifying the
    /// conversion at runtime.</typeparam>
    /// <typeparam name="T">The traits class that allows for reflecting on
    /// the individual enumeration values in <typeparamref name="E" />.
    /// </typeparam>
    /// <typeparam name="Vs">The individual enumeration values.</typeparam>
    /// <returns></returns>
    template<class E, template<E> class T, E... Vs>
    inline auto make_conversion_table3(enum_dispatch_list<E, Vs...>)
            -> decltype(make_conversion_table4<T<Vs>...>()) {
        return make_conversion_table4<T<Vs>...>();
    }

    /// <summary>
    /// Converts the output of <see cref="make_conversion_table3" /> from a
    /// tuple to a map that allows for constant-time lookup of the conversion
    /// functions.
    /// </summary>
    /// <typeparam name="E">The type of the enumeration identifying the
    /// conversion at runtime.</typeparam>
    /// <typeparam name="T">The traits class that allows for reflecting on
    /// the individual enumeration values in <typeparamref name="E" />.
    /// </typeparam>
    /// <typeparam name="Is">A index sequence for sequentially expanding the
    /// tuple.</typeparam>
    /// <returns></returns>
    template<class E, class T, std::size_t... Is>
    inline std::unordered_map<std::pair<E, E>, void (*)(void *, const void *)>
    make_conversion_table2(std::index_sequence<Is...>, T table) {
        typedef std::unordered_map<std::pair<E, E>,
            void (*)(void *, const void *)> table_type;
        return table_type { std::get<Is>(table)... };
    }

    /// <summary>
    /// Generates an index sequence that allows
    /// <see cref="make_conversion_table2" /> expanding the tuple generated
    /// by <see cref="make_conversion_table3" />.
    /// </summary>
    /// <typeparam name="E"></typeparam>
    /// <typeparam name="T"></typeparam>
    /// <param name="table"></param>
    /// <returns></returns>
    template<class E, class T>
    inline std::unordered_map<std::pair<E, E>, void (*)(void *, const void *)>
    make_conversion_table1(T table) {
        return make_conversion_table2<E>(std::make_index_sequence<
            std::tuple_size<T>::value> { }, table);
    }

    /// <summary>
    /// Builds a hash table that allows for looking up a per-component
    /// conversion function for two enumeration members of types like
    /// <see cref="vertex_type" /> or <see cref="colour_type" />.
    /// </summary>
    /// <typeparam name="E"></typeparam>
    /// <typeparam name="T"></typeparam>
    /// <returns></returns>
    template<class E, template<E> class T>
    inline std::unordered_map<std::pair<E, E>, void (*)(void *, const void *)>
    make_conversion_table() {
        return make_conversion_table1<E>(make_conversion_table3<E, T>(
            vertex_dispatch_list { }));
    }

} /* end namespace detail */
} /* end namespace mmpld */


/*
 * mmpld::convert
 */
template<class T>
std::size_t mmpld::convert(const void *src, const list_header& header,
        void *dst, const std::size_t cnt) {
    typedef T dst_view;
    typedef typename dst_view::vertex_value_type dst_vertex_scalar;

    const auto retval = (std::min)(static_cast<size_t>(header.particles), cnt);
    const auto dst_channels = dst_view::colour_traits::channels;
    const auto dst_colour = dst_view::colour_traits::colour_type;
    const auto dst_stride = dst_view::stride();
    const auto dst_vertex = dst_view::vertex_traits::value;
    const auto src_stride = get_stride<std::size_t>(header);
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


/*
 * mmpld::convert
 */
template<class T, class S>
void mmpld::convert(const particle_view<T>& src, const particle_view<T>& dst,
        const std::size_t cnt) {
    if (!src.good()) {
        throw std::invalid_argument("The source view must be valid.");
    }
    if (!dst.good()) {
        throw std::invalid_argument("The destination view must be valid.");
    }

#if false
    if ((src.vertex_type() == dst.colour_type())
            && (src.colour_type() == dst.colour_type())) {
        /* Source and destination types are the same, copy at once. */
        assert(src.stride() == dst.stride());
        ::memcpy(dst.data(), src.data(), cnt * dst_stride);

    } else {
        /* Convert one particle at a time. */
        for (std::size_t i = 0; i < cnt; ++i) {
            auto dst_pos = dst.position<void>();
            auto dst_rad = dst.radius<void>();
            auto dst_col = dst.colour<void>();
            auto src_pos = src.position<void>();
            auto src_rad = src.radius<void>();
            auto src_col = src.colour<void>();

            // Initialise the output particle with zeros.
            dst.clear();

            if ((dst_pos != nullptr) && (src_pos != nullptr)) {

                // We need to write a position and we have one (this should be
                // true for all valid data sets).
                switch (src.vertex_type()) {
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
#endif
}
