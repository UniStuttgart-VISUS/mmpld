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

        /// <summary>
        /// Tests for a bug reported by one of our master's students which
        /// prevents dropping all positional information retaining only the
        /// colour during conversion.
        /// </summary>
        TEST_METHOD(TestTischler001Convert) {
            typedef mmpld::particle_traits<mmpld::vertex_type::float_xyz, mmpld::colour_type::rgb32> traits_type;
            typedef mmpld::particle_traits<mmpld::vertex_type::none, mmpld::colour_type::rgba32> ColorFormat;
            typedef mmpld::particle_traits<mmpld::vertex_type::float_xyz, mmpld::colour_type::none> PositionFormat;

            mmpld::file_header fileHeader;
            mmpld::frame_header frameHeader;
            mmpld::list_header listHeader;
            mmpld::seek_table seekTable;

            std::vector<uint8_t> buffer;
            std::ifstream file;
            std::vector<uint8_t> particles;

            file.open("test_xyz_float_rgb_float.mmpld", std::ios::binary);
            Assert::IsTrue(file.is_open(), L"Test file has been opened", LINE_INFO());

            mmpld::read_file_header(file, fileHeader, seekTable);
            Assert::IsTrue(file.good(), L"Read file header", LINE_INFO());

            file.seekg(seekTable[0]);
            Assert::IsTrue(file.good(), L"Seek to frame", LINE_INFO());

            mmpld::read_frame_header(file, fileHeader.version, frameHeader);
            Assert::IsTrue(file.good(), L"Read frame header", LINE_INFO());

            mmpld::read_list_header(file, fileHeader.version, listHeader);
            Assert::IsTrue(file.good(), L"Read list header", LINE_INFO());
            const auto cnt = static_cast<std::size_t>(listHeader.particles);

            buffer.resize(mmpld::get_size<std::size_t>(listHeader));
            file.read(reinterpret_cast<char *>(buffer.data()), buffer.size());
            Assert::IsTrue(file.good(), L"Read particle data.", LINE_INFO());

            if (fileHeader.version == mmpld::make_version(1, 1)) {
                mmpld::skip_cluster_info(file);
            }

            // Assert valid input from file.
            {
                auto pos = traits_type::position(buffer.data() + 0 * traits_type::stride());
                auto col = traits_type::colour(buffer.data() + 0 * traits_type::stride());
                Assert::AreEqual(0.0f, pos[0], L"p0.x", LINE_INFO());
                Assert::AreEqual(0.0f, pos[1], L"p0.y", LINE_INFO());
                Assert::AreEqual(0.0f, pos[2], L"p0.z", LINE_INFO());
                Assert::AreEqual(1.0f, col[0], L"p0.r", LINE_INFO());
                Assert::AreEqual(1.0f, col[1], L"p0.g", LINE_INFO());
                Assert::AreEqual(1.0f, col[2], L"p0.b", LINE_INFO());
            }

            {
                auto pos = traits_type::position(buffer.data() + 1 * traits_type::stride());
                auto col = traits_type::colour(buffer.data() + 1 * traits_type::stride());
                Assert::AreEqual(1.0f, pos[0], L"p1.x", LINE_INFO());
                Assert::AreEqual(0.0f, pos[1], L"p1.y", LINE_INFO());
                Assert::AreEqual(0.0f, pos[2], L"p1.z", LINE_INFO());
                Assert::AreEqual(1.0f, col[0], L"p1.r", LINE_INFO());
                Assert::AreEqual(0.0f, col[1], L"p1.g", LINE_INFO());
                Assert::AreEqual(0.0f, col[2], L"p1.b", LINE_INFO());
            }

            {
                auto pos = traits_type::position(buffer.data() + 2 * traits_type::stride());
                auto col = traits_type::colour(buffer.data() + 2 * traits_type::stride());
                Assert::AreEqual(0.0f, pos[0], L"p2.x", LINE_INFO());
                Assert::AreEqual(1.0f, pos[1], L"p2.y", LINE_INFO());
                Assert::AreEqual(0.0f, pos[2], L"p2.z", LINE_INFO());
                Assert::AreEqual(0.0f, col[0], L"p2.r", LINE_INFO());
                Assert::AreEqual(1.0f, col[1], L"p2.g", LINE_INFO());
                Assert::AreEqual(0.0f, col[2], L"p2.b", LINE_INFO());
            }

            {
                auto pos = traits_type::position(buffer.data() + 3 * traits_type::stride());
                auto col = traits_type::colour(buffer.data() + 3 * traits_type::stride());
                Assert::AreEqual(0.0f, pos[0], L"p3.x", LINE_INFO());
                Assert::AreEqual(0.0f, pos[1], L"p3.y", LINE_INFO());
                Assert::AreEqual(1.0f, pos[2], L"p3.z", LINE_INFO());
                Assert::AreEqual(0.0f, col[0], L"p3.r", LINE_INFO());
                Assert::AreEqual(0.0f, col[1], L"p3.g", LINE_INFO());
                Assert::AreEqual(1.0f, col[2], L"p3.b", LINE_INFO());
            }

            // Extract positiony only.
            particles.resize(PositionFormat::size(cnt));
            mmpld::convert<PositionFormat>(buffer.data(), listHeader, particles.data(), cnt);

            Assert::AreEqual(3 * sizeof(float), PositionFormat::stride(), L"Output is only position", LINE_INFO());

            {
                auto pos = PositionFormat::position(particles.data() + 0 * PositionFormat::stride());
                Assert::AreEqual(0.0f, pos[0], L"p0.x", LINE_INFO());
                Assert::AreEqual(0.0f, pos[1], L"p0.y", LINE_INFO());
                Assert::AreEqual(0.0f, pos[2], L"p0.z", LINE_INFO());
            }

            {
                auto pos = PositionFormat::position(particles.data() + 1 * PositionFormat::stride());
                Assert::AreEqual(1.0f, pos[0], L"p1.x", LINE_INFO());
                Assert::AreEqual(0.0f, pos[1], L"p1.y", LINE_INFO());
                Assert::AreEqual(0.0f, pos[2], L"p1.z", LINE_INFO());
            }

            {
                auto pos = PositionFormat::position(particles.data() + 2 * PositionFormat::stride());
                Assert::AreEqual(0.0f, pos[0], L"p2.x", LINE_INFO());
                Assert::AreEqual(1.0f, pos[1], L"p2.y", LINE_INFO());
                Assert::AreEqual(0.0f, pos[2], L"p2.z", LINE_INFO());
            }

            {
                auto pos = PositionFormat::position(particles.data() + 3 * PositionFormat::stride());
                Assert::AreEqual(0.0f, pos[0], L"p3.x", LINE_INFO());
                Assert::AreEqual(0.0f, pos[1], L"p3.y", LINE_INFO());
                Assert::AreEqual(1.0f, pos[2], L"p3.z", LINE_INFO());
            }


            // Extract colours only.
            particles.resize(ColorFormat::size(cnt));
            mmpld::convert<ColorFormat>(buffer.data(), listHeader, particles.data(), cnt);

            Assert::AreEqual(4 * sizeof(float), ColorFormat::stride(), L"Output is RGB only", LINE_INFO());

            {
                auto col = ColorFormat::colour(particles.data() + 0 * ColorFormat::stride());
                Assert::AreEqual(1.0f, col[0], L"p0.r", LINE_INFO());
                Assert::AreEqual(1.0f, col[1], L"p0.g", LINE_INFO());
                Assert::AreEqual(1.0f, col[2], L"p0.b", LINE_INFO());
                Assert::AreEqual(1.0f, col[3], L"p0.a", LINE_INFO());
            }

            {
                auto col = ColorFormat::colour(particles.data() + 1 * ColorFormat::stride());
                Assert::AreEqual(1.0f, col[0], L"p1.r", LINE_INFO());
                Assert::AreEqual(0.0f, col[1], L"p1.g", LINE_INFO());
                Assert::AreEqual(0.0f, col[2], L"p1.b", LINE_INFO());
                Assert::AreEqual(1.0f, col[3], L"p0.a", LINE_INFO());
            }

            {
                auto col = ColorFormat::colour(particles.data() + 2 * ColorFormat::stride());
                Assert::AreEqual(0.0f, col[0], L"p2.r", LINE_INFO());
                Assert::AreEqual(1.0f, col[1], L"p2.g", LINE_INFO());
                Assert::AreEqual(0.0f, col[2], L"p2.b", LINE_INFO());
                Assert::AreEqual(1.0f, col[3], L"p0.a", LINE_INFO());
            }

            {
                auto col = ColorFormat::colour(particles.data() + 3 * ColorFormat::stride());
                Assert::AreEqual(0.0f, col[0], L"p3.r", LINE_INFO());
                Assert::AreEqual(0.0f, col[1], L"p3.g", LINE_INFO());
                Assert::AreEqual(1.0f, col[2], L"p3.b", LINE_INFO());
                Assert::AreEqual(1.0f, col[3], L"p0.a", LINE_INFO());
            }

            // Runtime conversion dropping all colour.
            auto targetListHeader = listHeader;
            targetListHeader.vertex_type = mmpld::vertex_type::float_xyz;
            targetListHeader.colour_type = mmpld::colour_type::none;
            mmpld::convert(buffer.data(), listHeader, particles.data(), targetListHeader);

            {
                auto pos = PositionFormat::position(particles.data() + 0 * PositionFormat::stride());
                Assert::AreEqual(0.0f, pos[0], L"p0.x", LINE_INFO());
                Assert::AreEqual(0.0f, pos[1], L"p0.y", LINE_INFO());
                Assert::AreEqual(0.0f, pos[2], L"p0.z", LINE_INFO());
            }

            {
                auto pos = PositionFormat::position(particles.data() + 1 * PositionFormat::stride());
                Assert::AreEqual(1.0f, pos[0], L"p1.x", LINE_INFO());
                Assert::AreEqual(0.0f, pos[1], L"p1.y", LINE_INFO());
                Assert::AreEqual(0.0f, pos[2], L"p1.z", LINE_INFO());
            }

            {
                auto pos = PositionFormat::position(particles.data() + 2 * PositionFormat::stride());
                Assert::AreEqual(0.0f, pos[0], L"p2.x", LINE_INFO());
                Assert::AreEqual(1.0f, pos[1], L"p2.y", LINE_INFO());
                Assert::AreEqual(0.0f, pos[2], L"p2.z", LINE_INFO());
            }

            {
                auto pos = PositionFormat::position(particles.data() + 3 * PositionFormat::stride());
                Assert::AreEqual(0.0f, pos[0], L"p3.x", LINE_INFO());
                Assert::AreEqual(0.0f, pos[1], L"p3.y", LINE_INFO());
                Assert::AreEqual(1.0f, pos[2], L"p3.z", LINE_INFO());
            }
        }
    };
}
