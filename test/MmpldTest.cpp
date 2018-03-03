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
            typedef mmpld::colour_type c_t;
            typedef mmpld::vertex_type v_t;
            typedef std::underlying_type<c_t>::type cc_t;
            typedef std::underlying_type<v_t>::type cv_t;
            this->setWorkingDirectory();

            {
                auto header = this->testLowLevelSingleList<std::ifstream>("test_xyz_float_int_float.mmpld");
                Assert::AreEqual(cv_t(v_t::float_xyz), cv_t(header.vertex_type), L"vertex_type of test_xyz_float_int_float.mmpld");
                Assert::AreEqual(cc_t(c_t::intensity), cc_t(header.colour_type), L"colour_type of test_xyz_float_int_float.mmpld");
            }
            {
                auto header = this->testLowLevelSingleList<FILE *>("test_xyz_float_none.mmpld");
                Assert::AreEqual(cv_t(v_t::float_xyz), cv_t(header.vertex_type), L"vertex_type of test_xyz_float_none.mmpld");
                Assert::AreEqual(cc_t(c_t::none), cc_t(header.colour_type), L"colour_type of test_xyz_float_none.mmpld");
            }
            {
                auto header = this->testLowLevelSingleList<int>("test_xyz_float_rgb_float.mmpld");
                Assert::AreEqual(cv_t(v_t::float_xyz), cv_t(header.vertex_type), L"vertex_type of test_xyz_float_rgb_float.mmpld");
                Assert::AreEqual(cc_t(c_t::rgb32), cc_t(header.colour_type), L"colour_type of test_xyz_float_rgb_float.mmpld");
            }
            {
                auto header = this->testLowLevelSingleList<HANDLE>("test_xyz_float_rgba_byte.mmpld");
                Assert::AreEqual(cv_t(v_t::float_xyz), cv_t(header.vertex_type), L"vertex_type of test_xyz_float_rgba_byte.mmpld");
                Assert::AreEqual(cc_t(c_t::rgba8), cc_t(header.colour_type), L"colour_type of test_xyz_float_rgba_byte.mmpld");
            }

            {
                auto header = this->testLowLevelSingleList<FILE *>(L"test_xyz_float_rgba_float.mmpld");
                Assert::AreEqual(cv_t(v_t::float_xyz), cv_t(header.vertex_type), L"vertex_type of test_xyz_float_rgba_float.mmpld");
                Assert::AreEqual(cc_t(c_t::rgba32), cc_t(header.colour_type), L"colour_type of test_xyz_float_rgba_float.mmpld");
            }
            {
                auto header = this->testLowLevelSingleList<int>(L"test_xyzr_float_int_float.mmpld");
                Assert::AreEqual(cv_t(v_t::float_xyzr), cv_t(header.vertex_type), L"vertex_type of test_xyzr_float_int_float.mmpld");
                Assert::AreEqual(cc_t(c_t::intensity), cc_t(header.colour_type), L"colour_type of test_xyzr_float_int_float.mmpld");
            }
            {
                auto header = this->testLowLevelSingleList<HANDLE>(L"test_xyzr_float_none.mmpld");
                Assert::AreEqual(cv_t(v_t::float_xyzr), cv_t(header.vertex_type), L"vertex_type of test_xyzr_float_none.mmpld");
                Assert::AreEqual(cc_t(c_t::none), cc_t(header.colour_type), L"colour_type of test_xyzr_float_none.mmpld");
            }
            {
                auto header = this->testLowLevelSingleList<HANDLE>(L"test_xyzr_float_rgb_float.mmpld");
                Assert::AreEqual(cv_t(v_t::float_xyzr), cv_t(header.vertex_type), L"vertex_type of test_xyzr_float_rgb_float.mmpld");
                Assert::AreEqual(cc_t(c_t::rgb32), cc_t(header.colour_type), L"colour_type of test_xyzr_float_rgb_float.mmpld");
            }
            {
                auto header = this->testLowLevelSingleList<HANDLE>(L"test_xyzr_float_rgba_byte.mmpld");
                Assert::AreEqual(cv_t(v_t::float_xyzr), cv_t(header.vertex_type), L"vertex_type of test_xyzr_float_rgba_byte.mmpld");
                Assert::AreEqual(cc_t(c_t::rgba8), cc_t(header.colour_type), L"colour_type of test_xyzr_float_rgba_byte.mmpld");
            }
            {
                auto header = this->testLowLevelSingleList<HANDLE>(L"test_xyzr_float_rgba_float.mmpld");
                Assert::AreEqual(cv_t(v_t::float_xyzr), cv_t(header.vertex_type), L"vertex_type of test_xyzr_float_rgba_float.mmpld");
                Assert::AreEqual(cc_t(c_t::rgba32), cc_t(header.colour_type), L"colour_type of test_xyzr_float_rgba_float.mmpld");
            }
        }

        TEST_METHOD(TestProperties) {
            typedef mmpld::particle_properties pp_t;
            typedef std::underlying_type<pp_t>::type p_t;
            mmpld::list_header header;
            p_t props;

            header.colour_type = mmpld::colour_type::none;
            header.vertex_type = mmpld::vertex_type::float_xyz;
            props = mmpld::get_properties<decltype(props)>(header);
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_radius)), L"per_particle_radius of float_xyz + none");
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_colour)), L"per_particle_colour of float_xyz + none");
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_intensity)), L"per_particle_intensity of float_xyz + none");
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::float_colour)), L"float_colour of float_xyz + none");

            header.colour_type = mmpld::colour_type::none;
            header.vertex_type = mmpld::vertex_type::float_xyzr;
            props = mmpld::get_properties<decltype(props)>(header);
            Assert::AreEqual(p_t(pp_t::per_particle_radius), (props & p_t(pp_t::per_particle_radius)), L"per_particle_radius of float_xyzr + none");
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_colour)), L"per_particle_colour of float_xyzr + none");
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_intensity)), L"per_particle_intensity of float_xyzr + none");
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::float_colour)), L"float_colour of float_xyzr + none");

            header.colour_type = mmpld::colour_type::none;
            header.vertex_type = mmpld::vertex_type::short_xyz;
            props = mmpld::get_properties<decltype(props)>(header);
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_radius)), L"per_particle_radius of short_xyz + none");
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_colour)), L"per_particle_colour of short_xyz + none");
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_intensity)), L"per_particle_intensity of short_xyz + none");
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::float_colour)), L"float_colour of short_xyz + none");

            header.colour_type = mmpld::colour_type::intensity;
            header.vertex_type = mmpld::vertex_type::float_xyz;
            props = mmpld::get_properties<decltype(props)>(header);
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_radius)), L"per_particle_radius of float_xyz + intensity");
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_colour)), L"per_particle_colour of float_xyz + intensity");
            Assert::AreEqual(p_t(pp_t::per_particle_intensity), (props & p_t(pp_t::per_particle_intensity)), L"per_particle_intensity of float_xyz + intensity");
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::float_colour)), L"float_colour of float_xyz + intensity");

            header.colour_type = mmpld::colour_type::intensity;
            header.vertex_type = mmpld::vertex_type::float_xyzr;
            props = mmpld::get_properties<decltype(props)>(header);
            Assert::AreEqual(p_t(pp_t::per_particle_radius), (props & p_t(pp_t::per_particle_radius)), L"per_particle_radius of float_xyzr + intensity");
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_colour)), L"per_particle_colour of float_xyzr + intensity");
            Assert::AreEqual(p_t(pp_t::per_particle_intensity), (props & p_t(pp_t::per_particle_intensity)), L"per_particle_intensity of float_xyzr + intensity");
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::float_colour)), L"float_colour of float_xyzr + intensity");

            header.colour_type = mmpld::colour_type::intensity;
            header.vertex_type = mmpld::vertex_type::short_xyz;
            props = mmpld::get_properties<decltype(props)>(header);
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_radius)), L"per_particle_radius of short_xyz + intensity");
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_colour)), L"per_particle_colour of short_xyz + intensity");
            Assert::AreEqual(p_t(pp_t::per_particle_intensity), (props & p_t(pp_t::per_particle_intensity)), L"per_particle_intensity of short_xyz + intensity");
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::float_colour)), L"float_colour of short_xyz + intensity");

            header.colour_type = mmpld::colour_type::rgb8;
            header.vertex_type = mmpld::vertex_type::float_xyz;
            props = mmpld::get_properties<decltype(props)>(header);
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_radius)), L"per_particle_radius of float_xyz + rgb8");
            Assert::AreEqual(p_t(pp_t::per_particle_colour), (props & p_t(pp_t::per_particle_colour)), L"per_particle_colour of float_xyz + rgb8");
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_intensity)), L"per_particle_intensity of float_xyz + rgb8");
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::float_colour)), L"float_colour of float_xyz + rgb8");

            header.colour_type = mmpld::colour_type::rgb8;
            header.vertex_type = mmpld::vertex_type::float_xyzr;
            props = mmpld::get_properties<decltype(props)>(header);
            Assert::AreEqual(p_t(pp_t::per_particle_radius), (props & p_t(pp_t::per_particle_radius)), L"per_particle_radius of float_xyzr + rgb8");
            Assert::AreEqual(p_t(pp_t::per_particle_colour), (props & p_t(pp_t::per_particle_colour)), L"per_particle_colour of float_xyzr + rgb8");
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_intensity)), L"per_particle_intensity of float_xyzr + rgb8");
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::float_colour)), L"float_colour of float_xyzr + rgb8");

            header.colour_type = mmpld::colour_type::rgb8;
            header.vertex_type = mmpld::vertex_type::short_xyz;
            props = mmpld::get_properties<decltype(props)>(header);
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_radius)), L"per_particle_radius of short_xyz + rgb8");
            Assert::AreEqual(p_t(pp_t::per_particle_colour), (props & p_t(pp_t::per_particle_colour)), L"per_particle_colour of short_xyz + rgb8");
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_intensity)), L"per_particle_intensity of short_xyz + rgb8");
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::float_colour)), L"float_colour of short_xyz + rgb8");

            header.colour_type = mmpld::colour_type::rgba8;
            header.vertex_type = mmpld::vertex_type::float_xyz;
            props = mmpld::get_properties<decltype(props)>(header);
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_radius)), L"per_particle_radius of float_xyz + rgba8");
            Assert::AreEqual(p_t(pp_t::per_particle_colour), (props & p_t(pp_t::per_particle_colour)), L"per_particle_colour of float_xyz + rgba8");
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_intensity)), L"per_particle_intensity of float_xyz + rgba8");
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::float_colour)), L"float_colour of float_xyz + rgba8");

            header.colour_type = mmpld::colour_type::rgba8;
            header.vertex_type = mmpld::vertex_type::float_xyzr;
            props = mmpld::get_properties<decltype(props)>(header);
            Assert::AreEqual(p_t(pp_t::per_particle_radius), (props & p_t(pp_t::per_particle_radius)), L"per_particle_radius of float_xyzr + rgba8");
            Assert::AreEqual(p_t(pp_t::per_particle_colour), (props & p_t(pp_t::per_particle_colour)), L"per_particle_colour of float_xyzr + rgba8");
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_intensity)), L"per_particle_intensity of float_xyzr + rgba8");
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::float_colour)), L"float_colour of float_xyzr + rgba8");

            header.colour_type = mmpld::colour_type::rgba8;
            header.vertex_type = mmpld::vertex_type::short_xyz;
            props = mmpld::get_properties<decltype(props)>(header);
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_radius)), L"per_particle_radius of short_xyz + rgba8");
            Assert::AreEqual(p_t(pp_t::per_particle_colour), (props & p_t(pp_t::per_particle_colour)), L"per_particle_colour of short_xyz + rgba8");
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_intensity)), L"per_particle_intensity of short_xyz + rgba8");
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::float_colour)), L"float_colour of short_xyz + rgba8");

            header.colour_type = mmpld::colour_type::rgb32;
            header.vertex_type = mmpld::vertex_type::float_xyz;
            props = mmpld::get_properties<decltype(props)>(header);
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_radius)), L"per_particle_radius of float_xyz + rgb32");
            Assert::AreEqual(p_t(pp_t::per_particle_colour), (props & p_t(pp_t::per_particle_colour)), L"per_particle_colour of float_xyz + rgb32");
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_intensity)), L"per_particle_intensity of float_xyz + rgb32");
            Assert::AreEqual(p_t(pp_t::float_colour), (props & p_t(pp_t::float_colour)), L"float_colour of float_xyz + rgb32");

            header.colour_type = mmpld::colour_type::rgb32;
            header.vertex_type = mmpld::vertex_type::float_xyzr;
            props = mmpld::get_properties<decltype(props)>(header);
            Assert::AreEqual(p_t(pp_t::per_particle_radius), (props & p_t(pp_t::per_particle_radius)), L"per_particle_radius of float_xyzr + rgb32");
            Assert::AreEqual(p_t(pp_t::per_particle_colour), (props & p_t(pp_t::per_particle_colour)), L"per_particle_colour of float_xyzr + rgb32");
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_intensity)), L"per_particle_intensity of float_xyzr + rgb32");
            Assert::AreEqual(p_t(pp_t::float_colour), (props & p_t(pp_t::float_colour)), L"float_colour of float_xyzr + rgb32");

            header.colour_type = mmpld::colour_type::rgb32;
            header.vertex_type = mmpld::vertex_type::short_xyz;
            props = mmpld::get_properties<decltype(props)>(header);
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_radius)), L"per_particle_radius of short_xyz + rgb32");
            Assert::AreEqual(p_t(pp_t::per_particle_colour), (props & p_t(pp_t::per_particle_colour)), L"per_particle_colour of short_xyz + rgb32");
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_intensity)), L"per_particle_intensity of short_xyz + rgb32");
            Assert::AreEqual(p_t(pp_t::float_colour), (props & p_t(pp_t::float_colour)), L"float_colour of short_xyz + rgb32");

            header.colour_type = mmpld::colour_type::rgba32;
            header.vertex_type = mmpld::vertex_type::float_xyz;
            props = mmpld::get_properties<decltype(props)>(header);
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_radius)), L"per_particle_radius of float_xyz + rgba32");
            Assert::AreEqual(p_t(pp_t::per_particle_colour), (props & p_t(pp_t::per_particle_colour)), L"per_particle_colour of float_xyz + rgba32");
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_intensity)), L"per_particle_intensity of float_xyz + rgba32");
            Assert::AreEqual(p_t(pp_t::float_colour), (props & p_t(pp_t::float_colour)), L"float_colour of float_xyz + rgba32");

            header.colour_type = mmpld::colour_type::rgba32;
            header.vertex_type = mmpld::vertex_type::float_xyzr;
            props = mmpld::get_properties<decltype(props)>(header);
            Assert::AreEqual(p_t(pp_t::per_particle_radius), (props & p_t(pp_t::per_particle_radius)), L"per_particle_radius of float_xyzr + rgba32");
            Assert::AreEqual(p_t(pp_t::per_particle_colour), (props & p_t(pp_t::per_particle_colour)), L"per_particle_colour of float_xyzr + rgba32");
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_intensity)), L"per_particle_intensity of float_xyzr + rgba32");
            Assert::AreEqual(p_t(pp_t::float_colour), (props & p_t(pp_t::float_colour)), L"float_colour of float_xyzr + rgba32");

            header.colour_type = mmpld::colour_type::rgba32;
            header.vertex_type = mmpld::vertex_type::short_xyz;
            props = mmpld::get_properties<decltype(props)>(header);
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_radius)), L"per_particle_radius of short_xyz + rgba32");
            Assert::AreEqual(p_t(pp_t::per_particle_colour), (props & p_t(pp_t::per_particle_colour)), L"per_particle_colour of short_xyz + rgba32");
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_intensity)), L"per_particle_intensity of short_xyz + rgba32");
            Assert::AreEqual(p_t(pp_t::float_colour), (props & p_t(pp_t::float_colour)), L"float_colour of short_xyz + rgba32");
        }

        TEST_METHOD(TestStride) {
            mmpld::list_header header;

            header.colour_type = mmpld::colour_type::none;
            header.vertex_type = mmpld::vertex_type::float_xyz;
            Assert::AreEqual(size_t(3 * sizeof(float)), mmpld::get_stride<size_t>(header), L"Stride of float_xyz + none");

            header.colour_type = mmpld::colour_type::none;
            header.vertex_type = mmpld::vertex_type::float_xyzr;
            Assert::AreEqual(size_t(4 * sizeof(float)), mmpld::get_stride<size_t>(header), L"Stride of float_xyzr + none");

            header.colour_type = mmpld::colour_type::none;
            header.vertex_type = mmpld::vertex_type::short_xyz;
            Assert::AreEqual(size_t(3 * sizeof(short)), mmpld::get_stride<size_t>(header), L"Stride of short_xyz + none");

            header.colour_type = mmpld::colour_type::intensity;
            header.vertex_type = mmpld::vertex_type::float_xyz;
            Assert::AreEqual(size_t(3 * sizeof(float) + sizeof(float)), mmpld::get_stride<size_t>(header), L"Stride of float_xyz + intensity");

            header.colour_type = mmpld::colour_type::intensity;
            header.vertex_type = mmpld::vertex_type::float_xyzr;
            Assert::AreEqual(size_t(4 * sizeof(float) + sizeof(float)), mmpld::get_stride<size_t>(header), L"Stride of float_xyzr + intensity");

            header.colour_type = mmpld::colour_type::intensity;
            header.vertex_type = mmpld::vertex_type::short_xyz;
            Assert::AreEqual(size_t(3 * sizeof(short) + sizeof(float)), mmpld::get_stride<size_t>(header), L"Stride of short_xyz + intensity");

            header.colour_type = mmpld::colour_type::rgb8;
            header.vertex_type = mmpld::vertex_type::float_xyz;
            Assert::AreEqual(size_t(3 * sizeof(float) + 3 * sizeof(char)), mmpld::get_stride<size_t>(header), L"Stride of float_xyz + rgb8");

            header.colour_type = mmpld::colour_type::rgb8;
            header.vertex_type = mmpld::vertex_type::float_xyzr;
            Assert::AreEqual(size_t(4 * sizeof(float) + 3 * sizeof(char)), mmpld::get_stride<size_t>(header), L"Stride of float_xyzr + rgb8");

            header.colour_type = mmpld::colour_type::rgb8;
            header.vertex_type = mmpld::vertex_type::short_xyz;
            Assert::AreEqual(size_t(3 * sizeof(short) + 3 * sizeof(char)), mmpld::get_stride<size_t>(header), L"Stride of short_xyz + rgb8");

            header.colour_type = mmpld::colour_type::rgba8;
            header.vertex_type = mmpld::vertex_type::float_xyz;
            Assert::AreEqual(size_t(3 * sizeof(float) + 4 * sizeof(char)), mmpld::get_stride<size_t>(header), L"Stride of float_xyz + rgba8");

            header.colour_type = mmpld::colour_type::rgba8;
            header.vertex_type = mmpld::vertex_type::float_xyzr;
            Assert::AreEqual(size_t(4 * sizeof(float) + 4 * sizeof(char)), mmpld::get_stride<size_t>(header), L"Stride of float_xyzr + rgba8");

            header.colour_type = mmpld::colour_type::rgba8;
            header.vertex_type = mmpld::vertex_type::short_xyz;
            Assert::AreEqual(size_t(3 * sizeof(short) + 4 * sizeof(char)), mmpld::get_stride<size_t>(header), L"Stride of short_xyz + rgba8");

            header.colour_type = mmpld::colour_type::rgb32;
            header.vertex_type = mmpld::vertex_type::float_xyz;
            Assert::AreEqual(size_t(3 * sizeof(float) + 3 * sizeof(float)), mmpld::get_stride<size_t>(header), L"Stride of float_xyz + rgb32");

            header.colour_type = mmpld::colour_type::rgb32;
            header.vertex_type = mmpld::vertex_type::float_xyzr;
            Assert::AreEqual(size_t(4 * sizeof(float) + 3 * sizeof(float)), mmpld::get_stride<size_t>(header), L"Stride of float_xyzr + rgb32");

            header.colour_type = mmpld::colour_type::rgb32;
            header.vertex_type = mmpld::vertex_type::short_xyz;
            Assert::AreEqual(size_t(3 * sizeof(short) + 3 * sizeof(float)), mmpld::get_stride<size_t>(header), L"Stride of short_xyz + rgb32");

            header.colour_type = mmpld::colour_type::rgba32;
            header.vertex_type = mmpld::vertex_type::float_xyz;
            Assert::AreEqual(size_t(3 * sizeof(float) + 4 * sizeof(float)), mmpld::get_stride<size_t>(header), L"Stride of float_xyz + rgba32");

            header.colour_type = mmpld::colour_type::rgba32;
            header.vertex_type = mmpld::vertex_type::float_xyzr;
            Assert::AreEqual(size_t(4 * sizeof(float) + 4 * sizeof(float)), mmpld::get_stride<size_t>(header), L"Stride of float_xyzr + rgba32");

            header.colour_type = mmpld::colour_type::rgba32;
            header.vertex_type = mmpld::vertex_type::short_xyz;
            Assert::AreEqual(size_t(3 * sizeof(short) + 4 * sizeof(float)), mmpld::get_stride<size_t>(header), L"Stride of short_xyz + rgba32");
        }

        TEST_METHOD(TestToString) {
            Assert::AreEqual("none", mmpld::to_string<char>(mmpld::colour_type::none).c_str(), L"Stringisation of colour type \"none\"");
            Assert::AreEqual("rgb8", mmpld::to_string<char>(mmpld::colour_type::rgb8).c_str(), L"Stringisation of colour type \"rgb8\"");
            Assert::AreEqual("rgba8", mmpld::to_string<char>(mmpld::colour_type::rgba8).c_str(), L"Stringisation of colour type \"rgba8\"");
            Assert::AreEqual("intensity", mmpld::to_string<char>(mmpld::colour_type::intensity).c_str(), L"Stringisation of colour type \"intensity\"");
            Assert::AreEqual("rgb32", mmpld::to_string<char>(mmpld::colour_type::rgb32).c_str(), L"Stringisation of colour type \"rgb32\"");
            Assert::AreEqual("rgba32", mmpld::to_string<char>(mmpld::colour_type::rgba32).c_str(), L"Stringisation of colour type \"rgba32\"");

            Assert::AreEqual(L"none", mmpld::to_string<wchar_t>(mmpld::colour_type::none).c_str(), L"Stringisation of colour type \"none\"");
            Assert::AreEqual(L"rgb8", mmpld::to_string<wchar_t>(mmpld::colour_type::rgb8).c_str(), L"Stringisation of colour type \"rgb8\"");
            Assert::AreEqual(L"rgba8", mmpld::to_string<wchar_t>(mmpld::colour_type::rgba8).c_str(), L"Stringisation of colour type \"rgba8\"");
            Assert::AreEqual(L"intensity", mmpld::to_string<wchar_t>(mmpld::colour_type::intensity).c_str(), L"Stringisation of colour type \"intensity\"");
            Assert::AreEqual(L"rgb32", mmpld::to_string<wchar_t>(mmpld::colour_type::rgb32).c_str(), L"Stringisation of colour type \"rgb32\"");
            Assert::AreEqual(L"rgba32", mmpld::to_string<wchar_t>(mmpld::colour_type::rgba32).c_str(), L"Stringisation of colour type \"rgba32\"");

            Assert::AreEqual("none", mmpld::to_string<char>(mmpld::vertex_type::none).c_str(), L"Stringisation of vertex type \"none\"");
            Assert::AreEqual("float_xyz", mmpld::to_string<char>(mmpld::vertex_type::float_xyz).c_str(), L"Stringisation of vertex type \"float_xyz\"");
            Assert::AreEqual("float_xyzr", mmpld::to_string<char>(mmpld::vertex_type::float_xyzr).c_str(), L"Stringisation of vertex type \"float_xyzr\"");
            Assert::AreEqual("short_xyz", mmpld::to_string<char>(mmpld::vertex_type::short_xyz).c_str(), L"Stringisation of vertex type \"short_xyz\"");

            Assert::AreEqual(L"none", mmpld::to_string<wchar_t>(mmpld::vertex_type::none).c_str(), L"Stringisation of vertex type \"none\"");
            Assert::AreEqual(L"float_xyz", mmpld::to_string<wchar_t>(mmpld::vertex_type::float_xyz).c_str(), L"Stringisation of vertex type \"float_xyz\"");
            Assert::AreEqual(L"float_xyzr", mmpld::to_string<wchar_t>(mmpld::vertex_type::float_xyzr).c_str(), L"Stringisation of vertex type \"float_xyzr\"");
            Assert::AreEqual(L"short_xyz", mmpld::to_string<wchar_t>(mmpld::vertex_type::short_xyz).c_str(), L"Stringisation of vertex type \"short_xyz\"");
        }

    private:

        template<class F, class C> mmpld::list_header testLowLevelSingleList(const C *path) {
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
            Assert::AreEqual(std::uint32_t(1), fileHeader.frames, L"Number of expected frames matches.");
            Assert::AreEqual(seekTable.size(), size_t(fileHeader.frames), L"Number of frames and size of seek table match.");

            io_type::seek(hFile, seekTable[0]);
            mmpld::read_frame_header(hFile, fileHeader.version, frameHeader);
            Assert::AreEqual(std::int32_t(1), frameHeader.lists, L"Frame #1 holds one particle list.");

            mmpld::read_list_header(hFile, listHeader);
            Assert::AreEqual(std::uint64_t(4), listHeader.particles, L"List holds four particles.");

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
