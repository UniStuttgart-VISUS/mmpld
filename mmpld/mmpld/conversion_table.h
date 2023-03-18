// <copyright file="conversion_table.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2018 - 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <type_traits>
#include <unordered_map>

#include "mmpld/colour_properties.h"
#include "mmpld/convert_colour.h"
#include "mmpld/convert_position.h"
#include "mmpld/enum_dispatch_list.h"
#include "mmpld/vertex_properties.h"


/// <summary>
/// Hash specialisation for pairs of <see cref="mmpld::vertex_type" />, which
/// are used to identify conversions.
/// </summary>
template<> struct std::hash<std::pair<mmpld::vertex_type, mmpld::vertex_type>> {

    typedef std::pair<mmpld::vertex_type, mmpld::vertex_type> value_type;

    inline std::size_t operator ()(const value_type& value) const noexcept {
        static_assert(std::is_same<value_type::first_type,
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
template<> struct std::hash<std::pair<mmpld::colour_type, mmpld::colour_type>> {

    typedef std::pair<mmpld::colour_type, mmpld::colour_type> value_type;

    inline std::size_t operator ()(const value_type& value) const noexcept {
        static_assert(std::is_same<value_type::first_type,
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
    /// Identifies a colour conversion from type <c>second</c> to
    /// <c>first</c>.
    /// </summary>
    typedef std::pair<colour_type, colour_type> colour_pair;

    /// <summary>
    /// Identifies a position conversion from type <c>second</c> to
    /// <c>first</c>.
    /// </summary>
    typedef std::pair<vertex_type, vertex_type> vertex_pair;

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
    /// <typeparam name="Vs">The individual enumeration values, which is
    /// used with an <see cref="enum_dispatch_list" /> to automatically
    /// resolve the runtime values.</typeparam>
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
    /// conversion at runtime. The key of the returned map is an
    /// <see cref="std::pair" /> of the target and the source value of this
    /// type.</typeparam>
    /// <typeparam name="T">The compile-time conversion table, which is an
    /// <see cref="std::tuple" /> of values of <typeparamref name="E" />
    /// generated by <see cref="make_conversion_table3" />.</typeparam>
    /// <typeparam name="F">The type of the conversion function, which is
    /// typically an instance of <see cref="std::function" />that receives a
    /// constant input pointer and a non-constant output pointer.</typeparam>
    /// <typeparam name="Is">A index sequence for sequentially expanding the
    /// tuple.</typeparam>
    /// <returns></returns>
    template<class E, class T, class F, std::size_t... Is>
    inline std::unordered_map<std::pair<E, E>, F>
    make_conversion_table2(std::index_sequence<Is...>, T table) {
        typedef std::unordered_map<std::pair<E, E>, F> table_type;
        return table_type { std::get<Is>(table)... };
    }

    /// <summary>
    /// Generates an index sequence that allows
    /// <see cref="make_conversion_table2" /> expanding the tuple generated
    /// by <see cref="make_conversion_table3" />.
    /// </summary>
    /// <typeparam name="M">The type of the runtime lookup table to be generated
    /// by this function. This must be an <see cref="std::unordered_map" /> from
    /// a pair of enumeration values to a conversion functor.</typeparam>
    /// <typeparam name="T">Cf. <see cref="make_conversion_table2" />.
    /// </typeparam>
    /// <param name="table"></param>
    /// <returns></returns>
    template<class M, class T>
    M make_conversion_table1(T table) {
        typedef typename M::key_type key_type;
        typedef typename key_type::first_type enum_type;
        static_assert(std::is_same<typename key_type::second_type,
            enum_type>::value, "Source and destination of a runtime conversion "
            "must be of the same type.");
        typedef typename M::mapped_type func_type;
        return make_conversion_table2<enum_type, T, func_type>(
            std::make_index_sequence<std::tuple_size<T>::value> { }, table);
    }

    /// <summary>
    /// Builds a hash table that allows for looking up a conversion function for
    /// two <see cref="colour_type" />s.
    /// </summary>
    /// <returns></returns>
    inline const std::unordered_map<colour_pair, conversion_function>&
    make_colour_conversion_table() {
        // Note: compile-time table cannot be typedef'd!
        typedef std::unordered_map<colour_pair, conversion_function>
            runtime_table_type;
        static const auto retval = make_conversion_table1<runtime_table_type>(
            make_conversion_table3<colour_type, colour_traits>(
            colour_dispatch_list { }));
        return retval;
    }

    /// <summary>
    /// Builds a hash table that allows for looking up a conversion function for
    /// two <see cref="vertex_type" />s.
    /// </summary>
    /// <returns></returns>
    inline const std::unordered_map<vertex_pair, conversion_function>&
    make_vertex_conversion_table() {
        // Note: compile-time table cannot be typedef'd!
        typedef std::unordered_map<vertex_pair, conversion_function>
            runtime_table_type;
        static const auto retval = make_conversion_table1<runtime_table_type>(
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

} /* end namespace detail */
} /* end namespace mmpld */
