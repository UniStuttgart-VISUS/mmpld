// <copyright file="convert.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2018 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


MMPLD_DETAIL_NAMESPACE_BEGIN

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
/// Read and convert the specified particle list from a file handle of
/// type <paramref name="F" />.
/// </summary>
template<class F, class O>
decltype(MMPLD_NAMESPACE::list_header::particles) read_as(
        F& file, const list_header& src_header,
        O *dst, list_header& dst_header,
        std::vector<std::uint8_t>& buffer) {
    typedef std::decay<decltype(src_header.particles)>::type count_type;
    typedef detail::basic_io_traits<F> io_traits;
    assert(buffer.size() > 0);

    auto d_header = dst_header;
    const auto dst_stride = get_stride<std::size_t>(dst_header);
    const auto retval = (std::min)(src_header.particles,
        dst_header.particles);
    const auto src_stride = get_stride<std::size_t>(src_header);
    assert(buffer.size() >= src_stride);
    const auto cnt_buffer = buffer.size() / src_stride;

    for (count_type i = 0; i < retval; i += cnt_buffer) {
        auto c = (std::min)(cnt_buffer,
            static_cast<std::size_t>(retval - i));
        auto d = reinterpret_cast<std::uint8_t *>(dst) + i * dst_stride;
        d_header.particles = c;
        io_traits::read(file, buffer.data(), c * src_stride);
        convert(buffer.data(), src_header, d, d_header);
    }

    return retval;
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

MMPLD_DETAIL_NAMESPACE_END


/*
 * MMPLD_NAMESPACE::convert
 */
template<class T, class I, class O>
decltype(MMPLD_NAMESPACE::list_header::particles) MMPLD_NAMESPACE::convert(
        const I *src, const list_header& header,
        O *dst, const decltype(list_header::particles) cnt) {
    typedef T dst_view;
    typedef typename dst_view::vertex_value_type dst_vertex_scalar;

    const auto retval = (std::min)(header.particles, cnt);
    const auto dst_colour = dst_view::colour_traits::value;
    const auto dst_stride = dst_view::stride();
    const auto dst_vertex = dst_view::vertex_traits::value;
    const auto src_stride = get_stride<std::size_t>(header);
    auto d = reinterpret_cast<std::uint8_t *>(dst);
    auto s = reinterpret_cast<const std::uint8_t *>(src);

    if ((src == nullptr) || (dst == nullptr) || (retval < 1)) {
        /* If either of the pointers is invalid, we cannot convert anything. */
        return 0;
    }

    if (is_same_format<T>(header)) {
        /* Source and destination types are the same, copy at once. */
        assert(dst_stride == src_stride);
        ::memcpy(d, s, static_cast<std::size_t>(retval) * dst_stride);

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

            // Delegate radius conversion to separate template that can handle
            // void input/output cases.
            detail::convert_radius<dst_vertex_scalar>(src_rad, header.radius,
                dst_rad);

            if (dst_col != nullptr) {
                typedef typename dst_view::colour_value_type dst_type;

                if (src_col == nullptr) {
                    // We have no valid offset for the source colour, so we
                    // need to use the global colour from the header.
                    global_col_conv(header.colour, dst_col,
                        header.min_intensity, header.max_intensity);

                } else {
                    // There is a per-vertex colour that needs to be converted.
                    assert(col_conv != nullptr);
                    col_conv(src_col, dst_col, header.min_intensity,
                        header.max_intensity);
                }
            }

            s += src_stride;
            d += dst_stride;
        }
    }

    return retval;
}


/*
 * MMPLD_NAMESPACE::convert
 */
template<class I, class O>
decltype(MMPLD_NAMESPACE::list_header::particles) MMPLD_NAMESPACE::convert(
        const I *src, const list_header& src_header,
        O *dst, list_header& dst_header) {
    const auto dst_stride = get_stride<std::size_t>(dst_header);
    const auto retval = (std::min)(src_header.particles, dst_header.particles);
    const auto src_stride = get_stride<std::size_t>(src_header);

    if ((src == nullptr) || (dst == nullptr) || (retval < 1)) {
        /* If either of the pointers is invalid, we cannot convert anything. */
        return 0;
    }

    if (is_same_format(src_header, dst_header)) {
        /* Source and destination types are the same, copy at once. */
        assert(src_stride == dst_stride);
        ::memcpy(dst, src, static_cast<std::size_t>(retval) * dst_stride);

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
                    global_col_conv(src_header.colour, dst_col,
                        src_header.min_intensity, src_header.max_intensity);

                } else {
                    // There is a per-vertex colour that needs to be converted.
                    assert(col_conv != nullptr);
                    col_conv(src_col, dst_col, src_header.min_intensity,
                        src_header.max_intensity);
                }
            }

            dst_view.advance();
            src_view.advance();
        }
    } /* end if (is_same_format(dst, header)) */

    return retval;
}


