// <copyright file="list_header.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2018 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Copyright © 2017 SFB-TRR 161.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


#if defined(MMPLD_WITH_DIRECT3D)
/*
 * MMPLD_NAMESPACE::get_input_layout
 */
template<class T>
std::vector<T> MMPLD_NAMESPACE::get_input_layout(const list_header& header) {
    T element;
    UINT offset = 0;
    std::vector<T> retval;

    detail::zero_memory(element);
    element.SemanticName = "POSITION";
    element.AlignedByteOffset = offset;
    // Note: D3D1{0, 1, 2}_INPUT_PER_VERTEX_DATA is zero.
    //element.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;

    switch (header.vertex_type) {
        case vertex_type::float_xyz:
            element.Format = DXGI_FORMAT_R32G32B32_FLOAT;
            offset += vertex_traits<vertex_type::float_xyz>::size;
            retval.push_back(element);
            break;

        case vertex_type::float_xyzr:
            element.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
            offset += vertex_traits<vertex_type::float_xyzr>::size;
            retval.push_back(element);
            break;

        default:
            throw std::runtime_error("The given vertex type is "
                "incompatible with Direct3D alignment requirements.");
    }

    detail::zero_memory(element);
    element.SemanticName = "COLOR";
    element.AlignedByteOffset = offset;
    // Note: D3D1{0, 1, 2}_INPUT_PER_VERTEX_DATA is zero.
    //element.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;

    switch (header.colour_type) {
        case colour_type::intensity:
            element.Format = DXGI_FORMAT_R32_FLOAT;
            offset += colour_traits<colour_type::intensity>::size;
            retval.push_back(element);
            break;

        case colour_type::rgb32:
            element.Format = DXGI_FORMAT_R32G32B32_FLOAT;
            offset += colour_traits<colour_type::rgb32>::size;
            retval.push_back(element);
            break;

        case colour_type::rgba32:
            element.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
            offset += colour_traits<colour_type::rgba32>::size;
            retval.push_back(element);
            break;

        case colour_type::rgba8:
            element.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            offset += colour_traits<colour_type::rgba8>::size;
            retval.push_back(element);
            break;

        default:
            throw std::runtime_error("The given colour type is "
                "incompatible with Direct3D alignment requirements.");
    }

    return retval;
}
#endif /* defined(MMPLD_WITH_DIRECT3D) */


/*
 * MMPLD_NAMESPACE::get_offsets
 */
template<class T> T MMPLD_NAMESPACE::get_offsets(const list_header& header,
        T& pos, T& rad, T& col) noexcept {
    const auto retval = std::is_signed<T>::value
        ? std::numeric_limits<T>::lowest()
        : (std::numeric_limits<T>::max)();
    colour_properties colourProps;
    vertex_properties vertexProps;

    pos = rad = col = retval;

    auto hasPosition = get_properties(header.vertex_type, vertexProps);
    auto hasColour = get_properties(header.colour_type, colourProps);

    if (hasPosition) {
        // Position is always first.
        pos = 0;
    }

    if (hasPosition && vertexProps.has_radius) {
        // Add offset of radius if we have per-vertex radii.
        rad = static_cast<T>(vertexProps.radius_offset);
    }

    if (hasColour) {
        // Colour offset depends on previous position.
        col = static_cast<T>(hasPosition ? vertexProps.size : 0);
    }

    return retval;
}


/*
 * MMPLD_NAMESPACE::get_properties
 */
template<class T>
T MMPLD_NAMESPACE::get_properties(const list_header& header) noexcept {
    static_assert(sizeof(T) >= sizeof(MMPLD_NAMESPACE::particle_properties),
        "Output type for particle properties is too small.");
    auto retval = MMPLD_NAMESPACE::particle_properties::none;
    colour_properties colourProps;
    vertex_properties vertexProps;

    if (get_properties(header.vertex_type, vertexProps)) {
        if (vertexProps.has_radius) {
            retval |= MMPLD_NAMESPACE::particle_properties::per_particle_radius;
        }
    }

    if (get_properties(header.colour_type, colourProps)) {
        if (colourProps.channels == 1) {
            retval |= MMPLD_NAMESPACE::particle_properties::per_particle_intensity;
        } else if (colourProps.channels > 1) {
            retval |= MMPLD_NAMESPACE::particle_properties::per_particle_colour;
        }

        if (colourProps.is_float) {
            retval |= MMPLD_NAMESPACE::particle_properties::float_colour;
        }
    }

    return static_cast<T>(retval);
}


