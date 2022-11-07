// <copyright file="file.inl" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2018 Visualisierungsinstitut der Universit�t Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph M�ller</author>


/*
 * mmpld::file<F, C>::file
 */
template<class F, class C> mmpld::file<F, C>::file(const char_type *path) {
    detail::zero_memory(this->_file_header);
    detail::zero_memory(this->_frame_header);

    // Open the file and read the header.
    io_traits_type::open_read(path, this->_file);
    read_file_header(this->_file, this->_file_header, this->_seek_table);

    // Read the first frame.
    this->open_frame(0);
}


/*
 * mmpld::file<F, C>::~file
 */
template<class F, class C> mmpld::file<F, C>::~file(void) {
    io_traits_type::close(this->_file);
}


/*
 * mmpld::file<F, C>::open_frame
 */
template<class F, class C>
void mmpld::file<F, C>::open_frame(const frame_number_type frame) {
    if (frame >= this->_seek_table.size()) {
        throw std::invalid_argument("The index of the requested frame is out "
            "of range.");
    }

    auto offset = static_cast<size_t>(this->_seek_table[frame]);
    io_traits_type::seek(this->_file, offset);
    read_frame_header(this->_file, this->_file_header.version,
        this->_frame_header);
}


/*
 * mmpld::file<F, C>::read_cluster_info
 */
template<class F, class C>
mmpld::cluster_info mmpld::file<F, C>::read_cluster_info(void) {
    if (this->_file_header.version == mmpld::make_version(1, 1)) {
        return mmpld::read_cluster_info(this->_file);
    } else {
        return cluster_info();
    }
}


/*
 * mmpld::file<F, C>::read_particles
 */
template<class F, class C>
typename mmpld::file<F, C>::size_type mmpld::file<F, C>::read_particles(
        const bool skip_remaining, list_header& header, void *dst,
        const size_type cnt) {
    mmpld::read_list_header(this->_file, this->_file_header.version, header);
    auto retval =  this->read_particles(header, dst, cnt);

    if (skip_remaining && (retval <= header.particles)) {
        auto stride = mmpld::get_stride<size_t>(header);
        auto cur = io_traits_type::tell(this->_file);
        auto rem = (header.particles - retval) * stride;
        io_traits_type::seek(this->_file, cur + rem);

        if (this->_file_header.version == mmpld::make_version(1, 1)) {
            // MMPLD 1.1 needs to skip the cluster information block as well.
            mmpld::skip_cluster_info(this->_file);
        }
    }

    return retval;
}


/*
 * mmpld::file<F, C>::read_particles
 */
template<class F, class C>
typename mmpld::file<F, C>::size_type mmpld::file<F, C>::read_particles(
        const list_header& header, void *dst, const size_type cnt) {
    auto stride = mmpld::get_stride<size_type>(header);
    auto retval = static_cast<size_type>(cnt / stride);

    if (retval > header.particles) {
        retval = static_cast<size_type>(header.particles);
    }

    if (dst != nullptr) {
        auto read = io_traits_type::read(this->_file, dst, retval * stride);

        if (read < static_cast<decltype(read)>(retval * stride)) {
            throw std::runtime_error("The end of file was reached before the "
                "requested number of particles could be read.");
        }
    }

    return retval;
}


/*
 *  mmpld::file<F, C>::read_particles
 */
template<class F, class C>
std::vector<std::uint8_t> mmpld::file<F, C>::read_particles(
        list_header& header, cluster_info *clusters) {
    this->read_particles(false, header, nullptr, 0);
    auto size = mmpld::get_size<std::size_t>(header);

    std::vector<std::uint8_t> retval(size);
    this->read_particles(header, retval.data(), size);

    if (clusters != nullptr) {
        *clusters = this->read_cluster_info();
    } else {
        this->skip_cluster_info();
    }

    return retval;
}


/*
 * mmpld::file<F, C>::skip_cluster_info
 */
template<class F, class C>
void mmpld::file<F, C>::skip_cluster_info(void) {
    if (this->_file_header.version == mmpld::make_version(1, 1)) {
        return mmpld::skip_cluster_info(this->_file);
    }
}

