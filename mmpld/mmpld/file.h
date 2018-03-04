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
        /// Gets the file header of the MMPLD data set.
        /// </summary>
        /// <returns>The MMPLD header.</returns>
        inline const mmpld::file_header& file_header(void) const {
            return this->_file_header;
        }

        /// <summary>
        /// Gets the number of the currently opened frame.
        /// <summary>
        /// <returns>The number of the current frame.</returns>
        inline frame_number_type frame(void) const {
            return this->_frame;
        }

        /// <summary>
        /// Gets the number of frames in the file.
        /// </summary>
        /// <returns>The number of frames in the file.</returns>
        inline size_type frames(void) const {
            return static_cast<size_type>(this->_file_header.frames);
        }

        /// <summary>
        /// Gets the header of the current frame.
        /// </summary>
        /// <returns>The header of the current frame.</returns>
        inline const mmpld::frame_header& frame_header(void) const {
            return this->_frame_header;
        }

        /// <summary>
        /// Opens the frame with the given number and makes it the current
        /// frame.
        /// </summary>
        /// <param name="frame">The zero-based number of the frame to open.
        /// </param>
        /// <exception cref="std::invalid_argument">If the given frame number is
        /// out of range, ie <see cref="frames" /> or larger.</exception>
        void open_frame(const frame_number_type frame);

        /// <summary>
        /// Gets the seek table for the MMPLD file.
        /// </summary>
        /// <returns>The seek table.</returns>
        inline const mmpld::seek_table& seek_table(void) const {
            return this->_seek_table;
        }

        /// <summary>
        /// Gets the MMPLD version from the file header.
        /// </summary>
        /// <param name="major"></param>
        /// <param name="minor"></param>
        inline void version(unsigned int& major, unsigned int& minor) const {
            mmpld::parse_version(this->_file_header.version, major, minor);
        }

    private:

        typedef detail::io_traits<F, C> io_traits_type;

        file_type _file;
        mmpld::file_header _file_header;
        frame_number_type _frame;
        mmpld::frame_header _frame_header;
        mmpld::seek_table _seek_table;

    };

} /* end namespace mmpld */

#include "mmpld/file.inl"
