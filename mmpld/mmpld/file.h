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
        /// Open the MMPLD file at the specified location.
        /// </summary>
        /// <param name="path">The path to the MMPLD file.</param>
        file(const char_type *path);

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        inline ~file(void) {
            detail::close(this->_file);
        }

        /// <summary>
        /// Gets the file header of the MMPLD data set.
        /// </summary>
        /// <returns>The MMPLD header.</returns>
        inline const mmpld::file_header& file_header(void) const {
            return this->file_header;
        }

    private:

        file_type _file;
        mmpld::file_header _file_header;
        mmpld::seek_table _seek_table;

    };

} /* end namespace mmpld */

#include "mmpld/file.inl"
