/// <copyright file="file.inl" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2018 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>


/*
 * mmpld::file<F, C>::file
 */
template<class F, class C> mmpld::file<F, C>::file(const char_type *path) {
    detail::zero_memory(this->_file_header);
    detail::zero_memory(this->_frame_header);

    // Open the file and read the header.
    io_traits_type::open(path, this->_file);
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
 * mmpld::file<F, C>::read_particles
 */
template<class F, class C>
typename mmpld::file<F, C>::size_type mmpld::file<F, C>::read_particles(
        const bool skip_remaining, list_header& header, void *dst,
        const size_type cnt) {
    mmpld::read_list_header(this->_file, header);
    auto retval =  this->read_particles(header, dst, cnt);

    if (skip_remaining && (retval < header.particles)) {
        auto stride = mmpld::get_stride<size_t>(header);
        auto cur = io_traits_type::tell(this->_file);
        auto rem = (header.particles - retval) * stride;
        io_traits_type::seek(this->_file, cur + rem);
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
        retval = header.particles;
    }

    if (dst != nullptr) {
        io_traits_type::read(this->_file, dst, retval * stride);
    }

    return retval;
}


/*
 *  mmpld::file<F, C>::read_particles
 */
template<class F, class C>
std::vector<std::uint8_t> mmpld::file<F, C>::read_particles(
        list_header& header) {
    this->read_particles(false, header, nullptr, 0);
    auto size = mmpld::get_size(header);

    std::vector<std::uint8_t> retval(size);
    this->read_particles(header, retval.data(), size);

    return retval;
}
