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

        TEST_METHOD(Test) {
            //mmpld::file<std::ifstream> cppFile("test_xyz_float_int_float.mmpld");
            mmpld::file<int> fhFile("test_xyz_float_int_float.mmpld");
            mmpld::file<FILE *> fpFile("test_xyz_float_int_float.mmpld");
           

            /*
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

    };
}