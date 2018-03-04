/// <copyright file="file.inl" company="Visualisierungsinstitut der Universit�t Stuttgart">
/// Copyright � 2018 Visualisierungsinstitut der Universit�t Stuttgart. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph M�ller</author>


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

    io_traits_type::seek(this->_file,
        static_cast<size_t>(this->_seek_table[frame]));
    read_frame_header(this->_file, this->_file_header.version,
        this->_frame_header);
}
