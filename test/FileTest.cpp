/// <copyright file="FileTest.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2018 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>

#include "stdafx.h"
#include "CppUnitTest.h"

#include "util.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace test {

    TEST_CLASS(FileTest) {

    public:

        TEST_METHOD(Test_test_xyz_float_int_float) {
            typedef std::underlying_type<mmpld::colour_type>::type c_t;
            typedef std::underlying_type<mmpld::vertex_type>::type v_t;
            ::SetMmpldWorkingDirectory();

            auto r1 = this->testFile<HANDLE>("test_xyz_float_int_float.mmpld");
            auto r2 = this->testFile<FILE *>("test_xyz_float_int_float.mmpld");
            auto r3 = this->testFile<int>("test_xyz_float_int_float.mmpld");
            auto r4 = this->testFile<std::ifstream>("test_xyz_float_int_float.mmpld");

            Assert::AreEqual(v_t(mmpld::vertex_type::float_xyz), v_t(r1.vertex_type), L"vertex_type of test_xyz_float_int_float.mmpld", LINE_INFO());
            Assert::AreEqual(c_t(mmpld::colour_type::intensity), c_t(r1.colour_type), L"colour_type of test_xyz_float_int_float.mmpld", LINE_INFO());
            Assert::AreEqual(0.1f, r1.radius, 0.0001f, L"Global radius in test_xyz_float_int_float.mmpld", LINE_INFO());
            Assert::AreEqual(0.0f, r1.min_intensity, 0.0001f, L"Minimal intensity in test_xyz_float_int_float.mmpld", LINE_INFO());
            Assert::AreEqual(255.0f, r1.max_intensity, 0.0001f, L"Maximal intensity in test_xyz_float_int_float.mmpld", LINE_INFO());

            Assert::AreEqual(decltype(r1.particles)(4), r1.particles, L"Number of particles is 4.", LINE_INFO());

            Assert::IsTrue(::memcmp(r1.colour, r2.colour, sizeof(r1.colour)) == 0, L"r2.colour matches reference.", LINE_INFO());
            Assert::IsTrue(::memcmp(r1.colour, r3.colour, sizeof(r1.colour)) == 0, L"r3.colour matches reference.", LINE_INFO());
            Assert::IsTrue(::memcmp(r1.colour, r4.colour, sizeof(r1.colour)) == 0, L"r4.colour matches reference.", LINE_INFO());

            Assert::AreEqual(c_t(r1.colour_type), c_t(r2.colour_type), L"r2.colour_type matches reference.", LINE_INFO());
            Assert::AreEqual(c_t(r1.colour_type), c_t(r3.colour_type), L"r3.colour_type matches reference.", LINE_INFO());
            Assert::AreEqual(c_t(r1.colour_type), c_t(r4.colour_type), L"r4.colour_type matches reference.", LINE_INFO());

            Assert::AreEqual(r1.max_intensity, r2.max_intensity, L"r2.max_intensity matches reference.", LINE_INFO());
            Assert::AreEqual(r1.max_intensity, r3.max_intensity, L"r3.max_intensity matches reference.", LINE_INFO());
            Assert::AreEqual(r1.max_intensity, r4.max_intensity, L"r4.max_intensity matches reference.", LINE_INFO());

            Assert::AreEqual(r1.min_intensity, r2.min_intensity, L"r2.min_intensity matches reference.", LINE_INFO());
            Assert::AreEqual(r1.min_intensity, r3.min_intensity, L"r3.min_intensity matches reference.", LINE_INFO());
            Assert::AreEqual(r1.min_intensity, r4.min_intensity, L"r4.min_intensity matches reference.", LINE_INFO());

            Assert::AreEqual(r1.particles, r2.particles, L"r2.particles matches reference.", LINE_INFO());
            Assert::AreEqual(r1.particles, r3.particles, L"r3.particles matches reference.", LINE_INFO());
            Assert::AreEqual(r1.particles, r4.particles, L"r4.particles matches reference.", LINE_INFO());

            Assert::AreEqual(r1.radius, r2.radius, L"r2.radius matches reference.", LINE_INFO());
            Assert::AreEqual(r1.radius, r3.radius, L"r3.radius matches reference.", LINE_INFO());
            Assert::AreEqual(r1.radius, r4.radius, L"r4.radius matches reference.", LINE_INFO());

            Assert::AreEqual(v_t(r1.vertex_type), v_t(r2.vertex_type), L"r2.vertex_type matches reference.", LINE_INFO());
            Assert::AreEqual(v_t(r1.vertex_type), v_t(r3.vertex_type), L"r3.vertex_type matches reference.", LINE_INFO());
            Assert::AreEqual(v_t(r1.vertex_type), v_t(r4.vertex_type), L"r4.vertex_type matches reference.", LINE_INFO());
        }

        TEST_METHOD(Test_test_xyz_float_none) {
            typedef std::underlying_type<mmpld::colour_type>::type c_t;
            typedef std::underlying_type<mmpld::vertex_type>::type v_t;
            ::SetMmpldWorkingDirectory();

            auto r1 = this->testFile<HANDLE>("test_xyz_float_none.mmpld");
            auto r2 = this->testFile<FILE *>("test_xyz_float_none.mmpld");
            auto r3 = this->testFile<int>("test_xyz_float_none.mmpld");
            auto r4 = this->testFile<std::ifstream>("test_xyz_float_none.mmpld");

            Assert::AreEqual(v_t(mmpld::vertex_type::float_xyz), v_t(r1.vertex_type), L"vertex_type of test_xyz_float_none.mmpld", LINE_INFO());
            Assert::AreEqual(c_t(mmpld::colour_type::none), c_t(r1.colour_type), L"colour_type of test_xyz_float_none.mmpld", LINE_INFO());
            Assert::AreEqual(0.1f, r1.radius, 0.0001f, L"Global radius in test_xyz_float_none.mmpld", LINE_INFO());
            Assert::AreEqual(1.0f, r1.colour[0], 0.0001f, L"Global colour[0]", LINE_INFO());
            Assert::AreEqual(1.0f, r1.colour[1], 0.0001f, L"Global colour[1]", LINE_INFO());
            Assert::AreEqual(0.0f, r1.colour[2], 0.0001f, L"Global colour[2]", LINE_INFO());
            Assert::AreEqual(1.0f, r1.colour[3], 0.0001f, L"Global colour[3]", LINE_INFO());

            Assert::AreEqual(decltype(r1.particles)(4), r1.particles, L"Number of particles is 4.", LINE_INFO());

            Assert::IsTrue(::memcmp(r1.colour, r2.colour, sizeof(r1.colour)) == 0, L"r2.colour matches reference.", LINE_INFO());
            Assert::IsTrue(::memcmp(r1.colour, r3.colour, sizeof(r1.colour)) == 0, L"r3.colour matches reference.", LINE_INFO());
            Assert::IsTrue(::memcmp(r1.colour, r4.colour, sizeof(r1.colour)) == 0, L"r4.colour matches reference.", LINE_INFO());

            Assert::AreEqual(c_t(r1.colour_type), c_t(r2.colour_type), L"r2.colour_type matches reference.", LINE_INFO());
            Assert::AreEqual(c_t(r1.colour_type), c_t(r3.colour_type), L"r3.colour_type matches reference.", LINE_INFO());
            Assert::AreEqual(c_t(r1.colour_type), c_t(r4.colour_type), L"r4.colour_type matches reference.", LINE_INFO());

            Assert::AreEqual(r1.max_intensity, r2.max_intensity, L"r2.max_intensity matches reference.", LINE_INFO());
            Assert::AreEqual(r1.max_intensity, r3.max_intensity, L"r3.max_intensity matches reference.", LINE_INFO());
            Assert::AreEqual(r1.max_intensity, r4.max_intensity, L"r4.max_intensity matches reference.", LINE_INFO());

            Assert::AreEqual(r1.min_intensity, r2.min_intensity, L"r2.min_intensity matches reference.", LINE_INFO());
            Assert::AreEqual(r1.min_intensity, r3.min_intensity, L"r3.min_intensity matches reference.", LINE_INFO());
            Assert::AreEqual(r1.min_intensity, r4.min_intensity, L"r4.min_intensity matches reference.", LINE_INFO());

            Assert::AreEqual(r1.particles, r2.particles, L"r2.particles matches reference.", LINE_INFO());
            Assert::AreEqual(r1.particles, r3.particles, L"r3.particles matches reference.", LINE_INFO());
            Assert::AreEqual(r1.particles, r4.particles, L"r4.particles matches reference.", LINE_INFO());

            Assert::AreEqual(r1.radius, r2.radius, L"r2.radius matches reference.", LINE_INFO());
            Assert::AreEqual(r1.radius, r3.radius, L"r3.radius matches reference.", LINE_INFO());
            Assert::AreEqual(r1.radius, r4.radius, L"r4.radius matches reference.", LINE_INFO());

            Assert::AreEqual(v_t(r1.vertex_type), v_t(r2.vertex_type), L"r2.vertex_type matches reference.", LINE_INFO());
            Assert::AreEqual(v_t(r1.vertex_type), v_t(r3.vertex_type), L"r3.vertex_type matches reference.", LINE_INFO());
            Assert::AreEqual(v_t(r1.vertex_type), v_t(r4.vertex_type), L"r4.vertex_type matches reference.", LINE_INFO());
        }

        TEST_METHOD(Test_test_xyz_float_rgb_float) {
            typedef std::underlying_type<mmpld::colour_type>::type c_t;
            typedef std::underlying_type<mmpld::vertex_type>::type v_t;
            ::SetMmpldWorkingDirectory();

            auto r1 = this->testFile<HANDLE>("test_xyz_float_rgb_float.mmpld");
            auto r2 = this->testFile<FILE *>("test_xyz_float_rgb_float.mmpld");
            auto r3 = this->testFile<int>("test_xyz_float_rgb_float.mmpld");
            auto r4 = this->testFile<std::ifstream>("test_xyz_float_rgb_float.mmpld");

            Assert::AreEqual(v_t(mmpld::vertex_type::float_xyz), v_t(r1.vertex_type), L"vertex_type of test_xyz_float_rgb_float.mmpld", LINE_INFO());
            Assert::AreEqual(c_t(mmpld::colour_type::rgb32), c_t(r1.colour_type), L"colour_type of test_xyz_float_rgb_float.mmpld", LINE_INFO());
            Assert::AreEqual(0.1f, r1.radius, 0.0001f, L"Global radius in test_xyz_float_rgb_float.mmpld", LINE_INFO());

            Assert::AreEqual(decltype(r1.particles)(4), r1.particles, L"Number of particles is 4.", LINE_INFO());

            Assert::IsTrue(::memcmp(r1.colour, r2.colour, sizeof(r1.colour)) == 0, L"r2.colour matches reference.", LINE_INFO());
            Assert::IsTrue(::memcmp(r1.colour, r3.colour, sizeof(r1.colour)) == 0, L"r3.colour matches reference.", LINE_INFO());
            Assert::IsTrue(::memcmp(r1.colour, r4.colour, sizeof(r1.colour)) == 0, L"r4.colour matches reference.", LINE_INFO());

            Assert::AreEqual(c_t(r1.colour_type), c_t(r2.colour_type), L"r2.colour_type matches reference.", LINE_INFO());
            Assert::AreEqual(c_t(r1.colour_type), c_t(r3.colour_type), L"r3.colour_type matches reference.", LINE_INFO());
            Assert::AreEqual(c_t(r1.colour_type), c_t(r4.colour_type), L"r4.colour_type matches reference.", LINE_INFO());

            Assert::AreEqual(r1.max_intensity, r2.max_intensity, L"r2.max_intensity matches reference.", LINE_INFO());
            Assert::AreEqual(r1.max_intensity, r3.max_intensity, L"r3.max_intensity matches reference.", LINE_INFO());
            Assert::AreEqual(r1.max_intensity, r4.max_intensity, L"r4.max_intensity matches reference.", LINE_INFO());

            Assert::AreEqual(r1.min_intensity, r2.min_intensity, L"r2.min_intensity matches reference.", LINE_INFO());
            Assert::AreEqual(r1.min_intensity, r3.min_intensity, L"r3.min_intensity matches reference.", LINE_INFO());
            Assert::AreEqual(r1.min_intensity, r4.min_intensity, L"r4.min_intensity matches reference.", LINE_INFO());

            Assert::AreEqual(r1.particles, r2.particles, L"r2.particles matches reference.", LINE_INFO());
            Assert::AreEqual(r1.particles, r3.particles, L"r3.particles matches reference.", LINE_INFO());
            Assert::AreEqual(r1.particles, r4.particles, L"r4.particles matches reference.", LINE_INFO());

            Assert::AreEqual(r1.radius, r2.radius, L"r2.radius matches reference.", LINE_INFO());
            Assert::AreEqual(r1.radius, r3.radius, L"r3.radius matches reference.", LINE_INFO());
            Assert::AreEqual(r1.radius, r4.radius, L"r4.radius matches reference.", LINE_INFO());

            Assert::AreEqual(v_t(r1.vertex_type), v_t(r2.vertex_type), L"r2.vertex_type matches reference.", LINE_INFO());
            Assert::AreEqual(v_t(r1.vertex_type), v_t(r3.vertex_type), L"r3.vertex_type matches reference.", LINE_INFO());
            Assert::AreEqual(v_t(r1.vertex_type), v_t(r4.vertex_type), L"r4.vertex_type matches reference.", LINE_INFO());
        }

        TEST_METHOD(Test_test_xyz_float_rgba_byte) {
            typedef std::underlying_type<mmpld::colour_type>::type c_t;
            typedef std::underlying_type<mmpld::vertex_type>::type v_t;
            ::SetMmpldWorkingDirectory();

            auto r1 = this->testFile<HANDLE>("test_xyz_float_rgba_byte.mmpld");
            auto r2 = this->testFile<FILE *>("test_xyz_float_rgba_byte.mmpld");
            auto r3 = this->testFile<int>("test_xyz_float_rgba_byte.mmpld");
            auto r4 = this->testFile<std::ifstream>("test_xyz_float_rgba_byte.mmpld");

            Assert::AreEqual(v_t(mmpld::vertex_type::float_xyz), v_t(r1.vertex_type), L"vertex_type of test_xyz_float_rgba_byte.mmpld", LINE_INFO());
            Assert::AreEqual(c_t(mmpld::colour_type::rgba8), c_t(r1.colour_type), L"colour_type of test_xyz_float_rgba_byte.mmpld", LINE_INFO());
            Assert::AreEqual(0.1f, r1.radius, 0.0001f, L"Global radius in test_xyz_float_rgba_byte.mmpld", LINE_INFO());

            Assert::AreEqual(decltype(r1.particles)(4), r1.particles, L"Number of particles is 4.", LINE_INFO());

            Assert::IsTrue(::memcmp(r1.colour, r2.colour, sizeof(r1.colour)) == 0, L"r2.colour matches reference.", LINE_INFO());
            Assert::IsTrue(::memcmp(r1.colour, r3.colour, sizeof(r1.colour)) == 0, L"r3.colour matches reference.", LINE_INFO());
            Assert::IsTrue(::memcmp(r1.colour, r4.colour, sizeof(r1.colour)) == 0, L"r4.colour matches reference.", LINE_INFO());

            Assert::AreEqual(c_t(r1.colour_type), c_t(r2.colour_type), L"r2.colour_type matches reference.", LINE_INFO());
            Assert::AreEqual(c_t(r1.colour_type), c_t(r3.colour_type), L"r3.colour_type matches reference.", LINE_INFO());
            Assert::AreEqual(c_t(r1.colour_type), c_t(r4.colour_type), L"r4.colour_type matches reference.", LINE_INFO());

            Assert::AreEqual(r1.max_intensity, r2.max_intensity, L"r2.max_intensity matches reference.", LINE_INFO());
            Assert::AreEqual(r1.max_intensity, r3.max_intensity, L"r3.max_intensity matches reference.", LINE_INFO());
            Assert::AreEqual(r1.max_intensity, r4.max_intensity, L"r4.max_intensity matches reference.", LINE_INFO());

            Assert::AreEqual(r1.min_intensity, r2.min_intensity, L"r2.min_intensity matches reference.", LINE_INFO());
            Assert::AreEqual(r1.min_intensity, r3.min_intensity, L"r3.min_intensity matches reference.", LINE_INFO());
            Assert::AreEqual(r1.min_intensity, r4.min_intensity, L"r4.min_intensity matches reference.", LINE_INFO());

            Assert::AreEqual(r1.particles, r2.particles, L"r2.particles matches reference.", LINE_INFO());
            Assert::AreEqual(r1.particles, r3.particles, L"r3.particles matches reference.", LINE_INFO());
            Assert::AreEqual(r1.particles, r4.particles, L"r4.particles matches reference.", LINE_INFO());

            Assert::AreEqual(r1.radius, r2.radius, L"r2.radius matches reference.", LINE_INFO());
            Assert::AreEqual(r1.radius, r3.radius, L"r3.radius matches reference.", LINE_INFO());
            Assert::AreEqual(r1.radius, r4.radius, L"r4.radius matches reference.", LINE_INFO());

            Assert::AreEqual(v_t(r1.vertex_type), v_t(r2.vertex_type), L"r2.vertex_type matches reference.", LINE_INFO());
            Assert::AreEqual(v_t(r1.vertex_type), v_t(r3.vertex_type), L"r3.vertex_type matches reference.", LINE_INFO());
            Assert::AreEqual(v_t(r1.vertex_type), v_t(r4.vertex_type), L"r4.vertex_type matches reference.", LINE_INFO());
        }

        TEST_METHOD(Test_test_xyz_float_rgba_float) {
            typedef std::underlying_type<mmpld::colour_type>::type c_t;
            typedef std::underlying_type<mmpld::vertex_type>::type v_t;
            ::SetMmpldWorkingDirectory();

            auto r1 = this->testFile<HANDLE>("test_xyz_float_rgba_float.mmpld");
            auto r2 = this->testFile<FILE *>("test_xyz_float_rgba_float.mmpld");
            auto r3 = this->testFile<int>("test_xyz_float_rgba_float.mmpld");
            auto r4 = this->testFile<std::ifstream>("test_xyz_float_rgba_float.mmpld");

            Assert::AreEqual(v_t(mmpld::vertex_type::float_xyz), v_t(r1.vertex_type), L"vertex_type of test_xyz_float_rgba_float.mmpld", LINE_INFO());
            Assert::AreEqual(c_t(mmpld::colour_type::rgba32), c_t(r1.colour_type), L"colour_type of test_xyz_float_rgba_float.mmpld", LINE_INFO());
            Assert::AreEqual(0.1f, r1.radius, 0.0001f, L"Global radius in test_xyz_float_rgba_float.mmpld", LINE_INFO());

            Assert::AreEqual(decltype(r1.particles)(4), r1.particles, L"Number of particles is 4.", LINE_INFO());

            Assert::IsTrue(::memcmp(r1.colour, r2.colour, sizeof(r1.colour)) == 0, L"r2.colour matches reference.", LINE_INFO());
            Assert::IsTrue(::memcmp(r1.colour, r3.colour, sizeof(r1.colour)) == 0, L"r3.colour matches reference.", LINE_INFO());
            Assert::IsTrue(::memcmp(r1.colour, r4.colour, sizeof(r1.colour)) == 0, L"r4.colour matches reference.", LINE_INFO());

            Assert::AreEqual(c_t(r1.colour_type), c_t(r2.colour_type), L"r2.colour_type matches reference.", LINE_INFO());
            Assert::AreEqual(c_t(r1.colour_type), c_t(r3.colour_type), L"r3.colour_type matches reference.", LINE_INFO());
            Assert::AreEqual(c_t(r1.colour_type), c_t(r4.colour_type), L"r4.colour_type matches reference.", LINE_INFO());

            Assert::AreEqual(r1.max_intensity, r2.max_intensity, L"r2.max_intensity matches reference.", LINE_INFO());
            Assert::AreEqual(r1.max_intensity, r3.max_intensity, L"r3.max_intensity matches reference.", LINE_INFO());
            Assert::AreEqual(r1.max_intensity, r4.max_intensity, L"r4.max_intensity matches reference.", LINE_INFO());

            Assert::AreEqual(r1.min_intensity, r2.min_intensity, L"r2.min_intensity matches reference.", LINE_INFO());
            Assert::AreEqual(r1.min_intensity, r3.min_intensity, L"r3.min_intensity matches reference.", LINE_INFO());
            Assert::AreEqual(r1.min_intensity, r4.min_intensity, L"r4.min_intensity matches reference.", LINE_INFO());

            Assert::AreEqual(r1.particles, r2.particles, L"r2.particles matches reference.", LINE_INFO());
            Assert::AreEqual(r1.particles, r3.particles, L"r3.particles matches reference.", LINE_INFO());
            Assert::AreEqual(r1.particles, r4.particles, L"r4.particles matches reference.", LINE_INFO());

            Assert::AreEqual(r1.radius, r2.radius, L"r2.radius matches reference.", LINE_INFO());
            Assert::AreEqual(r1.radius, r3.radius, L"r3.radius matches reference.", LINE_INFO());
            Assert::AreEqual(r1.radius, r4.radius, L"r4.radius matches reference.", LINE_INFO());

            Assert::AreEqual(v_t(r1.vertex_type), v_t(r2.vertex_type), L"r2.vertex_type matches reference.", LINE_INFO());
            Assert::AreEqual(v_t(r1.vertex_type), v_t(r3.vertex_type), L"r3.vertex_type matches reference.", LINE_INFO());
            Assert::AreEqual(v_t(r1.vertex_type), v_t(r4.vertex_type), L"r4.vertex_type matches reference.", LINE_INFO());
        }

        TEST_METHOD(Test_test_xyzr_float_int_float) {
            typedef std::underlying_type<mmpld::colour_type>::type c_t;
            typedef std::underlying_type<mmpld::vertex_type>::type v_t;
            ::SetMmpldWorkingDirectory();

            auto r1 = this->testFile<HANDLE>("test_xyzr_float_int_float.mmpld");
            auto r2 = this->testFile<FILE *>("test_xyzr_float_int_float.mmpld");
            auto r3 = this->testFile<int>("test_xyzr_float_int_float.mmpld");
            auto r4 = this->testFile<std::ifstream>("test_xyzr_float_int_float.mmpld");

            Assert::AreEqual(v_t(mmpld::vertex_type::float_xyzr), v_t(r1.vertex_type), L"vertex_type of test_xyzr_float_int_float.mmpld", LINE_INFO());
            Assert::AreEqual(c_t(mmpld::colour_type::intensity), c_t(r1.colour_type), L"colour_type of test_xyzr_float_int_float.mmpld", LINE_INFO());
            Assert::AreEqual(0.0f, r1.min_intensity, 0.0001f, L"Minimal intensity in test_xyzr_float_int_float.mmpld", LINE_INFO());
            Assert::AreEqual(255.0f, r1.max_intensity, 0.0001f, L"Maximal intensity in test_xyzr_float_int_float.mmpld", LINE_INFO());

            Assert::AreEqual(decltype(r1.particles)(4), r1.particles, L"Number of particles is 4.", LINE_INFO());

            Assert::IsTrue(::memcmp(r1.colour, r2.colour, sizeof(r1.colour)) == 0, L"r2.colour matches reference.", LINE_INFO());
            Assert::IsTrue(::memcmp(r1.colour, r3.colour, sizeof(r1.colour)) == 0, L"r3.colour matches reference.", LINE_INFO());
            Assert::IsTrue(::memcmp(r1.colour, r4.colour, sizeof(r1.colour)) == 0, L"r4.colour matches reference.", LINE_INFO());

            Assert::AreEqual(c_t(r1.colour_type), c_t(r2.colour_type), L"r2.colour_type matches reference.", LINE_INFO());
            Assert::AreEqual(c_t(r1.colour_type), c_t(r3.colour_type), L"r3.colour_type matches reference.", LINE_INFO());
            Assert::AreEqual(c_t(r1.colour_type), c_t(r4.colour_type), L"r4.colour_type matches reference.", LINE_INFO());

            Assert::AreEqual(r1.max_intensity, r2.max_intensity, L"r2.max_intensity matches reference.", LINE_INFO());
            Assert::AreEqual(r1.max_intensity, r3.max_intensity, L"r3.max_intensity matches reference.", LINE_INFO());
            Assert::AreEqual(r1.max_intensity, r4.max_intensity, L"r4.max_intensity matches reference.", LINE_INFO());

            Assert::AreEqual(r1.min_intensity, r2.min_intensity, L"r2.min_intensity matches reference.", LINE_INFO());
            Assert::AreEqual(r1.min_intensity, r3.min_intensity, L"r3.min_intensity matches reference.", LINE_INFO());
            Assert::AreEqual(r1.min_intensity, r4.min_intensity, L"r4.min_intensity matches reference.", LINE_INFO());

            Assert::AreEqual(r1.particles, r2.particles, L"r2.particles matches reference.", LINE_INFO());
            Assert::AreEqual(r1.particles, r3.particles, L"r3.particles matches reference.", LINE_INFO());
            Assert::AreEqual(r1.particles, r4.particles, L"r4.particles matches reference.", LINE_INFO());

            Assert::AreEqual(r1.radius, r2.radius, L"r2.radius matches reference.", LINE_INFO());
            Assert::AreEqual(r1.radius, r3.radius, L"r3.radius matches reference.", LINE_INFO());
            Assert::AreEqual(r1.radius, r4.radius, L"r4.radius matches reference.", LINE_INFO());

            Assert::AreEqual(v_t(r1.vertex_type), v_t(r2.vertex_type), L"r2.vertex_type matches reference.", LINE_INFO());
            Assert::AreEqual(v_t(r1.vertex_type), v_t(r3.vertex_type), L"r3.vertex_type matches reference.", LINE_INFO());
            Assert::AreEqual(v_t(r1.vertex_type), v_t(r4.vertex_type), L"r4.vertex_type matches reference.", LINE_INFO());
        }

        TEST_METHOD(Test_test_xyzr_float_none) {
            typedef std::underlying_type<mmpld::colour_type>::type c_t;
            typedef std::underlying_type<mmpld::vertex_type>::type v_t;
            ::SetMmpldWorkingDirectory();

            auto r1 = this->testFile<HANDLE>("test_xyzr_float_none.mmpld");
            auto r2 = this->testFile<FILE *>("test_xyzr_float_none.mmpld");
            auto r3 = this->testFile<int>("test_xyzr_float_none.mmpld");
            auto r4 = this->testFile<std::ifstream>("test_xyzr_float_none.mmpld");

            Assert::AreEqual(v_t(mmpld::vertex_type::float_xyzr), v_t(r1.vertex_type), L"vertex_type of test_xyzr_float_none.mmpld", LINE_INFO());
            Assert::AreEqual(c_t(mmpld::colour_type::none), c_t(r1.colour_type), L"colour_type of test_xyzr_float_none.mmpld", LINE_INFO());
            Assert::AreEqual(1.0f, r1.colour[0], 0.0001f, L"Global colour[0]", LINE_INFO());
            Assert::AreEqual(1.0f, r1.colour[1], 0.0001f, L"Global colour[1]", LINE_INFO());
            Assert::AreEqual(0.0f, r1.colour[2], 0.0001f, L"Global colour[2]", LINE_INFO());
            Assert::AreEqual(1.0f, r1.colour[3], 0.0001f, L"Global colour[3]", LINE_INFO());

            Assert::AreEqual(decltype(r1.particles)(4), r1.particles, L"Number of particles is 4.", LINE_INFO());

            Assert::IsTrue(::memcmp(r1.colour, r2.colour, sizeof(r1.colour)) == 0, L"r2.colour matches reference.", LINE_INFO());
            Assert::IsTrue(::memcmp(r1.colour, r3.colour, sizeof(r1.colour)) == 0, L"r3.colour matches reference.", LINE_INFO());
            Assert::IsTrue(::memcmp(r1.colour, r4.colour, sizeof(r1.colour)) == 0, L"r4.colour matches reference.", LINE_INFO());

            Assert::AreEqual(c_t(r1.colour_type), c_t(r2.colour_type), L"r2.colour_type matches reference.", LINE_INFO());
            Assert::AreEqual(c_t(r1.colour_type), c_t(r3.colour_type), L"r3.colour_type matches reference.", LINE_INFO());
            Assert::AreEqual(c_t(r1.colour_type), c_t(r4.colour_type), L"r4.colour_type matches reference.", LINE_INFO());

            Assert::AreEqual(r1.max_intensity, r2.max_intensity, L"r2.max_intensity matches reference.", LINE_INFO());
            Assert::AreEqual(r1.max_intensity, r3.max_intensity, L"r3.max_intensity matches reference.", LINE_INFO());
            Assert::AreEqual(r1.max_intensity, r4.max_intensity, L"r4.max_intensity matches reference.", LINE_INFO());

            Assert::AreEqual(r1.min_intensity, r2.min_intensity, L"r2.min_intensity matches reference.", LINE_INFO());
            Assert::AreEqual(r1.min_intensity, r3.min_intensity, L"r3.min_intensity matches reference.", LINE_INFO());
            Assert::AreEqual(r1.min_intensity, r4.min_intensity, L"r4.min_intensity matches reference.", LINE_INFO());

            Assert::AreEqual(r1.particles, r2.particles, L"r2.particles matches reference.", LINE_INFO());
            Assert::AreEqual(r1.particles, r3.particles, L"r3.particles matches reference.", LINE_INFO());
            Assert::AreEqual(r1.particles, r4.particles, L"r4.particles matches reference.", LINE_INFO());

            Assert::AreEqual(r1.radius, r2.radius, L"r2.radius matches reference.", LINE_INFO());
            Assert::AreEqual(r1.radius, r3.radius, L"r3.radius matches reference.", LINE_INFO());
            Assert::AreEqual(r1.radius, r4.radius, L"r4.radius matches reference.", LINE_INFO());

            Assert::AreEqual(v_t(r1.vertex_type), v_t(r2.vertex_type), L"r2.vertex_type matches reference.", LINE_INFO());
            Assert::AreEqual(v_t(r1.vertex_type), v_t(r3.vertex_type), L"r3.vertex_type matches reference.", LINE_INFO());
            Assert::AreEqual(v_t(r1.vertex_type), v_t(r4.vertex_type), L"r4.vertex_type matches reference.", LINE_INFO());
        }

        TEST_METHOD(Test_test_xyzr_float_rgb_float) {
            typedef std::underlying_type<mmpld::colour_type>::type c_t;
            typedef std::underlying_type<mmpld::vertex_type>::type v_t;
            ::SetMmpldWorkingDirectory();

            auto r1 = this->testFile<HANDLE>("test_xyzr_float_rgb_float.mmpld");
            auto r2 = this->testFile<FILE *>("test_xyzr_float_rgb_float.mmpld");
            auto r3 = this->testFile<int>("test_xyzr_float_rgb_float.mmpld");
            auto r4 = this->testFile<std::ifstream>("test_xyzr_float_rgb_float.mmpld");

            Assert::AreEqual(v_t(mmpld::vertex_type::float_xyzr), v_t(r1.vertex_type), L"vertex_type of test_xyzr_float_rgb_float.mmpld", LINE_INFO());
            Assert::AreEqual(c_t(mmpld::colour_type::rgb32), c_t(r1.colour_type), L"colour_type of test_xyzr_float_rgb_float.mmpld", LINE_INFO());

            Assert::AreEqual(decltype(r1.particles)(4), r1.particles, L"Number of particles is 4.", LINE_INFO());

            Assert::IsTrue(::memcmp(r1.colour, r2.colour, sizeof(r1.colour)) == 0, L"r2.colour matches reference.", LINE_INFO());
            Assert::IsTrue(::memcmp(r1.colour, r3.colour, sizeof(r1.colour)) == 0, L"r3.colour matches reference.", LINE_INFO());
            Assert::IsTrue(::memcmp(r1.colour, r4.colour, sizeof(r1.colour)) == 0, L"r4.colour matches reference.", LINE_INFO());

            Assert::AreEqual(c_t(r1.colour_type), c_t(r2.colour_type), L"r2.colour_type matches reference.", LINE_INFO());
            Assert::AreEqual(c_t(r1.colour_type), c_t(r3.colour_type), L"r3.colour_type matches reference.", LINE_INFO());
            Assert::AreEqual(c_t(r1.colour_type), c_t(r4.colour_type), L"r4.colour_type matches reference.", LINE_INFO());

            Assert::AreEqual(r1.max_intensity, r2.max_intensity, L"r2.max_intensity matches reference.", LINE_INFO());
            Assert::AreEqual(r1.max_intensity, r3.max_intensity, L"r3.max_intensity matches reference.", LINE_INFO());
            Assert::AreEqual(r1.max_intensity, r4.max_intensity, L"r4.max_intensity matches reference.", LINE_INFO());

            Assert::AreEqual(r1.min_intensity, r2.min_intensity, L"r2.min_intensity matches reference.", LINE_INFO());
            Assert::AreEqual(r1.min_intensity, r3.min_intensity, L"r3.min_intensity matches reference.", LINE_INFO());
            Assert::AreEqual(r1.min_intensity, r4.min_intensity, L"r4.min_intensity matches reference.", LINE_INFO());

            Assert::AreEqual(r1.particles, r2.particles, L"r2.particles matches reference.", LINE_INFO());
            Assert::AreEqual(r1.particles, r3.particles, L"r3.particles matches reference.", LINE_INFO());
            Assert::AreEqual(r1.particles, r4.particles, L"r4.particles matches reference.", LINE_INFO());

            Assert::AreEqual(r1.radius, r2.radius, L"r2.radius matches reference.", LINE_INFO());
            Assert::AreEqual(r1.radius, r3.radius, L"r3.radius matches reference.", LINE_INFO());
            Assert::AreEqual(r1.radius, r4.radius, L"r4.radius matches reference.", LINE_INFO());

            Assert::AreEqual(v_t(r1.vertex_type), v_t(r2.vertex_type), L"r2.vertex_type matches reference.", LINE_INFO());
            Assert::AreEqual(v_t(r1.vertex_type), v_t(r3.vertex_type), L"r3.vertex_type matches reference.", LINE_INFO());
            Assert::AreEqual(v_t(r1.vertex_type), v_t(r4.vertex_type), L"r4.vertex_type matches reference.", LINE_INFO());
        }

        TEST_METHOD(Test_test_xyzr_float_rgba_byte) {
            typedef std::underlying_type<mmpld::colour_type>::type c_t;
            typedef std::underlying_type<mmpld::vertex_type>::type v_t;
            ::SetMmpldWorkingDirectory();

            auto r1 = this->testFile<HANDLE>("test_xyzr_float_rgba_byte.mmpld");
            auto r2 = this->testFile<FILE *>("test_xyzr_float_rgba_byte.mmpld");
            auto r3 = this->testFile<int>("test_xyzr_float_rgba_byte.mmpld");
            auto r4 = this->testFile<std::ifstream>("test_xyzr_float_rgba_byte.mmpld");

            Assert::AreEqual(v_t(mmpld::vertex_type::float_xyzr), v_t(r1.vertex_type), L"vertex_type of test_xyzr_float_rgba_byte.mmpld", LINE_INFO());
            Assert::AreEqual(c_t(mmpld::colour_type::rgba8), c_t(r1.colour_type), L"colour_type of test_xyzr_float_rgba_byte.mmpld", LINE_INFO());

            Assert::AreEqual(decltype(r1.particles)(4), r1.particles, L"Number of particles is 4.", LINE_INFO());

            Assert::IsTrue(::memcmp(r1.colour, r2.colour, sizeof(r1.colour)) == 0, L"r2.colour matches reference.", LINE_INFO());
            Assert::IsTrue(::memcmp(r1.colour, r3.colour, sizeof(r1.colour)) == 0, L"r3.colour matches reference.", LINE_INFO());
            Assert::IsTrue(::memcmp(r1.colour, r4.colour, sizeof(r1.colour)) == 0, L"r4.colour matches reference.", LINE_INFO());

            Assert::AreEqual(c_t(r1.colour_type), c_t(r2.colour_type), L"r2.colour_type matches reference.", LINE_INFO());
            Assert::AreEqual(c_t(r1.colour_type), c_t(r3.colour_type), L"r3.colour_type matches reference.", LINE_INFO());
            Assert::AreEqual(c_t(r1.colour_type), c_t(r4.colour_type), L"r4.colour_type matches reference.", LINE_INFO());

            Assert::AreEqual(r1.max_intensity, r2.max_intensity, L"r2.max_intensity matches reference.", LINE_INFO());
            Assert::AreEqual(r1.max_intensity, r3.max_intensity, L"r3.max_intensity matches reference.", LINE_INFO());
            Assert::AreEqual(r1.max_intensity, r4.max_intensity, L"r4.max_intensity matches reference.", LINE_INFO());

            Assert::AreEqual(r1.min_intensity, r2.min_intensity, L"r2.min_intensity matches reference.", LINE_INFO());
            Assert::AreEqual(r1.min_intensity, r3.min_intensity, L"r3.min_intensity matches reference.", LINE_INFO());
            Assert::AreEqual(r1.min_intensity, r4.min_intensity, L"r4.min_intensity matches reference.", LINE_INFO());

            Assert::AreEqual(r1.particles, r2.particles, L"r2.particles matches reference.", LINE_INFO());
            Assert::AreEqual(r1.particles, r3.particles, L"r3.particles matches reference.", LINE_INFO());
            Assert::AreEqual(r1.particles, r4.particles, L"r4.particles matches reference.", LINE_INFO());

            Assert::AreEqual(r1.radius, r2.radius, L"r2.radius matches reference.", LINE_INFO());
            Assert::AreEqual(r1.radius, r3.radius, L"r3.radius matches reference.", LINE_INFO());
            Assert::AreEqual(r1.radius, r4.radius, L"r4.radius matches reference.", LINE_INFO());

            Assert::AreEqual(v_t(r1.vertex_type), v_t(r2.vertex_type), L"r2.vertex_type matches reference.", LINE_INFO());
            Assert::AreEqual(v_t(r1.vertex_type), v_t(r3.vertex_type), L"r3.vertex_type matches reference.", LINE_INFO());
            Assert::AreEqual(v_t(r1.vertex_type), v_t(r4.vertex_type), L"r4.vertex_type matches reference.", LINE_INFO());
        }

        TEST_METHOD(Test_test_xyzr_float_rgba_float) {
            typedef std::underlying_type<mmpld::colour_type>::type c_t;
            typedef std::underlying_type<mmpld::vertex_type>::type v_t;
            ::SetMmpldWorkingDirectory();

            auto r1 = this->testFile<HANDLE>("test_xyzr_float_rgba_float.mmpld");
            auto r2 = this->testFile<FILE *>("test_xyzr_float_rgba_float.mmpld");
            auto r3 = this->testFile<int>("test_xyzr_float_rgba_float.mmpld");
            auto r4 = this->testFile<std::ifstream>("test_xyzr_float_rgba_float.mmpld");

            Assert::AreEqual(v_t(mmpld::vertex_type::float_xyzr), v_t(r1.vertex_type), L"vertex_type of test_xyzr_float_rgba_float.mmpld", LINE_INFO());
            Assert::AreEqual(c_t(mmpld::colour_type::rgba32), c_t(r1.colour_type), L"colour_type of test_xyzr_float_rgba_float.mmpld", LINE_INFO());

            Assert::AreEqual(decltype(r1.particles)(4), r1.particles, L"Number of particles is 4.", LINE_INFO());

            Assert::IsTrue(::memcmp(r1.colour, r2.colour, sizeof(r1.colour)) == 0, L"r2.colour matches reference.", LINE_INFO());
            Assert::IsTrue(::memcmp(r1.colour, r3.colour, sizeof(r1.colour)) == 0, L"r3.colour matches reference.", LINE_INFO());
            Assert::IsTrue(::memcmp(r1.colour, r4.colour, sizeof(r1.colour)) == 0, L"r4.colour matches reference.", LINE_INFO());

            Assert::AreEqual(c_t(r1.colour_type), c_t(r2.colour_type), L"r2.colour_type matches reference.", LINE_INFO());
            Assert::AreEqual(c_t(r1.colour_type), c_t(r3.colour_type), L"r3.colour_type matches reference.", LINE_INFO());
            Assert::AreEqual(c_t(r1.colour_type), c_t(r4.colour_type), L"r4.colour_type matches reference.", LINE_INFO());

            Assert::AreEqual(r1.max_intensity, r2.max_intensity, L"r2.max_intensity matches reference.", LINE_INFO());
            Assert::AreEqual(r1.max_intensity, r3.max_intensity, L"r3.max_intensity matches reference.", LINE_INFO());
            Assert::AreEqual(r1.max_intensity, r4.max_intensity, L"r4.max_intensity matches reference.", LINE_INFO());

            Assert::AreEqual(r1.min_intensity, r2.min_intensity, L"r2.min_intensity matches reference.", LINE_INFO());
            Assert::AreEqual(r1.min_intensity, r3.min_intensity, L"r3.min_intensity matches reference.", LINE_INFO());
            Assert::AreEqual(r1.min_intensity, r4.min_intensity, L"r4.min_intensity matches reference.", LINE_INFO());

            Assert::AreEqual(r1.particles, r2.particles, L"r2.particles matches reference.", LINE_INFO());
            Assert::AreEqual(r1.particles, r3.particles, L"r3.particles matches reference.", LINE_INFO());
            Assert::AreEqual(r1.particles, r4.particles, L"r4.particles matches reference.", LINE_INFO());

            Assert::AreEqual(r1.radius, r2.radius, L"r2.radius matches reference.", LINE_INFO());
            Assert::AreEqual(r1.radius, r3.radius, L"r3.radius matches reference.", LINE_INFO());
            Assert::AreEqual(r1.radius, r4.radius, L"r4.radius matches reference.", LINE_INFO());

            Assert::AreEqual(v_t(r1.vertex_type), v_t(r2.vertex_type), L"r2.vertex_type matches reference.", LINE_INFO());
            Assert::AreEqual(v_t(r1.vertex_type), v_t(r3.vertex_type), L"r3.vertex_type matches reference.", LINE_INFO());
            Assert::AreEqual(v_t(r1.vertex_type), v_t(r4.vertex_type), L"r4.vertex_type matches reference.", LINE_INFO());
        }

    private:

        template<class F, class C> mmpld::list_header testFile(const C *path) {
            typedef mmpld::file<F, C> file_type;

            file_type file(path);

            Assert::AreEqual(decltype(file.frames())(1), file.frames(), L"File contains one frame", LINE_INFO());
            Assert::AreEqual(std::uint32_t(file.frames()), file.file_header().frames, L"Frame number and content of header matches.", LINE_INFO());
            Assert::AreEqual(size_t(file.frames()), file.seek_table().size(), L"Number of frames and size of seek table match.", LINE_INFO());
            Assert::AreEqual(std::int32_t(1), file.frame_header().lists, L"Frame #1 holds one particle list.", LINE_INFO());
            Assert::AreEqual(-2.0f, file.file_header().bounding_box[0], 0.0001f, L"Bounding box at 0", LINE_INFO());
            Assert::AreEqual(-2.0f, file.file_header().bounding_box[1], 0.0001f, L"Bounding box at 1", LINE_INFO());
            Assert::AreEqual(-2.0f, file.file_header().bounding_box[2], 0.0001f, L"Bounding box at 2", LINE_INFO());
            Assert::AreEqual(2.0f, file.file_header().bounding_box[3], 0.0001f, L"Bounding box at 3", LINE_INFO());
            Assert::AreEqual(2.0f, file.file_header().bounding_box[4], 0.0001f, L"Bounding box at 4", LINE_INFO());
            Assert::AreEqual(2.0f, file.file_header().bounding_box[5], 0.0001f, L"Bounding box at 5", LINE_INFO());

            mmpld::list_header retval;
            file.read_particles(true, retval, nullptr, 0);
            Assert::AreEqual(std::uint64_t(4), retval.particles, L"List holds four particles.", LINE_INFO());

            std::vector<std::uint8_t> buffer(mmpld::get_stride<std::uint64_t>(retval) * (retval.particles + 1));
            Assert::ExpectException<std::runtime_error>([&]() {
                file.read_particles(retval, buffer.data(), buffer.size());
            }, L"Premature end of file raises exception.", LINE_INFO());

            return retval;
        }
    };
}
