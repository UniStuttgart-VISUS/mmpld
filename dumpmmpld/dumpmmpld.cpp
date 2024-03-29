// <copyright file="dumpmmpld.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2018 - 2022 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "stdafx.h"


/// <summary>
/// Find (case-insensitively) the given switch in the given range.
/// </summary>
template<class I, class T> I FindSwitch(I begin, I end, const T *name) {
    std::basic_string<T> n(name);
    return std::find_if(begin, end, [&n](const std::basic_string<T>& s) {
        return ((n.length() == s.length())
            && std::equal(n.cbegin(), n.cend(), s.cbegin(),
            [](T l, T r) { return (std::tolower(l) == std::tolower(r)); }));
    });
}

/// <summary>
/// Find (case-insensitively) the given switch and return its argument.
/// </summary>
template<class I, class T> I FindArgument(I begin, I end, const T *name) {
    auto retval = ::FindSwitch(begin, end, name);
    return (retval != end) ? ++retval : retval;
}


/// <summary>
/// Entry point of dumpmmpld.
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int _tmain(const int argc, const _TCHAR **argv) {
    const std::vector<std::basic_string<_TCHAR>> CMD_LINE(argv, argv + argc);

    {
        auto it = ::FindSwitch(CMD_LINE.begin(), CMD_LINE.end(), _T("/nologo"));
        if (it == CMD_LINE.end()) {
            std::tcout << _T("dumpmmpld ") << MMPLD_API_MAJOR_VERSION << _T(".")
                << MMPLD_API_MINOR_VERSION << std::endl;
            std::tcout << _T("Copyright (C) 2018 - 2022 ")
                _T("Visualisierungsinstitut der Universität Stuttgart.")
                << std::endl;
            std::tcout << _T("Alle Rechte vorbehalten.") << std::endl;
            std::tcout << std::endl;
        }
    }

    try {
        auto cntSamples = 0;
        std::basic_string<_TCHAR> path;
        std::vector<std::uint8_t> sampleData;

        {
            auto it = ::FindArgument(CMD_LINE.begin(), CMD_LINE.end(),
                _T("/path"));
            if (it != CMD_LINE.end()) {
                path = *it;
            } else {
                throw std::runtime_error("The mandatory command line argument "
                    "/path is missing.");
            }
        }

        {
            auto it = ::FindArgument(CMD_LINE.begin(), CMD_LINE.end(),
                _T("/samples"));
            if (it != CMD_LINE.end()) {
                cntSamples = ::_ttoi(it->c_str());
                auto maxStride = mmpld::particle_traits<
                    mmpld::vertex_type::double_xyz,
                    mmpld::colour_type::rgba32>::stride();
                sampleData.resize(cntSamples * maxStride);
            }
        }

        std::tcout << _T("Path            : ")
            << path << std::endl;
        mmpld::file<HANDLE, _TCHAR> file(path.c_str());

        /* Dump information from MMPLD file header. */
        {
            unsigned int major, minor;
            file.version(major, minor);
            std::tcout << _T("Version         : ") 
                << major << _T(".") << minor
                << std::endl;
        }

        std::tcout << _T("Frames          : ")
            << file.file_header().frames
            << std::endl;

        std::tcout << _T("Bounding Box    : (")
            << file.file_header().bounding_box[0] << _T(", ")
            << file.file_header().bounding_box[1] << _T(", ")
            << file.file_header().bounding_box[2] << _T(") - (")
            << file.file_header().bounding_box[3] << _T(", ")
            << file.file_header().bounding_box[4] << _T(", ")
            << file.file_header().bounding_box[5] << _T(")")
            << std::endl;

        std::tcout << _T("Clipping Box    : (")
            << file.file_header().clipping_box[0] << _T(", ")
            << file.file_header().clipping_box[1] << _T(", ")
            << file.file_header().clipping_box[2] << _T(") - (")
            << file.file_header().clipping_box[3] << _T(", ")
            << file.file_header().clipping_box[4] << _T(", ")
            << file.file_header().clipping_box[5] << _T(")")
            << std::endl;

        /* Dump all frames. */
        for (decltype(file)::frame_number_type f = 0; f < file.frames(); ++f) {
            file.open_frame(f);

            std::tcout << std::endl;
            std::tcout << _T("Frame           : ")
                << file.frame()
                << std::endl;

            std::tcout << _T("Particle lists  : ")
                << file.frame_header().lists
                << std::endl;

            std::tcout << _T("Timestamp       : ")
                << file.frame_header().timestamp
                << std::endl;

            /* Dump all lists. */
            for (auto l = 0; l < file.frame_header().lists; ++l) {
                mmpld::list_header listHeader;
                file.read_particles(true, listHeader, sampleData.data(),
                    sampleData.size());

                std::tcout << std::endl;
                std::tcout << _T("Frame           : ")
                    << file.frame()
                    << std::endl;

                std::tcout << _T("List            : ")
                    << l
                    << std::endl;

                std::tcout << _T("Particles       : ")
                    << listHeader.particles
                    << std::endl;

                std::tcout << _T("Particle type   : ")
                    << mmpld::to_string<_TCHAR>(listHeader.vertex_type)
                    << std::endl;

                std::tcout << _T("Global radius   : ")
                    << listHeader.radius
                    << std::endl;

                std::tcout << _T("Colour type     : ")
                    << mmpld::to_string<_TCHAR>(listHeader.colour_type)
                    << std::endl;

                std::tcout << _T("Global colour   : ")
                    << listHeader.colour[0] << _T(", ")
                    << listHeader.colour[1] << _T(", ")
                    << listHeader.colour[2] << _T(", ")
                    << listHeader.colour[3]
                    << std::endl;

                std::tcout << _T("Intensity range : ")
                    << listHeader.min_intensity << _T(" - ")
                    << listHeader.max_intensity
                    << std::endl;

                if (file.file_header().version >= mmpld::make_version(1, 3)) {
                    std::tcout << _T("Bounding Box    : (")
                        << listHeader.bounding_box[0] << _T(", ")
                        << listHeader.bounding_box[1] << _T(", ")
                        << listHeader.bounding_box[2] << _T(") - (")
                        << listHeader.bounding_box[3] << _T(", ")
                        << listHeader.bounding_box[4] << _T(", ")
                        << listHeader.bounding_box[5] << _T(")")
                        << std::endl;
                }

                /* Dump sample data if any. */
                if (cntSamples > 0) {
                    typedef mmpld::colour_type c_t;
                    typedef mmpld::vertex_type v_t;

                    mmpld::particle_view<std::uint8_t> sampleView(
                        listHeader.vertex_type,
                        listHeader.colour_type,
                        sampleData.data());

                    // Print header.
                    std::tcout << std::endl << _T("First ") << cntSamples
                        << _T(" particle(s):") << std::endl;
                    std::tcout << std::setw(10) << _T("x")
                        << std::setw(10) << _T("y")
                        << std::setw(10) << _T("z")
                        << std::setw(10) << _T("radius");
                    switch (sampleView.colour_type()) {
                        case c_t::intensity:
                        case c_t::intensity64:
                            std::tcout << std::setw(40) << _T("intensity");
                            break;

                        case c_t::rgb32:
                        case c_t::rgb8:
                        case c_t::rgba32:
                        case c_t::rgba8:
                        case c_t::rgba16:
                            std::tcout << std::setw(10) << _T("r")
                                << std::setw(10) << _T("g")
                                << std::setw(10) << _T("b")
                                << std::setw(10) << _T("a");
                            break;
                    }
                    std::tcout << std::endl;

                    // Print rows.
                    for (auto i = 0; i < cntSamples; ++i) {
                        switch (sampleView.vertex_type()) {
                            case v_t::float_xyz:
                                std::tcout << std::setw(10)
                                    << sampleView.position<v_t::float_xyz>()[0]
                                    << std::setw(10)
                                    << sampleView.position<v_t::float_xyz>()[1]
                                    << std::setw(10)
                                    << sampleView.position<v_t::float_xyz>()[2]
                                    << std::setw(10)
                                    << _T("-");
                                break;

                            case v_t::float_xyzr:
                                std::tcout << std::setw(10)
                                    << sampleView.position<v_t::float_xyzr>()[0]
                                    << std::setw(10)
                                    << sampleView.position<v_t::float_xyzr>()[1]
                                    << std::setw(10)
                                    << sampleView.position<v_t::float_xyzr>()[2]
                                    << std::setw(10)
                                    << sampleView.position<v_t::float_xyzr>()[3];
                                break;

                            case v_t::short_xyz:
                                std::tcout << std::setw(10)
                                    << sampleView.position<v_t::short_xyz>()[0]
                                    << std::setw(10)
                                    << sampleView.position<v_t::short_xyz>()[1]
                                    << std::setw(10)
                                    << sampleView.position<v_t::short_xyz>()[2]
                                    << std::setw(10)
                                    << _T("-");
                                break;

                            case v_t::double_xyz:
                                std::tcout << std::setw(10)
                                    << sampleView.position<v_t::double_xyz>()[0]
                                    << std::setw(10)
                                    << sampleView.position<v_t::double_xyz>()[1]
                                    << std::setw(10)
                                    << sampleView.position<v_t::double_xyz>()[2]
                                    << std::setw(10)
                                    << _T("-");
                                break;
                        }

                        switch (sampleView.colour_type()) {
                            case c_t::intensity:
                                std::tcout << std::setw(40)
                                    << sampleView.colour<c_t::intensity>()[0];
                                break;

                            case c_t::rgb32:
                                std::tcout << std::setw(10)
                                    << sampleView.colour<c_t::rgb32>()[0]
                                    << std::setw(10)
                                    << sampleView.colour<c_t::rgb32>()[1]
                                    << std::setw(10)
                                    << sampleView.colour<c_t::rgb32>()[2]
                                    << std::setw(10)
                                    << _T("-");
                                break;

                            case c_t::rgb8:
                                std::tcout << std::setw(10)
                                    << sampleView.colour<c_t::rgb8>()[0]
                                    << std::setw(10)
                                    << sampleView.colour<c_t::rgb8>()[1]
                                    << std::setw(10)
                                    << sampleView.colour<c_t::rgb8>()[2]
                                    << std::setw(10)
                                    << _T("-");
                                break;

                            case c_t::rgba32:
                                std::tcout << std::setw(10)
                                    << sampleView.colour<c_t::rgba32>()[0]
                                    << std::setw(10)
                                    << sampleView.colour<c_t::rgba32>()[1]
                                    << std::setw(10)
                                    << sampleView.colour<c_t::rgba32>()[2]
                                    << std::setw(10)
                                    << sampleView.colour<c_t::rgba32>()[3];
                                break;

                            case c_t::rgba8:
                                std::tcout << std::setw(10)
                                    << sampleView.colour<c_t::rgba8>()[0]
                                    << std::setw(10)
                                    << sampleView.colour<c_t::rgba8>()[1]
                                    << std::setw(10)
                                    << sampleView.colour<c_t::rgba8>()[2]
                                    << std::setw(10)
                                    << sampleView.colour<c_t::rgba8>()[3];
                                break;

                            case c_t::rgba16:
                                std::tcout << std::setw(10)
                                    << sampleView.colour<c_t::rgba16>()[0]
                                    << std::setw(10)
                                    << sampleView.colour<c_t::rgba16>()[1]
                                    << std::setw(10)
                                    << sampleView.colour<c_t::rgba16>()[2]
                                    << std::setw(10)
                                    << sampleView.colour<c_t::rgba16>()[3];
                                break;

                            case c_t::intensity64:
                                std::tcout << std::setw(40)
                                    << sampleView.colour<c_t::intensity64>()[0];
                                break;
                        }

                        std::tcout << std::endl;
                        ++sampleView;
                    } /* end for (size_t i = 0; i < cntSamples; ++i) */
                } /* end if (cntSamples > 0) */

            } /* end for (auto l = 0; l < file.frame_header().lists; ++l) */
        } /* end for (size_t f = 0; f < file.frames(); ++f) */

        return 0;
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return -1;
    }

}
