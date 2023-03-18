// <copyright file="LowLevelTest.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2018 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "stdafx.h"
#include "CppUnitTest.h"

#include "util.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace test {

    TEST_CLASS(LowLevelTest) {

    public:

        TEST_METHOD(TestDirect3D11) {
            {
                mmpld::list_header header;
                header.vertex_type = mmpld::vertex_type::float_xyz;
                header.colour_type = mmpld::colour_type::intensity;

                auto layout = mmpld::get_input_layout<D3D11_INPUT_ELEMENT_DESC>(header);
                Assert::AreEqual("POSITION", layout[0].SemanticName, L"Has position semantic", LINE_INFO());
                Assert::AreEqual(UINT(DXGI_FORMAT_R32G32B32_FLOAT), UINT(layout[0].Format), L"Position format", LINE_INFO());
                Assert::AreEqual("COLOR", layout[1].SemanticName, L"Has colour semantic", LINE_INFO());
                Assert::AreEqual(UINT(DXGI_FORMAT_R32_FLOAT), UINT(layout[1].Format), L"Colour format", LINE_INFO());
            }
        }

        TEST_METHOD(TestLowLevelIo) {
            typedef mmpld::colour_type c_t;
            typedef mmpld::vertex_type v_t;
            typedef std::underlying_type<c_t>::type cc_t;
            typedef std::underlying_type<v_t>::type cv_t;
            ::SetMmpldWorkingDirectory();   // Need to have access to the test files.

            {
                auto header = this->testLowLevelSingleList<std::ifstream>("test_xyz_float_int_float.mmpld");
                Assert::AreEqual(cv_t(v_t::float_xyz), cv_t(header.vertex_type), L"vertex_type of test_xyz_float_int_float.mmpld", LINE_INFO());
                Assert::AreEqual(cc_t(c_t::intensity), cc_t(header.colour_type), L"colour_type of test_xyz_float_int_float.mmpld", LINE_INFO());
            }
            {
                auto header = this->testLowLevelSingleList<FILE *>("test_xyz_float_none.mmpld");
                Assert::AreEqual(cv_t(v_t::float_xyz), cv_t(header.vertex_type), L"vertex_type of test_xyz_float_none.mmpld", LINE_INFO());
                Assert::AreEqual(cc_t(c_t::none), cc_t(header.colour_type), L"colour_type of test_xyz_float_none.mmpld", LINE_INFO());
            }
            {
                auto header = this->testLowLevelSingleList<int>("test_xyz_float_rgb_float.mmpld");
                Assert::AreEqual(cv_t(v_t::float_xyz), cv_t(header.vertex_type), L"vertex_type of test_xyz_float_rgb_float.mmpld", LINE_INFO());
                Assert::AreEqual(cc_t(c_t::rgb32), cc_t(header.colour_type), L"colour_type of test_xyz_float_rgb_float.mmpld", LINE_INFO());
            }
            {
                auto header = this->testLowLevelSingleList<HANDLE>("test_xyz_float_rgba_byte.mmpld");
                Assert::AreEqual(cv_t(v_t::float_xyz), cv_t(header.vertex_type), L"vertex_type of test_xyz_float_rgba_byte.mmpld", LINE_INFO());
                Assert::AreEqual(cc_t(c_t::rgba8), cc_t(header.colour_type), L"colour_type of test_xyz_float_rgba_byte.mmpld", LINE_INFO());
            }

            {
                auto header = this->testLowLevelSingleList<FILE *>(L"test_xyz_float_rgba_float.mmpld");
                Assert::AreEqual(cv_t(v_t::float_xyz), cv_t(header.vertex_type), L"vertex_type of test_xyz_float_rgba_float.mmpld", LINE_INFO());
                Assert::AreEqual(cc_t(c_t::rgba32), cc_t(header.colour_type), L"colour_type of test_xyz_float_rgba_float.mmpld", LINE_INFO());
            }
            {
                auto header = this->testLowLevelSingleList<int>(L"test_xyzr_float_int_float.mmpld");
                Assert::AreEqual(cv_t(v_t::float_xyzr), cv_t(header.vertex_type), L"vertex_type of test_xyzr_float_int_float.mmpld", LINE_INFO());
                Assert::AreEqual(cc_t(c_t::intensity), cc_t(header.colour_type), L"colour_type of test_xyzr_float_int_float.mmpld", LINE_INFO());
            }
            {
                auto header = this->testLowLevelSingleList<HANDLE>(L"test_xyzr_float_none.mmpld");
                Assert::AreEqual(cv_t(v_t::float_xyzr), cv_t(header.vertex_type), L"vertex_type of test_xyzr_float_none.mmpld", LINE_INFO());
                Assert::AreEqual(cc_t(c_t::none), cc_t(header.colour_type), L"colour_type of test_xyzr_float_none.mmpld", LINE_INFO());
            }
            {
                auto header = this->testLowLevelSingleList<HANDLE>(L"test_xyzr_float_rgb_float.mmpld");
                Assert::AreEqual(cv_t(v_t::float_xyzr), cv_t(header.vertex_type), L"vertex_type of test_xyzr_float_rgb_float.mmpld", LINE_INFO());
                Assert::AreEqual(cc_t(c_t::rgb32), cc_t(header.colour_type), L"colour_type of test_xyzr_float_rgb_float.mmpld", LINE_INFO());
            }
            {
                auto header = this->testLowLevelSingleList<HANDLE>(L"test_xyzr_float_rgba_byte.mmpld");
                Assert::AreEqual(cv_t(v_t::float_xyzr), cv_t(header.vertex_type), L"vertex_type of test_xyzr_float_rgba_byte.mmpld", LINE_INFO());
                Assert::AreEqual(cc_t(c_t::rgba8), cc_t(header.colour_type), L"colour_type of test_xyzr_float_rgba_byte.mmpld", LINE_INFO());
            }
            {
                auto header = this->testLowLevelSingleList<HANDLE>(L"test_xyzr_float_rgba_float.mmpld");
                Assert::AreEqual(cv_t(v_t::float_xyzr), cv_t(header.vertex_type), L"vertex_type of test_xyzr_float_rgba_float.mmpld", LINE_INFO());
                Assert::AreEqual(cc_t(c_t::rgba32), cc_t(header.colour_type), L"colour_type of test_xyzr_float_rgba_float.mmpld", LINE_INFO());
            }

            {
                auto header = this->testLowLevelMultiList<HANDLE>(L"test_xyz_double_int_double.mmpld");
                Assert::AreEqual(cv_t(v_t::double_xyz), cv_t(header.vertex_type), L"vertex_type of test_xyz_double_int_double.mmpld", LINE_INFO());
                Assert::AreEqual(cc_t(c_t::intensity64), cc_t(header.colour_type), L"colour_type of test_xyz_double_int_double.mmpld", LINE_INFO());
            }
            {
                auto header = this->testLowLevelMultiList<HANDLE>(L"test_xyz_double_int_float.mmpld");
                Assert::AreEqual(cv_t(v_t::double_xyz), cv_t(header.vertex_type), L"vertex_type of test_xyz_double_int_float.mmpld", LINE_INFO());
                Assert::AreEqual(cc_t(c_t::intensity32), cc_t(header.colour_type), L"colour_type of test_xyz_double_int_float.mmpld", LINE_INFO());
            }
            {
                auto header = this->testLowLevelMultiList<HANDLE>(L"test_xyz_double_none.mmpld");
                Assert::AreEqual(cv_t(v_t::double_xyz), cv_t(header.vertex_type), L"vertex_type of test_xyz_double_none.mmpld", LINE_INFO());
                Assert::AreEqual(cc_t(c_t::none), cc_t(header.colour_type), L"colour_type of test_xyz_double_none.mmpld", LINE_INFO());
            }
            {
                auto header = this->testLowLevelMultiList<HANDLE>(L"test_xyz_double_rgb_float.mmpld");
                Assert::AreEqual(cv_t(v_t::double_xyz), cv_t(header.vertex_type), L"vertex_type of test_xyz_double_rgb_float.mmpld", LINE_INFO());
                Assert::AreEqual(cc_t(c_t::rgb32), cc_t(header.colour_type), L"colour_type of test_xyz_double_rgb_float.mmpld", LINE_INFO());
            }
            {
                auto header = this->testLowLevelMultiList<HANDLE>(L"test_xyz_double_rgba_byte.mmpld");
                Assert::AreEqual(cv_t(v_t::double_xyz), cv_t(header.vertex_type), L"vertex_type of test_xyz_double_rgba_byte.mmpld", LINE_INFO());
                Assert::AreEqual(cc_t(c_t::rgba8), cc_t(header.colour_type), L"colour_type of test_xyz_double_rgba_byte.mmpld", LINE_INFO());
            }
            {
                auto header = this->testLowLevelMultiList<HANDLE>(L"test_xyz_double_rgba_float.mmpld");
                Assert::AreEqual(cv_t(v_t::double_xyz), cv_t(header.vertex_type), L"vertex_type of test_xyz_double_rgba_float.mmpld", LINE_INFO());
                Assert::AreEqual(cc_t(c_t::rgba32), cc_t(header.colour_type), L"colour_type of test_xyz_double_rgba_float.mmpld", LINE_INFO());
            }
            {
                auto header = this->testLowLevelMultiList<HANDLE>(L"test_xyz_double_rgba_short.mmpld");
                Assert::AreEqual(cv_t(v_t::double_xyz), cv_t(header.vertex_type), L"vertex_type of test_xyz_double_rgba_short.mmpld", LINE_INFO());
                Assert::AreEqual(cc_t(c_t::rgba16), cc_t(header.colour_type), L"colour_type of test_xyz_double_rgba_short.mmpld", LINE_INFO());
            }
        }

        TEST_METHOD(TestParticleTraits) {
            const auto DATA = reinterpret_cast<std::uint8_t *>(1);

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::float_xyz, mmpld::colour_type::intensity> view_type;
                typedef view_type::colour_value_type *c_t;
                typedef view_type::vertex_value_type *v_t;
                Assert::AreEqual(c_t(DATA + 12), view_type::colour(DATA), L"Colour pointer of colour_type::intensity", LINE_INFO());
                Assert::AreEqual(v_t(DATA + 0), view_type::position(DATA), L"Position pointer of vertex_type::float_xyz", LINE_INFO());
                Assert::AreEqual(v_t(nullptr), view_type::radius(DATA), L"Radius pointer of vertex_type::float_xyz", LINE_INFO());
            }

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::float_xyz, mmpld::colour_type::intensity64> view_type;
                typedef view_type::colour_value_type *c_t;
                typedef view_type::vertex_value_type *v_t;
                Assert::AreEqual(c_t(DATA + 12), view_type::colour(DATA), L"Colour pointer of colour_type::intensity64", LINE_INFO());
                Assert::AreEqual(v_t(DATA + 0), view_type::position(DATA), L"Position pointer of vertex_type::float_xyz", LINE_INFO());
                Assert::AreEqual(v_t(nullptr), view_type::radius(DATA), L"Radius pointer of vertex_type::float_xyz", LINE_INFO());
            }

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::float_xyz, mmpld::colour_type::none> view_type;
                typedef view_type::colour_value_type *c_t;
                typedef view_type::vertex_value_type *v_t;
                Assert::AreEqual(c_t(nullptr), view_type::colour(DATA), L"Colour pointer of colour_type::none", LINE_INFO());
                Assert::AreEqual(v_t(DATA + 0), view_type::position(DATA), L"Position pointer of vertex_value_type::float_xyz", LINE_INFO());
                Assert::AreEqual(v_t(nullptr), view_type::radius(DATA), L"Radius pointer of vertex_type::float_xyz", LINE_INFO());
            }

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::float_xyz, mmpld::colour_type::rgb32> view_type;
                typedef view_type::colour_value_type *c_t;
                typedef view_type::vertex_value_type *v_t;
                Assert::AreEqual(c_t(DATA + 12), view_type::colour(DATA), L"Colour pointer of colour_type::rgb32", LINE_INFO());
                Assert::AreEqual(v_t(DATA + 0), view_type::position(DATA), L"Position pointer of vertex_type::float_xyz", LINE_INFO());
                Assert::AreEqual(v_t(nullptr), view_type::radius(DATA), L"Radius pointer of vertex_type::float_xyz", LINE_INFO());
            }

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::float_xyz, mmpld::colour_type::rgb8> view_type;
                typedef view_type::colour_value_type *c_t;
                typedef view_type::vertex_value_type *v_t;
                Assert::AreEqual(c_t(DATA + 12), view_type::colour(DATA), L"Colour pointer of colour_type::rgb8", LINE_INFO());
                Assert::AreEqual(v_t(DATA + 0), view_type::position(DATA), L"Position pointer of vertex_type::float_xyz", LINE_INFO());
                Assert::AreEqual(v_t(nullptr), view_type::radius(DATA), L"Radius pointer of vertex_type::float_xyz", LINE_INFO());
            }

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::float_xyz, mmpld::colour_type::rgba32> view_type;
                typedef view_type::colour_value_type *c_t;
                typedef view_type::vertex_value_type *v_t;
                Assert::AreEqual(c_t(DATA + 12), view_type::colour(DATA), L"Colour pointer of colour_type::rgba32", LINE_INFO());
                Assert::AreEqual(v_t(DATA + 0), view_type::position(DATA), L"Position pointer of vertex_type::float_xyz", LINE_INFO());
                Assert::AreEqual(v_t(nullptr), view_type::radius(DATA), L"Radius pointer of vertex_type::float_xyz", LINE_INFO());
            }

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::float_xyz, mmpld::colour_type::rgba8> view_type;
                typedef view_type::colour_value_type *c_t;
                typedef view_type::vertex_value_type *v_t;
                Assert::AreEqual(c_t(DATA + 12), view_type::colour(DATA), L"Colour pointer of colour_type::rgba8", LINE_INFO());
                Assert::AreEqual(v_t(DATA + 0), view_type::position(DATA), L"Position pointer of vertex_type::float_xyz", LINE_INFO());
                Assert::AreEqual(v_t(nullptr), view_type::radius(DATA), L"Radius pointer of vertex_type::float_xyz", LINE_INFO());
            }

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::float_xyzr, mmpld::colour_type::intensity> view_type;
                typedef view_type::colour_value_type *c_t;
                typedef view_type::vertex_value_type *v_t;
                Assert::AreEqual(c_t(DATA + 16), view_type::colour(DATA), L"Colour pointer of colour_type::intensity", LINE_INFO());
                Assert::AreEqual(v_t(DATA + 0), view_type::position(DATA), L"Position pointer of vertex_type::float_xyzr", LINE_INFO());
                Assert::AreEqual(v_t(DATA + 12), view_type::radius(DATA), L"Radius pointer of vertex_type::float_xyzr", LINE_INFO());
            }

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::float_xyzr, mmpld::colour_type::intensity64> view_type;
                typedef view_type::colour_value_type *c_t;
                typedef view_type::vertex_value_type *v_t;
                Assert::AreEqual(c_t(DATA + 16), view_type::colour(DATA), L"Colour pointer of colour_type::intensity64", LINE_INFO());
                Assert::AreEqual(v_t(DATA + 0), view_type::position(DATA), L"Position pointer of vertex_type::float_xyzr", LINE_INFO());
                Assert::AreEqual(v_t(DATA + 12), view_type::radius(DATA), L"Radius pointer of vertex_type::float_xyzr", LINE_INFO());
            }

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::float_xyzr, mmpld::colour_type::none> view_type;
                typedef view_type::colour_value_type *c_t;
                typedef view_type::vertex_value_type *v_t;
                Assert::AreEqual(c_t(nullptr), view_type::colour(DATA), L"Colour pointer of colour_type::none", LINE_INFO());
                Assert::AreEqual(v_t(DATA + 0), view_type::position(DATA), L"Position pointer of vertex_type::float_xyzr", LINE_INFO());
                Assert::AreEqual(v_t(DATA + 12), view_type::radius(DATA), L"Radius pointer of vertex_type::float_xyzr", LINE_INFO());
            }

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::float_xyzr, mmpld::colour_type::rgb32> view_type;
                typedef view_type::colour_value_type *c_t;
                typedef view_type::vertex_value_type *v_t;
                Assert::AreEqual(c_t(DATA + 16), view_type::colour(DATA), L"Colour pointer of colour_type::rgb32", LINE_INFO());
                Assert::AreEqual(v_t(DATA + 0), view_type::position(DATA), L"Position pointer of vertex_type::float_xyzr", LINE_INFO());
                Assert::AreEqual(v_t(DATA + 12), view_type::radius(DATA), L"Radius pointer of vertex_type::float_xyzr", LINE_INFO());
            }

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::float_xyzr, mmpld::colour_type::rgb8> view_type;
                typedef view_type::colour_value_type *c_t;
                typedef view_type::vertex_value_type *v_t;
                Assert::AreEqual(c_t(DATA + 16), view_type::colour(DATA), L"Colour pointer of colour_type::rgb8", LINE_INFO());
                Assert::AreEqual(v_t(DATA + 0), view_type::position(DATA), L"Position pointer of vertex_type::float_xyzr", LINE_INFO());
                Assert::AreEqual(v_t(DATA + 12), view_type::radius(DATA), L"Radius pointer of vertex_type::float_xyzr", LINE_INFO());
            }

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::float_xyzr, mmpld::colour_type::rgba32> view_type;
                typedef view_type::colour_value_type *c_t;
                typedef view_type::vertex_value_type *v_t;
                Assert::AreEqual(c_t(DATA + 16), view_type::colour(DATA), L"Colour pointer of colour_type::rgba32", LINE_INFO());
                Assert::AreEqual(v_t(DATA + 0), view_type::position(DATA), L"Position pointer of vertex_type::float_xyzr", LINE_INFO());
                Assert::AreEqual(v_t(DATA + 12), view_type::radius(DATA), L"Radius pointer of vertex_type::float_xyzr", LINE_INFO());
            }

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::float_xyzr, mmpld::colour_type::rgba8> view_type;
                typedef view_type::colour_value_type *c_t;
                typedef view_type::vertex_value_type *v_t;
                Assert::AreEqual(c_t(DATA + 16), view_type::colour(DATA), L"Colour pointer of colour_type::rgba8", LINE_INFO());
                Assert::AreEqual(v_t(DATA + 0), view_type::position(DATA), L"Position pointer of vertex_type::float_xyzr", LINE_INFO());
                Assert::AreEqual(v_t(DATA + 12), view_type::radius(DATA), L"Radius pointer of vertex_type::float_xyzr", LINE_INFO());
            }

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::short_xyz, mmpld::colour_type::intensity> view_type;
                typedef view_type::colour_value_type *c_t;
                typedef view_type::vertex_value_type *v_t;
                Assert::AreEqual(c_t(DATA + 6), view_type::colour(DATA), L"Colour pointer of colour_type::intensity", LINE_INFO());
                Assert::AreEqual(v_t(DATA + 0), view_type::position(DATA), L"Position pointer of vertex_type::short_xyz", LINE_INFO());
                Assert::AreEqual(v_t(nullptr), view_type::radius(DATA), L"Radius pointer of vertex_type::short_xyz", LINE_INFO());
            }

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::short_xyz, mmpld::colour_type::intensity64> view_type;
                typedef view_type::colour_value_type *c_t;
                typedef view_type::vertex_value_type *v_t;
                Assert::AreEqual(c_t(DATA + 6), view_type::colour(DATA), L"Colour pointer of colour_type::intensity64", LINE_INFO());
                Assert::AreEqual(v_t(DATA + 0), view_type::position(DATA), L"Position pointer of vertex_type::short_xyz", LINE_INFO());
                Assert::AreEqual(v_t(nullptr), view_type::radius(DATA), L"Radius pointer of vertex_type::short_xyz", LINE_INFO());
            }

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::short_xyz, mmpld::colour_type::none> view_type;
                typedef view_type::colour_value_type *c_t;
                typedef view_type::vertex_value_type *v_t;
                Assert::AreEqual(c_t(nullptr), view_type::colour(DATA), L"Colour pointer of colour_type::none", LINE_INFO());
                Assert::AreEqual(v_t(DATA + 0), view_type::position(DATA), L"Position pointer of vertex_type::short_xyz", LINE_INFO());
                Assert::AreEqual(v_t(nullptr), view_type::radius(DATA), L"Radius pointer of vertex_type::short_xyz", LINE_INFO());
            }

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::short_xyz, mmpld::colour_type::rgb32> view_type;
                typedef view_type::colour_value_type *c_t;
                typedef view_type::vertex_value_type *v_t;
                Assert::AreEqual(c_t(DATA + 6), view_type::colour(DATA), L"Colour pointer of colour_type::rgb32", LINE_INFO());
                Assert::AreEqual(v_t(DATA + 0), view_type::position(DATA), L"Position pointer of vertex_type::short_xyz", LINE_INFO());
                Assert::AreEqual(v_t(nullptr), view_type::radius(DATA), L"Radius pointer of vertex_type::short_xyz", LINE_INFO());
            }

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::short_xyz, mmpld::colour_type::rgb8> view_type;
                typedef view_type::colour_value_type *c_t;
                typedef view_type::vertex_value_type *v_t;
                Assert::AreEqual(c_t(DATA + 6), view_type::colour(DATA), L"Colour pointer of colour_type::rgb8", LINE_INFO());
                Assert::AreEqual(v_t(DATA + 0), view_type::position(DATA), L"Position pointer of vertex_type::short_xyz", LINE_INFO());
                Assert::AreEqual(v_t(nullptr), view_type::radius(DATA), L"Radius pointer of vertex_type::short_xyz", LINE_INFO());
            }

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::short_xyz, mmpld::colour_type::rgba32> view_type;
                typedef view_type::colour_value_type *c_t;
                typedef view_type::vertex_value_type *v_t;
                Assert::AreEqual(c_t(DATA + 6), view_type::colour(DATA), L"Colour pointer of colour_type::rgba32", LINE_INFO());
                Assert::AreEqual(v_t(DATA + 0), view_type::position(DATA), L"Position pointer of vertex_type::short_xyz", LINE_INFO());
                Assert::AreEqual(v_t(nullptr), view_type::radius(DATA), L"Radius pointer of vertex_type::short_xyz", LINE_INFO());
            }

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::short_xyz, mmpld::colour_type::rgba8> view_type;
                typedef view_type::colour_value_type *c_t;
                typedef view_type::vertex_value_type *v_t;
                Assert::AreEqual(c_t(DATA + 6), view_type::colour(DATA), L"Colour pointer of colour_type::rgba8", LINE_INFO());
                Assert::AreEqual(v_t(DATA + 0), view_type::position(DATA), L"Position pointer of vertex_type::short_xyz", LINE_INFO());
                Assert::AreEqual(v_t(nullptr), view_type::radius(DATA), L"Radius pointer of vertex_type::short_xyz", LINE_INFO());
            }

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::double_xyz, mmpld::colour_type::intensity> view_type;
                typedef view_type::colour_value_type *c_t;
                typedef view_type::vertex_value_type *v_t;
                Assert::AreEqual(c_t(DATA + 24), view_type::colour(DATA), L"Colour pointer of colour_type::intensity", LINE_INFO());
                Assert::AreEqual(v_t(DATA + 0), view_type::position(DATA), L"Position pointer of vertex_type::double_xyz", LINE_INFO());
                Assert::AreEqual(v_t(nullptr), view_type::radius(DATA), L"Radius pointer of vertex_type::double_xyz", LINE_INFO());
            }

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::double_xyz, mmpld::colour_type::intensity> view_type;
                typedef view_type::colour_value_type *c_t;
                typedef view_type::vertex_value_type *v_t;
                Assert::AreEqual(c_t(DATA + 24), view_type::colour(DATA), L"Colour pointer of colour_type::intensity64", LINE_INFO());
                Assert::AreEqual(v_t(DATA + 0), view_type::position(DATA), L"Position pointer of vertex_type::double_xyz", LINE_INFO());
                Assert::AreEqual(v_t(nullptr), view_type::radius(DATA), L"Radius pointer of vertex_type::double_xyz", LINE_INFO());
            }

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::double_xyz, mmpld::colour_type::none> view_type;
                typedef view_type::colour_value_type *c_t;
                typedef view_type::vertex_value_type *v_t;
                Assert::AreEqual(c_t(nullptr), view_type::colour(DATA), L"Colour pointer of colour_type::none", LINE_INFO());
                Assert::AreEqual(v_t(DATA + 0), view_type::position(DATA), L"Position pointer of vertex_value_type::double_xyz", LINE_INFO());
                Assert::AreEqual(v_t(nullptr), view_type::radius(DATA), L"Radius pointer of vertex_type::double_xyz", LINE_INFO());
            }

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::double_xyz, mmpld::colour_type::rgb32> view_type;
                typedef view_type::colour_value_type *c_t;
                typedef view_type::vertex_value_type *v_t;
                Assert::AreEqual(c_t(DATA + 24), view_type::colour(DATA), L"Colour pointer of colour_type::rgb32", LINE_INFO());
                Assert::AreEqual(v_t(DATA + 0), view_type::position(DATA), L"Position pointer of vertex_type::double_xyz", LINE_INFO());
                Assert::AreEqual(v_t(nullptr), view_type::radius(DATA), L"Radius pointer of vertex_type::double_xyz", LINE_INFO());
            }

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::double_xyz, mmpld::colour_type::rgb8> view_type;
                typedef view_type::colour_value_type *c_t;
                typedef view_type::vertex_value_type *v_t;
                Assert::AreEqual(c_t(DATA + 24), view_type::colour(DATA), L"Colour pointer of colour_type::rgb8", LINE_INFO());
                Assert::AreEqual(v_t(DATA + 0), view_type::position(DATA), L"Position pointer of vertex_type::double_xyz", LINE_INFO());
                Assert::AreEqual(v_t(nullptr), view_type::radius(DATA), L"Radius pointer of vertex_type::double_xyz", LINE_INFO());
            }

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::double_xyz, mmpld::colour_type::rgba32> view_type;
                typedef view_type::colour_value_type *c_t;
                typedef view_type::vertex_value_type *v_t;
                Assert::AreEqual(c_t(DATA + 24), view_type::colour(DATA), L"Colour pointer of colour_type::rgba32", LINE_INFO());
                Assert::AreEqual(v_t(DATA + 0), view_type::position(DATA), L"Position pointer of vertex_type::double_xyz", LINE_INFO());
                Assert::AreEqual(v_t(nullptr), view_type::radius(DATA), L"Radius pointer of vertex_type::double_xyz", LINE_INFO());
            }

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::double_xyz, mmpld::colour_type::rgba8> view_type;
                typedef view_type::colour_value_type *c_t;
                typedef view_type::vertex_value_type *v_t;
                Assert::AreEqual(c_t(DATA + 24), view_type::colour(DATA), L"Colour pointer of colour_type::rgba8", LINE_INFO());
                Assert::AreEqual(v_t(DATA + 0), view_type::position(DATA), L"Position pointer of vertex_type::double_xyz", LINE_INFO());
                Assert::AreEqual(v_t(nullptr), view_type::radius(DATA), L"Radius pointer of vertex_type::double_xyz", LINE_INFO());
            }

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::double_xyz, mmpld::colour_type::intensity> lhs;
                typedef mmpld::particle_traits<mmpld::vertex_type::double_xyz, mmpld::colour_type::intensity> rhs;
                Assert::IsTrue(mmpld::is_same_format<lhs, rhs>(), L"Same formats detected by is_same_format", LINE_INFO());
            }

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::float_xyz, mmpld::colour_type::intensity> lhs;
                typedef mmpld::particle_traits<mmpld::vertex_type::double_xyz, mmpld::colour_type::intensity> rhs;
                Assert::IsFalse(mmpld::is_same_format<lhs, rhs>(), L"Different vertex formats detected by is_same_format", LINE_INFO());
            }

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::double_xyz, mmpld::colour_type::rgb32> lhs;
                typedef mmpld::particle_traits<mmpld::vertex_type::double_xyz, mmpld::colour_type::intensity> rhs;
                Assert::IsFalse(mmpld::is_same_format<lhs, rhs>(), L"Different colour formats detected by is_same_format", LINE_INFO());
            }

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::double_xyz, mmpld::colour_type::intensity> lhs;

                mmpld::list_header rhs = { };
                rhs.vertex_type = mmpld::vertex_type::double_xyz;
                rhs.colour_type = mmpld::colour_type::intensity;

                Assert::IsTrue(mmpld::is_same_format<lhs>(rhs), L"Same formats detected by is_same_format", LINE_INFO());
            }

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::float_xyz, mmpld::colour_type::intensity> lhs;

                mmpld::list_header rhs = { };
                rhs.vertex_type = mmpld::vertex_type::double_xyz;
                rhs.colour_type = mmpld::colour_type::intensity;

                Assert::IsFalse(mmpld::is_same_format<lhs>(rhs), L"Different vertex formats detected by is_same_format", LINE_INFO());
            }

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::double_xyz, mmpld::colour_type::rgb32> lhs;

                mmpld::list_header rhs = { };
                rhs.vertex_type = mmpld::vertex_type::double_xyz;
                rhs.colour_type = mmpld::colour_type::intensity;

                Assert::IsFalse(mmpld::is_same_format<lhs>(rhs), L"Different colour formats detected by is_same_format", LINE_INFO());
            }
        }

        TEST_METHOD(TestParticleView) {
            // Note: This test assumes that the traits are working correctly.
            typedef mmpld::particle_view<void> mutable_view;
            typedef mmpld::particle_view<const void> const_view;

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::float_xyz, mmpld::colour_type::intensity> src_view;
                std::vector<std::uint8_t> src(src_view::stride());

                const_view dst(src_view::vertex_type(), src_view::colour_type(), src.data());

                auto dst2 = dst;
                Assert::AreEqual(dst.byte_data(), dst2.byte_data(), L"Copy byte_data", LINE_INFO());
                Assert::AreEqual(dst.colour(), dst2.colour(), L"Copy colour", LINE_INFO());
                Assert::AreEqual(int(dst.colour_type()), int(dst2.colour_type()), L"Copy colour_type", LINE_INFO());
                Assert::AreEqual(dst.data(), dst2.data(), L"Copy data", LINE_INFO());
                Assert::AreEqual(dst.good(), dst2.good(), L"Copy good", LINE_INFO());
                Assert::AreEqual(dst.position(), dst2.position(), L"Copy position", LINE_INFO());
                Assert::AreEqual(dst.radius(), dst2.radius(), L"Copy radius", LINE_INFO());
                Assert::AreEqual(dst.stride(), dst2.stride(), L"Copy stride", LINE_INFO());
                Assert::AreEqual(int(dst.vertex_type()), int(dst2.vertex_type()), L"Copy vertex_type", LINE_INFO());

                auto dst3 = std::move(dst2);
                Assert::AreEqual(dst.byte_data(), dst3.byte_data(), L"Move byte_data", LINE_INFO());
                Assert::AreEqual(dst.colour(), dst3.colour(), L"Move colour", LINE_INFO());
                Assert::AreEqual(int(dst.colour_type()), int(dst3.colour_type()), L"Move colour_type", LINE_INFO());
                Assert::AreEqual(dst.data(), dst3.data(), L"Move data", LINE_INFO());
                Assert::AreEqual(dst.good(), dst3.good(), L"Move good", LINE_INFO());
                Assert::AreEqual(dst.position(), dst3.position(), L"Move position", LINE_INFO());
                Assert::AreEqual(dst.radius(), dst3.radius(), L"Move radius", LINE_INFO());
                Assert::AreEqual(dst.stride(), dst3.stride(), L"Move stride", LINE_INFO());
                Assert::AreEqual(int(dst.vertex_type()), int(dst3.vertex_type()), L"Move vertex_type", LINE_INFO());

                Assert::AreEqual(decltype(dst2.byte_data())(nullptr), dst2.byte_data(), L"Move erased byte_data", LINE_INFO());
                Assert::AreEqual(decltype(dst2.colour())(nullptr), dst2.colour(), L"Move erased colour", LINE_INFO());
                Assert::AreEqual(int(mmpld::colour_type::none), int(dst2.colour_type()), L"Move erased colour_type", LINE_INFO());
                Assert::AreEqual(decltype(dst2.data())(nullptr), dst2.data(), L"Move erased data", LINE_INFO());
                Assert::AreEqual(false, dst2.good(), L"Move erased good", LINE_INFO());
                Assert::AreEqual(decltype(dst2.position())(nullptr), dst2.position(), L"Move erased position", LINE_INFO());
                Assert::AreEqual(decltype(dst2.radius())(nullptr), dst2.radius(), L"Move erased radius", LINE_INFO());
                Assert::AreEqual(decltype(dst2.stride())(0), dst2.stride(), L"Move erased stride", LINE_INFO());
                Assert::AreEqual(int(mmpld::vertex_type::none), int(dst2.vertex_type()), L"Move erased vertex_type", LINE_INFO());
            }

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::float_xyz, mmpld::colour_type::intensity> src_view;
                std::vector<std::uint8_t> src(2 * src_view::stride());

                src_view::position(src.data())[0] = 1.0f;
                src_view::position(src.data())[1] = 2.0f;
                src_view::position(src.data())[2] = 3.0f;
                *src_view::colour(src.data()) = 0.5f;

                src_view::position(src.data() + src_view::stride())[0] = 4.0f;
                src_view::position(src.data() + src_view::stride())[1] = 5.0f;
                src_view::position(src.data() + src_view::stride())[2] = 6.0f;
                *src_view::colour(src.data() + src_view::stride()) = 1.0f;

                const_view dst(src_view::vertex_type(), src_view::colour_type(), src.data());
                Assert::AreEqual(src_view::position(src.data())[0], dst.position<src_view::vertex_traits::value>()[0], L"P1: View on position[0] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data())[1], dst.position<src_view::vertex_traits::value>()[1], L"P1: View on position[1] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data())[2], dst.position<src_view::vertex_traits::value>()[2], L"P1: View on position[2] correct", LINE_INFO());
                Assert::AreEqual((const void *) nullptr, dst.radius(), L"P1: View has no radius", LINE_INFO());
                Assert::AreEqual((const src_view::vertex_value_type *) nullptr, dst.radius<src_view::vertex_traits::value>(), L"P1: View has no radius", LINE_INFO());
                Assert::AreEqual(src_view::colour(src.data())[0], dst.colour<src_view::colour_traits::colour_type>()[0], L"P1: View on colour correct", LINE_INFO());

                dst.advance();
                Assert::AreEqual(src_view::position(src.data() + src_view::stride())[0], dst.position<src_view::vertex_traits::value>()[0], L"P2: View on position[0] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data() + src_view::stride())[1], dst.position<src_view::vertex_traits::value>()[1], L"P2: View on position[1] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data() + src_view::stride())[2], dst.position<src_view::vertex_traits::value>()[2], L"P2: View on position[2] correct", LINE_INFO());
                Assert::AreEqual((const void *) nullptr, dst.radius(), L"P2: View has no radius", LINE_INFO());
                Assert::AreEqual((const src_view::vertex_value_type *) nullptr, dst.radius<src_view::vertex_traits::value>(), L"P2: View has no radius", LINE_INFO());
                Assert::AreEqual(src_view::colour(src.data() + src_view::stride())[0], dst.colour<src_view::colour_traits::colour_type>()[0], L"P2: View on colour correct", LINE_INFO());
            }

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::float_xyzr, mmpld::colour_type::rgb32> src_view;
                std::vector<std::uint8_t> src(2 * src_view::stride());

                src_view::position(src.data())[0] = 1.0f;
                src_view::position(src.data())[1] = 2.0f;
                src_view::position(src.data())[2] = 3.0f;
                src_view::position(src.data())[3] = 10.0f;
                src_view::colour(src.data())[0] = 0.1f;
                src_view::colour(src.data())[1] = 0.2f;
                src_view::colour(src.data())[2] = 0.3f;

                src_view::position(src.data() + src_view::stride())[0] = 4.0f;
                src_view::position(src.data() + src_view::stride())[1] = 5.0f;
                src_view::position(src.data() + src_view::stride())[2] = 6.0f;
                src_view::position(src.data() + src_view::stride())[3] = 20.0f;
                src_view::colour(src.data() + src_view::stride())[0] = 0.5f;
                src_view::colour(src.data() + src_view::stride())[1] = 0.6f;
                src_view::colour(src.data() + src_view::stride())[2] = 0.7f;

                mutable_view dst(src_view::vertex_type(), src_view::colour_type(), src.data());
                Assert::AreEqual(src_view::position(src.data())[0], dst.position<src_view::vertex_traits::value>()[0], L"P1: View on position[0] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data())[1], dst.position<src_view::vertex_traits::value>()[1], L"P1: View on position[1] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data())[2], dst.position<src_view::vertex_traits::value>()[2], L"P1: View on position[2] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data())[3], dst.position<src_view::vertex_traits::value>()[3], L"P1: View on position[3] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data())[3], *dst.radius<src_view::vertex_traits::value>(), L"P1: View on radius correct", LINE_INFO());
                Assert::AreEqual(src_view::colour(src.data())[0], dst.colour<src_view::colour_traits::colour_type>()[0], L"P2: View on colour[0] correct", LINE_INFO());
                Assert::AreEqual(src_view::colour(src.data())[1], dst.colour<src_view::colour_traits::colour_type>()[1], L"P2: View on colour[1] correct", LINE_INFO());
                Assert::AreEqual(src_view::colour(src.data())[2], dst.colour<src_view::colour_traits::colour_type>()[2], L"P2: View on colour[2] correct", LINE_INFO());

                dst.advance();
                Assert::AreEqual(src_view::position(src.data() + src_view::stride())[0], dst.position<src_view::vertex_traits::value>()[0], L"P1: View on position[0] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data() + src_view::stride())[1], dst.position<src_view::vertex_traits::value>()[1], L"P1: View on position[1] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data() + src_view::stride())[2], dst.position<src_view::vertex_traits::value>()[2], L"P1: View on position[2] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data() + src_view::stride())[3], dst.position<src_view::vertex_traits::value>()[3], L"P1: View on position[3] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data() + src_view::stride())[3], *dst.radius<src_view::vertex_traits::value>(), L"P1: View on radius correct", LINE_INFO());
                Assert::AreEqual(src_view::colour(src.data() + src_view::stride())[0], dst.colour<src_view::colour_traits::colour_type>()[0], L"P2: View on colour[0] correct", LINE_INFO());
                Assert::AreEqual(src_view::colour(src.data() + src_view::stride())[1], dst.colour<src_view::colour_traits::colour_type>()[1], L"P2: View on colour[1] correct", LINE_INFO());
                Assert::AreEqual(src_view::colour(src.data() + src_view::stride())[2], dst.colour<src_view::colour_traits::colour_type>()[2], L"P2: View on colour[2] correct", LINE_INFO());
            }

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::float_xyzr, mmpld::colour_type::rgba8> src_view;
                std::vector<std::uint8_t> src(2 * src_view::stride());

                src_view::position(src.data())[0] = 1.0f;
                src_view::position(src.data())[1] = 2.0f;
                src_view::position(src.data())[2] = 3.0f;
                src_view::position(src.data())[3] = 10.0f;
                src_view::colour(src.data())[0] = 0;
                src_view::colour(src.data())[1] = 16;
                src_view::colour(src.data())[2] = 32;
                src_view::colour(src.data())[3] = 1;

                src_view::position(src.data() + src_view::stride())[0] = 4.0f;
                src_view::position(src.data() + src_view::stride())[1] = 5.0f;
                src_view::position(src.data() + src_view::stride())[2] = 6.0f;
                src_view::position(src.data() + src_view::stride())[3] = 20.0f;
                src_view::colour(src.data() + src_view::stride())[0] = 64;
                src_view::colour(src.data() + src_view::stride())[1] = 128;
                src_view::colour(src.data() + src_view::stride())[2] = 255;
                src_view::colour(src.data() + src_view::stride())[2] = 2;

                const_view dst(src_view::vertex_type(), src_view::colour_type(), src.data());
                Assert::AreEqual(src_view::position(src.data())[0], dst.position<src_view::vertex_traits::value>()[0], L"P1: View on position[0] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data())[1], dst.position<src_view::vertex_traits::value>()[1], L"P1: View on position[1] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data())[2], dst.position<src_view::vertex_traits::value>()[2], L"P1: View on position[2] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data())[3], dst.position<src_view::vertex_traits::value>()[3], L"P1: View on position[3] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data())[3], *dst.radius<src_view::vertex_traits::value>(), L"P1: View on radius correct", LINE_INFO());
                Assert::AreEqual(src_view::colour(src.data())[0], dst.colour<src_view::colour_traits::colour_type>()[0], L"P2: View on colour[0] correct", LINE_INFO());
                Assert::AreEqual(src_view::colour(src.data())[1], dst.colour<src_view::colour_traits::colour_type>()[1], L"P2: View on colour[1] correct", LINE_INFO());
                Assert::AreEqual(src_view::colour(src.data())[2], dst.colour<src_view::colour_traits::colour_type>()[2], L"P2: View on colour[2] correct", LINE_INFO());
                Assert::AreEqual(src_view::colour(src.data())[3], dst.colour<src_view::colour_traits::colour_type>()[3], L"P2: View on colour[3] correct", LINE_INFO());

                dst.advance();
                Assert::AreEqual(src_view::position(src.data() + src_view::stride())[0], dst.position<src_view::vertex_traits::value>()[0], L"P1: View on position[0] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data() + src_view::stride())[1], dst.position<src_view::vertex_traits::value>()[1], L"P1: View on position[1] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data() + src_view::stride())[2], dst.position<src_view::vertex_traits::value>()[2], L"P1: View on position[2] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data() + src_view::stride())[3], dst.position<src_view::vertex_traits::value>()[3], L"P1: View on position[3] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data() + src_view::stride())[3], *dst.radius<src_view::vertex_traits::value>(), L"P1: View on radius correct", LINE_INFO());
                Assert::AreEqual(src_view::colour(src.data() + src_view::stride())[0], dst.colour<src_view::colour_traits::colour_type>()[0], L"P2: View on colour[0] correct", LINE_INFO());
                Assert::AreEqual(src_view::colour(src.data() + src_view::stride())[1], dst.colour<src_view::colour_traits::colour_type>()[1], L"P2: View on colour[1] correct", LINE_INFO());
                Assert::AreEqual(src_view::colour(src.data() + src_view::stride())[2], dst.colour<src_view::colour_traits::colour_type>()[2], L"P2: View on colour[2] correct", LINE_INFO());
                Assert::AreEqual(src_view::colour(src.data() + src_view::stride())[3], dst.colour<src_view::colour_traits::colour_type>()[3], L"P2: View on colour[3] correct", LINE_INFO());
            }

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::double_xyz, mmpld::colour_type::intensity64> src_view;
                std::vector<std::uint8_t> src(2 * src_view::stride());

                src_view::position(src.data())[0] = 1.0;
                src_view::position(src.data())[1] = 2.0;
                src_view::position(src.data())[2] = 3.0;
                src_view::position(src.data())[3] = 10.0;
                src_view::colour(src.data())[0] = 0.0;

                src_view::position(src.data() + src_view::stride())[0] = 4.0;
                src_view::position(src.data() + src_view::stride())[1] = 5.0;
                src_view::position(src.data() + src_view::stride())[2] = 6.0;
                src_view::position(src.data() + src_view::stride())[3] = 20.0;
                src_view::colour(src.data() + src_view::stride())[0] = 1.0;

                const_view dst(src_view::vertex_type(), src_view::colour_type(), src.data());
                Assert::AreEqual(src_view::position(src.data())[0], dst.position<src_view::vertex_traits::value>()[0], L"P1: View on position[0] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data())[1], dst.position<src_view::vertex_traits::value>()[1], L"P1: View on position[1] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data())[2], dst.position<src_view::vertex_traits::value>()[2], L"P1: View on position[2] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data())[3], dst.position<src_view::vertex_traits::value>()[3], L"P1: View on position[3] correct", LINE_INFO());
                Assert::AreEqual(src_view::colour(src.data())[0], dst.colour<src_view::colour_traits::colour_type>()[0], L"P1: View on intensity correct", LINE_INFO());

                dst.advance();
                Assert::AreEqual(src_view::position(src.data() + src_view::stride())[0], dst.position<src_view::vertex_traits::value>()[0], L"P2: View on position[0] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data() + src_view::stride())[1], dst.position<src_view::vertex_traits::value>()[1], L"P2: View on position[1] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data() + src_view::stride())[2], dst.position<src_view::vertex_traits::value>()[2], L"P2: View on position[2] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data() + src_view::stride())[3], dst.position<src_view::vertex_traits::value>()[3], L"P2: View on position[3] correct", LINE_INFO());
                Assert::AreEqual(src_view::colour(src.data() + src_view::stride())[0], dst.colour<src_view::colour_traits::colour_type>()[0], L"P2: View on intensity correct", LINE_INFO());
            }

            {
                mmpld::particle_view<> lhs(mmpld::vertex_type::double_xyz, mmpld::colour_type::intensity);
                mmpld::particle_view<> rhs(mmpld::vertex_type::double_xyz, mmpld::colour_type::intensity);
                Assert::IsTrue(mmpld::is_same_format(lhs, rhs), L"Same formats detected by is_same_format", LINE_INFO());
            }

            {
                mmpld::particle_view<> lhs(mmpld::vertex_type::double_xyz, mmpld::colour_type::intensity);
                mmpld::particle_view<> rhs(mmpld::vertex_type::float_xyz, mmpld::colour_type::intensity);
                Assert::IsFalse(mmpld::is_same_format(lhs, rhs), L"Different vertex formats detected by is_same_format", LINE_INFO());
            }

            {
                mmpld::particle_view<> lhs(mmpld::vertex_type::double_xyz, mmpld::colour_type::intensity);
                mmpld::particle_view<> rhs(mmpld::vertex_type::double_xyz, mmpld::colour_type::rgb32);
                Assert::IsFalse(mmpld::is_same_format(lhs, rhs), L"Different colour formats detected by is_same_format", LINE_INFO());
            }

            {
                mmpld::particle_view<> lhs(mmpld::vertex_type::double_xyz, mmpld::colour_type::intensity);

                mmpld::list_header rhs = { };
                rhs.vertex_type = mmpld::vertex_type::double_xyz;
                rhs.colour_type = mmpld::colour_type::intensity;

                Assert::IsTrue(mmpld::is_same_format(lhs, rhs), L"Same formats detected by is_same_format", LINE_INFO());
            }

            {
                mmpld::particle_view<> lhs(mmpld::vertex_type::double_xyz, mmpld::colour_type::intensity);

                mmpld::list_header rhs = { };
                rhs.vertex_type = mmpld::vertex_type::float_xyz;
                rhs.colour_type = mmpld::colour_type::intensity;

                Assert::IsFalse(mmpld::is_same_format(lhs, rhs), L"Different vertex formats detected by is_same_format", LINE_INFO());
            }

            {
                mmpld::particle_view<> lhs(mmpld::vertex_type::double_xyz, mmpld::colour_type::intensity);

                mmpld::list_header rhs = { };
                rhs.vertex_type = mmpld::vertex_type::double_xyz;
                rhs.colour_type = mmpld::colour_type::rgb32;

                Assert::IsFalse(mmpld::is_same_format(lhs, rhs), L"Different colour formats detected by is_same_format", LINE_INFO());
            }

            {
                mmpld::particle_view<std::int8_t> lhs(mmpld::vertex_type::double_xyz, mmpld::colour_type::intensity);
                mmpld::particle_view<> rhs(mmpld::vertex_type::double_xyz, mmpld::colour_type::intensity);
                Assert::IsTrue(mmpld::is_same_format(lhs, rhs), L"Same formats detected by is_same_format", LINE_INFO());
            }

            {
                mmpld::particle_view<std::int8_t> lhs(mmpld::vertex_type::double_xyz, mmpld::colour_type::intensity);
                mmpld::particle_view<> rhs(mmpld::vertex_type::float_xyz, mmpld::colour_type::intensity);
                Assert::IsFalse(mmpld::is_same_format(lhs, rhs), L"Different vertex formats detected by is_same_format", LINE_INFO());
            }

            {
                mmpld::particle_view<std::int8_t> lhs(mmpld::vertex_type::double_xyz, mmpld::colour_type::intensity);
                mmpld::particle_view<> rhs(mmpld::vertex_type::double_xyz, mmpld::colour_type::rgb32);
                Assert::IsFalse(mmpld::is_same_format(lhs, rhs), L"Different colour formats detected by is_same_format", LINE_INFO());
            }

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::double_xyz, mmpld::colour_type::intensity> lhs;
                mmpld::particle_view<> rhs(mmpld::vertex_type::double_xyz, mmpld::colour_type::intensity);
                Assert::IsTrue(mmpld::is_same_format<lhs>(rhs), L"Same formats detected by is_same_format", LINE_INFO());
            }

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::float_xyz, mmpld::colour_type::intensity> lhs;
                mmpld::particle_view<> rhs(mmpld::vertex_type::double_xyz, mmpld::colour_type::intensity);
                Assert::IsFalse(mmpld::is_same_format<lhs>(rhs), L"Different vertex formats detected by is_same_format", LINE_INFO());
            }

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::double_xyz, mmpld::colour_type::rgb32> lhs;
                mmpld::particle_view<> rhs(mmpld::vertex_type::double_xyz, mmpld::colour_type::intensity);
                Assert::IsFalse(mmpld::is_same_format<lhs>(rhs), L"Different colour formats detected by is_same_format", LINE_INFO());
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
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_radius)), L"per_particle_radius of float_xyz + none", LINE_INFO());
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_colour)), L"per_particle_colour of float_xyz + none", LINE_INFO());
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_intensity)), L"per_particle_intensity of float_xyz + none", LINE_INFO());
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::float_colour)), L"float_colour of float_xyz + none", LINE_INFO());

            header.colour_type = mmpld::colour_type::none;
            header.vertex_type = mmpld::vertex_type::float_xyzr;
            props = mmpld::get_properties<decltype(props)>(header);
            Assert::AreEqual(p_t(pp_t::per_particle_radius), (props & p_t(pp_t::per_particle_radius)), L"per_particle_radius of float_xyzr + none", LINE_INFO());
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_colour)), L"per_particle_colour of float_xyzr + none", LINE_INFO());
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_intensity)), L"per_particle_intensity of float_xyzr + none", LINE_INFO());
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::float_colour)), L"float_colour of float_xyzr + none", LINE_INFO());

            header.colour_type = mmpld::colour_type::none;
            header.vertex_type = mmpld::vertex_type::short_xyz;
            props = mmpld::get_properties<decltype(props)>(header);
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_radius)), L"per_particle_radius of short_xyz + none", LINE_INFO());
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_colour)), L"per_particle_colour of short_xyz + none", LINE_INFO());
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_intensity)), L"per_particle_intensity of short_xyz + none", LINE_INFO());
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::float_colour)), L"float_colour of short_xyz + none", LINE_INFO());

            header.colour_type = mmpld::colour_type::intensity;
            header.vertex_type = mmpld::vertex_type::float_xyz;
            props = mmpld::get_properties<decltype(props)>(header);
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_radius)), L"per_particle_radius of float_xyz + intensity", LINE_INFO());
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_colour)), L"per_particle_colour of float_xyz + intensity", LINE_INFO());
            Assert::AreEqual(p_t(pp_t::per_particle_intensity), (props & p_t(pp_t::per_particle_intensity)), L"per_particle_intensity of float_xyz + intensity", LINE_INFO());
            Assert::AreEqual(p_t(pp_t::float_colour), (props & p_t(pp_t::float_colour)), L"float_colour of float_xyz + intensity", LINE_INFO());

            header.colour_type = mmpld::colour_type::intensity;
            header.vertex_type = mmpld::vertex_type::float_xyzr;
            props = mmpld::get_properties<decltype(props)>(header);
            Assert::AreEqual(p_t(pp_t::per_particle_radius), (props & p_t(pp_t::per_particle_radius)), L"per_particle_radius of float_xyzr + intensity", LINE_INFO());
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_colour)), L"per_particle_colour of float_xyzr + intensity", LINE_INFO());
            Assert::AreEqual(p_t(pp_t::per_particle_intensity), (props & p_t(pp_t::per_particle_intensity)), L"per_particle_intensity of float_xyzr + intensity", LINE_INFO());
            Assert::AreEqual(p_t(pp_t::float_colour), (props & p_t(pp_t::float_colour)), L"float_colour of float_xyzr + intensity", LINE_INFO());

            header.colour_type = mmpld::colour_type::intensity;
            header.vertex_type = mmpld::vertex_type::short_xyz;
            props = mmpld::get_properties<decltype(props)>(header);
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_radius)), L"per_particle_radius of short_xyz + intensity", LINE_INFO());
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_colour)), L"per_particle_colour of short_xyz + intensity", LINE_INFO());
            Assert::AreEqual(p_t(pp_t::per_particle_intensity), (props & p_t(pp_t::per_particle_intensity)), L"per_particle_intensity of short_xyz + intensity", LINE_INFO());
            Assert::AreEqual(p_t(pp_t::float_colour), (props & p_t(pp_t::float_colour)), L"float_colour of short_xyz + intensity", LINE_INFO());

            header.colour_type = mmpld::colour_type::rgb8;
            header.vertex_type = mmpld::vertex_type::float_xyz;
            props = mmpld::get_properties<decltype(props)>(header);
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_radius)), L"per_particle_radius of float_xyz + rgb8", LINE_INFO());
            Assert::AreEqual(p_t(pp_t::per_particle_colour), (props & p_t(pp_t::per_particle_colour)), L"per_particle_colour of float_xyz + rgb8", LINE_INFO());
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_intensity)), L"per_particle_intensity of float_xyz + rgb8", LINE_INFO());
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::float_colour)), L"float_colour of float_xyz + rgb8", LINE_INFO());

            header.colour_type = mmpld::colour_type::rgb8;
            header.vertex_type = mmpld::vertex_type::float_xyzr;
            props = mmpld::get_properties<decltype(props)>(header);
            Assert::AreEqual(p_t(pp_t::per_particle_radius), (props & p_t(pp_t::per_particle_radius)), L"per_particle_radius of float_xyzr + rgb8", LINE_INFO());
            Assert::AreEqual(p_t(pp_t::per_particle_colour), (props & p_t(pp_t::per_particle_colour)), L"per_particle_colour of float_xyzr + rgb8", LINE_INFO());
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_intensity)), L"per_particle_intensity of float_xyzr + rgb8", LINE_INFO());
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::float_colour)), L"float_colour of float_xyzr + rgb8", LINE_INFO());

            header.colour_type = mmpld::colour_type::rgb8;
            header.vertex_type = mmpld::vertex_type::short_xyz;
            props = mmpld::get_properties<decltype(props)>(header);
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_radius)), L"per_particle_radius of short_xyz + rgb8", LINE_INFO());
            Assert::AreEqual(p_t(pp_t::per_particle_colour), (props & p_t(pp_t::per_particle_colour)), L"per_particle_colour of short_xyz + rgb8", LINE_INFO());
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_intensity)), L"per_particle_intensity of short_xyz + rgb8", LINE_INFO());
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::float_colour)), L"float_colour of short_xyz + rgb8", LINE_INFO());

            header.colour_type = mmpld::colour_type::rgba8;
            header.vertex_type = mmpld::vertex_type::float_xyz;
            props = mmpld::get_properties<decltype(props)>(header);
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_radius)), L"per_particle_radius of float_xyz + rgba8", LINE_INFO());
            Assert::AreEqual(p_t(pp_t::per_particle_colour), (props & p_t(pp_t::per_particle_colour)), L"per_particle_colour of float_xyz + rgba8", LINE_INFO());
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_intensity)), L"per_particle_intensity of float_xyz + rgba8", LINE_INFO());
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::float_colour)), L"float_colour of float_xyz + rgba8", LINE_INFO());

            header.colour_type = mmpld::colour_type::rgba8;
            header.vertex_type = mmpld::vertex_type::float_xyzr;
            props = mmpld::get_properties<decltype(props)>(header);
            Assert::AreEqual(p_t(pp_t::per_particle_radius), (props & p_t(pp_t::per_particle_radius)), L"per_particle_radius of float_xyzr + rgba8", LINE_INFO());
            Assert::AreEqual(p_t(pp_t::per_particle_colour), (props & p_t(pp_t::per_particle_colour)), L"per_particle_colour of float_xyzr + rgba8", LINE_INFO());
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_intensity)), L"per_particle_intensity of float_xyzr + rgba8", LINE_INFO());
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::float_colour)), L"float_colour of float_xyzr + rgba8", LINE_INFO());

            header.colour_type = mmpld::colour_type::rgba8;
            header.vertex_type = mmpld::vertex_type::short_xyz;
            props = mmpld::get_properties<decltype(props)>(header);
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_radius)), L"per_particle_radius of short_xyz + rgba8", LINE_INFO());
            Assert::AreEqual(p_t(pp_t::per_particle_colour), (props & p_t(pp_t::per_particle_colour)), L"per_particle_colour of short_xyz + rgba8", LINE_INFO());
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_intensity)), L"per_particle_intensity of short_xyz + rgba8", LINE_INFO());
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::float_colour)), L"float_colour of short_xyz + rgba8", LINE_INFO());

            header.colour_type = mmpld::colour_type::rgb32;
            header.vertex_type = mmpld::vertex_type::float_xyz;
            props = mmpld::get_properties<decltype(props)>(header);
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_radius)), L"per_particle_radius of float_xyz + rgb32", LINE_INFO());
            Assert::AreEqual(p_t(pp_t::per_particle_colour), (props & p_t(pp_t::per_particle_colour)), L"per_particle_colour of float_xyz + rgb32", LINE_INFO());
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_intensity)), L"per_particle_intensity of float_xyz + rgb32", LINE_INFO());
            Assert::AreEqual(p_t(pp_t::float_colour), (props & p_t(pp_t::float_colour)), L"float_colour of float_xyz + rgb32", LINE_INFO());

            header.colour_type = mmpld::colour_type::rgb32;
            header.vertex_type = mmpld::vertex_type::float_xyzr;
            props = mmpld::get_properties<decltype(props)>(header);
            Assert::AreEqual(p_t(pp_t::per_particle_radius), (props & p_t(pp_t::per_particle_radius)), L"per_particle_radius of float_xyzr + rgb32", LINE_INFO());
            Assert::AreEqual(p_t(pp_t::per_particle_colour), (props & p_t(pp_t::per_particle_colour)), L"per_particle_colour of float_xyzr + rgb32", LINE_INFO());
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_intensity)), L"per_particle_intensity of float_xyzr + rgb32", LINE_INFO());
            Assert::AreEqual(p_t(pp_t::float_colour), (props & p_t(pp_t::float_colour)), L"float_colour of float_xyzr + rgb32", LINE_INFO());

            header.colour_type = mmpld::colour_type::rgb32;
            header.vertex_type = mmpld::vertex_type::short_xyz;
            props = mmpld::get_properties<decltype(props)>(header);
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_radius)), L"per_particle_radius of short_xyz + rgb32", LINE_INFO());
            Assert::AreEqual(p_t(pp_t::per_particle_colour), (props & p_t(pp_t::per_particle_colour)), L"per_particle_colour of short_xyz + rgb32", LINE_INFO());
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_intensity)), L"per_particle_intensity of short_xyz + rgb32", LINE_INFO());
            Assert::AreEqual(p_t(pp_t::float_colour), (props & p_t(pp_t::float_colour)), L"float_colour of short_xyz + rgb32", LINE_INFO());

            header.colour_type = mmpld::colour_type::rgba32;
            header.vertex_type = mmpld::vertex_type::float_xyz;
            props = mmpld::get_properties<decltype(props)>(header);
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_radius)), L"per_particle_radius of float_xyz + rgba32", LINE_INFO());
            Assert::AreEqual(p_t(pp_t::per_particle_colour), (props & p_t(pp_t::per_particle_colour)), L"per_particle_colour of float_xyz + rgba32", LINE_INFO());
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_intensity)), L"per_particle_intensity of float_xyz + rgba32", LINE_INFO());
            Assert::AreEqual(p_t(pp_t::float_colour), (props & p_t(pp_t::float_colour)), L"float_colour of float_xyz + rgba32", LINE_INFO());

            header.colour_type = mmpld::colour_type::rgba32;
            header.vertex_type = mmpld::vertex_type::float_xyzr;
            props = mmpld::get_properties<decltype(props)>(header);
            Assert::AreEqual(p_t(pp_t::per_particle_radius), (props & p_t(pp_t::per_particle_radius)), L"per_particle_radius of float_xyzr + rgba32", LINE_INFO());
            Assert::AreEqual(p_t(pp_t::per_particle_colour), (props & p_t(pp_t::per_particle_colour)), L"per_particle_colour of float_xyzr + rgba32", LINE_INFO());
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_intensity)), L"per_particle_intensity of float_xyzr + rgba32", LINE_INFO());
            Assert::AreEqual(p_t(pp_t::float_colour), (props & p_t(pp_t::float_colour)), L"float_colour of float_xyzr + rgba32", LINE_INFO());

            header.colour_type = mmpld::colour_type::rgba32;
            header.vertex_type = mmpld::vertex_type::short_xyz;
            props = mmpld::get_properties<decltype(props)>(header);
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_radius)), L"per_particle_radius of short_xyz + rgba32", LINE_INFO());
            Assert::AreEqual(p_t(pp_t::per_particle_colour), (props & p_t(pp_t::per_particle_colour)), L"per_particle_colour of short_xyz + rgba32", LINE_INFO());
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_intensity)), L"per_particle_intensity of short_xyz + rgba32", LINE_INFO());
            Assert::AreEqual(p_t(pp_t::float_colour), (props & p_t(pp_t::float_colour)), L"float_colour of short_xyz + rgba32", LINE_INFO());

            header.colour_type = mmpld::colour_type::intensity64;
            header.vertex_type = mmpld::vertex_type::double_xyz;
            props = mmpld::get_properties<decltype(props)>(header);
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_radius)), L"per_particle_radius of double_xyz + intensity64", LINE_INFO());
            Assert::AreEqual(p_t(0), (props & p_t(pp_t::per_particle_colour)), L"per_particle_colour of double_xyz + intensity64", LINE_INFO());
            Assert::AreEqual(p_t(pp_t::per_particle_intensity), (props & p_t(pp_t::per_particle_intensity)), L"per_particle_intensity of double_xyz + intensity64", LINE_INFO());
            Assert::AreEqual(p_t(pp_t::float_colour), (props & p_t(pp_t::float_colour)), L"float_colour of double_xyz + intensity64", LINE_INFO());
        }

        TEST_METHOD(TestStride) {
            mmpld::list_header header;

            header.colour_type = mmpld::colour_type::none;
            header.vertex_type = mmpld::vertex_type::float_xyz;
            Assert::AreEqual(size_t(3 * sizeof(float)), mmpld::get_stride<size_t>(header), L"Stride of float_xyz + none", LINE_INFO());

            header.colour_type = mmpld::colour_type::none;
            header.vertex_type = mmpld::vertex_type::float_xyzr;
            Assert::AreEqual(size_t(4 * sizeof(float)), mmpld::get_stride<size_t>(header), L"Stride of float_xyzr + none", LINE_INFO());

            header.colour_type = mmpld::colour_type::none;
            header.vertex_type = mmpld::vertex_type::short_xyz;
            Assert::AreEqual(size_t(3 * sizeof(short)), mmpld::get_stride<size_t>(header), L"Stride of short_xyz + none", LINE_INFO());

            header.colour_type = mmpld::colour_type::none;
            header.vertex_type = mmpld::vertex_type::double_xyz;
            Assert::AreEqual(size_t(3 * sizeof(double)), mmpld::get_stride<size_t>(header), L"Stride of double_xyz + none", LINE_INFO());

            header.colour_type = mmpld::colour_type::intensity;
            header.vertex_type = mmpld::vertex_type::float_xyz;
            Assert::AreEqual(size_t(3 * sizeof(float) + sizeof(float)), mmpld::get_stride<size_t>(header), L"Stride of float_xyz + intensity", LINE_INFO());

            header.colour_type = mmpld::colour_type::intensity;
            header.vertex_type = mmpld::vertex_type::float_xyzr;
            Assert::AreEqual(size_t(4 * sizeof(float) + sizeof(float)), mmpld::get_stride<size_t>(header), L"Stride of float_xyzr + intensity", LINE_INFO());

            header.colour_type = mmpld::colour_type::intensity;
            header.vertex_type = mmpld::vertex_type::short_xyz;
            Assert::AreEqual(size_t(3 * sizeof(short) + sizeof(float)), mmpld::get_stride<size_t>(header), L"Stride of short_xyz + intensity", LINE_INFO());

            header.colour_type = mmpld::colour_type::intensity64;
            header.vertex_type = mmpld::vertex_type::float_xyz;
            Assert::AreEqual(size_t(3 * sizeof(float) + sizeof(double)), mmpld::get_stride<size_t>(header), L"Stride of float_xyz + intensity64", LINE_INFO());

            header.colour_type = mmpld::colour_type::intensity64;
            header.vertex_type = mmpld::vertex_type::float_xyzr;
            Assert::AreEqual(size_t(4 * sizeof(float) + sizeof(double)), mmpld::get_stride<size_t>(header), L"Stride of float_xyzr + intensity64", LINE_INFO());

            header.colour_type = mmpld::colour_type::intensity64;
            header.vertex_type = mmpld::vertex_type::short_xyz;
            Assert::AreEqual(size_t(3 * sizeof(short) + sizeof(double)), mmpld::get_stride<size_t>(header), L"Stride of short_xyz + intensity64", LINE_INFO());

            header.colour_type = mmpld::colour_type::intensity64;
            header.vertex_type = mmpld::vertex_type::double_xyz;
            Assert::AreEqual(size_t(3 * sizeof(double) + sizeof(double)), mmpld::get_stride<size_t>(header), L"Stride of double_xyz + intensity64", LINE_INFO());

            header.colour_type = mmpld::colour_type::rgb8;
            header.vertex_type = mmpld::vertex_type::float_xyz;
            Assert::AreEqual(size_t(3 * sizeof(float) + 3 * sizeof(char)), mmpld::get_stride<size_t>(header), L"Stride of float_xyz + rgb8", LINE_INFO());

            header.colour_type = mmpld::colour_type::rgb8;
            header.vertex_type = mmpld::vertex_type::float_xyzr;
            Assert::AreEqual(size_t(4 * sizeof(float) + 3 * sizeof(char)), mmpld::get_stride<size_t>(header), L"Stride of float_xyzr + rgb8", LINE_INFO());

            header.colour_type = mmpld::colour_type::rgb8;
            header.vertex_type = mmpld::vertex_type::short_xyz;
            Assert::AreEqual(size_t(3 * sizeof(short) + 3 * sizeof(char)), mmpld::get_stride<size_t>(header), L"Stride of short_xyz + rgb8", LINE_INFO());

            header.colour_type = mmpld::colour_type::rgba8;
            header.vertex_type = mmpld::vertex_type::float_xyz;
            Assert::AreEqual(size_t(3 * sizeof(float) + 4 * sizeof(char)), mmpld::get_stride<size_t>(header), L"Stride of float_xyz + rgba8", LINE_INFO());

            header.colour_type = mmpld::colour_type::rgba8;
            header.vertex_type = mmpld::vertex_type::float_xyzr;
            Assert::AreEqual(size_t(4 * sizeof(float) + 4 * sizeof(char)), mmpld::get_stride<size_t>(header), L"Stride of float_xyzr + rgba8", LINE_INFO());

            header.colour_type = mmpld::colour_type::rgba8;
            header.vertex_type = mmpld::vertex_type::short_xyz;
            Assert::AreEqual(size_t(3 * sizeof(short) + 4 * sizeof(char)), mmpld::get_stride<size_t>(header), L"Stride of short_xyz + rgba8", LINE_INFO());

            header.colour_type = mmpld::colour_type::rgba8;
            header.vertex_type = mmpld::vertex_type::double_xyz;
            Assert::AreEqual(size_t(3 * sizeof(double) + 4 * sizeof(char)), mmpld::get_stride<size_t>(header), L"Stride of double_xyz + rgba8", LINE_INFO());

            header.colour_type = mmpld::colour_type::rgb32;
            header.vertex_type = mmpld::vertex_type::float_xyz;
            Assert::AreEqual(size_t(3 * sizeof(float) + 3 * sizeof(float)), mmpld::get_stride<size_t>(header), L"Stride of float_xyz + rgb32", LINE_INFO());

            header.colour_type = mmpld::colour_type::rgb32;
            header.vertex_type = mmpld::vertex_type::float_xyzr;
            Assert::AreEqual(size_t(4 * sizeof(float) + 3 * sizeof(float)), mmpld::get_stride<size_t>(header), L"Stride of float_xyzr + rgb32", LINE_INFO());

            header.colour_type = mmpld::colour_type::rgb32;
            header.vertex_type = mmpld::vertex_type::short_xyz;
            Assert::AreEqual(size_t(3 * sizeof(short) + 3 * sizeof(float)), mmpld::get_stride<size_t>(header), L"Stride of short_xyz + rgb32", LINE_INFO());

            header.colour_type = mmpld::colour_type::rgb32;
            header.vertex_type = mmpld::vertex_type::double_xyz;
            Assert::AreEqual(size_t(3 * sizeof(double) + 3 * sizeof(float)), mmpld::get_stride<size_t>(header), L"Stride of double_xyz + rgb32", LINE_INFO());

            header.colour_type = mmpld::colour_type::rgba32;
            header.vertex_type = mmpld::vertex_type::float_xyz;
            Assert::AreEqual(size_t(3 * sizeof(float) + 4 * sizeof(float)), mmpld::get_stride<size_t>(header), L"Stride of float_xyz + rgba32", LINE_INFO());

            header.colour_type = mmpld::colour_type::rgba32;
            header.vertex_type = mmpld::vertex_type::float_xyzr;
            Assert::AreEqual(size_t(4 * sizeof(float) + 4 * sizeof(float)), mmpld::get_stride<size_t>(header), L"Stride of float_xyzr + rgba32", LINE_INFO());

            header.colour_type = mmpld::colour_type::rgba32;
            header.vertex_type = mmpld::vertex_type::short_xyz;
            Assert::AreEqual(size_t(3 * sizeof(short) + 4 * sizeof(float)), mmpld::get_stride<size_t>(header), L"Stride of short_xyz + rgba32", LINE_INFO());

            header.colour_type = mmpld::colour_type::rgba32;
            header.vertex_type = mmpld::vertex_type::double_xyz;
            Assert::AreEqual(size_t(3 * sizeof(double) + 4 * sizeof(float)), mmpld::get_stride<size_t>(header), L"Stride of double_xyz + rgba32", LINE_INFO());
        }

        TEST_METHOD(TestToString) {
            Assert::AreEqual("none", mmpld::to_string<char>(mmpld::colour_type::none).c_str(), L"Stringisation of colour type \"none\"", LINE_INFO());
            Assert::AreEqual("rgb8", mmpld::to_string<char>(mmpld::colour_type::rgb8).c_str(), L"Stringisation of colour type \"rgb8\"", LINE_INFO());
            Assert::AreEqual("rgba8", mmpld::to_string<char>(mmpld::colour_type::rgba8).c_str(), L"Stringisation of colour type \"rgba8\"", LINE_INFO());
            Assert::AreEqual("intensity", mmpld::to_string<char>(mmpld::colour_type::intensity).c_str(), L"Stringisation of colour type \"intensity\"", LINE_INFO());
            Assert::AreEqual("rgb32", mmpld::to_string<char>(mmpld::colour_type::rgb32).c_str(), L"Stringisation of colour type \"rgb32\"", LINE_INFO());
            Assert::AreEqual("rgba32", mmpld::to_string<char>(mmpld::colour_type::rgba32).c_str(), L"Stringisation of colour type \"rgba32\"", LINE_INFO());
            Assert::AreEqual("intensity64", mmpld::to_string<char>(mmpld::colour_type::intensity64).c_str(), L"Stringisation of colour type \"intensity64\"", LINE_INFO());

            Assert::AreEqual(L"none", mmpld::to_string<wchar_t>(mmpld::colour_type::none).c_str(), L"Stringisation of colour type \"none\"", LINE_INFO());
            Assert::AreEqual(L"rgb8", mmpld::to_string<wchar_t>(mmpld::colour_type::rgb8).c_str(), L"Stringisation of colour type \"rgb8\"", LINE_INFO());
            Assert::AreEqual(L"rgba8", mmpld::to_string<wchar_t>(mmpld::colour_type::rgba8).c_str(), L"Stringisation of colour type \"rgba8\"", LINE_INFO());
            Assert::AreEqual(L"intensity", mmpld::to_string<wchar_t>(mmpld::colour_type::intensity).c_str(), L"Stringisation of colour type \"intensity\"", LINE_INFO());
            Assert::AreEqual(L"rgb32", mmpld::to_string<wchar_t>(mmpld::colour_type::rgb32).c_str(), L"Stringisation of colour type \"rgb32\"", LINE_INFO());
            Assert::AreEqual(L"rgba32", mmpld::to_string<wchar_t>(mmpld::colour_type::rgba32).c_str(), L"Stringisation of colour type \"rgba32\"", LINE_INFO());
            Assert::AreEqual(L"intensity64", mmpld::to_string<wchar_t>(mmpld::colour_type::intensity64).c_str(), L"Stringisation of colour type \"intensity64\"", LINE_INFO());

            Assert::AreEqual("none", mmpld::to_string<char>(mmpld::vertex_type::none).c_str(), L"Stringisation of vertex type \"none\"", LINE_INFO());
            Assert::AreEqual("float_xyz", mmpld::to_string<char>(mmpld::vertex_type::float_xyz).c_str(), L"Stringisation of vertex type \"float_xyz\"", LINE_INFO());
            Assert::AreEqual("float_xyzr", mmpld::to_string<char>(mmpld::vertex_type::float_xyzr).c_str(), L"Stringisation of vertex type \"float_xyzr\"", LINE_INFO());
            Assert::AreEqual("short_xyz", mmpld::to_string<char>(mmpld::vertex_type::short_xyz).c_str(), L"Stringisation of vertex type \"short_xyz\"", LINE_INFO());
            Assert::AreEqual("double_xyz", mmpld::to_string<char>(mmpld::vertex_type::double_xyz).c_str(), L"Stringisation of vertex type \"double_xyz\"", LINE_INFO());

            Assert::AreEqual(L"none", mmpld::to_string<wchar_t>(mmpld::vertex_type::none).c_str(), L"Stringisation of vertex type \"none\"", LINE_INFO());
            Assert::AreEqual(L"float_xyz", mmpld::to_string<wchar_t>(mmpld::vertex_type::float_xyz).c_str(), L"Stringisation of vertex type \"float_xyz\"", LINE_INFO());
            Assert::AreEqual(L"float_xyzr", mmpld::to_string<wchar_t>(mmpld::vertex_type::float_xyzr).c_str(), L"Stringisation of vertex type \"float_xyzr\"", LINE_INFO());
            Assert::AreEqual(L"short_xyz", mmpld::to_string<wchar_t>(mmpld::vertex_type::short_xyz).c_str(), L"Stringisation of vertex type \"short_xyz\"", LINE_INFO());
            Assert::AreEqual(L"double_xyz", mmpld::to_string<wchar_t>(mmpld::vertex_type::double_xyz).c_str(), L"Stringisation of vertex type \"double_xyz\"", LINE_INFO());
        }

        TEST_METHOD(TestTraits) {
            Assert::AreEqual(size_t(0), mmpld::colour_traits<mmpld::colour_type::none>::size, L"Size of colour_type::none", LINE_INFO());
            Assert::AreEqual(size_t(3), mmpld::colour_traits<mmpld::colour_type::rgb8>::size, L"Size of colour_type::rgb8", LINE_INFO());
            Assert::AreEqual(size_t(4), mmpld::colour_traits<mmpld::colour_type::rgba8>::size, L"Size of colour_type::rgba8", LINE_INFO());
            Assert::AreEqual(size_t(4), mmpld::colour_traits<mmpld::colour_type::intensity>::size, L"Size of colour_type::intensity", LINE_INFO());
            Assert::AreEqual(size_t(12), mmpld::colour_traits<mmpld::colour_type::rgb32>::size, L"Size of colour_type::rgb32", LINE_INFO());
            Assert::AreEqual(size_t(16), mmpld::colour_traits<mmpld::colour_type::rgba32>::size, L"Size of colour_type::rgba32", LINE_INFO());
            Assert::AreEqual(size_t(8), mmpld::colour_traits<mmpld::colour_type::intensity64>::size, L"Size of colour_type::intensity64", LINE_INFO());

            Assert::AreEqual(size_t(0), mmpld::vertex_traits<mmpld::vertex_type::none>::size, L"Size of vertex_type::none", LINE_INFO());
            Assert::AreEqual(size_t(12), mmpld::vertex_traits<mmpld::vertex_type::float_xyz>::size, L"Size of vertex_type::float_xyz", LINE_INFO());
            Assert::AreEqual(size_t(16), mmpld::vertex_traits<mmpld::vertex_type::float_xyzr>::size, L"Size of vertex_type::float_xyzr", LINE_INFO());
            Assert::AreEqual(size_t(6), mmpld::vertex_traits<mmpld::vertex_type::short_xyz>::size, L"Size of vertex_type::short_xyz", LINE_INFO());
            Assert::AreEqual(size_t(24), mmpld::vertex_traits<mmpld::vertex_type::double_xyz>::size, L"Size of vertex_type::double_xyz", LINE_INFO());
        }

        TEST_METHOD(TestWriteRoundtrip) {
            this->testRoundTrip<std::ifstream, std::ofstream>("test_xyz_float_int_float.mmpld");
            this->testRoundTrip<FILE *, FILE *>("test_xyz_float_none.mmpld");
            this->testRoundTrip<int, int>("test_xyz_float_rgb_float.mmpld");
            this->testRoundTrip<HANDLE, HANDLE>("test_xyz_float_rgba_byte.mmpld");
            this->testRoundTrip<FILE *, FILE *>("test_xyz_float_rgba_float.mmpld");
            this->testRoundTrip<int, int>("test_xyzr_float_int_float.mmpld");
            this->testRoundTrip<HANDLE, FILE *>("test_xyzr_float_none.mmpld");
            this->testRoundTrip<HANDLE, int>("test_xyzr_float_rgb_float.mmpld");
            this->testRoundTrip<HANDLE, int>("test_xyzr_float_rgba_byte.mmpld");
            this->testRoundTrip<HANDLE, HANDLE>("test_xyzr_float_rgba_float.mmpld");
            this->testRoundTrip<HANDLE, FILE *>("test_xyz_double_int_double.mmpld");
            this->testRoundTrip<HANDLE, std::ofstream>("test_xyz_double_int_float.mmpld");
            this->testRoundTrip<HANDLE, int>("test_xyz_double_none.mmpld");
            this->testRoundTrip<HANDLE, HANDLE>("test_xyz_double_rgb_float.mmpld");
            this->testRoundTrip<HANDLE, HANDLE>("test_xyz_double_rgba_byte.mmpld");
            this->testRoundTrip<HANDLE, FILE *>("test_xyz_double_rgba_float.mmpld");
            this->testRoundTrip<HANDLE, int>("test_xyz_double_rgba_short.mmpld");
        }

        TEST_METHOD(TestCount) {
            this->testCount<std::ifstream>("test_xyz_double_int_double.mmpld");
            this->testCount<FILE *>("test_xyz_double_int_double.mmpld");
            this->testCount<HANDLE>("test_xyz_double_int_double.mmpld");
            this->testCount<int>("test_xyz_double_int_double.mmpld");
        }

    private:

        template<class F, class C> void testCount(const C *path) {
            typedef F file_type;
            typedef mmpld::detail::io_traits<F, C> io_type;

            mmpld::file_header fileHeader;
            mmpld::frame_header frameHeader;
            file_type hFile;
            mmpld::list_header listHeader;
            mmpld::seek_table seekTable;
            std::size_t totalCount = 0;

            io_type::open_read(path, hFile);

            mmpld::read_file_header(hFile, fileHeader, seekTable);
            io_type::seek(hFile, static_cast<size_t>(seekTable[0]));
            mmpld::read_frame_header(hFile, fileHeader.version, frameHeader);
            Assert::AreEqual(std::int32_t(4), frameHeader.lists, L"Frame #1 holds four particle lists.", LINE_INFO());

            mmpld::read_list_header(hFile, fileHeader.version, listHeader);
            {
                auto cnt = mmpld::count<std::size_t>(listHeader);
                Assert::AreEqual(std::size_t(listHeader.particles), cnt, L"Count returns # of particles in list 1", LINE_INFO());
                totalCount += cnt;
            }
            mmpld::skip_particles(hFile, listHeader);

            mmpld::read_list_header(hFile, fileHeader.version, listHeader);
            {
                auto cnt = mmpld::count<std::size_t>(listHeader);
                Assert::AreEqual(std::size_t(listHeader.particles), cnt, L"Count returns # of particles in list 2", LINE_INFO());
                totalCount += cnt;
            }
            mmpld::skip_particles(hFile, listHeader);

            mmpld::read_list_header(hFile, fileHeader.version, listHeader);
            {
                auto cnt = mmpld::count<std::size_t>(listHeader);
                Assert::AreEqual(std::size_t(listHeader.particles), cnt, L"Count returns # of particles in list 3", LINE_INFO());
                totalCount += cnt;
            }
            mmpld::skip_particles(hFile, listHeader);

            mmpld::read_list_header(hFile, fileHeader.version, listHeader);
            {
                auto cnt = mmpld::count<std::size_t>(listHeader);
                Assert::AreEqual(std::size_t(listHeader.particles), cnt, L"Count returns # of particles in list 4", LINE_INFO());
                totalCount += cnt;
            }
            mmpld::skip_particles(hFile, listHeader);

            io_type::seek(hFile, static_cast<size_t>(seekTable[0]));
            mmpld::read_frame_header(hFile, fileHeader.version, frameHeader);
            {
                auto pos = io_type::tell(hFile);
                auto cnt = mmpld::count<std::size_t>(frameHeader, fileHeader.version, hFile);
                Assert::AreEqual(totalCount, cnt, L"Count on whole frame returns number over all lists", LINE_INFO());
                Assert::AreEqual(pos, io_type::tell(hFile), L"File pointer returned to begin of frame", LINE_INFO());
            }

            io_type::close(hFile);
        }

        template<class F, class G> void testRoundTrip(const char *path) {
            typedef F ifile_type;
            typedef G ofile_type;
            typedef mmpld::detail::io_traits<F, char> iio_type;
            typedef mmpld::detail::io_traits<G, char> oio_type;

            static const auto TEST_FILE = "_test_roundtrip.mmpld";

            mmpld::file_header expectedFileHeader, roundtripFileHeader;
            std::vector<mmpld::frame_header> expectedFrameHeader;
            mmpld::frame_header roundtripFrameHeader;
            std::vector<mmpld::list_header> expectedListHeader;
            mmpld::list_header roundtripListHeader;
            mmpld::seek_table expectedSeekTable, roundtripSeekTable;

            {
                ifile_type inFile;
                iio_type::open_read(path, inFile);

                ofile_type outFile;
                oio_type::open_write(TEST_FILE, outFile);

                mmpld::read_file_header(inFile, expectedFileHeader, expectedSeekTable);
                Assert::AreEqual(std::uint32_t(1), expectedFileHeader.frames, L"Test file has one frame.", LINE_INFO());
                mmpld::write_file_header(expectedFileHeader, expectedSeekTable, outFile);

                for (decltype(expectedFileHeader.frames) f = 0; f < expectedFileHeader.frames; ++f) {
                    iio_type::seek(inFile, static_cast<std::size_t>(expectedSeekTable[f]));
                    expectedFrameHeader.emplace_back();
                    mmpld::read_frame_header(inFile, expectedFileHeader.version, expectedFrameHeader.back());

                    oio_type::seek(outFile, static_cast<std::size_t>(expectedSeekTable[f]));
                    mmpld::write_frame_header(expectedFrameHeader.back(), expectedFileHeader.version, outFile);

                    for (decltype(expectedFrameHeader.back().lists) l = 0; l < expectedFrameHeader.back().lists; ++l) {
                        expectedListHeader.emplace_back();
                        mmpld::read_list_header(inFile, expectedFileHeader.version, expectedListHeader.back());
                        iio_type::seek(inFile, iio_type::tell(inFile) + mmpld::get_size<iio_type::size_type>(expectedListHeader.back()));
                        mmpld::write_list_header(expectedListHeader.back(), expectedFileHeader.version, outFile);
                        oio_type::seek(outFile, oio_type::tell(outFile) + mmpld::get_size<oio_type::size_type>(expectedListHeader.back()));
                    }
                }

                iio_type::close(inFile);
                oio_type::close(outFile);
            }

            {
                ifile_type hFile;
                iio_type::open_read(TEST_FILE, hFile);

                mmpld::read_file_header(hFile, roundtripFileHeader, roundtripSeekTable);
                Assert::AreEqual(0, ::memcmp(&expectedFileHeader, &roundtripFileHeader, sizeof(expectedFileHeader)), L"File headers are identical", LINE_INFO());

                auto el = 0;
                for (decltype(expectedFileHeader.frames) f = 0; f < expectedFileHeader.frames; ++f) {
                    iio_type::seek(hFile, static_cast<std::size_t>(roundtripSeekTable[f]));
                    mmpld::read_frame_header(hFile, roundtripFileHeader.version, roundtripFrameHeader);
                    Assert::AreEqual(0, ::memcmp(&expectedFrameHeader[f], &roundtripFrameHeader, sizeof(roundtripFrameHeader)), L"Frame headers are identical", LINE_INFO());

                    for (decltype(roundtripFrameHeader.lists) l = 0; l < roundtripFrameHeader.lists; ++l) {
                        mmpld::read_list_header(hFile, roundtripFileHeader.version, roundtripListHeader);
                        iio_type::seek(hFile, iio_type::tell(hFile) + mmpld::get_size<iio_type::size_type>(expectedListHeader[el]));
                        Assert::AreEqual(0, ::memcmp(&expectedListHeader[el], &roundtripListHeader, sizeof(roundtripListHeader)), L"List headers are identical", LINE_INFO());
                        ++el;
                    }
                }

                iio_type::close(hFile);
            }
        }

        template<class F, class C> mmpld::list_header testLowLevelSingleList(const C *path) {
            // Test for old format with only one particle list.
            typedef F file_type;
            typedef mmpld::detail::io_traits<F, C> io_type;

            mmpld::file_header fileHeader;
            mmpld::frame_header frameHeader;
            file_type hFile;
            mmpld::list_header listHeader;
            mmpld::seek_table seekTable;

            //Assert::ExpectException([&hFile]() { io_type::open(nullptr, hFile); }, L"Opening nullptr raises exception.");

            io_type::open_read(path, hFile);

            mmpld::read_file_header(hFile, fileHeader, seekTable);
            Assert::AreNotEqual(int(mmpld::make_version(1, 1)), int(fileHeader.version), L"MMPLD version is not 1.1.", LINE_INFO());
            Assert::AreEqual(std::uint32_t(1), fileHeader.frames, L"Number of expected frames matches.", LINE_INFO());
            Assert::AreEqual(seekTable.size(), size_t(fileHeader.frames), L"Number of frames and size of seek table match.", LINE_INFO());

            io_type::seek(hFile, static_cast<size_t>(seekTable[0]));
            mmpld::read_frame_header(hFile, fileHeader.version, frameHeader);
            Assert::AreEqual(std::int32_t(1), frameHeader.lists, L"Frame #1 holds one particle list.", LINE_INFO());

            mmpld::read_list_header(hFile, fileHeader.version, listHeader);
            Assert::AreEqual(std::uint64_t(4), listHeader.particles, L"List holds four particles.", LINE_INFO());

            io_type::close(hFile);

            return listHeader;
        }

        template<class F, class C> mmpld::list_header testLowLevelMultiList(const C *path) {
            // Test for new format holding coordinate cross and three lists along the axes.
            typedef F file_type;
            typedef mmpld::detail::io_traits<F, C> io_type;

            mmpld::file_header fileHeader;
            mmpld::frame_header frameHeader;
            file_type hFile;
            mmpld::list_header listHeader;
            mmpld::list_header retval;
            mmpld::seek_table seekTable;

            io_type::open_read(path, hFile);

            mmpld::read_file_header(hFile, fileHeader, seekTable);
            Assert::AreNotEqual(int(mmpld::make_version(1, 1)), int(fileHeader.version), L"MMPLD version is not 1.1.", LINE_INFO());
            Assert::AreEqual(std::uint32_t(1), fileHeader.frames, L"Number of expected frames matches.", LINE_INFO());
            Assert::AreEqual(seekTable.size(), size_t(fileHeader.frames), L"Number of frames and size of seek table match.", LINE_INFO());

            io_type::seek(hFile, static_cast<size_t>(seekTable[0]));
            mmpld::read_frame_header(hFile, fileHeader.version, frameHeader);
            Assert::AreEqual(std::int32_t(4), frameHeader.lists, L"Frame #1 holds four particle lists.", LINE_INFO());

            mmpld::read_list_header(hFile, fileHeader.version, listHeader);
            Assert::AreEqual(std::uint64_t(4), listHeader.particles, L"First list holds four particles.", LINE_INFO());
            io_type::seek(hFile, io_type::tell(hFile) + mmpld::get_size<io_type::size_type>(listHeader));
            retval = listHeader;

            mmpld::read_list_header(hFile, fileHeader.version, listHeader);
            Assert::AreEqual(std::uint64_t(5), listHeader.particles, L"Second list holds five particles.", LINE_INFO());
            io_type::seek(hFile, io_type::tell(hFile) + mmpld::get_size<io_type::size_type>(listHeader));

            mmpld::read_list_header(hFile, fileHeader.version, listHeader);
            Assert::AreEqual(std::uint64_t(5), listHeader.particles, L"Third list holds five particles.", LINE_INFO());
            io_type::seek(hFile, io_type::tell(hFile) + mmpld::get_size<io_type::size_type>(listHeader));

            mmpld::read_list_header(hFile, fileHeader.version, listHeader);
            Assert::AreEqual(std::uint64_t(5), listHeader.particles, L"Fourth list holds five particles.", LINE_INFO());
            io_type::seek(hFile, io_type::tell(hFile) + mmpld::get_size<io_type::size_type>(listHeader));

            io_type::close(hFile);

            return retval;
        }

    };
}
