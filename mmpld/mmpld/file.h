/// <copyright file="file.h" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2018 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>

#pragma once

#include <stdexcept>

#include "mmpld/file_header.h"
#include "mmpld/frame_header.h"
#include "mmpld/list_header.h"


namespace mmpld {

    /// <summary>
    /// Representation of an MMPLD file.
    /// </summary>
    /// <tparam name="F">The type of the file stream to read. This can be either
    /// an <c>std::istream</c>, a file descriptor or a <c>FILE</c> handle.
    /// </tparam>
    /// <tparam name="C">The character type for strings, which defaults to
    /// <c>char</c>.</tparam>
    template<class F, class C = char> class file {

    public:

        /// <summary>
        /// The character type.
        /// </summary>
        typedef C char_type;

        /// <summary>
        /// The type of the file stream.
        /// </summary>
        typedef F file_type;

        /// <summary>
        /// The type used to reference a frame.
        /// </summary>
        typedef std::decay<decltype(mmpld::file_header::frames)>::type
            frame_number_type;

        /// <summary>
        /// The type for file sizes and counters.
        /// </summary>
        typedef size_t size_type;

        /// <summary>
        /// Open the MMPLD file at the specified location.
        /// </summary>
        /// <param name="path">The path to the MMPLD file.</param>
        /// <exception cref="std::invalid_argument">If the path is a
        /// <c>nullptr</c>.</exception>
        file(const char_type *path);

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        ~file(void);

        /// <summary>
        /// Gets the number of frames in the file.
        /// </summary>
        /// <returns>The number of frames in the file.</returns>
        inline size_type frames(void) const {
            return static_cast<size_type>(this->_file_header.frames);
        }

        /// <summary>
        /// Gets the file header of the MMPLD data set.
        /// </summary>
        /// <returns>The MMPLD header.</returns>
        inline const mmpld::file_header& file_header(void) const {
            return this->_file_header;
        }

        /// <summary>
        /// Reads the frame header of the given frame into
        /// <paramref name="header" /> and returns the offsets of the particle
        /// lists to <paramref name="oit" />.
        /// </summary>
        /// <tparam name="I">The type of the output iterator for the offsets,
        /// which must be either a back inserter or designate a range that is
        /// large enough to hold the offsets.</tparam>
        /// <param name="frame">The number of the frame to be read.</param>
        /// <param name="header">Receives the frame header.</param>
        /// <param name="oit">Receives the offsets of the list headers from the
        /// file in bytes.</param>
        /// <returns>The number of particle lists returned to
        /// <paramref name="oit" />.</returns>
        /// <exception cref="std::invalid_argument">If the
        /// <paramref name="frame" /> number is out of range.</exception>
        template<class I> size_type read_frame(const frame_number_type frame,
            frame_header& header, I oit);

        /// <summary>
        /// Gets the seek table for the MMPLD file.
        /// </summary>
        /// <returns>The seek table.</returns>
        inline const mmpld::seek_table& seek_table(void) const {
            return this->_seek_table;
        }

    private:

        typedef detail::io_traits<F, C> io_traits_type;

        file_type _file;
        mmpld::file_header _file_header;
        mmpld::seek_table _seek_table;

    };

} /* end namespace mmpld */

#include "mmpld/file.inl"
