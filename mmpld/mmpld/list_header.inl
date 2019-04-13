/// <copyright file="list_header.inl" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2018 - 2019 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
/// Copyright © 2017 SFB-TRR 161. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>


#if defined(MMPLD_WITH_DIRECT3D)
/*
 * mmpld::get_input_layout
 */
template<class T>
std::vector<T> mmpld::get_input_layout(const list_header& header) {
    T element;
    UINT offset = 0;
    std::vector<T> retval;

    detail::zero_memory(element);
    element.SemanticName = "POSITION";
    element.AlignedByteOffset = offset;
    element.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;

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
    element.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;

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

    return std::move(retval);
}
#endif /* defined(MMPLD_WITH_DIRECT3D) */


namespace mmpld {
namespace detail {

    //template<vertex_type V>

} /* end namespace detail */
} /* end namespace mmpld */


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
    detail::enum_dispatch(detail::vertex_dispatch_list(), header.vertex_type,
        [&pos, &rad, &col](void) {

    });

    switch (header.vertex_type) {
        case mmpld::vertex_type::none:
            break;

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

        case mmpld::vertex_type::double_xyz:
            pos = 0;
            col = vertex_traits<vertex_type::double_xyz>::size;
            break;

        default:
            throw std::runtime_error("An unexpected vertex type was "
                "encountered. Make sure to update mmpld::get_offsets if "
                "you add new vertex types.");
    }

    // Update the offset of the colour using the actual configuration.
    switch (header.colour_type) {
        case mmpld::colour_type::rgb8:
        case mmpld::colour_type::rgba8:
        case mmpld::colour_type::intensity:
        case mmpld::colour_type::rgb32:
        case mmpld::colour_type::rgba32:
        case mmpld::colour_type::intensity64:
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
        case mmpld::colour_type::intensity64:
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
        case mmpld::vertex_type::none:
            break;

        case mmpld::vertex_type::float_xyz:
            retval += vertex_traits<vertex_type::float_xyz>::size;
            break;

        case mmpld::vertex_type::float_xyzr:
            retval += vertex_traits<vertex_type::float_xyzr>::size;
            break;

        case mmpld::vertex_type::short_xyz:
            retval += vertex_traits<vertex_type::short_xyz>::size;
            break;

        case mmpld::vertex_type::double_xyz:
            retval += vertex_traits<vertex_type::double_xyz>::size;

        default:
            throw std::runtime_error("An unexpected vertex type was "
                "encountered. Make sure to update mmpld::get_offsets if "
                "you add new vertex types.");
    }

    switch (header.colour_type) {
        case mmpld::colour_type::none:
            break;

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

        case mmpld::colour_type::intensity64:
            retval += colour_traits<colour_type::intensity64>::size;
            break;

        default:
            throw std::runtime_error("An unexpected colour type was "
                "encountered. Make sure to update mmpld::get_offsets if "
                "you add new vertex types.");
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
            // TODO: How does intensity64 behave here?!
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
