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

        /// <summary>
        /// Tests for a bug reported by Michael that the reader would crash if
        /// a frame does neither have positions nor colours.
        /// </summary>
        TEST_METHOD(TestBecher001Crash) {
            mmpld::file_header fileHeader { 0 };
            mmpld::list_header listHeader { 0 };
            mmpld::seek_table seekTable;

            {
                mmpld::set_magic_identifier(fileHeader);
                mmpld::set_version(fileHeader, 1, 0);
                fileHeader.frames = 1;

                seekTable.push_back(sizeof(fileHeader) + sizeof(mmpld::seek_table::value_type));

                std::ofstream output("testbecher001crash.mmpld", std::ios::trunc);
                mmpld::write_file_header(fileHeader, seekTable, output);

                listHeader.colour_type = mmpld::colour_type::none;
                listHeader.vertex_type = mmpld::vertex_type::none;
                listHeader.particles = 42;
                Assert::AreEqual(0, mmpld::get_stride<int>(listHeader), L"Stride", LINE_INFO());
                mmpld::write_list_header(listHeader, fileHeader.version, output);
            }

            {
                mmpld::file<HANDLE, char> input("testbecher001crash.mmpld");
                Assert::AreEqual(std::uint32_t(1), input.file_header().frames, L"One frame", LINE_INFO());
                input.open_frame(0);
                Assert::AreEqual(std::uint32_t(0), input.frame(), L"First frame open", LINE_INFO());
                auto parts = input.read_particles(listHeader, nullptr);
                Assert::IsTrue(parts.empty(), L"Particle list empty", LINE_INFO());
            }
        }

        /// <summary>
        /// Tests for a bug reported by Michael that the converter would crash
        /// if the source has neither a position nor colour.
        /// </summary>
        TEST_METHOD(TestBecher002Crash) {
            mmpld::file_header fileHeader { 0 };
            mmpld::list_header listHeader { 0 };
            mmpld::seek_table seekTable;

            {
                mmpld::set_magic_identifier(fileHeader);
                mmpld::set_version(fileHeader, 1, 0);
                fileHeader.frames = 1;

                seekTable.push_back(sizeof(fileHeader) + sizeof(mmpld::seek_table::value_type));

                std::ofstream output("testbecher002crash.mmpld", std::ios::trunc);
                mmpld::write_file_header(fileHeader, seekTable, output);

                listHeader.colour_type = mmpld::colour_type::none;
                listHeader.vertex_type = mmpld::vertex_type::none;
                listHeader.particles = 42;
                Assert::AreEqual(0, mmpld::get_stride<int>(listHeader), L"Stride", LINE_INFO());
                mmpld::write_list_header(listHeader, fileHeader.version, output);
            }

            mmpld::file<HANDLE, char> input("testbecher002crash.mmpld");
            Assert::AreEqual(std::uint32_t(1), input.file_header().frames, L"One frame", LINE_INFO());
            input.open_frame(0);
            Assert::AreEqual(std::uint32_t(0), input.frame(), L"First frame open", LINE_INFO());
            auto parts = input.read_particles(listHeader, nullptr);
            Assert::IsTrue(parts.empty(), L"Particle lsit empty", LINE_INFO());

            auto dstListHeader = listHeader;
            dstListHeader.vertex_type = mmpld::vertex_type::float_xyz;
            auto cntConv = mmpld::convert(parts.data(), listHeader, static_cast<std::uint8_t *>(nullptr), dstListHeader);
            Assert::AreEqual(std::uint64_t(0), cntConv, L"Nothing converted", LINE_INFO());
        }
    };
}
