﻿// <copyright file="particle_view.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2018 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * mmpld::particle_view<T>::particle_view
 */
template<class T>
mmpld::particle_view<T>::particle_view(const mmpld::vertex_type vertex_type,
        const mmpld::colour_type colour_type, pointer_type data) : _data(data) {
    mmpld::list_header dummy;
    dummy.colour_type = colour_type;
    dummy.vertex_type = vertex_type;
    this->set_properties(dummy);
}


/*
 * mmpld::particle_view<T>::particle_view
 */
template<class T>
mmpld::particle_view<T>::particle_view(const mmpld::list_header& header,
        pointer_type data) : _data(data) {
    this->set_properties(header);
}


/*
 * mmpld::particle_view<T>::colour
 */
template<class T>
typename mmpld::particle_view<T>::pointer_type mmpld::particle_view<T>::colour(
        void) {
    auto retval = this->byte_data();

    if (this->_colour_offset != this->_invalid_offset) {
        retval += this->_colour_offset;
    } else {
        retval = nullptr;
    }

    return reinterpret_cast<pointer_type>(retval);
}


/*
 * mmpld::particle_view<T>::position
 */
template<class T>
typename mmpld::particle_view<T>::pointer_type
mmpld::particle_view<T>::position(void) {
    auto retval = this->byte_data();

    if (this->_position_offset != this->_invalid_offset) {
        retval += this->_position_offset;
    } else {
        retval = nullptr;
    }

    return reinterpret_cast<pointer_type>(retval);
}


/*
 * mmpld::particle_view<T>::radius
 */
template<class T>
typename mmpld::particle_view<T>::pointer_type mmpld::particle_view<T>::radius(
        void) {
    auto retval = this->byte_data();

    if (this->_radius_offset != this->_invalid_offset) {
        retval += this->_radius_offset;
    } else {
        retval = nullptr;
    }

    return reinterpret_cast<pointer_type>(retval);
}


/*
 * mmpld::particle_view<T>::operator =
 */
template<class T>
mmpld::particle_view<T>& mmpld::particle_view<T>::operator =(
        const particle_view& rhs) {
    if (this != std::addressof(rhs)) {
        this->_colour_offset = rhs._colour_offset;
        this->_colour_type = rhs._colour_type;
        this->_data = rhs._data;
        this->_invalid_offset = rhs._invalid_offset;
        this->_position_offset = rhs._position_offset;
        this->_radius_offset = rhs._radius_offset;
        this->_stride = rhs._stride;
        this->_vertex_type = rhs._vertex_type;
    }
    return *this;
}


/*
 * mmpld::particle_view<T>::operator =
 */
template<class T>
mmpld::particle_view<T>& mmpld::particle_view<T>::operator =(
        particle_view&& rhs) {
    if (this != std::addressof(rhs)) {
        const auto invalid_offset = rhs._invalid_offset;
        this->_colour_offset = rhs._colour_offset;
        rhs._colour_offset = invalid_offset;
        this->_colour_type = rhs._colour_type;
        rhs._colour_type = mmpld::colour_type::none;
        this->_data = rhs._data;
        rhs._data = nullptr;
        this->_invalid_offset = rhs._invalid_offset;
        // Do not erase the invalid offset!
        this->_position_offset = rhs._position_offset;
        rhs._position_offset = invalid_offset;
        this->_radius_offset = rhs._radius_offset;
        rhs._radius_offset = invalid_offset;
        this->_stride = rhs._stride;
        rhs._stride = 0;
        this->_vertex_type = rhs._vertex_type;
        rhs._vertex_type = mmpld::vertex_type::none;
    }
    return *this;
}


/*
 * mmpld::particle_view<T>::set_properties
 */
template<class T>
void mmpld::particle_view<T>::set_properties(const mmpld::list_header& header) {
    this->_colour_type = header.colour_type;
    this->_invalid_offset = mmpld::get_offsets<size_type>(header,
        this->_position_offset, this->_radius_offset, this->_colour_offset);
    this->_stride = mmpld::get_stride<size_type>(header);
    this->_vertex_type = header.vertex_type;
}
