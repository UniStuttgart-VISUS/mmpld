/// <copyright file="FileTest.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2018 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>

#include "stdafx.h"
#include "CppUnitTest.h"

#include "util.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace test {

    TEST_CLASS(FileTEst) {

    public:

        TEST_METHOD(TestRealFiles) {
            ::SetMmpldWorkingDirectory();

            this->testFile<HANDLE>("test_xyz_float_int_float.mmpld");
            this->testFile<HANDLE>("test_xyz_float_none.mmpld");
            this->testFile<HANDLE>("test_xyz_float_rgb_float.mmpld");
            this->testFile<HANDLE>("test_xyz_float_rgba_byte.mmpld");
            this->testFile<HANDLE>("test_xyz_float_rgba_float.mmpld");
            this->testFile<HANDLE>("test_xyzr_float_int_float.mmpld");
            this->testFile<HANDLE>("test_xyzr_float_none.mmpld");
            this->testFile<HANDLE>("test_xyzr_float_rgb_float.mmpld");
            this->testFile<HANDLE>("test_xyzr_float_rgba_byte.mmpld");
            this->testFile<HANDLE>("test_xyzr_float_rgba_float.mmpld");

            this->testFile<FILE *>("test_xyz_float_int_float.mmpld");
            this->testFile<FILE *>("test_xyz_float_none.mmpld");
            this->testFile<FILE *>("test_xyz_float_rgb_float.mmpld");
            this->testFile<FILE *>("test_xyz_float_rgba_byte.mmpld");
            this->testFile<FILE *>("test_xyz_float_rgba_float.mmpld");
            this->testFile<FILE *>("test_xyzr_float_int_float.mmpld");
            this->testFile<FILE *>("test_xyzr_float_none.mmpld");
            this->testFile<FILE *>("test_xyzr_float_rgb_float.mmpld");
            this->testFile<FILE *>("test_xyzr_float_rgba_byte.mmpld");
            this->testFile<FILE *>("test_xyzr_float_rgba_float.mmpld");

            this->testFile<int>("test_xyz_float_int_float.mmpld");
            this->testFile<int>("test_xyz_float_none.mmpld");
            this->testFile<int>("test_xyz_float_rgb_float.mmpld");
            this->testFile<int>("test_xyz_float_rgba_byte.mmpld");
            this->testFile<int>("test_xyz_float_rgba_float.mmpld");
            this->testFile<int>("test_xyzr_float_int_float.mmpld");
            this->testFile<int>("test_xyzr_float_none.mmpld");
            this->testFile<int>("test_xyzr_float_rgb_float.mmpld");
            this->testFile<int>("test_xyzr_float_rgba_byte.mmpld");
            this->testFile<int>("test_xyzr_float_rgba_float.mmpld");

            this->testFile<std::ifstream>("test_xyz_float_int_float.mmpld");
            this->testFile<std::ifstream>("test_xyz_float_none.mmpld");
            this->testFile<std::ifstream>("test_xyz_float_rgb_float.mmpld");
            this->testFile<std::ifstream>("test_xyz_float_rgba_byte.mmpld");
            this->testFile<std::ifstream>("test_xyz_float_rgba_float.mmpld");
            this->testFile<std::ifstream>("test_xyzr_float_int_float.mmpld");
            this->testFile<std::ifstream>("test_xyzr_float_none.mmpld");
            this->testFile<std::ifstream>("test_xyzr_float_rgb_float.mmpld");
            this->testFile<std::ifstream>("test_xyzr_float_rgba_byte.mmpld");
            this->testFile<std::ifstream>("test_xyzr_float_rgba_float.mmpld");

        }

    private:

        template<class F, class C> mmpld::list_header testFile(const C *path) {
            typedef mmpld::file<F, C> file_type;

            file_type file(path);

            Assert::AreEqual(decltype(file.frames())(1), file.frames(), L"File contains one frame", LINE_INFO());
            Assert::AreEqual(std::uint32_t(file.frames()), file.file_header().frames, L"Frame number and content of header matches.", LINE_INFO());
            Assert::AreEqual(size_t(file.frames()), file.seek_table().size(), L"Number of frames and size of seek table match.", LINE_INFO());
            Assert::AreEqual(std::int32_t(1), file.frame_header().lists, L"Frame #1 holds one particle list.", LINE_INFO());

            mmpld::list_header retval;
            file.read_particles(true, retval, nullptr, 0);
            Assert::AreEqual(std::uint64_t(4), retval.particles, L"List holds four particles.", LINE_INFO());

            std::vector<std::uint8_t> buffer(mmpld::get_stride<size_t>(retval) * (retval.particles + 1));
            Assert::ExpectException<std::runtime_error>([&]() {
                file.read_particles(retval, buffer.data(), buffer.size());
            }, L"Premature end of file raises exception.", LINE_INFO());

            return retval;
        }
    };
}
