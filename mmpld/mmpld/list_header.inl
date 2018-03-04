/// <copyright file="list_header.inl" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2018 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
/// Copyright © 2017 SFB-TRR 161. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>


/*
 * mmpld::get_offsets
 */
template<class T>
T mmpld::get_offsets(const list_header& header, T& pos, T& rad, T& col) {
    const auto retval = std::is_signed<T>::value
        ? std::numeric_limits<T>::lowest()
        : (std::numeric_limits<T>::max)();

    pos = rad = col = retval;

    // Set pointers to radius and colour, assuming there is a valid colour
    // for now.
    switch (header.vertex_type) {
        case mmpld::vertex_type::float_xyz:
            pos = 0;
            col = vertex_traits<vertex_type::float_xyz>::size;
            break;

        case mmpld::vertex_type::float_xyzr:
            pos = 0;
            rad = 3 * sizeof(float);
            col = vertex_traits<vertex_type::float_xyzr>::size;
            break;

        case mmpld::vertex_type::short_xyz:
            pos = 0;
            col = vertex_traits<vertex_type::short_xyz>::size;
            break;
    }

    // Update the offset of the colour using the actual configuration.
    switch (header.colour_type) {
        case mmpld::colour_type::rgb8:
        case mmpld::colour_type::rgba8:
        case mmpld::colour_type::intensity:
        case mmpld::colour_type::rgb32:
        case mmpld::colour_type::rgba32:
            if (pos == retval) {
                col = 0;
            }
            break;

        case mmpld::colour_type::none:
        default:
            col = retval;
            break;
    }

    return retval;
}


/*
 * mmpld::get_properties
 */
template<class T> T mmpld::get_properties(const list_header& header) {
    static_assert(sizeof(T) >= sizeof(mmpld::particle_properties), "Output "
        "type for particle properties is too small.");
    auto retval = mmpld::particle_properties::none;

    switch (header.vertex_type) {
        case mmpld::vertex_type::float_xyzr:
            retval |= mmpld::particle_properties::per_particle_radius;
            break;

        default:
            // Nothing to do.
            break;
    }

    switch (header.colour_type) {
        case mmpld::colour_type::intensity:
            retval |= mmpld::particle_properties::per_particle_intensity;
            break;

        case mmpld::colour_type::none:
            // Nothing to do.
            break;

        case mmpld::colour_type::rgb32:
        case mmpld::colour_type::rgba32:
            retval |= mmpld::particle_properties::float_colour;
        default:
            retval |= mmpld::particle_properties::per_particle_colour;
            break;
    }

    return static_cast<T>(retval);
}


/*
 * mmpld::get_stride
 */
template<class T> T mmpld::get_stride(const list_header& header) {
    std::size_t retval = 0;

    switch (header.vertex_type) {
        case mmpld::vertex_type::float_xyz:
            retval += vertex_traits<vertex_type::float_xyz>::size;
            break;

        case mmpld::vertex_type::float_xyzr:
            retval += vertex_traits<vertex_type::float_xyzr>::size;
            break;

        case mmpld::vertex_type::short_xyz:
            retval += vertex_traits<vertex_type::short_xyz>::size;
            break;
    }

    switch (header.colour_type) {
        case mmpld::colour_type::rgb8:
            retval += colour_traits<colour_type::rgb8>::size;
            break;

        case mmpld::colour_type::rgba8:
            retval += colour_traits<colour_type::rgba8>::size;
            break;

        case mmpld::colour_type::intensity:
            retval += colour_traits<colour_type::intensity>::size;
            break;

        case mmpld::colour_type::rgb32:
            retval += colour_traits<colour_type::rgb32>::size;
            break;

        case mmpld::colour_type::rgba32:
            retval += colour_traits<colour_type::rgba32>::size;
            break;
    }

    return static_cast<T>(retval);
}


/*
 * mmpld::read_list_header
 */
template<class T> T& mmpld::read_list_header(T& stream, list_header& header) {
    static const auto MAX_COLOUR = static_cast<float>(
        (std::numeric_limits<std::uint8_t>::max)());
    detail::zero_memory(header);

    detail::read(stream, header.vertex_type);
    detail::read(stream, header.colour_type);

    switch (header.vertex_type) {
        case vertex_type::float_xyz:
        case vertex_type::short_xyz:
            detail::read(stream, header.radius);
        break;

        default:
            header.radius = -1.0f;
            break;
    }

    switch (header.colour_type) {
        case mmpld::colour_type::none: {
            std::uint8_t rgba[4];
            detail::read(stream, rgba);
            for (size_t i = 0; i < 4; ++i) {
                header.colour[i] = static_cast<float>(rgba[i]) / MAX_COLOUR;
            }
            header.min_intensity = 0.0f;
            header.max_intensity = -1.0f;
            } break;

        case mmpld::colour_type::intensity:
            detail::zero_memory(header.colour);
            detail::read(stream, header.min_intensity);
            detail::read(stream, header.max_intensity);
            break;

        default:
            detail::zero_memory(header.colour);
            header.min_intensity = 0.0f;
            header.max_intensity = -1.0f;
            break;
    }

    detail::read(stream, header.particles);

    return stream;
}
