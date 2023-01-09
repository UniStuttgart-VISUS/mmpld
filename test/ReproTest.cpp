// <copyright file="ReproTest.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "stdafx.h"
#include "CppUnitTest.h"

#include "util.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace test {

    /// <summary>
    /// Test cases for reproducing bug reports.
    /// </summary>
    TEST_CLASS(ReproTest) {

    public:

        TEST_METHOD(TestTischler001Convert) {
            typedef mmpld::particle_traits<mmpld::vertex_type::none, mmpld::colour_type::rgba32> ColorFormat;
            typedef mmpld::particle_traits<mmpld::vertex_type::float_xyz, mmpld::colour_type::none> PositionFormat;

            mmpld::file_header fileHeader;
            mmpld::frame_header frameHeader;
            mmpld::list_header listHeader;
            mmpld::seek_table seekTable;

            std::vector<uint8_t> buffer;
            std::ifstream file;
            std::vector<uint8_t> particles;

            file.open("test_xyz_double_rgb_float.mmpld", std::ios::binary);
            Assert::IsTrue(file.is_open(), L"Test file has been opened.", LINE_INFO());

            mmpld::read_file_header(file, fileHeader, seekTable);

            file.seekg(seekTable[0]), L"Seek to frame", LINE_INFO();

            mmpld::read_frame_header(file, fileHeader.version, frameHeader);

            for (decltype(frameHeader.lists) l = 0; l < frameHeader.lists; ++l) {
                mmpld::read_list_header(file, fileHeader.version, listHeader);
                const auto cnt = static_cast<std::size_t>(listHeader.particles);

                buffer.resize(mmpld::get_size<std::size_t>(listHeader));
                Assert::IsTrue(!file.read((char *) buffer.data(), cnt), L"Read particle data.", LINE_INFO());

                if (fileHeader.version == mmpld::make_version(1, 1)) {
                    mmpld::skip_cluster_info(file);
                }

                particles.resize(PositionFormat::size(cnt));
                mmpld::convert<PositionFormat>(buffer.data(), listHeader, particles.data(), cnt);

                //particles.resize(ColorFormat::size(cnt));
                //mmpld::convert<ColorFormat>(buffer.data(), listHeader, particles.data(), cnt);

                auto targetListHeader = listHeader;
                targetListHeader.vertex_type = mmpld::vertex_type::float_xyz;
                targetListHeader.colour_type = mmpld::colour_type::none;
                mmpld::convert(buffer.data(), listHeader, particles.data(), targetListHeader);
            }
        }
    };
}