/*
 * MMPLD_NAMESPACE::get_stride
 */
template<class T> T MMPLD_NAMESPACE::get_stride(
        const vertex_type vertexType,
        const colour_type colourType) noexcept {
    std::size_t retval = 0;
    colour_properties colourProps;
    vertex_properties vertexProps;

    if (get_properties(vertexType, vertexProps)) {
        retval += vertexProps.size;
    }

    if (get_properties(colourType, colourProps)) {
        retval += colourProps.size;
    }

    return static_cast<T>(retval);
}


/*
 * MMPLD_NAMESPACE::read_list_header
 */
template<class T>
T& MMPLD_NAMESPACE::read_list_header(
        T& stream,
        const std::uint16_t fileVersion,
        list_header& header) {
    static const auto MAX_COLOUR = static_cast<float>(
        (std::numeric_limits<std::uint8_t>::max)());
    detail::zero_memory(header);

    detail::read(stream, header.vertex_type);
    detail::read(stream, header.colour_type);

    switch (header.vertex_type) {
        case vertex_type::float_xyz:
        case vertex_type::short_xyz:
        case vertex_type::double_xyz:
            detail::read(stream, header.radius);
        break;

        default:
            header.radius = -1.0f;
            break;
    }

    switch (header.colour_type) {
        case MMPLD_NAMESPACE::colour_type::none: {
            std::uint8_t rgba[4];
            detail::read(stream, rgba);
            for (size_t i = 0; i < 4; ++i) {
                header.colour[i] = static_cast<float>(rgba[i]) / MAX_COLOUR;
            }
            header.min_intensity = 0.0f;
            header.max_intensity = -1.0f;
            } break;

        case MMPLD_NAMESPACE::colour_type::intensity32:
        case MMPLD_NAMESPACE::colour_type::intensity64:
            // 32-bit and 64-bit intensity values both use 32-bit ranges. This
            // is a specification bug of MMPLD 1.3, which we need to keep for
            // compatibility with existing files.
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

    if (fileVersion == 103) {
        // TODO: I think it does not make sense testing for equality here, but
        // this should be forward-compatible (>= 103).
        detail::read(stream, header.bounding_box);
    } else {
        ::memset(header.bounding_box, 0, sizeof(header.bounding_box));
    }

    return stream;
}



/*
 * MMPLD_NAMESPACE::write_list_header
 */
template<class T>
T& MMPLD_NAMESPACE::write_list_header(
        const list_header& header,
        const std::uint16_t fileVersion,
        T& stream) {
    static const auto MAX_COLOUR = static_cast<float>(
        (std::numeric_limits<std::uint8_t>::max)());

    detail::write(header.vertex_type, stream);
    detail::write(header.colour_type, stream);

    switch (header.vertex_type) {
        case vertex_type::float_xyz:
        case vertex_type::short_xyz:
        case vertex_type::double_xyz:
            detail::write(header.radius, stream);
            break;

        default:
            // Nothing to do.
            break;
    }

    switch (header.colour_type) {
        case MMPLD_NAMESPACE::colour_type::none:
            for (size_t i = 0; i < 4; ++i) {
                detail::write(static_cast<std::uint8_t>(
                    header.colour[i] * MAX_COLOUR), stream);
            }
            break;

        case MMPLD_NAMESPACE::colour_type::intensity32:
        case MMPLD_NAMESPACE::colour_type::intensity64:
            // 32-bit and 64-bit intensity values both use 32-bit ranges. This
            // is a specification bug of MMPLD 1.3, which we need to keep for
            // compatibility with existing files.
            detail::write(header.min_intensity, stream);
            detail::write(header.max_intensity, stream);
            break;

        default:
            // Nothing to do.
            break;
    }

    detail::write(header.particles, stream);

    if (fileVersion == 103) {
        // TODO: I think it does not make sense testing for equality here, but
        // this should be forward-compatible (>= 103).
        for (auto b : header.bounding_box) {
            detail::write(b, stream);
        }
    }

    return stream;
}