/*
 * MMPLD_NAMESPACE::read_as
 */
template<class F, class O>
decltype(MMPLD_NAMESPACE::list_header::particles) MMPLD_NAMESPACE::read_as(
        F& file, const list_header& src_header,
        O *dst, list_header& dst_header,
        decltype(list_header::particles) cnt_buffer) {
    typedef detail::basic_io_traits<F> io_traits;

    const auto retval = (std::min)(src_header.particles, dst_header.particles);
    const auto src_stride = get_stride<std::size_t>(src_header);

    if (is_same_format(src_header, dst_header)) {
        assert(src_stride == get_stride<std::size_t>(dst_header));
        io_traits::read(file, dst, retval * src_stride);

    } else {
        if (cnt_buffer == 0) {
            cnt_buffer = retval;
        }

        std::vector<std::uint8_t> buffer(static_cast<std::size_t>(cnt_buffer)
            * src_stride);
        detail::read_as(file, src_header, dst, dst_header, buffer);
    }

    return retval;
}


/*
 * MMPLD_NAMESPACE::read_as
 */
template<class T, class F, class O>
decltype(MMPLD_NAMESPACE::list_header::particles) MMPLD_NAMESPACE::read_as(
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


/*
 * MMPLD_NAMESPACE::read_as
 */
template<class F, class O>
decltype(MMPLD_NAMESPACE::list_header::particles) MMPLD_NAMESPACE::read_as(
        F& file, const frame_header& src_header,
        const std::uint16_t file_version,
        O *dst, list_header& dst_header,
        const decltype(list_header::particles) cnt_buffer) {
    typedef detail::basic_io_traits<F> io_traits;

    const auto dst_stride = get_stride<std::size_t>(dst_header);

    std::vector<std::uint8_t> buffer(0);
    auto d = reinterpret_cast<std::uint8_t *>(dst);
    list_header header;
    auto rem = dst_header.particles;
    auto retval = static_cast<decltype(list_header::particles)>(0);

    // Initialise the bounding box and the intensity range.
    dst_header.bounding_box[0]
        = dst_header.bounding_box[1]
        = dst_header.bounding_box[2]
        = dst_header.min_intensity
        = (std::numeric_limits<float>::max)();
    dst_header.bounding_box[3]
        = dst_header.bounding_box[4]
        = dst_header.bounding_box[5]
        = dst_header.max_intensity
        = (std::numeric_limits<float>::lowest)();

    for (decltype(MMPLD_NAMESPACE::frame_header::lists) i = 0; i < src_header.lists;
            ++i) {
        read_list_header(file, file_version, header);
        const auto src_stride = get_stride<std::size_t>(header);

        // Update global variables.
        union_bounding_box(dst_header, header);
        union_intensity_range(dst_header, header);

        // Convert the particles.
        if (is_same_format(header, dst_header)) {
            // Format is as requested, so we can just copy.
            assert(src_stride == dst_stride);
            auto cnt = (std::min)(header.particles, rem);
            io_traits::read(file, d + retval * dst_stride, cnt * src_stride);
            retval += cnt;
            rem -= cnt;

        } else {
            // A conversion is required for this list. Make sure that the buffer
            // is either large enough to hold the whole frame or to hold the
            // user-defined number of particles to be converted at once.
            if (cnt_buffer > 0) {
                const auto s = static_cast<std::size_t>(header.particles
                    * src_stride);
                if (buffer.size() < s) { 
                    buffer.resize(s);
                }

            } else {
                const auto s = static_cast<std::size_t>(dst_header.particles
                    * src_stride);
                if (buffer.size() < s) {
                    buffer.resize(s);
                }
            }

            dst_header.particles = (std::min)(header.particles, rem);
            auto cnt = detail::read_as(file, header, d + retval * dst_stride,
                dst_header, buffer);
            retval += cnt;
            rem -= cnt;
        }

        // Skip cluster info in MMPLD 1.1.
        if (file_version == MMPLD_NAMESPACE::make_version(1, 1)) {
            MMPLD_NAMESPACE::skip_cluster_info(file);
        }
    }

    dst_header.particles = retval;

    return retval;
}
