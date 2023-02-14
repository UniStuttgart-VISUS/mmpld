// <copyright file="ExampleTest.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "stdafx.h"
#include "CppUnitTest.h"

#include "util.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace test {

    /// <summary>
    /// Tests all the examples in the readme file.
    /// </summary>
    TEST_CLASS(ExampleTest) {

        static constexpr auto TEST_FILE = _T("test_xyz_float_rgba_byte.mmpld");

        TEST_METHOD(TestReferenceContent) {
            ::SetMmpldWorkingDirectory();   // Need to have access to the test files.

            mmpld::file<HANDLE, TCHAR> file(TEST_FILE);
            auto& header = file.file_header();

            Assert::AreEqual(decltype(header.frames)(1), header.frames, L"One frame in test file", LINE_INFO());
            Assert::AreEqual(decltype(file.frame())(0), file.frame(), L"On first frame", LINE_INFO());

            auto& frame = file.frame_header();
            Assert::AreEqual(decltype(frame.lists)(1), frame.lists, L"One list in frame", LINE_INFO());

            mmpld::list_header list;
            auto particles = file.read_particles(list);
            Assert::AreEqual(int(mmpld::vertex_type::float_xyz), int(list.vertex_type), L"vertex_type", LINE_INFO());
            Assert::AreEqual(int(mmpld::colour_type::rgba8), int(list.colour_type), L"colour_type", LINE_INFO());
            Assert::AreEqual(decltype(list.particles)(4), list.particles, L"Four particles", LINE_INFO());

            mmpld::particle_view<void> view(list.vertex_type, list.colour_type, particles.data());
            {
                auto p = static_cast<const float *>(view.position());
                auto c = static_cast<const std::uint8_t *>(view.colour());
                Assert::AreEqual(0.0f, p[0], L"p[0].x", LINE_INFO());
                Assert::AreEqual(0.0f, p[1], L"p[0].y", LINE_INFO());
                Assert::AreEqual(0.0f, p[2], L"p[0].z", LINE_INFO());
                Assert::AreEqual(std::uint8_t(0xFF), c[0], L"c[0].r", LINE_INFO());
                Assert::AreEqual(std::uint8_t(0xFF), c[1], L"c[0].g", LINE_INFO());
                Assert::AreEqual(std::uint8_t(0xFF), c[2], L"c[0].b", LINE_INFO());
                Assert::AreEqual(std::uint8_t(0xFF), c[3], L"c[0].a", LINE_INFO());
            }

            view.advance();

            {
                auto p = static_cast<const float *>(view.position());
                auto c = static_cast<const std::uint8_t *>(view.colour());
                Assert::AreEqual(1.0f, p[0], L"p[1].x", LINE_INFO());
                Assert::AreEqual(0.0f, p[1], L"p[1].y", LINE_INFO());
                Assert::AreEqual(0.0f, p[2], L"p[1].z", LINE_INFO());
                Assert::AreEqual(std::uint8_t(0xFF), c[0], L"c[1].r", LINE_INFO());
                Assert::AreEqual(std::uint8_t(0x00), c[1], L"c[1].g", LINE_INFO());
                Assert::AreEqual(std::uint8_t(0x00), c[2], L"c[1].b", LINE_INFO());
                Assert::AreEqual(std::uint8_t(0xFF), c[3], L"c[1].a", LINE_INFO());
            }

            view.advance();

            {
                auto p = static_cast<const float *>(view.position());
                auto c = static_cast<const std::uint8_t *>(view.colour());
                Assert::AreEqual(0.0f, p[0], L"p[2].x", LINE_INFO());
                Assert::AreEqual(1.0f, p[1], L"p[2].y", LINE_INFO());
                Assert::AreEqual(0.0f, p[2], L"p[2].z", LINE_INFO());
                Assert::AreEqual(std::uint8_t(0x00), c[0], L"c[2].r", LINE_INFO());
                Assert::AreEqual(std::uint8_t(0xFF), c[1], L"c[2].g", LINE_INFO());
                Assert::AreEqual(std::uint8_t(0x00), c[2], L"c[2].b", LINE_INFO());
                Assert::AreEqual(std::uint8_t(0xFF), c[3], L"c[2].a", LINE_INFO());
            }

            view.advance();

            {
                auto p = static_cast<const float *>(view.position());
                auto c = static_cast<const std::uint8_t *>(view.colour());
                Assert::AreEqual(0.0f, p[0], L"p[3].x", LINE_INFO());
                Assert::AreEqual(0.0f, p[1], L"p[3].y", LINE_INFO());
                Assert::AreEqual(1.0f, p[2], L"p[3].z", LINE_INFO());
                Assert::AreEqual(std::uint8_t(0x00), c[0], L"c[3].r", LINE_INFO());
                Assert::AreEqual(std::uint8_t(0x00), c[1], L"c[3].g", LINE_INFO());
                Assert::AreEqual(std::uint8_t(0xFF), c[2], L"c[3].b", LINE_INFO());
                Assert::AreEqual(std::uint8_t(0xFF), c[3], L"c[3].a", LINE_INFO());
            }
        }

        TEST_METHOD(TestLowLevelIO) {
            ::SetMmpldWorkingDirectory();   // Need to have access to the test files.

            mmpld::file_header fileHeader;
            mmpld::frame_header frameHeader;
            mmpld::list_header listHeader;
            std::vector<std::uint8_t> particles;
            mmpld::seek_table seekTable;

            // Open the file with your preferred API, in this case WIN32.
            auto hFile = ::CreateFile(TEST_FILE, GENERIC_READ, FILE_SHARE_READ,
                nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);
            if (hFile == INVALID_HANDLE_VALUE) { /* Handle error. */ }

            // Read the file header to obtain information about the frames in the file.
            mmpld::read_file_header(hFile, fileHeader, seekTable);

            // Read the frame header of each frame in the file.
            for (decltype(fileHeader.frames) i = 0; i < fileHeader.frames; ++i) {
                LARGE_INTEGER offset;
                offset.QuadPart = seekTable[i];

                // Seek to the begin of the frame using the offset from 'seekTable'.
                if (!::SetFilePointerEx(hFile, offset, nullptr, FILE_BEGIN)) { /* Handle error. */ }

                // Read the frame header.
                mmpld::read_frame_header(hFile, fileHeader.version, frameHeader);

                // Process all particle lists which are located directly after the frame
                // header. Each particle list has its own header which allows for finding
                // out about its format and size.
                for (decltype(frameHeader.lists) j = 0; j < frameHeader.lists; ++j) {
                    mmpld::read_list_header(hFile, fileHeader.version, listHeader);

                    // Compute the number of bytes required for all particles.
                    auto rem = mmpld::get_size<DWORD>(listHeader);

                    // Allocate the buffer for all particles.
                    particles.resize(rem);

                    // Initialise the destination pointer.
                    auto ptr = particles.data();

                    // Read until we have all particles in memory.
                    while (rem > 0) {
                        DWORD cnt = 0;
                        if (!::ReadFile(hFile, ptr, rem, &cnt, nullptr)) { /* Handle error. */ }
                        ptr += cnt;
                        rem -= cnt;
                    }

                    // In MMPLD 1.1, a block of cluster information follows here. We need to
                    // skip this, because otherwise, the next list would be bogus.
                    if (fileHeader.version == mmpld::make_version(1, 1)) {
                        mmpld::skip_cluster_info(hFile);
                    }

                    /* Do something with the content of 'particles'. */
                    mmpld::particle_view<void> view(listHeader.vertex_type, listHeader.colour_type, particles.data());
                    {
                        auto p = static_cast<const float *>(view.position());
                        auto c = static_cast<const std::uint8_t *>(view.colour());
                        Assert::AreEqual(0.0f, p[0], L"p[0].x", LINE_INFO());
                        Assert::AreEqual(0.0f, p[1], L"p[0].y", LINE_INFO());
                        Assert::AreEqual(0.0f, p[2], L"p[0].z", LINE_INFO());
                        Assert::AreEqual(std::uint8_t(0xFF), c[0], L"c[0].r", LINE_INFO());
                        Assert::AreEqual(std::uint8_t(0xFF), c[1], L"c[0].g", LINE_INFO());
                        Assert::AreEqual(std::uint8_t(0xFF), c[2], L"c[0].b", LINE_INFO());
                        Assert::AreEqual(std::uint8_t(0xFF), c[3], L"c[0].a", LINE_INFO());
                    }

                    view.advance();

                    {
                        auto p = static_cast<const float *>(view.position());
                        auto c = static_cast<const std::uint8_t *>(view.colour());
                        Assert::AreEqual(1.0f, p[0], L"p[1].x", LINE_INFO());
                        Assert::AreEqual(0.0f, p[1], L"p[1].y", LINE_INFO());
                        Assert::AreEqual(0.0f, p[2], L"p[1].z", LINE_INFO());
                        Assert::AreEqual(std::uint8_t(0xFF), c[0], L"c[1].r", LINE_INFO());
                        Assert::AreEqual(std::uint8_t(0x00), c[1], L"c[1].g", LINE_INFO());
                        Assert::AreEqual(std::uint8_t(0x00), c[2], L"c[1].b", LINE_INFO());
                        Assert::AreEqual(std::uint8_t(0xFF), c[3], L"c[1].a", LINE_INFO());
                    }

                    view.advance();

                    {
                        auto p = static_cast<const float *>(view.position());
                        auto c = static_cast<const std::uint8_t *>(view.colour());
                        Assert::AreEqual(0.0f, p[0], L"p[2].x", LINE_INFO());
                        Assert::AreEqual(1.0f, p[1], L"p[2].y", LINE_INFO());
                        Assert::AreEqual(0.0f, p[2], L"p[2].z", LINE_INFO());
                        Assert::AreEqual(std::uint8_t(0x00), c[0], L"c[2].r", LINE_INFO());
                        Assert::AreEqual(std::uint8_t(0xFF), c[1], L"c[2].g", LINE_INFO());
                        Assert::AreEqual(std::uint8_t(0x00), c[2], L"c[2].b", LINE_INFO());
                        Assert::AreEqual(std::uint8_t(0xFF), c[3], L"c[2].a", LINE_INFO());
                    }

                    view.advance();

                    {
                        auto p = static_cast<const float *>(view.position());
                        auto c = static_cast<const std::uint8_t *>(view.colour());
                        Assert::AreEqual(0.0f, p[0], L"p[3].x", LINE_INFO());
                        Assert::AreEqual(0.0f, p[1], L"p[3].y", LINE_INFO());
                        Assert::AreEqual(1.0f, p[2], L"p[3].z", LINE_INFO());
                        Assert::AreEqual(std::uint8_t(0x00), c[0], L"c[3].r", LINE_INFO());
                        Assert::AreEqual(std::uint8_t(0x00), c[1], L"c[3].g", LINE_INFO());
                        Assert::AreEqual(std::uint8_t(0xFF), c[2], L"c[3].b", LINE_INFO());
                        Assert::AreEqual(std::uint8_t(0xFF), c[3], L"c[3].a", LINE_INFO());
                    }

                } /* end for (decltype(frameHeader.lists) j = 0; ... */
            } /* end for (decltype(fileHeader.frames) i = 0; ... */

            ::CloseHandle(hFile);
        }

        TEST_METHOD(TestWriting) {
            ::SetMmpldWorkingDirectory();   // Need to have access to the test files.

            mmpld::file_header inFileHeader;
            mmpld::frame_header inFrameHeader;
            mmpld::list_header inListHeader;
            std::vector<char> particles;
            mmpld::seek_table inSeekTable;

            // Read test data into memory.
            {
                std::ifstream stream;
                stream.exceptions(std::ios::badbit | std::ios::failbit);
                stream.open(TEST_FILE, std::ios::binary);

                mmpld::read_file_header(stream, inFileHeader, inSeekTable);
                stream.seekg(inSeekTable[0]);
                mmpld::read_frame_header(stream, inFileHeader.version, inFrameHeader);
                mmpld::read_list_header(stream, inFileHeader.version, inListHeader);

                particles.resize(mmpld::get_size<std::size_t>(inListHeader));
                stream.read(particles.data(), particles.size());
            }

            // BEGIN OF SAMPLE
            std::ofstream file("out.mmpld", std::ios::binary | std::ios::trunc);

            /* Describe the file and write its header. */
            mmpld::file_header fileHeader;
            mmpld::seek_table seekTable;
            // Fill the file header and the seek table. If you do not know the size of the
            // particle lists in advance, there is another variant of write_file_header
            // that writes only the header. You need to reserve the size of the seek table
            // (number of frames * sizeof(seek_table::value_type)) after the header though
            // and write it at the end.
            fileHeader = std::move(inFileHeader);
            seekTable = std::move(inSeekTable);

            mmpld::write_file_header(fileHeader, seekTable, file);

            /* Prepare each frame and write it to the file. */
            for (std::size_t f = 0; f < seekTable.size(); ++f) {
                mmpld::frame_header frameHeader;
                // Fill the frame header.

                file.seekp(seekTable[f], std::ios::beg);
                mmpld::write_frame_header(frameHeader, fileHeader.version, file);

                /* Write all particle lists of the frame. */
                for (decltype(frameHeader.lists) l = 0; l < frameHeader.lists; ++l) {
                    mmpld::list_header listHeader;
                    // Fill the list header.
                    listHeader = std::move(inListHeader);

                    mmpld::write_list_header(listHeader, fileHeader.version, file);
                    // Append the actual particles here.
                    file.write(particles.data(), particles.size());
                }
            }

            file.close();
            // END OF SAMPLE
        }

        TEST_METHOD(TestConvert) {
            std::vector<char> buffer;
            mmpld::file_header fileHeader;
            mmpld::frame_header frameHeader;
            mmpld::list_header listHeader;
            std::vector<std::uint8_t> particles;
            mmpld::seek_table seekTable;

            // The target type we want to have our particles converted to.
            typedef mmpld::particle_traits<mmpld::vertex_type::float_xyz,
                mmpld::colour_type::rgb32> ParticleFormat;

            // Open the input file, for example as STL input stream.
            std::ifstream file(TEST_FILE, std::ios::binary);
            if (file.fail()) { /* Handle error. */ }

            // Read the file header to obtain information about the frames in the file.
            mmpld::read_file_header(file, fileHeader, seekTable);

            // Read the frame header of each frame in the file.
            for (decltype(fileHeader.frames) i = 0; i < fileHeader.frames; ++i) {
                // Seek to the begin of the frame using the offset from 'seekTable'.
                file.seekg(seekTable[i]);
                if (!file.good()) { /* Handle error. */ }

                // Read the frame header.
                mmpld::read_frame_header(file, fileHeader.version, frameHeader);

                // Load the particle lists into memory one after the other.
                for (decltype(frameHeader.lists) j = 0; j < frameHeader.lists; ++j) {
                    mmpld::read_list_header(file, fileHeader.version, listHeader);
                    const auto cnt = static_cast<std::size_t>(listHeader.particles);
                    const auto mem = mmpld::get_size<std::size_t>(listHeader);

                    // Allocate the buffer for all particles.
                    buffer.resize(mem);
                    particles.resize(ParticleFormat::size(cnt));

                    // Read the particles.
                    file.read(buffer.data(), mem);
                    if (!file.good()) { /* Handle error. */ }

                    // In MMPLD 1.1, a block of cluster information follows here. We need to
                    // skip this, because otherwise, the next list would be bogus.
                    if (fileHeader.version == mmpld::make_version(1, 1)) {
                        mmpld::skip_cluster_info(file);
                    }

                    // Convert the particles.
                    mmpld::convert<ParticleFormat>(buffer.data(), listHeader,
                        particles.data(), cnt);

                    /* Do something with the content of 'particles'. */
                    mmpld::particle_view<void> view(ParticleFormat::vertex_type(), ParticleFormat::colour_type(), particles.data());

                    {
                        auto p = static_cast<const float *>(view.position());
                        auto c = static_cast<const float *>(view.colour());
                        Assert::AreEqual(0.0f, p[0], L"p[0].x", LINE_INFO());
                        Assert::AreEqual(0.0f, p[1], L"p[0].y", LINE_INFO());
                        Assert::AreEqual(0.0f, p[2], L"p[0].z", LINE_INFO());
                        Assert::AreEqual(1.0f, c[0], L"c[0].r", LINE_INFO());
                        Assert::AreEqual(1.0f, c[1], L"c[0].g", LINE_INFO());
                        Assert::AreEqual(1.0f, c[2], L"c[0].b", LINE_INFO());
                    }

                    view.advance();

                    {
                        auto p = static_cast<const float *>(view.position());
                        auto c = static_cast<const float *>(view.colour());
                        Assert::AreEqual(1.0f, p[0], L"p[1].x", LINE_INFO());
                        Assert::AreEqual(0.0f, p[1], L"p[1].y", LINE_INFO());
                        Assert::AreEqual(0.0f, p[2], L"p[1].z", LINE_INFO());
                        Assert::AreEqual(1.0f, c[0], L"c[1].r", LINE_INFO());
                        Assert::AreEqual(0.0f, c[1], L"c[1].g", LINE_INFO());
                        Assert::AreEqual(0.0f, c[2], L"c[1].b", LINE_INFO());
                    }

                    view.advance();

                    {
                        auto p = static_cast<const float *>(view.position());
                        auto c = static_cast<const float *>(view.colour());
                        Assert::AreEqual(0.0f, p[0], L"p[2].x", LINE_INFO());
                        Assert::AreEqual(1.0f, p[1], L"p[2].y", LINE_INFO());
                        Assert::AreEqual(0.0f, p[2], L"p[2].z", LINE_INFO());
                        Assert::AreEqual(0.0f, c[0], L"c[2].r", LINE_INFO());
                        Assert::AreEqual(1.0f, c[1], L"c[2].g", LINE_INFO());
                        Assert::AreEqual(0.0f, c[2], L"c[2].b", LINE_INFO());
                    }

                    view.advance();

                    {
                        auto p = static_cast<const float *>(view.position());
                        auto c = static_cast<const float *>(view.colour());
                        Assert::AreEqual(0.0f, p[0], L"p[3].x", LINE_INFO());
                        Assert::AreEqual(0.0f, p[1], L"p[3].y", LINE_INFO());
                        Assert::AreEqual(1.0f, p[2], L"p[3].z", LINE_INFO());
                        Assert::AreEqual(0.0f, c[0], L"c[3].r", LINE_INFO());
                        Assert::AreEqual(0.0f, c[1], L"c[3].g", LINE_INFO());
                        Assert::AreEqual(1.0f, c[2], L"c[3].b", LINE_INFO());
                    }

                } /* end for (decltype(frameHeader.lists) j = 0; ... */
            } /* end for (decltype(fileHeader.frames) i = 0; ... */

            file.close();
        }

        TEST_METHOD(TestReadAs) {
            ::SetMmpldWorkingDirectory();   // Need to have access to the test files.

            mmpld::file_header fileHeader;
            mmpld::frame_header frameHeader;
            mmpld::list_header listHeader;
            std::vector<std::uint8_t> particles;
            mmpld::seek_table seekTable;

            // Open the file with your preferred API, in this case WIN32.
            auto hFile = ::CreateFile(TEST_FILE, GENERIC_READ, FILE_SHARE_READ,
                nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);
            if (hFile == INVALID_HANDLE_VALUE) { /* Handle error. */ }

            // Read the file header to obtain information about the frames in the file.
            mmpld::read_file_header(hFile, fileHeader, seekTable);

            // Read the frame header of each frame in the file.
            for (decltype(fileHeader.frames) i = 0; i < fileHeader.frames; ++i) {
                LARGE_INTEGER offset;
                offset.QuadPart = seekTable[i];

                // Seek to the begin of the frame using the offset from 'seekTable'.
                if (!::SetFilePointerEx(hFile, offset, nullptr, FILE_BEGIN)) { /* Handle error. */ }

                // Read the frame header.
                mmpld::read_frame_header(hFile, fileHeader.version, frameHeader);

                // Process all particle lists which are located directly after the frame
                // header. Each particle list has its own header which allows for finding
                // out about its format and size.
                for (decltype(frameHeader.lists) j = 0; j < frameHeader.lists; ++j) {
                    mmpld::read_list_header(hFile, fileHeader.version, listHeader);

                    // We need to tell the read_as API how big our buffer is, which is done
                    // by copying the available size to 'targetListHeader'.
                    auto targetListHeader = listHeader;

                    // Next, set the format we want to have the particles in. In this
                    // example, the format is a compile-time constant, but you could use
                    // any format at runtime here.
                    targetListHeader.vertex_type = mmpld::vertex_type::float_xyz;
                    targetListHeader.colour_type = mmpld::colour_type::rgb32;

                    // Allocate the buffer for all converted particles. It is important to
                    // use 'targetListHeader' here and not the list header read from the
                    // file, because the conversion target might have a different size than
                    // the original input.
                    particles.resize(mmpld::get_size<std::size_t>(targetListHeader));

                    // Initialise the destination pointer.
                    auto ptr = particles.data();

                    // Read the particles and let the API convert it to the format of
                    // 'targetListHeader'. If the format in 'listHeader' happens to be the
                    // same format, you do not need to pay for any conversion, but the input
                    // is directly read to 'ptr'.
                    mmpld::read_as(hFile, listHeader, ptr, targetListHeader);

                    // You could specify the size of the conversion buffer here like this,
                    // which would instruct the API to allocate a temporary buffer for 16
                    // particles and read and convert the input in batches of 16.
                    // mmpld::read_as(hFile, listHeader, ptr, targetListHeader, 16);

                    // In MMPLD 1.1, a block of cluster information follows here. We need to
                    // skip this, because otherwise, the next list would be bogus.
                    if (fileHeader.version == mmpld::make_version(1, 1)) {
                        mmpld::skip_cluster_info(hFile);
                    }

                    /* Do something with the content of 'particles'. */
                    mmpld::particle_view<void> view(targetListHeader.vertex_type, targetListHeader.colour_type, particles.data());

                    {
                        auto p = static_cast<const float *>(view.position());
                        auto c = static_cast<const float *>(view.colour());
                        Assert::AreEqual(0.0f, p[0], L"p[0].x", LINE_INFO());
                        Assert::AreEqual(0.0f, p[1], L"p[0].y", LINE_INFO());
                        Assert::AreEqual(0.0f, p[2], L"p[0].z", LINE_INFO());
                        Assert::AreEqual(1.0f, c[0], L"c[0].r", LINE_INFO());
                        Assert::AreEqual(1.0f, c[1], L"c[0].g", LINE_INFO());
                        Assert::AreEqual(1.0f, c[2], L"c[0].b", LINE_INFO());
                    }

                    view.advance();

                    {
                        auto p = static_cast<const float *>(view.position());
                        auto c = static_cast<const float *>(view.colour());
                        Assert::AreEqual(1.0f, p[0], L"p[1].x", LINE_INFO());
                        Assert::AreEqual(0.0f, p[1], L"p[1].y", LINE_INFO());
                        Assert::AreEqual(0.0f, p[2], L"p[1].z", LINE_INFO());
                        Assert::AreEqual(1.0f, c[0], L"c[1].r", LINE_INFO());
                        Assert::AreEqual(0.0f, c[1], L"c[1].g", LINE_INFO());
                        Assert::AreEqual(0.0f, c[2], L"c[1].b", LINE_INFO());
                    }

                    view.advance();

                    {
                        auto p = static_cast<const float *>(view.position());
                        auto c = static_cast<const float *>(view.colour());
                        Assert::AreEqual(0.0f, p[0], L"p[2].x", LINE_INFO());
                        Assert::AreEqual(1.0f, p[1], L"p[2].y", LINE_INFO());
                        Assert::AreEqual(0.0f, p[2], L"p[2].z", LINE_INFO());
                        Assert::AreEqual(0.0f, c[0], L"c[2].r", LINE_INFO());
                        Assert::AreEqual(1.0f, c[1], L"c[2].g", LINE_INFO());
                        Assert::AreEqual(0.0f, c[2], L"c[2].b", LINE_INFO());
                    }

                    view.advance();

                    {
                        auto p = static_cast<const float *>(view.position());
                        auto c = static_cast<const float *>(view.colour());
                        Assert::AreEqual(0.0f, p[0], L"p[3].x", LINE_INFO());
                        Assert::AreEqual(0.0f, p[1], L"p[3].y", LINE_INFO());
                        Assert::AreEqual(1.0f, p[2], L"p[3].z", LINE_INFO());
                        Assert::AreEqual(0.0f, c[0], L"c[3].r", LINE_INFO());
                        Assert::AreEqual(0.0f, c[1], L"c[3].g", LINE_INFO());
                        Assert::AreEqual(1.0f, c[2], L"c[3].b", LINE_INFO());
                    }

                } /* end for (decltype(frameHeader.lists) j = 0; ... */
            } /* end for (decltype(fileHeader.frames) i = 0; ... */

            ::CloseHandle(hFile);
        }

        TEST_METHOD(TestFile) {
            ::SetMmpldWorkingDirectory();   // Need to have access to the test files.

            // Open the file and prepare the first frame.
            mmpld::file<HANDLE, TCHAR> file(TEST_FILE);

            // Iterate over all frames in the file. Note that if you are only
            // interested in the first one, you can use it right away without calling
            // file.open_frame again, because the first frame is opened in the ctor.
            for (decltype(file)::frame_number_type f = 0; f < file.frames(); ++f) {
                file.open_frame(f);

                for (auto l = 0; l < file.frame_header().lists; ++l) {
                    mmpld::list_header listHeader;
                    auto particles = file.read_particles(listHeader);

                    /* Do something with the content of 'particles'. */
                    mmpld::particle_view<void> view(listHeader.vertex_type, listHeader.colour_type, particles.data());
                    {
                        auto p = static_cast<const float *>(view.position());
                        auto c = static_cast<const std::uint8_t *>(view.colour());
                        Assert::AreEqual(0.0f, p[0], L"p[0].x", LINE_INFO());
                        Assert::AreEqual(0.0f, p[1], L"p[0].y", LINE_INFO());
                        Assert::AreEqual(0.0f, p[2], L"p[0].z", LINE_INFO());
                        Assert::AreEqual(std::uint8_t(0xFF), c[0], L"c[0].r", LINE_INFO());
                        Assert::AreEqual(std::uint8_t(0xFF), c[1], L"c[0].g", LINE_INFO());
                        Assert::AreEqual(std::uint8_t(0xFF), c[2], L"c[0].b", LINE_INFO());
                        Assert::AreEqual(std::uint8_t(0xFF), c[3], L"c[0].a", LINE_INFO());
                    }

                    view.advance();

                    {
                        auto p = static_cast<const float *>(view.position());
                        auto c = static_cast<const std::uint8_t *>(view.colour());
                        Assert::AreEqual(1.0f, p[0], L"p[1].x", LINE_INFO());
                        Assert::AreEqual(0.0f, p[1], L"p[1].y", LINE_INFO());
                        Assert::AreEqual(0.0f, p[2], L"p[1].z", LINE_INFO());
                        Assert::AreEqual(std::uint8_t(0xFF), c[0], L"c[1].r", LINE_INFO());
                        Assert::AreEqual(std::uint8_t(0x00), c[1], L"c[1].g", LINE_INFO());
                        Assert::AreEqual(std::uint8_t(0x00), c[2], L"c[1].b", LINE_INFO());
                        Assert::AreEqual(std::uint8_t(0xFF), c[3], L"c[1].a", LINE_INFO());
                    }

                    view.advance();

                    {
                        auto p = static_cast<const float *>(view.position());
                        auto c = static_cast<const std::uint8_t *>(view.colour());
                        Assert::AreEqual(0.0f, p[0], L"p[2].x", LINE_INFO());
                        Assert::AreEqual(1.0f, p[1], L"p[2].y", LINE_INFO());
                        Assert::AreEqual(0.0f, p[2], L"p[2].z", LINE_INFO());
                        Assert::AreEqual(std::uint8_t(0x00), c[0], L"c[2].r", LINE_INFO());
                        Assert::AreEqual(std::uint8_t(0xFF), c[1], L"c[2].g", LINE_INFO());
                        Assert::AreEqual(std::uint8_t(0x00), c[2], L"c[2].b", LINE_INFO());
                        Assert::AreEqual(std::uint8_t(0xFF), c[3], L"c[2].a", LINE_INFO());
                    }

                    view.advance();

                    {
                        auto p = static_cast<const float *>(view.position());
                        auto c = static_cast<const std::uint8_t *>(view.colour());
                        Assert::AreEqual(0.0f, p[0], L"p[3].x", LINE_INFO());
                        Assert::AreEqual(0.0f, p[1], L"p[3].y", LINE_INFO());
                        Assert::AreEqual(1.0f, p[2], L"p[3].z", LINE_INFO());
                        Assert::AreEqual(std::uint8_t(0x00), c[0], L"c[3].r", LINE_INFO());
                        Assert::AreEqual(std::uint8_t(0x00), c[1], L"c[3].g", LINE_INFO());
                        Assert::AreEqual(std::uint8_t(0xFF), c[2], L"c[3].b", LINE_INFO());
                        Assert::AreEqual(std::uint8_t(0xFF), c[3], L"c[3].a", LINE_INFO());
                    }
                }
            }
        }

        TEST_METHOD(TestInputLayout) {
            ::SetMmpldWorkingDirectory();   // Need to have access to the test files.

            // Open the file and prepare the first frame.
            mmpld::file<HANDLE, TCHAR> file(TEST_FILE);

            // Iterate over all particle lists in the first frame.
            for (auto l = 0; l < file.frame_header().lists; ++l) {
                mmpld::list_header listHeader;

                // Read the list header and skip the data (and potential
                // cluster info).
                file.read_particles(true, listHeader, nullptr, 0);

                // Get the input elements for the list.
                auto desc = mmpld::get_input_layout<D3D11_INPUT_ELEMENT_DESC>(
                    listHeader);

                Assert::AreEqual(std::size_t(2), desc.size(), L"Two components in input layout", LINE_INFO());
                Assert::AreEqual("POSITION", desc[0].SemanticName, L"Semantic of first component", LINE_INFO());
                Assert::AreEqual(unsigned int(DXGI_FORMAT_R32G32B32_FLOAT), unsigned int(desc[0].Format), L"Format of first component", LINE_INFO());
                Assert::AreEqual("COLOR", desc[1].SemanticName, L"Semantic of second component", LINE_INFO());
                Assert::AreEqual(unsigned int(DXGI_FORMAT_R8G8B8A8_UNORM), unsigned int(desc[1].Format), L"Format of second component", LINE_INFO());
            }
        }

        TEST_METHOD(ReadToUserBuffer) {
            ::SetMmpldWorkingDirectory();   // Need to have access to the test files.

            // Open the file and prepare the first frame.
            mmpld::file<HANDLE, TCHAR> file(TEST_FILE);

            // Retrieve the header of the first list and determine the size of the particles.
            mmpld::list_header listHeader;
            file.read_particles(false, listHeader, nullptr, 0);
            auto listSize = mmpld::get_size<UINT>(listHeader);

            std::vector<std::uint8_t> buffer(listSize);
            D3D11_MAPPED_SUBRESOURCE map;
            map.pData = buffer.data();

            // We assume that the GPU buffer is large enough to hold the particles and is
            // mapped to 'map'. Now read the actual particles using the continuation
            // variant of read_particles.
            file.read_particles(listHeader, map.pData, listSize);

            // As we read manually, we need to skip cluster infos now. It is safe to call
            // this method on all file versions. It has no effect if the file is not
            // MMPLD 1.1. Please note that this method must not be called if the particle
            // list has not been completely consumed!
            file.skip_cluster_info();

            mmpld::particle_view<void> view(listHeader.vertex_type, listHeader.colour_type, buffer.data());
            {
                auto p = static_cast<const float *>(view.position());
                auto c = static_cast<const std::uint8_t *>(view.colour());
                Assert::AreEqual(0.0f, p[0], L"p[0].x", LINE_INFO());
                Assert::AreEqual(0.0f, p[1], L"p[0].y", LINE_INFO());
                Assert::AreEqual(0.0f, p[2], L"p[0].z", LINE_INFO());
                Assert::AreEqual(std::uint8_t(0xFF), c[0], L"c[0].r", LINE_INFO());
                Assert::AreEqual(std::uint8_t(0xFF), c[1], L"c[0].g", LINE_INFO());
                Assert::AreEqual(std::uint8_t(0xFF), c[2], L"c[0].b", LINE_INFO());
                Assert::AreEqual(std::uint8_t(0xFF), c[3], L"c[0].a", LINE_INFO());
            }

            view.advance();

            {
                auto p = static_cast<const float *>(view.position());
                auto c = static_cast<const std::uint8_t *>(view.colour());
                Assert::AreEqual(1.0f, p[0], L"p[1].x", LINE_INFO());
                Assert::AreEqual(0.0f, p[1], L"p[1].y", LINE_INFO());
                Assert::AreEqual(0.0f, p[2], L"p[1].z", LINE_INFO());
                Assert::AreEqual(std::uint8_t(0xFF), c[0], L"c[1].r", LINE_INFO());
                Assert::AreEqual(std::uint8_t(0x00), c[1], L"c[1].g", LINE_INFO());
                Assert::AreEqual(std::uint8_t(0x00), c[2], L"c[1].b", LINE_INFO());
                Assert::AreEqual(std::uint8_t(0xFF), c[3], L"c[1].a", LINE_INFO());
            }

            view.advance();

            {
                auto p = static_cast<const float *>(view.position());
                auto c = static_cast<const std::uint8_t *>(view.colour());
                Assert::AreEqual(0.0f, p[0], L"p[2].x", LINE_INFO());
                Assert::AreEqual(1.0f, p[1], L"p[2].y", LINE_INFO());
                Assert::AreEqual(0.0f, p[2], L"p[2].z", LINE_INFO());
                Assert::AreEqual(std::uint8_t(0x00), c[0], L"c[2].r", LINE_INFO());
                Assert::AreEqual(std::uint8_t(0xFF), c[1], L"c[2].g", LINE_INFO());
                Assert::AreEqual(std::uint8_t(0x00), c[2], L"c[2].b", LINE_INFO());
                Assert::AreEqual(std::uint8_t(0xFF), c[3], L"c[2].a", LINE_INFO());
            }

            view.advance();

            {
                auto p = static_cast<const float *>(view.position());
                auto c = static_cast<const std::uint8_t *>(view.colour());
                Assert::AreEqual(0.0f, p[0], L"p[3].x", LINE_INFO());
                Assert::AreEqual(0.0f, p[1], L"p[3].y", LINE_INFO());
                Assert::AreEqual(1.0f, p[2], L"p[3].z", LINE_INFO());
                Assert::AreEqual(std::uint8_t(0x00), c[0], L"c[3].r", LINE_INFO());
                Assert::AreEqual(std::uint8_t(0x00), c[1], L"c[3].g", LINE_INFO());
                Assert::AreEqual(std::uint8_t(0xFF), c[2], L"c[3].b", LINE_INFO());
                Assert::AreEqual(std::uint8_t(0xFF), c[3], L"c[3].a", LINE_INFO());
            }
        }

    };
}
