/// <copyright file="file.inl" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2018 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>


/*
 * mmpld::file<F, C>::file
 */
template<class F, class C> mmpld::file<F, C>::file(const char_type *path) {
    detail::zero_memory(this->_file_header);
    io_traits_type::open(path, this->_file);
    read_file_header(this->_file, this->_file_header, this->_seek_table);
}


/*
 * mmpld::file<F, C>::~file
 */
template<class F, class C> mmpld::file<F, C>::~file(void) {
    io_traits_type::close(this->_file);
}


/*
 * mmpld::file<F, C>::read_frame
 */
template<class F, class C>
template<class I> size_t mmpld::file<F, C>::read_frame(
        const frame_number_type frame, frame_header& header, I oit) {
    size_t retval = 0;
    if (frame >= this->_seek_table.size()) {
        throw std::invalid_argument("The index of the requested frame is "
            "out of range.");
    }

    io_traits_type::seek(this->_file, this->_seek_table[frame]);
    //this->_seek_table[frame]

    return retval;
}
