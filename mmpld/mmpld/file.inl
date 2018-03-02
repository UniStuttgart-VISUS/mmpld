/// <copyright file="file.inl" company="Visualisierungsinstitut der Universit�t Stuttgart">
/// Copyright � 2018 Visualisierungsinstitut der Universit�t Stuttgart. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph M�ller</author>


/*
 * mmpld::file<F, C>::file
 */
template<class F, class C> mmpld::file<F, C>::file(const char_type *path) {
    detail::open(path, this->_file);
    read_file_header(this->_file, this->_file_header, this->_seek_table);
}
