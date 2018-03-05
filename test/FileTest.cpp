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

        TEST_METHOD(Test_test_xyz_float_int_float) {
            ::SetMmpldWorkingDirectory();

            auto r1 = this->testFile<HANDLE>("test_xyz_float_int_float.mmpld");
            auto r2 = this->testFile<FILE *>("test_xyz_float_int_float.mmpld");
            auto r3 = this->testFile<int>("test_xyz_float_int_float.mmpld");
            auto r4 = this->testFile<std::ifstream>("test_xyz_float_int_float.mmpld");

            Assert::IsTrue(::memcmp(r1.colour, r2.colour, sizeof(r1.colour)) == 0, L"r3.colour matches reference.", LINE_INFO());
            Assert::IsTrue(::memcmp(r1.colour, r3.colour, sizeof(r1.colour)) == 0, L"r3.colour matches reference.", LINE_INFO());
            Assert::IsTrue(::memcmp(r1.colour, r4.colour, sizeof(r1.colour)) == 0, L"r4.colour matches reference.", LINE_INFO());
        }

        TEST_METHOD(Test_test_xyz_float_none) {
            ::SetMmpldWorkingDirectory();

            auto r1 = this->testFile<HANDLE>("test_xyz_float_none.mmpld");
            auto r2 = this->testFile<FILE *>("test_xyz_float_none.mmpld");
            auto r3 = this->testFile<int>("test_xyz_float_none.mmpld");
            auto r4 = this->testFile<std::ifstream>("test_xyz_float_none.mmpld");
        }

        TEST_METHOD(Test_test_xyz_float_rgb_float) {
            ::SetMmpldWorkingDirectory();

            auto r1 = this->testFile<HANDLE>("test_xyz_float_rgb_float.mmpld");
            auto r2 = this->testFile<FILE *>("test_xyz_float_rgb_float.mmpld");
            auto r3 = this->testFile<int>("test_xyz_float_rgb_float.mmpld");
            auto r4 = this->testFile<std::ifstream>("test_xyz_float_rgb_float.mmpld");
        }

        TEST_METHOD(Test_test_xyz_float_rgba_byte) {
            ::SetMmpldWorkingDirectory();

            auto r1 = this->testFile<HANDLE>("test_xyz_float_rgba_byte.mmpld");
            auto r2 = this->testFile<FILE *>("test_xyz_float_rgba_byte.mmpld");
            auto r3 = this->testFile<int>("test_xyz_float_rgba_byte.mmpld");
            auto r4 = this->testFile<std::ifstream>("test_xyz_float_rgba_byte.mmpld");
        }

        TEST_METHOD(Test_test_xyz_float_rgba_float) {
            ::SetMmpldWorkingDirectory();

            auto r1 = this->testFile<HANDLE>("test_xyz_float_rgba_float.mmpld");
            auto r2 = this->testFile<FILE *>("test_xyz_float_rgba_float.mmpld");
            auto r3 = this->testFile<int>("test_xyz_float_rgba_float.mmpld");
            auto r4 = this->testFile<std::ifstream>("test_xyz_float_rgba_float.mmpld");
        }

        TEST_METHOD(Test_test_xyzr_float_int_float) {
            ::SetMmpldWorkingDirectory();

            auto r1 = this->testFile<HANDLE>("test_xyzr_float_int_float.mmpld");
            auto r2 = this->testFile<FILE *>("test_xyzr_float_int_float.mmpld");
            auto r3 = this->testFile<int>("test_xyzr_float_int_float.mmpld");
            auto r4 = this->testFile<std::ifstream>("test_xyzr_float_int_float.mmpld");
        }

        TEST_METHOD(Test_test_xyzr_float_none) {
            ::SetMmpldWorkingDirectory();

            auto r1 = this->testFile<HANDLE>("test_xyzr_float_none.mmpld");
            auto r2 = this->testFile<FILE *>("test_xyzr_float_none.mmpld");
            auto r3 = this->testFile<int>("test_xyzr_float_none.mmpld");
            auto r4 = this->testFile<std::ifstream>("test_xyzr_float_none.mmpld");
        }

        TEST_METHOD(Test_test_xyzr_float_rgb_float) {
            ::SetMmpldWorkingDirectory();

            auto r1 = this->testFile<HANDLE>("test_xyzr_float_rgb_float.mmpld");
            auto r2 = this->testFile<FILE *>("test_xyzr_float_rgb_float.mmpld");
            auto r3 = this->testFile<int>("test_xyzr_float_rgb_float.mmpld");
            auto r4 = this->testFile<std::ifstream>("test_xyzr_float_rgb_float.mmpld");
        }

        TEST_METHOD(Test_test_xyzr_float_rgba_byte) {
            ::SetMmpldWorkingDirectory();

            auto r1 = this->testFile<HANDLE>("test_xyzr_float_rgba_byte.mmpld");
            auto r2 = this->testFile<FILE *>("test_xyzr_float_rgba_byte.mmpld");
            auto r3 = this->testFile<int>("test_xyzr_float_rgba_byte.mmpld");
            auto r4 = this->testFile<std::ifstream>("test_xyzr_float_rgba_byte.mmpld");
        }

        TEST_METHOD(Test_test_xyzr_float_rgba_float) {
            ::SetMmpldWorkingDirectory();

            auto r1 = this->testFile<HANDLE>("test_xyzr_float_rgba_float.mmpld");
            auto r2 = this->testFile<FILE *>("test_xyzr_float_rgba_float.mmpld");
            auto r3 = this->testFile<int>("test_xyzr_float_rgba_float.mmpld");
            auto r4 = this->testFile<std::ifstream>("test_xyzr_float_rgba_float.mmpld");
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
