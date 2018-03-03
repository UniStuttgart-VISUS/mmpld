/// <copyright file="Mmpldtest.h" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2018 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>

#include "stdafx.h"
#include "CppUnitTest.h"

#include "mmpld.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace test {

    TEST_CLASS(MmpldTest) {

    public:

        TEST_METHOD(TestLowLevel) {
            this->setWorkingDirectory();

            this->testLowLevlSingleList<std::ifstream>("test_xyz_float_int_float.mmpld");
            this->testLowLevlSingleList<FILE *>("test_xyz_float_int_float.mmpld");
            this->testLowLevlSingleList<int>("test_xyz_float_int_float.mmpld");
            this->testLowLevlSingleList<HANDLE>("test_xyz_float_int_float.mmpld");

            this->testLowLevlSingleList<FILE *>(L"test_xyz_float_int_float.mmpld");
            this->testLowLevlSingleList<int>(L"test_xyz_float_int_float.mmpld");
            this->testLowLevlSingleList<HANDLE>(L"test_xyz_float_int_float.mmpld");


            /*
            mmpld::file<std::ifstream> cppFile("test_xyz_float_int_float.mmpld");
            mmpld::file<int> fhFile("test_xyz_float_int_float.mmpld");
            mmpld::file<FILE *> fpFile("test_xyz_float_int_float.mmpld");
            mmpld::file<HANDLE> wFile("test_xyz_float_int_float.mmpld");
           
            mmpld::frame_header frameHeader;
            std::vector<std::uint64_t> offsets;
            cppFile.read_frame(0, frameHeader, std::back_inserter(offsets));
            fhFile.read_frame(0, frameHeader, std::back_inserter(offsets));
            fpFile.read_frame(0, frameHeader, std::back_inserter(offsets));
            wFile.read_frame(0, frameHeader, std::back_inserter(offsets));

            std::ifstream cs("mmpld", std::ios::binary);
            mmpld::read_file_header(cs, fileHeader, seekTable);
            mmpld::read_frame_header(cs, frameHeader, fileHeader.version);
            mmpld::read_list_header(cs, listHeader);

            int fh = ::_open("mmpld", O_RDONLY);
            mmpld::read_file_header(fh, fileHeader, seekTable);
            mmpld::read_frame_header(fh, frameHeader, fileHeader.version);
            mmpld::read_list_header(fh, listHeader);

            FILE *fp = ::fopen("mmpld", "wr");
            mmpld::read_file_header(fp, fileHeader, seekTable);
            mmpld::read_frame_header(fp, frameHeader, fileHeader.version);
            mmpld::read_list_header(fp, listHeader);

            auto props = mmpld::get_properties<unsigned int>(listHeader);
            auto stride = mmpld::get_stride<unsigned int>(listHeader);
            */

        }

    private:

        template<class F, class C> mmpld::list_header testLowLevlSingleList(const C *path) {
            typedef F file_type;
            typedef mmpld::detail::io_traits<F, C> io_type;

            mmpld::file_header fileHeader;
            mmpld::frame_header frameHeader;
            file_type hFile;
            mmpld::list_header listHeader;
            mmpld::seek_table seekTable;

            //Assert::ExpectException([&hFile]() { io_type::open(nullptr, hFile); }, L"Opening nullptr raises exception.");

            io_type::open(path, hFile);

            mmpld::read_file_header(hFile, fileHeader, seekTable);
            Assert::AreEqual(fileHeader.frames, std::uint32_t(1), L"Number of expected frames matches.");
            Assert::AreEqual(size_t(fileHeader.frames), seekTable.size(), L"Number of frames and size of seek table match.");

            io_type::seek(hFile, seekTable[0]);
            mmpld::read_frame_header(hFile, frameHeader, fileHeader.version);
            Assert::AreEqual(frameHeader.lists, std::int32_t(1), L"Frame #1 holds one particle list.");

            mmpld::read_list_header(hFile, listHeader);
            Assert::AreEqual(listHeader.particles, std::uint64_t(4), L"List holds four particles.");

            return listHeader;
        }

        template<class F, class C> void testMmpldFile(const C *path) {
            typedef mmpld::file<F, C> file_type;

            file_type file(path);
        }

        void setWorkingDirectory(void) {
            // https://social.msdn.microsoft.com/Forums/vstudio/en-US/cc60ce12-f0aa-4f7d-88ab-8f17efbc6853/cppunittestframework-find-path-to-solutiondir-from-test-method?forum=vcgeneral
            static TCHAR c;
            HMODULE hModule;
            TCHAR path[_MAX_PATH + 1];
            ::GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, &c, &hModule);
            ::GetModuleFileName(hModule, path, sizeof(path) / sizeof(*path));
            *::_tcsrchr(path, '\\') = 0;
            ::SetCurrentDirectory(path);
        }


    };
}
