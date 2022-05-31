// <copyright file="particle_view.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2018 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cassert>
#include <cstring>
#include <memory>

#include "mmpld/colour_type.h"
#include "mmpld/list_header.h"
#include "mmpld/vertex_type.h"


namespace mmpld {

    /// <summary>
    /// This structure allows for creating a runtime view on particle data.
    /// </summary>
    /// <remarks>
    /// <para><see cref="mmpld::particle_traits" /> is the compile-time
    /// equivalent of this class.</para>
    /// <para>Be aware that all pointer-based operations are unchecked!</para>
    /// </remarks>
    /// <tparam name="T">The value type of the pointer to be used. This
    /// parameter allows for controlling the const-ness of the view.</tparam>
    template<class T = const void> class particle_view {

    public:

        /// <summary>
        /// A pointer compatible with <see cref="pointer_type" /> wrt.
        /// constness.
        /// </summary>
        template<class Tp>
        using const_compatible_type = typename std::conditional<
            std::is_const<T>::value, 
            const typename std::remove_const<Tp>::type,
            typename std::remove_const<Tp>::type>::type;

        /// <summary>
        /// The type of the data pointer.
        /// </summary>
        typedef T *pointer_type;

        /// <summary>
        /// The type to measure sizes.
        /// </summary>
        typedef size_t size_type;

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="vertex_type">The type of the positional information.
        /// </param>
        /// <param name="colour_type">The type of the colour information.
        /// </param>
        /// <param name="data">The pointer to the data, which defaults to
        /// <c>nullptr</c>.</param>
        particle_view(const mmpld::vertex_type vertex_type,
            const mmpld::colour_type colour_type, pointer_type data = nullptr);

        /// <summary>
        /// Clones <paramref name="rhs" />.
        /// <summary>
        /// <param name="rhs">The object to be cloned.</param>
        inline particle_view(const particle_view& rhs)
            : _colour_offset(rhs._colour_offset),
            _colour_type(rhs._colour_type),
            _data(rhs._data),
            _invalid_offset(rhs._invalid_offset),
            _position_offset(rhs._position_offset),
            _radius_offset(rhs._radius_offset),
            _stride(rhs._stride),
            _vertex_type(rhs._vertex_type) { }

        /// <summary>
        /// Moves <paramref name="rhs" />.
        /// <summary>
        /// <param name="rhs">The object to be moved.</param>
        inline particle_view(particle_view&& rhs) {
            *this = std::move(rhs);
        }

        /// <summary>
        /// Advances the data pointer by the stride of one particle.
        /// </summary>
        inline void advance(void) {
            assert(this->good());
            auto d = this->byte_data();
            this->_data = (d + this->stride());
        }

        /// <summary>
        /// Zero the memory of the particle.
        /// </summary>
        void clear(void) {
            assert(this->good());
            ::memset(this->_data, 0, this->stride());
        }

        /// <summary>
        /// Answer the data as pointer with byte-wise increment.
        /// </summary>
        /// <returns>The data pointer.</returns>
        inline const_compatible_type<std::uint8_t> *byte_data(void) {
            return reinterpret_cast<const_compatible_type<std::uint8_t> *>(
                this->_data);
        }

        /// <summary>
        /// Provide access to the first colour component if any.
        /// </summary>
        /// <returns>The first colour component or <c>nullptr</c>.</returns>
        pointer_type colour(void);

        /// <summary>
        /// Provide access to the first colour component if any.
        /// </summary>
        /// <tparam name="Tp">The type to which the returned pointer should be
        /// casted.</tparam>
        /// <returns>The first colour component or <c>nullptr</c>.</returns>
        template<class Tp> inline Tp *colour(void) {
            return reinterpret_cast<Tp *>(this->colour());
        }

        /// <summary>
        /// Provide access to the first colour component if any.
        /// </summary>
        /// <tparam name="Tp">The <see cref="mmpld::colour_type" /> which
        /// determines the type of the pointer being returned.</tparam>
        /// <returns>The first colour component or <c>nullptr</c>.</returns>
        template<mmpld::colour_type Tp>
        const_compatible_type<typename mmpld::colour_traits<Tp>::value_type> *
        colour(void) {
            typedef typename mmpld::colour_traits<Tp>::value_type v_t;
            assert(Tp == this->_colour_type);
            return this->colour<const_compatible_type<v_t>>();
        }

        /// <summary>
        /// Answer the type of the colour data.
        /// </summary>
        /// <returns>The type of the colour data.</returns>
        inline mmpld::colour_type colour_type(void) const {
            return this->_colour_type;
        }

        /// <summary>
        /// Answer the current data pointer.
        /// </summary>
        /// <returns>The current data pointer.</returns>
        inline pointer_type data(void) {
            return this->_data;
        }

        /// <summary>
        /// Answer whether the particle view holds a non-null pointer.
        /// </summary>
        /// <returns><c>true</c> if the data pointer is not <c>nullptr</c>,
        /// <c>false</c> otherwise.</returns>
        inline bool good(void) const {
            return (this->_data != nullptr);
        }

        /// <summary>
        /// Provide access to the first position component if any.
        /// </summary>
        /// <returns>The first position component or <c>nullptr</c>.</returns>
        pointer_type position(void);

        /// <summary>
        /// Provide access to the first position component if any.
        /// </summary>
        /// <tparam name="Tp">The type to which the returned pointer should be
        /// casted.</tparam>
        /// <returns>The first position component or <c>nullptr</c>.</returns>
        template<class Tp> inline Tp *position(void) {
            return reinterpret_cast<Tp *>(this->position());
        }

        /// <summary>
        /// Provide access to the first position component if any.
        /// </summary>
        /// <tparam name="Tp">The <see cref="mmpld::vertex_type" /> which
        /// determines the type of the pointer being returned.</tparam>
        /// <returns>The first position component or <c>nullptr</c>.</returns>
        template<mmpld::vertex_type Tp>
        const_compatible_type<typename mmpld::vertex_traits<Tp>::value_type> *
        position(void) {
            typedef typename mmpld::vertex_traits<Tp>::value_type v_t;
            assert(Tp == this->_vertex_type);
            return this->position<const_compatible_type<v_t>>();
        }

        /// <summary>
        /// Answer the type of the vertex data.
        /// </summary>
        /// <returns>The type of the vertex data.</returns>
        inline mmpld::vertex_type position_type(void) const {
            return this->_vertex_type;
        }

        /// <summary>
        /// Provide access to the radius if any.
        /// </summary>
        /// <returns>The radius or <c>nullptr</c>.</returns>
        pointer_type radius(void);

        /// <summary>
        /// Provide access to the radius if any.
        /// </summary>
        /// <tparam name="Tp">The type to which the returned pointer should be
        /// casted.</tparam>
        /// <returns>The radius or <c>nullptr</c>.</returns>
        template<class Tp> inline Tp *radius(void) {
            return reinterpret_cast<Tp *>(this->radius());
        }

        /// <summary>
        /// Provide access to the radius if any.
        /// </summary>
        /// <tparam name="Tp">The <see cref="mmpld::vertex_type" /> which
        /// determines the type of the pointer being returned.</tparam>
        /// <returns>The radius or <c>nullptr</c>.</returns>
        template<mmpld::vertex_type Tp>
        const_compatible_type<typename mmpld::vertex_traits<Tp>::value_type> *
        radius(void) {
            typedef typename mmpld::vertex_traits<Tp>::value_type v_t;
            assert(Tp == this->_vertex_type);
            return this->radius<const_compatible_type<v_t>>();
        }

        /// <summary>
        /// Resets the data pointer of the view.
        /// </summary>
        /// <param name="data">The new data pointer, which defaults to
        /// <c>nullptr</c>.</param>
        inline void reset(pointer_type data = nullptr) {
            this->_data = data;
        }

        /// <summary>
        /// Gets the particle stride.
        /// </summary>
        /// <returns>The particle stride in bytes.</returns>
        inline size_type stride(void) const {
            return this->_stride;
        }

        /// <summary>
        /// Answer the type of the vertex data.
        /// </summary>
        /// <returns>The type of the vertex data.</returns>
        inline mmpld::vertex_type vertex_type(void) const {
            return this->_vertex_type;
        }

        /// <summary>
        /// Assignment.
        /// </summary>
        /// <param name="rhs">The right-hand side operand.</param>
        /// <returns><c>*this</c>.</returns>
        particle_view& operator =(const particle_view& rhs);

        /// <summary>
        /// Move assignment.
        /// </summary>
        /// <param name="rhs">The right-hand side operand.</param>
        /// <returns><c>*this</c>.</returns>
        particle_view& operator =(particle_view&& rhs);

        /// <summary>
        /// Advance the data pointer and return the new view.
        /// </summary>
        /// <returns><c>this</c>.</returns>
        inline particle_view& operator ++(void) {
            this->advance();
            return *this;
        }

        /// <summary>
        /// Advance the data pointer and return the previous view.
        /// </summary>
        /// <returns>A copy of the previous state of the view.</returns>
        inline particle_view& operator ++(int) {
            auto retval = *this;
            this->advance();
            return retval;
        }

        /// <summary>
        /// Answer whether the particle view holds a non-null pointer.
        /// </summary>
        /// <returns><c>true</c> if the data pointer is not <c>nullptr</c>,
        /// <c>false</c> otherwise.</returns>
        inline operator bool(void) const {
            return this->good();
        }

    private:

        size_type _colour_offset;
        mmpld::colour_type _colour_type;
        pointer_type _data;
        size_type _invalid_offset;
        size_type _position_offset;
        size_type _radius_offset;
        size_type _stride;
        mmpld::vertex_type _vertex_type;
    };

} /* end namespace mmpld */

#include "mmpld/particle_view.inl"
