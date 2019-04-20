/// <copyright file="cluster_info.h" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2019 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>
#include <memory>
#include <vector>

#include "mmpld/io.h"


namespace mmpld {

    /// <summary>
    /// Represents per-particle list clustering data specific to MMPLD 1.1.
    /// </summary>
    class cluster_info {

    public:

        /// <summary>
        /// The index type used to represent the contents of the cluster.
        /// </summary>
        typedef std::uint32_t index_type;

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        inline cluster_info(void) : _count(0) { }

        /// <summary>
        /// Moves <paramref name="rhs" /> to a new object.
        /// </summary>
        /// <param name="rhs">The object to be moved.</param>
        inline cluster_info(cluster_info&& rhs)
                : _count(rhs._count), _data(std::move(rhs._data)) {
            rhs._count = 0;
            assert(rhs._data.empty());
        }

        /// <summary>
        /// Answer the number of clusters.
        /// </summary>
        /// <returns>The number of clusters.</returns>
        inline std::size_t count(void) const {
            return this->_count;
        }

        /// <summary>
        /// Answer the raw cluster data.
        /// </summary>
        /// <returns>The raw cluster data.</returns>
        inline const std::vector<index_type>& data(void) const {
            return this->_data;
        }

        /// <summary>
        /// Move assignment.
        /// </summary>
        /// <param name="rhs">The object to be moved.</param>
        /// <returns><c>*this</c>.</returns>
        inline cluster_info& operator =(cluster_info&& rhs) {
            if (this != std::addressof(rhs)) {
                this->_count = rhs._count;
                rhs._count = 0;
                this->_data = std::move(rhs._data);
                assert(rhs._data.empty());
            }
            return *this;
        }

    private:

        std::size_t _count;
        std::vector<index_type> _data;

        /* Allow 'read_cluster_info' filling in the data. */
        template<class F> friend cluster_info read_cluster_info(F&);
    };

    /// <summary>
    /// Reads a <see cref="cluster_info" /> from <paramref name="file" />.
    /// </summary>
    /// <remarks>
    /// The caller is responsible to ensure that the file pointer is currently
    /// at the begin or a cluster information. This is the case at the end of a
    /// particle list in MMPLD 1.1 files only.
    /// </remarks>
    /// <typeparam name="F">The type of the file handle to read from.
    /// </typeparam>
    /// <param name="file">The handle of an MMPLD file to read a cluster
    /// information from </param>
    /// <returns>The cluster information that has been read.</returns>
    template<class F> cluster_info read_cluster_info(F& file);

    /// <summary>
    /// Skips a cluster information block in <paramref name="file" />.
    /// </summary>
    /// <remarks>
    /// The caller is responsible to ensure that the file pointer is currently
    /// at the begin or a cluster information. This is the case at the end of a
    /// particle list in MMPLD 1.1 files only.
    /// </remarks>
    /// <typeparam name="F">The type of the file handle to read from.
    /// </typeparam>
    /// <param name="file">The handle of an MMPLD file to skip a cluster
    /// information in.</param>
    template<class F> void skip_cluster_info(F& file);

} /* end namespace mmpld */

#include "mmpld/cluster_info.inl"
