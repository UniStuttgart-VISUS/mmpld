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

    typedef void (*conversion_function)(const void *, void *);

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
                    // Determine the fallback colour: For alpha (i == 3), use
                    // white, otherwise splat the grey value or use black.
                    auto g = (cnt_in == 1) ? input[0] : b;
                    auto f = (i == 3) ? w : g;
                    auto c = (i < cnt_in) ? input[i] : f;
                    c *= static_cast<I>((std::numeric_limits<O>::max)());
                    static_cast<O *>(output)[i] = static_cast<O>(c);

                } else if (!float_in && float_out) {
                    // Input is no floating point, but output is: Scale values
                    // to maximum of input type.
                    auto w = static_cast<O>((std::numeric_limits<I>::max)());
                    auto b = static_cast<O>(0);
                    // Determine the fallback colour: For alpha (i == 3), use
                    // white, otherwise splat the grey value or use black.
                    auto g = (cnt_in == 1) ? static_cast<O>(input[0]) : b;
                    auto f = (i == 3) ? w : g;
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
                    // Determine the fallback colour: For alpha (i == 3), use
                    // white, otherwise splat the grey value or use black.
                    auto g = (cnt_in == 1) ? static_cast<O>(input[0]) : b;
                    auto f = (i == 3) ? w : g;
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

    /// <summary>
    /// Specialised conversion for colours, which redirects the conversion to
    /// <see cref="convert_colour" />.
    /// </summary>
    template<colour_type O, colour_type I>
    struct runtime_converter<colour_type, O, I> {
        typedef colour_traits<O> output_traits;
        typedef colour_traits<I> input_traits;

        static inline void convert(const void *src, void *dst) {
            auto s = static_cast<const typename input_traits::value_type *>(src);
            convert_colour<typename output_traits::value_type>(
                s, input_traits::channels, dst, output_traits::channels);
        }
    };

    /// <summary>
    /// Further specialisation for conversion of no colour.
    /// </summary>
    template<> struct runtime_converter<colour_type, colour_type::none,
            colour_type::none> {
        static inline void convert(const void *src, void *dst) { }
    };

    /// <summary>
    /// Further specialisation generating a medium grey for missing position
    /// input.
    /// </summary>
    template<colour_type O>
    struct runtime_converter<colour_type, O, colour_type::none> {
        typedef colour_traits<O> output_traits;

        static inline void convert(const void *src, void *dst) {
            static constexpr std::array<std::uint8_t, 4> GREY {
                128, 128, 128, 255
            };
            convert_colour<typename output_traits::value_type>(GREY.data(),
                GREY.size(), dst, output_traits::channels);
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
    inline std::unordered_map<std::pair<E, E>, conversion_function>
    make_conversion_table2(std::index_sequence<Is...>, T table) {
        typedef std::unordered_map<std::pair<E, E>,
            conversion_function> table_type;
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
    inline std::unordered_map<std::pair<E, E>, conversion_function>
    make_conversion_table1(T table) {
        return make_conversion_table2<E>(std::make_index_sequence<
            std::tuple_size<T>::value> { }, table);
    }

    /// <summary>
    /// Builds a hash table that allows for looking up a conversion function for
    /// two <see cref="colour_type" />s.
    /// </summary>
    /// <returns></returns>
    inline const std::unordered_map<std::pair<colour_type, colour_type>,
        conversion_function>&
    make_colour_conversion_table() {
        static const auto retval = make_conversion_table1<colour_type>(
            make_conversion_table3<colour_type, colour_traits>(
            colour_dispatch_list { }));
        return retval;
    }

    /// <summary>
    /// Builds a hash table that allows for looking up a conversion function for
    /// two <see cref="vertex_type" />s.
    /// </summary>
    /// <returns></returns>
    inline const std::unordered_map<std::pair<vertex_type, vertex_type>,
        conversion_function>&
    make_vertex_conversion_table() {
        static const auto retval = make_conversion_table1<vertex_type>(
            make_conversion_table3<vertex_type, vertex_traits>(
            vertex_dispatch_list { }));
        return retval;
    }

    /// <summary>
    /// Gets the colour converter function for the specified conversion.
    /// </summary>
    /// <param name="dst"></param>
    /// <param name="src"></param>
    /// <returns></returns>
    inline conversion_function get_colour_converter(const colour_type dst,
            const colour_type src) {
        static const auto& TABLE = detail::make_colour_conversion_table();
        auto it = TABLE.find(std::make_pair(dst, src));
        if (it != TABLE.end()) {
            return it->second;
        } else {
            throw std::logic_error("No valid converter was registered for the "
                "requested colour conversion");
        }
    }

    /// <summary>
    /// Gets the vertex/position converter function for the specified
    /// conversion.
    /// </summary>
    /// <param name="dst"></param>
    /// <param name="src"></param>
    /// <returns></returns>
    inline conversion_function get_vertex_converter(const vertex_type dst,
            const vertex_type src) {
        static const auto& TABLE = detail::make_vertex_conversion_table();
        auto it = TABLE.find(std::make_pair(dst, src));
        if (it != TABLE.end()) {
            return it->second;
        } else {
            throw std::logic_error("No valid converter was registered for the "
                "requested position conversion");
        }
    }

    /// <summary>
    /// Incrementally computes the mean of a series of numbers.
    /// </summary>
    /// <typeparam name="T">The type of the numbers.</typeparam>
    /// <typeparam name="C">The type of the counter.</typeparam>
    /// <param name="mean">A reference to the incrementally computed mean.
    /// This variable must be initialised with zero.</param>
    /// <param name="count">The number of already accumulated values, not
    /// including the one that is added now.</param>
    /// <param name="n">The next number to be added to the mean.</param>
    template<class T, class C>
    inline void incremental_mean(T& mean, const C count, T n) {
        mean += (n - mean) / (count + 1);
    }

} /* end namespace detail */
} /* end namespace mmpld */


/*
 * mmpld::convert
 */
template<class T, class I, class O>
decltype(mmpld::list_header::particles) mmpld::convert(
        const I *src, const list_header& header,
        O *dst, const decltype(list_header::particles) cnt) {
    typedef T dst_view;
    typedef typename dst_view::vertex_value_type dst_vertex_scalar;

    const auto retval = (std::min)(header.particles, cnt);
    const auto dst_channels = dst_view::colour_traits::channels;
    const auto dst_colour = dst_view::colour_traits::colour_type;
    const auto dst_stride = dst_view::stride();
    const auto dst_vertex = dst_view::vertex_traits::value;
    const auto src_stride = get_stride<std::size_t>(header);
    auto d = reinterpret_cast<std::uint8_t *>(dst);
    auto s = reinterpret_cast<const std::uint8_t *>(src);

    if (is_same_format<T>(header)) {
        /* Source and destination types are the same, copy at once. */
        assert(dst_stride == src_stride);
        ::memcpy(d, s, retval * dst_stride);

    } else {
        /* Convert one particle at a time. */
        std::size_t src_col_offset, src_pos_offset, src_rad_offset;
        const auto invalid = get_offsets<size_t>(header, src_pos_offset,
            src_rad_offset, src_col_offset);
        const auto col_conv = detail::get_colour_converter(dst_colour,
            header.colour_type);
        const auto global_col_conv = detail::get_colour_converter(dst_colour,
            colour_type::rgba32);
        const auto pos_conv = detail::get_vertex_converter(dst_vertex,
            header.vertex_type);

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
                assert(pos_conv != nullptr);
                pos_conv(src_pos, dst_pos);
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
                    global_col_conv(header.colour, dst_col);

                } else {
                    // There is a per-vertex colour that needs to be converted.
                    assert(col_conv != nullptr);
                    col_conv(src_col, dst_col);
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
template<class I, class O>
decltype(mmpld::list_header::particles) mmpld::convert(
        const I *src, const list_header& src_header,
        O *dst, list_header& dst_header) {
    assert(src != nullptr);
    assert(dst != nullptr);
    const auto dst_stride = get_stride<std::size_t>(dst_header);
    const auto retval = (std::min)(src_header.particles, dst_header.particles);
    const auto src_stride = get_stride<std::size_t>(src_header);

    if (is_same_format(src_header, dst_header)) {
        /* Source and destination types are the same, copy at once. */
        assert(src_stride == dst_stride);
        ::memcpy(dst, src, retval * dst_stride);

    } else {
        const auto col_conv = detail::get_colour_converter(
            dst_header.colour_type, src_header.colour_type);
        const auto global_col_conv = detail::get_colour_converter(
            dst_header.colour_type, colour_type::rgba32);
        const auto pos_conv = detail::get_vertex_converter(
            dst_header.vertex_type, src_header.vertex_type);
        auto dst_view = make_particle_view(dst_header, dst);
        auto src_view = make_particle_view(src_header, src);

        // Prepare the global radius of the destination for computing the mean
        // radius of the input in case the destination has no per-particle
        // radius, but the input has.
        {
            vertex_properties dst_props, src_props;

            if (get_properties(src_view.vertex_type(), src_props)
                    && get_properties(dst_view.vertex_type(), dst_props)) {
                if (src_props.has_radius && !dst_props.has_radius) {
                    dst_header.radius = 0.0f;
                }
            }
        }

        /* Convert one particle at a time. */
        for (std::size_t i = 0; i < retval; ++i) {
            auto dst_pos = dst_view.template position<void>();
            auto dst_rad = dst_view.template radius<float>();
            auto dst_col = dst_view.template colour<void>();
            auto src_pos = src_view.template position<const void>();
            auto src_rad = src_view.template radius<const float>();
            auto src_col = src_view.template colour<const void>();

            // Initialise the output particle with zeros.
            dst_view.clear();

            if ((dst_pos != nullptr) && (src_pos != nullptr)) {
                assert(pos_conv != nullptr);
                pos_conv(src_pos, dst_pos);
            }

            if (dst_rad != nullptr) {
                // Note: We make the simplyfing assumption that the radius is
                // always float, which is true for the current version of MMPLD.
                // If additional vertex types are added in the future, this
                // might not hold any more and this code (and the 'dst_rad' and
                // 'src_rad' above need to be refactored).
                assert(dst_view.vertex_type() == vertex_type::float_xyzr);

                if (src_rad == nullptr) {
                    // We have no valid offset for the source radius, so we
                    // need to copy the global radius to each particle.
                    *dst_rad = src_header.radius;

                } else {
                    // We know that all radii are float, so we can reinterpret
                    // the source pointer.
                    assert(src_view.vertex_type() == vertex_type::float_xyzr);
                    *dst_rad = *src_rad;
                }

            } else if (src_rad != nullptr) {
                // We have no per-particle radius in the destination view, but
                // we have radii in the source, so compute the average radius
                // into the header of the destination.
                detail::incremental_mean(dst_header.radius, i, *src_rad);
            }

            if (dst_col != nullptr) {
                if (src_col == nullptr) {
                    // We have no valid offset for the source colour, so we
                    // need to use the global colour from the header.
                    assert(global_col_conv != nullptr);
                    global_col_conv(src_header.colour, dst_col);

                } else {
                    // There is a per-vertex colour that needs to be converted.
                    assert(col_conv != nullptr);
                    col_conv(src_col, dst_col);
                }
            }

            dst_view.advance();
            src_view.advance();
        }
    } /* end if (is_same_format(dst, header)) */

    return retval;
}


/*
 * mmpld::read_as
 */
template<class F, class O>
decltype(mmpld::list_header::particles) mmpld::read_as(
        F& file, const list_header& src_header,
        O *dst, list_header& dst_header,
        decltype(list_header::particles) cnt_buffer) {
    typedef detail::basic_io_traits<F> io_traits;

    const auto dst_stride = get_stride<std::size_t>(dst_header);
    const auto retval = (std::min)(src_header.particles, dst_header.particles);
    const auto src_stride = get_stride<std::size_t>(src_header);

    if (is_same_format(src_header, dst_header)) {
        assert(src_stride == dst_stride);
        io_traits::read(file, dst, retval * src_stride);

    } else {
        if (cnt_buffer == 0) {
            cnt_buffer = retval;
        }

        std::vector<std::uint8_t> buffer(cnt_buffer * src_stride);
        auto d_header = dst_header;

        for (std::size_t i = 0; i < retval; i += cnt_buffer) {
            auto c = (std::min)(cnt_buffer, retval - i);
            auto d = reinterpret_cast<std::uint8_t *>(dst) + i * dst_stride;
            d_header.particles = c;
            io_traits::read(file, buffer.data(), c * src_stride);
            convert(buffer.data(), src_header, d, d_header);
        }
    }

    return retval;
}


/*
 * mmpld::read_as
 */
template<class T, class F, class O>
decltype(mmpld::list_header::particles) mmpld::read_as(
        F& file, const list_header& header,
        O *dst, const decltype(list_header::particles) cnt,
        decltype(list_header::particles) cnt_buffer) {
    list_header dst_header;
    ::memset(&dst_header, sizeof(dst_header), 0);
    dst_header.vertex_type = T::vertex_type();
    dst_header.colour_type = T::colour_type();
    dst_header.particles = cnt;
    return read_as(file, header, dst, dst_header, cnt_buffer);
}
