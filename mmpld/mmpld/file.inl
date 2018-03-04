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
        list_header& header, void *dst, const size_type cnt) {
    mmpld::read_list_header(this->_file, header);
    auto stride = mmpld::get_stride<size_type>(header);
    auto retval = static_cast<size_type>(cnt / stride);

    if (dst != nullptr) {
        io_traits_type::read(this->_file, dst, retval * stride);
    }

    if (retval < header.particles) {
        auto missing = (header.particles - retval) * stride;
        auto offset = io_traits_type::tell(this->_file);
        io_traits_type::seek(this->_file, offset + missing);
    }

    return retval;
}


/*
 *
 */
template<class F, class C>
std::vector<std::uint8_t> mmpld::file<F, C>::read_particles(
        list_header& header) {
    mmpld::read_list_header(this->_file, header);
    auto size = mmpld::get_size(header);

    std::vector<std::uint8_t> retval(size);
    io_traits_type::read(this->_file, retval.data(), size);

    return retval;
}
