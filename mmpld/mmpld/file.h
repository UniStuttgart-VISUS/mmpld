// <copyright file="file.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2018 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <stdexcept>

#include "mmpld/cluster_info.h"
#include "mmpld/file_header.h"
#include "mmpld/frame_header.h"
#include "mmpld/list_header.h"


namespace mmpld {

    /// <summary>
    /// Representation of an MMPLD file.
    /// </summary>
    /// <typeparam name="F">The type of the file stream to read. This can be either
    /// an <c>std::istream</c>, a file descriptor or a <c>FILE</c> handle.
    /// </typeparam>
    /// <typeparam name="C">The character type for strings, which defaults to
    /// <c>char</c>.</typeparam>
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
        /// The type used to reference a particle list.
        /// </summary>
        typedef std::decay<decltype(mmpld::frame_header::lists)>::type
            list_number_type;

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
        /// Reads cluster information from the current position in the file.
        /// </summary>
        /// <remarks>
        /// <para>This method has no effect on files having a version other than
        /// 1.1. The method does nothing in this case and the returned cluster
        /// information object is empty.</para>
        /// <para>The caller is responsible to call this method only if the file
        /// pointer is pointing to a cluster information block at the end of a
        /// particle list.</para>
        /// </remarks>
        /// <returns>The cluster information that has been read from the file.
        /// </returns>
        cluster_info read_cluster_info(void);

        /// <summary>
        /// Reads the begin of a particle list from the current position in the
        /// file.
        /// </summary>
        /// <remarks>
        /// <para>The method assumes that the file pointer stands at the begin
        /// of a particle list header. If this assumption does not hold, the
        /// results of the call are undefined!</para>
        /// <para>The list header will be read in any case and returned to
        /// <paramref name="header" />. For the actual data, the same operations
        /// are performed as for the overload in which the caller must provide
        /// the list header, ie the bounds of the memory block provided are
        /// honoured. This overload provides, however, the option to skip until
        /// the end of the particle list.</para>
        /// <para>Please not that it is important to consume the whole
        /// particle list or reset the file to a new frame as otherwise,
        /// subsequent operations might lead corrupt results! It is strongly
        /// recommended to use other overloads allocating the memory themselves
        /// instead of this method.</para>
        /// <para>If the file is MMPLD 1.1 and
        /// <paramref name="skip_remaining" /> is set <c>true</c>, the cluster
        /// information block will be skipped as well. Otherwise, the caller
        /// needs to process or skip the cluster information manually using
        /// <see cref="read_cluster_info" /> or
        /// <see cref="skip_cluster_info" />.</para>
        /// </remarks>
        /// <param name="skip_remaining">If <c>true</c>, skip all particle data
        /// that could not be returned to <paramref name="dst" />. This includes
        /// the cluster information at the end of the file. Cluster information
        /// will be skipped also in the case that all particles have been read.
        /// </param>
        /// <param name="header">Receives the list header.</param>
        /// <param name="dst">Receives at most <paramref name="cnt" /> bytes
        /// of particle data if not <c>nullptr</c>.</param>
        /// <param name="cnt">The number of bytes that can be written to
        /// <paramref name="dst" />.</param>
        /// <returns>The number of particles that has actually been read
        /// from the file</returns>
        size_type read_particles(const bool skip_remaining, list_header& header,
            void *dst, const size_type cnt);

        /// <summary>
        /// Reads particles from the current position in the file, assuming
        /// that <paramref name="header" /> is the list header of the list
        /// to be read.
        /// </summary>
        /// <remarks>
        /// <para>The method assumes that the file pointer stands on the begin
        /// of valid particle, eg after a particle list header. The results of
        /// a call to this method if this assumption does not hold are
        /// undefined!</para>
        /// <para>If <paramref name="dst" /> is not <c>nullptr</c>, it is
        /// assumed that <paramref name="cnt" /> bytes of data can be written
        /// to this location. In this case, the method will read as many
        /// particles as possible and store them to <paramref name="dst" />.
        /// Please note that only full particles are read, ie if
        /// <paramref name="cnt" /> is not divisible by the stride of the
        /// particles in the list, not the whole buffer will be filled. You
        /// can make subsequent calls this this method to read the rest
        /// of the list.</para>
        /// <para>Please note that it is important to consume the whole
        /// particle list or reset the file to a new frame as otherwise,
        /// subsequent operations might lead corrupt results! It is strongly
        /// recommended to use other overloads allocating the memory themselves
        /// instead of this method.</para>
        /// <para>Please also note that this variant of the method does not
        /// skip or read the cluster information at the end of a particle list
        /// in MMPLD 1.1 files. The caller needs to do this manually using
        /// <see cref="read_cluster_info" /> or
        /// <see cref="skip_cluster_info" />.</para>
        /// </remarks>
        /// <param name="header">The list header describing the particles.
        /// </param>
        /// <param name="dst">Receives at most <paramref name="cnt" /> bytes
        /// of particle data if not <c>nullptr</c>.</param>
        /// <param name="cnt">The number of bytes that can be written to
        /// <paramref name="dst" />.</param>
        /// <returns>The number of particles that have actually been read
        /// from the file</returns>
        size_type read_particles(const list_header& header, void *dst,
            const size_type cnt);

        /// <summary>
        /// Reads a particle list from the current position in the file.
        /// </summary>
        /// <param name="header">Receives the list header.</param>
        /// <param name="cluster">If not <c>nullptr</c>, receives the cluster
        /// information if the file version is 1.1. If <c>nullptr</c> and the
        /// file version is 1.1, the cluster information block will be
        /// discarded. If the file version is not 1.1, this parameter has no
        /// effect.</param>
        /// <returns>All particle data in the frame</returns>
        std::vector<std::uint8_t> read_particles(list_header& header,
            cluster_info *clusters = nullptr);

        /// <summary>
        /// Gets the seek table for the MMPLD file.
        /// </summary>
        /// <returns>The seek table.</returns>
        inline const mmpld::seek_table& seek_table(void) const {
            return this->_seek_table;
        }

        /// <summary>
        /// Skips cluster information from the current position in the file.
        /// </summary>
        /// <remarks>
        /// <para>This method has no effect on files having a version other than
        /// 1.1. The method does nothing in this case.</para>
        /// <para>The caller is responsible to call this method only if the file
        /// pointer is pointing to a cluster information block at the end of a
        /// particle list.</para>
        /// </remarks>
        void skip_cluster_info(void);

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
