// <copyright file="ConvertTest.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "stdafx.h"
#include "CppUnitTest.h"

#include "util.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace test {

    /// <summary>
    /// Tests the conversion functions
    /// </summary>
    TEST_CLASS(ConvertTest) {

        TEST_METHOD(TestStaticConvertXyzFloatIntFloatToXyzFloatIntFloat) {
            typedef mmpld::particle_traits<mmpld::vertex_type::float_xyz, mmpld::colour_type::intensity> src_view;
            typedef src_view dst_view;
            std::vector<std::uint8_t> src(2 * src_view::stride());
            std::vector<std::uint8_t> dst(2 * dst_view::stride());
            mmpld::list_header src_header;
            src_header.particles = 2;
            src_header.vertex_type = src_view::vertex_traits::value;
            src_header.colour_type = src_view::colour_traits::colour_type;
            src_header.radius = 12.0f;
            src_header.colour[0] = 0.7f;
            src_header.colour[1] = 0.8f;
            src_header.colour[2] = 0.9f;
            src_header.colour[3] = 0.5f;

            src_view::position(src.data())[0] = 1.0f;
            src_view::position(src.data())[1] = 2.0f;
            src_view::position(src.data())[2] = 3.0f;
            *src_view::colour(src.data()) = 0.5f;

            src_view::position(src.data() + src_view::stride())[0] = 4.0f;
            src_view::position(src.data() + src_view::stride())[1] = 5.0f;
            src_view::position(src.data() + src_view::stride())[2] = 6.0f;
            *src_view::colour(src.data() + src_view::stride()) = 1.0f;

            auto cnt = mmpld::convert<dst_view>(src.data(), src_header, dst.data(), 2);
            Assert::AreEqual(std::uint64_t(2), cnt, L"All particles have been converted.", LINE_INFO());

            for (size_t i = 0, end = src.size(); i < end; ++i) {
                Assert::AreEqual(src[i], dst[i], L"Particle byte has been copied.", LINE_INFO());
            }
        }

        TEST_METHOD(TestStaticConvertXyzFloatIntFloatToXyzShortIntFloat) {
            typedef mmpld::particle_traits<mmpld::vertex_type::float_xyz, mmpld::colour_type::intensity> src_view;
            typedef mmpld::particle_traits<mmpld::vertex_type::short_xyz, mmpld::colour_type::intensity> dst_view;
            std::vector<std::uint8_t> src(2 * src_view::stride());
            std::vector<std::uint8_t> dst(2 * dst_view::stride());
            mmpld::list_header src_header;
            src_header.particles = 2;
            src_header.vertex_type = src_view::vertex_traits::value;
            src_header.colour_type = src_view::colour_traits::colour_type;
            src_header.radius = 12.0f;
            src_header.colour[0] = 0.7f;
            src_header.colour[1] = 0.8f;
            src_header.colour[2] = 0.9f;
            src_header.colour[3] = 0.5f;

            src_view::position(src.data())[0] = 1.0f;
            src_view::position(src.data())[1] = 2.0f;
            src_view::position(src.data())[2] = 3.0f;
            *src_view::colour(src.data()) = 0.5f;

            src_view::position(src.data() + src_view::stride())[0] = 4.0f;
            src_view::position(src.data() + src_view::stride())[1] = 5.0f;
            src_view::position(src.data() + src_view::stride())[2] = 6.0f;
            *src_view::colour(src.data() + src_view::stride()) = 1.0f;

            auto cnt = mmpld::convert<dst_view>(src.data(), src_header, dst.data(), 2);
            Assert::AreEqual(std::uint64_t(2), cnt, L"All particles have been converted.", LINE_INFO());

            Assert::AreEqual(dst_view::vertex_value_type(1), dst_view::position(dst.data())[0], L"P1: Conversion to short at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(2), dst_view::position(dst.data())[1], L"P1: Conversion to short at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(3), dst_view::position(dst.data())[2], L"P1: Conversion to short at [2]", LINE_INFO());
            Assert::AreEqual(*src_view::colour(src.data()), *dst_view::colour(dst.data()), L"P1: Unchanged intensity", LINE_INFO());

            Assert::AreEqual(dst_view::vertex_value_type(4), dst_view::position(dst.data() + dst_view::stride())[0], L"P2: Conversion to short at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(5), dst_view::position(dst.data() + dst_view::stride())[1], L"P2: Conversion to short at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(6), dst_view::position(dst.data() + dst_view::stride())[2], L"P2: Conversion to short at [2]", LINE_INFO());
            Assert::AreEqual(*src_view::colour(src.data() + src_view::stride()), *dst_view::colour(dst.data() + dst_view::stride()), L"P2: Unchanged intensity", LINE_INFO());
        }

        TEST_METHOD(TestStaticConvertXyzFloatIntFloatToXyzrFloatNone) {
            typedef mmpld::particle_traits<mmpld::vertex_type::float_xyz, mmpld::colour_type::intensity> src_view;
            typedef mmpld::particle_traits<mmpld::vertex_type::float_xyzr, mmpld::colour_type::none> dst_view;
            std::vector<std::uint8_t> src(2 * src_view::stride());
            std::vector<std::uint8_t> dst(2 * dst_view::stride());
            mmpld::list_header src_header;
            src_header.particles = 2;
            src_header.vertex_type = src_view::vertex_traits::value;
            src_header.colour_type = src_view::colour_traits::colour_type;
            src_header.radius = 12.0f;
            src_header.colour[0] = 0.7f;
            src_header.colour[1] = 0.8f;
            src_header.colour[2] = 0.9f;
            src_header.colour[3] = 0.5f;

            src_view::position(src.data())[0] = 1.0f;
            src_view::position(src.data())[1] = 2.0f;
            src_view::position(src.data())[2] = 3.0f;
            *src_view::colour(src.data()) = 0.5f;

            src_view::position(src.data() + src_view::stride())[0] = 4.0f;
            src_view::position(src.data() + src_view::stride())[1] = 5.0f;
            src_view::position(src.data() + src_view::stride())[2] = 6.0f;
            *src_view::colour(src.data() + src_view::stride()) = 1.0f;

            auto cnt = mmpld::convert<dst_view>(src.data(), src_header, dst.data(), 2);
            Assert::AreEqual(std::uint64_t(2), cnt, L"All particles have been converted.", LINE_INFO());

            Assert::AreEqual(dst_view::vertex_value_type(1), dst_view::position(dst.data())[0], L"P1: Conversion to short at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(2), dst_view::position(dst.data())[1], L"P1: Conversion to short at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(3), dst_view::position(dst.data())[2], L"P1: Conversion to short at [2]", LINE_INFO());
            Assert::AreEqual(src_header.radius, *dst_view::radius(dst.data()), L"P1: Global radius has been converted.", LINE_INFO());

            Assert::AreEqual(dst_view::vertex_value_type(4), dst_view::position(dst.data() + dst_view::stride())[0], L"P2: Conversion to short at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(5), dst_view::position(dst.data() + dst_view::stride())[1], L"P2: Conversion to short at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(6), dst_view::position(dst.data() + dst_view::stride())[2], L"P2: Conversion to short at [2]", LINE_INFO());
            Assert::AreEqual(src_header.radius, *dst_view::radius(dst.data() + dst_view::stride()), L"P2: Global radius has been converted.", LINE_INFO());
        }

        TEST_METHOD(TestStaticConvertXyzShortNoneToXyzrFloatRgba32) {
            typedef mmpld::particle_traits<mmpld::vertex_type::short_xyz, mmpld::colour_type::none> src_view;
            typedef mmpld::particle_traits<mmpld::vertex_type::float_xyzr, mmpld::colour_type::rgba32> dst_view;
            std::vector<std::uint8_t> src(2 * src_view::stride());
            std::vector<std::uint8_t> dst(2 * dst_view::stride());
            mmpld::list_header src_header;
            src_header.particles = 2;
            src_header.vertex_type = src_view::vertex_traits::value;
            src_header.colour_type = src_view::colour_traits::colour_type;
            src_header.radius = 12.0f;
            src_header.colour[0] = 0.7f;
            src_header.colour[1] = 0.8f;
            src_header.colour[2] = 0.9f;
            src_header.colour[3] = 0.5f;

            src_view::position(src.data())[0] = 1;
            src_view::position(src.data())[1] = 2;
            src_view::position(src.data())[2] = 3;

            src_view::position(src.data() + src_view::stride())[0] = 4;
            src_view::position(src.data() + src_view::stride())[1] = 5;
            src_view::position(src.data() + src_view::stride())[2] = 6;

            auto cnt = mmpld::convert<dst_view>(src.data(), src_header, dst.data(), 2);
            Assert::AreEqual(std::uint64_t(2), cnt, L"All particles have been converted.", LINE_INFO());

            Assert::AreEqual(dst_view::vertex_value_type(1), dst_view::position(dst.data())[0], L"P1: Conversion to float at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(2), dst_view::position(dst.data())[1], L"P1: Conversion to float at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(3), dst_view::position(dst.data())[2], L"P1: Conversion to float at [2]", LINE_INFO());
            Assert::AreEqual(src_header.radius, *dst_view::radius(dst.data()), L"P1: Global radius has been converted.", LINE_INFO());
            Assert::AreEqual(src_header.colour[0], dst_view::colour(dst.data())[0], L"P1: Global colour has been copied to [0]", LINE_INFO());
            Assert::AreEqual(src_header.colour[1], dst_view::colour(dst.data())[1], L"P1: Global colour has been copied to [1]", LINE_INFO());
            Assert::AreEqual(src_header.colour[2], dst_view::colour(dst.data())[2], L"P1: Global colour has been copied to [2]", LINE_INFO());
            Assert::AreEqual(src_header.colour[3], dst_view::colour(dst.data())[3], L"P1: Global colour has been copied to [3]", LINE_INFO());

            Assert::AreEqual(dst_view::vertex_value_type(4), dst_view::position(dst.data() + dst_view::stride())[0], L"P2: Conversion to float at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(5), dst_view::position(dst.data() + dst_view::stride())[1], L"P2: Conversion to float at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(6), dst_view::position(dst.data() + dst_view::stride())[2], L"P2: Conversion to float at [2]", LINE_INFO());
            Assert::AreEqual(src_header.radius, *dst_view::radius(dst.data() + dst_view::stride()), L"P2: Global radius has been converted.", LINE_INFO());
            Assert::AreEqual(src_header.colour[0], dst_view::colour(dst.data() + dst_view::stride())[0], L"P2: Global colour has been copied to [0]", LINE_INFO());
            Assert::AreEqual(src_header.colour[1], dst_view::colour(dst.data() + dst_view::stride())[1], L"P2: Global colour has been copied to [1]", LINE_INFO());
            Assert::AreEqual(src_header.colour[2], dst_view::colour(dst.data() + dst_view::stride())[2], L"P2: Global colour has been copied to [2]", LINE_INFO());
            Assert::AreEqual(src_header.colour[3], dst_view::colour(dst.data() + dst_view::stride())[3], L"P2: Global colour has been copied to [3]", LINE_INFO());
        }

        TEST_METHOD(TestStaticConvertXyzShortRgb8ToXyzrFloatRgba32) {
            typedef mmpld::particle_traits<mmpld::vertex_type::short_xyz, mmpld::colour_type::rgb8> src_view;
            typedef mmpld::particle_traits<mmpld::vertex_type::float_xyzr, mmpld::colour_type::rgba32> dst_view;
            std::vector<std::uint8_t> src(2 * src_view::stride());
            std::vector<std::uint8_t> dst(2 * dst_view::stride());
            mmpld::list_header src_header;
            src_header.particles = 2;
            src_header.vertex_type = src_view::vertex_traits::value;
            src_header.colour_type = src_view::colour_traits::colour_type;
            src_header.radius = 12.0f;
            src_header.colour[0] = 0.7f;
            src_header.colour[1] = 0.8f;
            src_header.colour[2] = 0.9f;
            src_header.colour[3] = 0.5f;

            src_view::position(src.data())[0] = 1;
            src_view::position(src.data())[1] = 2;
            src_view::position(src.data())[2] = 3;
            src_view::colour(src.data())[0] = 0;
            src_view::colour(src.data())[1] = 16;
            src_view::colour(src.data())[2] = 32;

            src_view::position(src.data() + src_view::stride())[0] = 4;
            src_view::position(src.data() + src_view::stride())[1] = 5;
            src_view::position(src.data() + src_view::stride())[2] = 6;
            src_view::colour(src.data() + src_view::stride())[0] = 64;
            src_view::colour(src.data() + src_view::stride())[1] = 128;
            src_view::colour(src.data() + src_view::stride())[2] = 255;

            auto cnt = mmpld::convert<dst_view>(src.data(), src_header, dst.data(), 2);
            Assert::AreEqual(std::uint64_t(2), cnt, L"All particles have been converted.", LINE_INFO());

            Assert::AreEqual(dst_view::vertex_value_type(1), dst_view::position(dst.data())[0], L"P1: Conversion to float at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(2), dst_view::position(dst.data())[1], L"P1: Conversion to float at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(3), dst_view::position(dst.data())[2], L"P1: Conversion to float at [2]", LINE_INFO());
            Assert::AreEqual(src_header.radius, *dst_view::radius(dst.data()), L"P1: Global radius has been converted.", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(0.f / 255.f), dst_view::colour(dst.data())[0], L"P1: Byte to float colour conversion at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(16.f / 255.f), dst_view::colour(dst.data())[1], L"P1: Byte to float colour conversion at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(32.f / 255.f), dst_view::colour(dst.data())[2], L"P1: Byte to float colour conversion at [2]", LINE_INFO());

            Assert::AreEqual(dst_view::vertex_value_type(4), dst_view::position(dst.data() + dst_view::stride())[0], L"P2: Conversion to float at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(5), dst_view::position(dst.data() + dst_view::stride())[1], L"P2: Conversion to float at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(6), dst_view::position(dst.data() + dst_view::stride())[2], L"P2: Conversion to float at [2]", LINE_INFO());
            Assert::AreEqual(src_header.radius, *dst_view::radius(dst.data() + dst_view::stride()), L"P2: Global radius has been converted.", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(64.f / 255.f), dst_view::colour(dst.data() + dst_view::stride())[0], L"P2: Byte to float colour conversion at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(128.f / 255.f), dst_view::colour(dst.data() + dst_view::stride())[1], L"P2: Byte to float colour conversion at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(255.f / 255.f), dst_view::colour(dst.data() + dst_view::stride())[2], L"P2: Byte to float colour conversion at [2]", LINE_INFO());
        }

        TEST_METHOD(TestStaticConvertXyzShortRgb8ToXyzFloatRgba8) {
            typedef mmpld::particle_traits<mmpld::vertex_type::short_xyz, mmpld::colour_type::rgb8> src_view;
            typedef mmpld::particle_traits<mmpld::vertex_type::float_xyz, mmpld::colour_type::rgba8> dst_view;
            std::vector<std::uint8_t> src(2 * src_view::stride());
            std::vector<std::uint8_t> dst(2 * dst_view::stride());
            mmpld::list_header src_header;
            src_header.particles = 2;
            src_header.vertex_type = src_view::vertex_traits::value;
            src_header.colour_type = src_view::colour_traits::colour_type;
            src_header.radius = 12.0f;
            src_header.colour[0] = 0.7f;
            src_header.colour[1] = 0.8f;
            src_header.colour[2] = 0.9f;
            src_header.colour[3] = 0.5f;

            src_view::position(src.data())[0] = 1;
            src_view::position(src.data())[1] = 2;
            src_view::position(src.data())[2] = 3;
            src_view::colour(src.data())[0] = 0;
            src_view::colour(src.data())[1] = 16;
            src_view::colour(src.data())[2] = 32;

            src_view::position(src.data() + src_view::stride())[0] = 4;
            src_view::position(src.data() + src_view::stride())[1] = 5;
            src_view::position(src.data() + src_view::stride())[2] = 6;
            src_view::colour(src.data() + src_view::stride())[0] = 64;
            src_view::colour(src.data() + src_view::stride())[1] = 128;
            src_view::colour(src.data() + src_view::stride())[2] = 255;

            auto cnt = mmpld::convert<dst_view>(src.data(), src_header, dst.data(), 2);
            Assert::AreEqual(std::uint64_t(2), cnt, L"All particles have been converted.", LINE_INFO());

            Assert::AreEqual(dst_view::vertex_value_type(1), dst_view::position(dst.data())[0], L"P1: Conversion to float at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(2), dst_view::position(dst.data())[1], L"P1: Conversion to float at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(3), dst_view::position(dst.data())[2], L"P1: Conversion to float at [2]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(0), dst_view::colour(dst.data())[0], L"P1: Byte colour copy at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(16), dst_view::colour(dst.data())[1], L"P1: Byte colour copy at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(32), dst_view::colour(dst.data())[2], L"P1: Byte colour copy at [2]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(255), dst_view::colour(dst.data())[3], L"P1: Opaque alpha inserted at [3]", LINE_INFO());


            Assert::AreEqual(dst_view::vertex_value_type(4), dst_view::position(dst.data() + dst_view::stride())[0], L"P2: Conversion to float at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(5), dst_view::position(dst.data() + dst_view::stride())[1], L"P2: Conversion to float at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(6), dst_view::position(dst.data() + dst_view::stride())[2], L"P2: Conversion to float at [2]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(64), dst_view::colour(dst.data() + dst_view::stride())[0], L"P2: Byte colour copy at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(128), dst_view::colour(dst.data() + dst_view::stride())[1], L"P2: Byte colour copy at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(255), dst_view::colour(dst.data() + dst_view::stride())[2], L"P2: Byte colour copy at [2]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(255), dst_view::colour(dst.data() + dst_view::stride())[3], L"P2: Opaque alpha inserted at [3]", LINE_INFO());
        }

        TEST_METHOD(TestStatiConvertXyzShortRgb32ToXyzFloatRgba32) {
            typedef mmpld::particle_traits<mmpld::vertex_type::short_xyz, mmpld::colour_type::rgb32> src_view;
            typedef mmpld::particle_traits<mmpld::vertex_type::float_xyz, mmpld::colour_type::rgba32> dst_view;
            std::vector<std::uint8_t> src(2 * src_view::stride());
            std::vector<std::uint8_t> dst(2 * dst_view::stride());
            mmpld::list_header src_header;
            src_header.particles = 2;
            src_header.vertex_type = src_view::vertex_traits::value;
            src_header.colour_type = src_view::colour_traits::colour_type;
            src_header.radius = 12.0f;
            src_header.colour[0] = 0.7f;
            src_header.colour[1] = 0.8f;
            src_header.colour[2] = 0.9f;
            src_header.colour[3] = 0.5f;

            src_view::position(src.data())[0] = 1;
            src_view::position(src.data())[1] = 2;
            src_view::position(src.data())[2] = 3;
            src_view::colour(src.data())[0] = 0.1f;
            src_view::colour(src.data())[1] = 0.2f;
            src_view::colour(src.data())[2] = 0.3f;

            src_view::position(src.data() + src_view::stride())[0] = 4;
            src_view::position(src.data() + src_view::stride())[1] = 5;
            src_view::position(src.data() + src_view::stride())[2] = 6;
            src_view::colour(src.data() + src_view::stride())[0] = 0.4f;
            src_view::colour(src.data() + src_view::stride())[1] = 0.5f;
            src_view::colour(src.data() + src_view::stride())[2] = 0.6f;

            auto cnt = mmpld::convert<dst_view>(src.data(), src_header, dst.data(), 2);
            Assert::AreEqual(std::uint64_t(2), cnt, L"All particles have been converted.", LINE_INFO());

            Assert::AreEqual(dst_view::vertex_value_type(1), dst_view::position(dst.data())[0], L"P1: Conversion to float at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(2), dst_view::position(dst.data())[1], L"P1: Conversion to float at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(3), dst_view::position(dst.data())[2], L"P1: Conversion to float at [2]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(0.1), dst_view::colour(dst.data())[0], L"P1: Float colour copy at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(0.2), dst_view::colour(dst.data())[1], L"P1: Float colour copy at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(0.3), dst_view::colour(dst.data())[2], L"P1: Float colour copy at [2]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(1.0), dst_view::colour(dst.data())[3], L"P1: Opaque alpha inserted at [3]", LINE_INFO());

            Assert::AreEqual(dst_view::vertex_value_type(4), dst_view::position(dst.data() + dst_view::stride())[0], L"P2: Conversion to float at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(5), dst_view::position(dst.data() + dst_view::stride())[1], L"P2: Conversion to float at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(6), dst_view::position(dst.data() + dst_view::stride())[2], L"P2: Conversion to float at [2]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(0.4), dst_view::colour(dst.data() + dst_view::stride())[0], L"P2: Float colour copy at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(0.5), dst_view::colour(dst.data() + dst_view::stride())[1], L"P2: Float colour copy at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(0.6), dst_view::colour(dst.data() + dst_view::stride())[2], L"P2: Float colour copy at [2]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(1.0), dst_view::colour(dst.data() + dst_view::stride())[3], L"P2: Opaque alpha inserted at [3]", LINE_INFO());
        }

        TEST_METHOD(TestStaticConvertXyzShortRgb8ToXyzFloatRgba32) {
            typedef mmpld::particle_traits<mmpld::vertex_type::short_xyz, mmpld::colour_type::rgb8> src_view;
            typedef mmpld::particle_traits<mmpld::vertex_type::float_xyzr, mmpld::colour_type::rgba32> dst_view;
            std::vector<std::uint8_t> src(2 * src_view::stride());
            std::vector<std::uint8_t> dst(2 * dst_view::stride());
            mmpld::list_header src_header;
            src_header.particles = 2;
            src_header.vertex_type = src_view::vertex_traits::value;
            src_header.colour_type = src_view::colour_traits::colour_type;
            src_header.radius = 12.0f;
            src_header.colour[0] = 0.7f;
            src_header.colour[1] = 0.8f;
            src_header.colour[2] = 0.9f;
            src_header.colour[3] = 0.5f;

            src_view::position(src.data())[0] = 1;
            src_view::position(src.data())[1] = 2;
            src_view::position(src.data())[2] = 3;
            src_view::colour(src.data())[0] = 0;
            src_view::colour(src.data())[1] = 16;
            src_view::colour(src.data())[2] = 32;

            src_view::position(src.data() + src_view::stride())[0] = 4;
            src_view::position(src.data() + src_view::stride())[1] = 5;
            src_view::position(src.data() + src_view::stride())[2] = 6;
            src_view::colour(src.data() + src_view::stride())[0] = 64;
            src_view::colour(src.data() + src_view::stride())[1] = 128;
            src_view::colour(src.data() + src_view::stride())[2] = 255;

            auto cnt = mmpld::convert<dst_view>(src.data(), src_header, dst.data(), 2);
            Assert::AreEqual(std::uint64_t(2), cnt, L"All particles have been converted.", LINE_INFO());

            Assert::AreEqual(dst_view::vertex_value_type(1), dst_view::position(dst.data())[0], L"P1: Conversion to float at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(2), dst_view::position(dst.data())[1], L"P1: Conversion to float at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(3), dst_view::position(dst.data())[2], L"P1: Conversion to float at [2]", LINE_INFO());
            Assert::AreEqual(src_header.radius, *dst_view::radius(dst.data()), L"P1: Global radius has been converted.", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(0.0 / 255.0), dst_view::colour(dst.data())[0], L"P1: Conversion to float colour at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(16.0 / 255.0), dst_view::colour(dst.data())[1], L"P1: Conversion to float colour at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(32.0 / 255.0), dst_view::colour(dst.data())[2], L"P1: Conversion to float colour at [2]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(1.0), dst_view::colour(dst.data())[3], L"P1: Opaque alpha inserted at [3]", LINE_INFO());

            Assert::AreEqual(dst_view::vertex_value_type(4), dst_view::position(dst.data() + dst_view::stride())[0], L"P2: Conversion to float at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(5), dst_view::position(dst.data() + dst_view::stride())[1], L"P2: Conversion to float at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(6), dst_view::position(dst.data() + dst_view::stride())[2], L"P2: Conversion to float at [2]", LINE_INFO());
            Assert::AreEqual(src_header.radius, *dst_view::radius(dst.data() + dst_view::stride()), L"P2: Global radius has been converted.", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(64.0 / 255.0), dst_view::colour(dst.data() + dst_view::stride())[0], L"P2: Conversion to float colour at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(128.0 / 255.0), dst_view::colour(dst.data() + dst_view::stride())[1], L"P2: Conversion to float colour at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(255.0 / 255.0), dst_view::colour(dst.data() + dst_view::stride())[2], L"P2: Conversion to float colour at [2]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(1.0), dst_view::colour(dst.data() + dst_view::stride())[3], L"P2: Opaque alpha inserted at [3]", LINE_INFO());
        }

        TEST_METHOD(TestStaticConvertXyzFloatRgb32ToXyzShortRgba8) {
            typedef mmpld::particle_traits<mmpld::vertex_type::float_xyz, mmpld::colour_type::rgb32> src_view;
            typedef mmpld::particle_traits<mmpld::vertex_type::short_xyz, mmpld::colour_type::rgba8> dst_view;
            std::vector<std::uint8_t> src(2 * src_view::stride());
            std::vector<std::uint8_t> dst(2 * dst_view::stride());
            mmpld::list_header src_header;
            src_header.particles = 2;
            src_header.vertex_type = src_view::vertex_traits::value;
            src_header.colour_type = src_view::colour_traits::colour_type;
            src_header.radius = 12.0f;
            src_header.colour[0] = 0.7f;
            src_header.colour[1] = 0.8f;
            src_header.colour[2] = 0.9f;
            src_header.colour[3] = 0.5f;

            src_view::position(src.data())[0] = 1.0f;
            src_view::position(src.data())[1] = 2.0f;
            src_view::position(src.data())[2] = 3.0f;
            src_view::colour(src.data())[0] = 0.0f;
            src_view::colour(src.data())[1] = 16.0f / 255.0f;
            src_view::colour(src.data())[2] = 32.0f / 255.0f;

            src_view::position(src.data() + src_view::stride())[0] = 4.0f;
            src_view::position(src.data() + src_view::stride())[1] = 5.0f;
            src_view::position(src.data() + src_view::stride())[2] = 6.0f;
            src_view::colour(src.data() + src_view::stride())[0] = 64.0f / 255.0f;
            src_view::colour(src.data() + src_view::stride())[1] = 128.0f / 255.0f;
            src_view::colour(src.data() + src_view::stride())[2] = 255.0f / 255.0f;

            auto cnt = mmpld::convert<dst_view>(src.data(), src_header, dst.data(), 2);
            Assert::AreEqual(std::uint64_t(2), cnt, L"All particles have been converted.", LINE_INFO());

            Assert::AreEqual(dst_view::vertex_value_type(1), dst_view::position(dst.data())[0], L"P1: Conversion to float at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(2), dst_view::position(dst.data())[1], L"P1: Conversion to float at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(3), dst_view::position(dst.data())[2], L"P1: Conversion to float at [2]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(0), dst_view::colour(dst.data())[0], L"P1: Conversion to byte colour at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(16), dst_view::colour(dst.data())[1], L"P1: Conversion to byte colour at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(32), dst_view::colour(dst.data())[2], L"P1: Conversion to byte colour at [2]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(255), dst_view::colour(dst.data())[3], L"P1: Opaque alpha inserted at [3]", LINE_INFO());

            Assert::AreEqual(dst_view::vertex_value_type(4), dst_view::position(dst.data() + dst_view::stride())[0], L"P2: Conversion to float at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(5), dst_view::position(dst.data() + dst_view::stride())[1], L"P2: Conversion to float at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(6), dst_view::position(dst.data() + dst_view::stride())[2], L"P2: Conversion to float at [2]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(64), dst_view::colour(dst.data() + dst_view::stride())[0], L"P2: Conversion to byte colour at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(128), dst_view::colour(dst.data() + dst_view::stride())[1], L"P2: Conversion to byte colour at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(255), dst_view::colour(dst.data() + dst_view::stride())[2], L"P2: Conversion to byte colour at [2]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(255), dst_view::colour(dst.data() + dst_view::stride())[3], L"P2: Opaque alpha inserted at [3]", LINE_INFO());
        }

        TEST_METHOD(TestStaticConvertXyzDoubleIntDoubleToXyzFloatIntFloat) {
            typedef mmpld::particle_traits<mmpld::vertex_type::double_xyz, mmpld::colour_type::intensity64> src_view;
            typedef mmpld::particle_traits<mmpld::vertex_type::float_xyz, mmpld::colour_type::intensity32> dst_view;
            std::vector<std::uint8_t> src(2 * src_view::stride());
            std::vector<std::uint8_t> dst(2 * dst_view::stride());
            mmpld::list_header src_header;
            src_header.particles = 2;
            src_header.vertex_type = src_view::vertex_traits::value;
            src_header.colour_type = src_view::colour_traits::colour_type;
            src_header.radius = 12.0f;
            src_header.min_intensity = 0.0f;
            src_header.max_intensity = 1.0f;

            src_view::position(src.data())[0] = 1.0;
            src_view::position(src.data())[1] = 2.0;
            src_view::position(src.data())[2] = 3.0;
            src_view::colour(src.data())[0] = 0.0;

            src_view::position(src.data() + src_view::stride())[0] = 4.0;
            src_view::position(src.data() + src_view::stride())[1] = 5.0;
            src_view::position(src.data() + src_view::stride())[2] = 6.0;
            src_view::colour(src.data() + src_view::stride())[0] = 1.0;

            auto cnt = mmpld::convert<dst_view>(src.data(), src_header, dst.data(), 2);
            Assert::AreEqual(std::uint64_t(2), cnt, L"All particles have been converted.", LINE_INFO());

            Assert::AreEqual(dst_view::vertex_value_type(1), dst_view::position(dst.data())[0], L"P1: Conversion to float at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(2), dst_view::position(dst.data())[1], L"P1: Conversion to float at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(3), dst_view::position(dst.data())[2], L"P1: Conversion to float at [2]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(0), dst_view::colour(dst.data())[0], L"P1: Conversion to float intensity", LINE_INFO());

            Assert::AreEqual(dst_view::vertex_value_type(4), dst_view::position(dst.data() + dst_view::stride())[0], L"P2: Conversion to float at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(5), dst_view::position(dst.data() + dst_view::stride())[1], L"P2: Conversion to float at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(6), dst_view::position(dst.data() + dst_view::stride())[2], L"P2: Conversion to float at [2]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(1), dst_view::colour(dst.data() + dst_view::stride())[0], L"P2: Conversion to float intensity", LINE_INFO());
        }

        TEST_METHOD(TestStaticReadXyzFloatIntFloatAsXyzFloatIntFloat) {
            ::SetMmpldWorkingDirectory();   // Need to have access to the test files.

            typedef mmpld::particle_traits<mmpld::vertex_type::float_xyz, mmpld::colour_type::intensity> traits_type;
            auto particles = this->testStaticReadAs<traits_type, std::ifstream>("test_xyz_float_int_float.mmpld");

            {
                auto pos = traits_type::position(particles.data() + 0 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 0 * traits_type::stride());
                Assert::AreEqual(0.0f, pos[0], L"First position x", LINE_INFO());
                Assert::AreEqual(0.0f, pos[1], L"First position y", LINE_INFO());
                Assert::AreEqual(0.0f, pos[2], L"First position z", LINE_INFO());
                Assert::AreEqual(255.0f, col[0], L"First intensity", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 1 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 1 * traits_type::stride());
                Assert::AreEqual(1.0f, pos[0], L"Second position x", LINE_INFO());
                Assert::AreEqual(0.0f, pos[1], L"Second position y", LINE_INFO());
                Assert::AreEqual(0.0f, pos[2], L"Second position z", LINE_INFO());
                Assert::AreEqual(64.0f, col[0], L"Second intensity", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 2 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 2 * traits_type::stride());
                Assert::AreEqual(0.0f, pos[0], L"Third position x", LINE_INFO());
                Assert::AreEqual(1.0f, pos[1], L"Third position y", LINE_INFO());
                Assert::AreEqual(0.0f, pos[2], L"Third position z", LINE_INFO());
                Assert::AreEqual(128.0f, col[0], L"Third intensity", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 3 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 3 * traits_type::stride());
                Assert::AreEqual(0.0f, pos[0], L"Fourth position x", LINE_INFO());
                Assert::AreEqual(0.0f, pos[1], L"Fourth position y", LINE_INFO());
                Assert::AreEqual(1.0f, pos[2], L"Fourth position z", LINE_INFO());
                Assert::AreEqual(192.0f, col[0], L"Fourth intensity", LINE_INFO());
            }
        }

        TEST_METHOD(TestStaticReadXyzFloatIntFloatAsXyzShortIntFloat) {
            ::SetMmpldWorkingDirectory();   // Need to have access to the test files.

            typedef mmpld::particle_traits<mmpld::vertex_type::short_xyz, mmpld::colour_type::intensity> traits_type;
            auto particles = this->testStaticReadAs<traits_type, std::ifstream>("test_xyz_float_int_float.mmpld");

            {
                auto pos = traits_type::position(particles.data() + 0 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 0 * traits_type::stride());
                Assert::AreEqual(std::int16_t(0), pos[0], L"First position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[1], L"First position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[2], L"First position z", LINE_INFO());
                Assert::AreEqual(255.0f, col[0], L"First intensity", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 1 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 1 * traits_type::stride());
                Assert::AreEqual(std::int16_t(1), pos[0], L"Second position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[1], L"Second position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[2], L"Second position z", LINE_INFO());
                Assert::AreEqual(64.0f, col[0], L"Second intensity", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 2 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 2 * traits_type::stride());
                Assert::AreEqual(std::int16_t(0), pos[0], L"Third position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(1), pos[1], L"Third position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[2], L"Third position z", LINE_INFO());
                Assert::AreEqual(128.0f, col[0], L"Third intensity", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 3 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 3 * traits_type::stride());
                Assert::AreEqual(std::int16_t(0), pos[0], L"Fourth position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[1], L"Fourth position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(1), pos[2], L"Fourth position z", LINE_INFO());
                Assert::AreEqual(192.0f, col[0], L"Fourth intensity", LINE_INFO());
            }
        }

        TEST_METHOD(TestStaticReadXyzFloatIntFloatAsXyzShortIntDouble) {
            ::SetMmpldWorkingDirectory();   // Need to have access to the test files.

            typedef mmpld::particle_traits<mmpld::vertex_type::short_xyz, mmpld::colour_type::intensity64> traits_type;
            auto particles = this->testStaticReadAs<traits_type, HANDLE>("test_xyz_float_int_float.mmpld");

            {
                auto pos = traits_type::position(particles.data() + 0 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 0 * traits_type::stride());
                Assert::AreEqual(std::int16_t(0), pos[0], L"First position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[1], L"First position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[2], L"First position z", LINE_INFO());
                Assert::AreEqual(255.0, col[0], L"First intensity", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 1 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 1 * traits_type::stride());
                Assert::AreEqual(std::int16_t(1), pos[0], L"Second position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[1], L"Second position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[2], L"Second position z", LINE_INFO());
                Assert::AreEqual(64.0, col[0], L"Second intensity", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 2 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 2 * traits_type::stride());
                Assert::AreEqual(std::int16_t(0), pos[0], L"Third position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(1), pos[1], L"Third position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[2], L"Third position z", LINE_INFO());
                Assert::AreEqual(128.0, col[0], L"Third intensity", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 3 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 3 * traits_type::stride());
                Assert::AreEqual(std::int16_t(0), pos[0], L"Fourth position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[1], L"Fourth position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(1), pos[2], L"Fourth position z", LINE_INFO());
                Assert::AreEqual(192.0, col[0], L"Fourth intensity", LINE_INFO());
            }
        }

        TEST_METHOD(TestStaticReadXyzFloatIntFloatAsXyzShortIntRgb32) {
            ::SetMmpldWorkingDirectory();   // Need to have access to the test files.

            typedef mmpld::particle_traits<mmpld::vertex_type::short_xyz, mmpld::colour_type::rgb32> traits_type;
            auto particles = this->testStaticReadAs<traits_type, HANDLE>("test_xyz_float_int_float.mmpld");

            // TODO
            {
                auto pos = traits_type::position(particles.data() + 0 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 0 * traits_type::stride());
                Assert::AreEqual(std::int16_t(0), pos[0], L"First position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[1], L"First position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[2], L"First position z", LINE_INFO());
                Assert::AreEqual(255.0f / 255.0f, col[0], L"First intensity r", LINE_INFO());
                Assert::AreEqual(255.0f / 255.0f, col[1], L"First intensity g", LINE_INFO());
                Assert::AreEqual(255.0f / 255.0f, col[2], L"First intensity b", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 1 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 1 * traits_type::stride());
                Assert::AreEqual(std::int16_t(1), pos[0], L"Second position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[1], L"Second position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[2], L"Second position z", LINE_INFO());
                Assert::AreEqual(64.0f / 255.0f, col[0], L"Second intensity r", LINE_INFO());
                Assert::AreEqual(64.0f / 255.0f, col[1], L"Second intensity g", LINE_INFO());
                Assert::AreEqual(64.0f / 255.0f, col[2], L"Second intensity b", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 2 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 2 * traits_type::stride());
                Assert::AreEqual(std::int16_t(0), pos[0], L"Third position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(1), pos[1], L"Third position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[2], L"Third position z", LINE_INFO());
                Assert::AreEqual(128.0f / 255.0f, col[0], L"Third intensity r", LINE_INFO());
                Assert::AreEqual(128.0f / 255.0f, col[1], L"Third intensity g", LINE_INFO());
                Assert::AreEqual(128.0f / 255.0f, col[2], L"Third intensity b", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 3 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 3 * traits_type::stride());
                Assert::AreEqual(std::int16_t(0), pos[0], L"Fourth position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[1], L"Fourth position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(1), pos[2], L"Fourth position z", LINE_INFO());
                Assert::AreEqual(192.0f / 255.0f, col[0], L"Fourth intensity r", LINE_INFO());
                Assert::AreEqual(192.0f / 255.0f, col[1], L"Fourth intensity g", LINE_INFO());
                Assert::AreEqual(192.0f / 255.0f, col[2], L"Fourth intensity b", LINE_INFO());
            }
        }

        TEST_METHOD(TestStaticReadXyzFloatIntFloatAsXyzFloatRgb32) {
            ::SetMmpldWorkingDirectory();   // Need to have access to the test files.

            typedef mmpld::particle_traits<mmpld::vertex_type::float_xyz, mmpld::colour_type::rgb32> traits_type;
            auto particles = this->testStaticReadAs<traits_type, FILE *>("test_xyz_float_rgb_float.mmpld");

            {
                auto pos = traits_type::position(particles.data() + 0 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 0 * traits_type::stride());
                Assert::AreEqual(0.0f, pos[0], L"First position x", LINE_INFO());
                Assert::AreEqual(0.0f, pos[1], L"First position y", LINE_INFO());
                Assert::AreEqual(0.0f, pos[2], L"First position z", LINE_INFO());
                Assert::AreEqual(1.0f, col[0], L"First intensity r", LINE_INFO());
                Assert::AreEqual(1.0f, col[1], L"First intensity g", LINE_INFO());
                Assert::AreEqual(1.0f, col[2], L"First intensity b", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 1 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 1 * traits_type::stride());
                Assert::AreEqual(1.0f, pos[0], L"Second position x", LINE_INFO());
                Assert::AreEqual(0.0f, pos[1], L"Second position y", LINE_INFO());
                Assert::AreEqual(0.0f, pos[2], L"Second position z", LINE_INFO());
                Assert::AreEqual(1.0f, col[0], L"Second intensity r", LINE_INFO());
                Assert::AreEqual(0.0f, col[1], L"Second intensity g", LINE_INFO());
                Assert::AreEqual(0.0f, col[2], L"Second intensity b", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 2 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 2 * traits_type::stride());
                Assert::AreEqual(0.0f, pos[0], L"Third position x", LINE_INFO());
                Assert::AreEqual(1.0f, pos[1], L"Third position y", LINE_INFO());
                Assert::AreEqual(0.0f, pos[2], L"Third position z", LINE_INFO());
                Assert::AreEqual(0.0f, col[0], L"Third intensity r", LINE_INFO());
                Assert::AreEqual(1.0f, col[1], L"Third intensity g", LINE_INFO());
                Assert::AreEqual(0.0f, col[2], L"Third intensity b", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 3 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 3 * traits_type::stride());
                Assert::AreEqual(0.0f, pos[0], L"Fourth position x", LINE_INFO());
                Assert::AreEqual(0.0f, pos[1], L"Fourth position y", LINE_INFO());
                Assert::AreEqual(1.0f, pos[2], L"Fourth position z", LINE_INFO());
                Assert::AreEqual(0.0f, col[0], L"Fourth intensity r", LINE_INFO());
                Assert::AreEqual(0.0f, col[1], L"Fourth intensity g", LINE_INFO());
                Assert::AreEqual(1.0f, col[2], L"Fourth intensity b", LINE_INFO());
            }
        }

        TEST_METHOD(TestStaticReadXyzFloatRgbFloatAsXyzShortRgb32) {
            ::SetMmpldWorkingDirectory();   // Need to have access to the test files.

            typedef mmpld::particle_traits<mmpld::vertex_type::short_xyz, mmpld::colour_type::rgba32> traits_type;
            auto particles = this->testStaticReadAs<traits_type, HANDLE>("test_xyz_float_rgb_float.mmpld");

            {
                auto pos = traits_type::position(particles.data() + 0 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 0 * traits_type::stride());
                Assert::AreEqual(std::int16_t(0), pos[0], L"First position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[1], L"First position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[2], L"First position z", LINE_INFO());
                Assert::AreEqual(1.0f, col[0], L"First intensity r", LINE_INFO());
                Assert::AreEqual(1.0f, col[1], L"First intensity g", LINE_INFO());
                Assert::AreEqual(1.0f, col[2], L"First intensity b", LINE_INFO());
                Assert::AreEqual(1.0f, col[3], L"First intensity a", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 1 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 1 * traits_type::stride());
                Assert::AreEqual(std::int16_t(1), pos[0], L"Second position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[1], L"Second position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[2], L"Second position z", LINE_INFO());
                Assert::AreEqual(1.0f, col[0], L"Second intensity r", LINE_INFO());
                Assert::AreEqual(0.0f, col[1], L"Second intensity g", LINE_INFO());
                Assert::AreEqual(0.0f, col[2], L"Second intensity b", LINE_INFO());
                Assert::AreEqual(1.0f, col[3], L"Second intensity a", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 2 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 2 * traits_type::stride());
                Assert::AreEqual(std::int16_t(0), pos[0], L"Third position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(1), pos[1], L"Third position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[2], L"Third position z", LINE_INFO());
                Assert::AreEqual(0.0f, col[0], L"Third intensity r", LINE_INFO());
                Assert::AreEqual(1.0f, col[1], L"Third intensity g", LINE_INFO());
                Assert::AreEqual(0.0f, col[2], L"Third intensity b", LINE_INFO());
                Assert::AreEqual(1.0f, col[3], L"Third intensity a", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 3 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 3 * traits_type::stride());
                Assert::AreEqual(std::int16_t(0), pos[0], L"Fourth position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[1], L"Fourth position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(1), pos[2], L"Fourth position z", LINE_INFO());
                Assert::AreEqual(0.0f, col[0], L"Fourth intensity r", LINE_INFO());
                Assert::AreEqual(0.0f, col[1], L"Fourth intensity g", LINE_INFO());
                Assert::AreEqual(1.0f, col[2], L"Fourth intensity b", LINE_INFO());
                Assert::AreEqual(1.0f, col[3], L"Fourth intensity a", LINE_INFO());
            }
        }

        TEST_METHOD(TestStaticReadXyzFloatRgbFloatAsXyzShortRgba8) {
            ::SetMmpldWorkingDirectory();   // Need to have access to the test files.

            typedef mmpld::particle_traits<mmpld::vertex_type::short_xyz, mmpld::colour_type::rgba8> traits_type;
            auto particles = this->testStaticReadAs<traits_type, HANDLE>("test_xyz_float_rgb_float.mmpld");

            {
                auto pos = traits_type::position(particles.data() + 0 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 0 * traits_type::stride());
                Assert::AreEqual(std::int16_t(0), pos[0], L"First position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[1], L"First position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[2], L"First position z", LINE_INFO());
                Assert::AreEqual(std::uint8_t(255), col[0], L"First intensity r", LINE_INFO());
                Assert::AreEqual(std::uint8_t(255), col[1], L"First intensity g", LINE_INFO());
                Assert::AreEqual(std::uint8_t(255), col[2], L"First intensity b", LINE_INFO());
                Assert::AreEqual(std::uint8_t(255), col[3], L"First intensity a", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 1 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 1 * traits_type::stride());
                Assert::AreEqual(std::int16_t(1), pos[0], L"Second position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[1], L"Second position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[2], L"Second position z", LINE_INFO());
                Assert::AreEqual(std::uint8_t(255), col[0], L"Second intensity r", LINE_INFO());
                Assert::AreEqual(std::uint8_t(0), col[1], L"Second intensity g", LINE_INFO());
                Assert::AreEqual(std::uint8_t(0), col[2], L"Second intensity b", LINE_INFO());
                Assert::AreEqual(std::uint8_t(255), col[3], L"Second intensity a", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 2 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 2 * traits_type::stride());
                Assert::AreEqual(std::int16_t(0), pos[0], L"Third position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(1), pos[1], L"Third position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[2], L"Third position z", LINE_INFO());
                Assert::AreEqual(std::uint8_t(0), col[0], L"Third intensity r", LINE_INFO());
                Assert::AreEqual(std::uint8_t(255), col[1], L"Third intensity g", LINE_INFO());
                Assert::AreEqual(std::uint8_t(0), col[2], L"Third intensity b", LINE_INFO());
                Assert::AreEqual(std::uint8_t(255), col[3], L"Third intensity a", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 3 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 3 * traits_type::stride());
                Assert::AreEqual(std::int16_t(0), pos[0], L"Fourth position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[1], L"Fourth position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(1), pos[2], L"Fourth position z", LINE_INFO());
                Assert::AreEqual(std::uint8_t(0), col[0], L"Fourth intensity r", LINE_INFO());
                Assert::AreEqual(std::uint8_t(0), col[1], L"Fourth intensity g", LINE_INFO());
                Assert::AreEqual(std::uint8_t(255), col[2], L"Fourth intensity b", LINE_INFO());
                Assert::AreEqual(std::uint8_t(255), col[3], L"Fourth intensity a", LINE_INFO());
            }
        }

        TEST_METHOD(TestRuntimeReadXyzFloatIntFloatAsXyzFloatIntFloat) {
            ::SetMmpldWorkingDirectory();   // Need to have access to the test files.

            typedef mmpld::particle_traits<mmpld::vertex_type::float_xyz, mmpld::colour_type::intensity> traits_type;
            mmpld::list_header dst_header;
            dst_header.vertex_type = traits_type::vertex_type();
            dst_header.colour_type = traits_type::colour_type();

            auto particles = this->testRuntimeReadAs<std::ifstream>("test_xyz_float_int_float.mmpld", dst_header);

            {
                auto pos = traits_type::position(particles.data() + 0 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 0 * traits_type::stride());
                Assert::AreEqual(0.0f, pos[0], L"First position x", LINE_INFO());
                Assert::AreEqual(0.0f, pos[1], L"First position y", LINE_INFO());
                Assert::AreEqual(0.0f, pos[2], L"First position z", LINE_INFO());
                Assert::AreEqual(255.0f, col[0], L"First intensity", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 1 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 1 * traits_type::stride());
                Assert::AreEqual(1.0f, pos[0], L"Second position x", LINE_INFO());
                Assert::AreEqual(0.0f, pos[1], L"Second position y", LINE_INFO());
                Assert::AreEqual(0.0f, pos[2], L"Second position z", LINE_INFO());
                Assert::AreEqual(64.0f, col[0], L"Second intensity", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 2 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 2 * traits_type::stride());
                Assert::AreEqual(0.0f, pos[0], L"Third position x", LINE_INFO());
                Assert::AreEqual(1.0f, pos[1], L"Third position y", LINE_INFO());
                Assert::AreEqual(0.0f, pos[2], L"Third position z", LINE_INFO());
                Assert::AreEqual(128.0f, col[0], L"Third intensity", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 3 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 3 * traits_type::stride());
                Assert::AreEqual(0.0f, pos[0], L"Fourth position x", LINE_INFO());
                Assert::AreEqual(0.0f, pos[1], L"Fourth position y", LINE_INFO());
                Assert::AreEqual(1.0f, pos[2], L"Fourth position z", LINE_INFO());
                Assert::AreEqual(192.0f, col[0], L"Fourth intensity", LINE_INFO());
            }
        }

        TEST_METHOD(TestReadXyzFloatIntFloatAsXyzShortIntFloat) {
            ::SetMmpldWorkingDirectory();   // Need to have access to the test files.

            typedef mmpld::particle_traits<mmpld::vertex_type::short_xyz, mmpld::colour_type::intensity> traits_type;
            mmpld::list_header dst_header;
            dst_header.vertex_type = traits_type::vertex_type();
            dst_header.colour_type = traits_type::colour_type();

            auto particles = this->testRuntimeReadAs<HANDLE>("test_xyz_float_int_float.mmpld", dst_header);

            {
                auto pos = traits_type::position(particles.data() + 0 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 0 * traits_type::stride());
                Assert::AreEqual(std::int16_t(0), pos[0], L"First position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[1], L"First position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[2], L"First position z", LINE_INFO());
                Assert::AreEqual(255.0f, col[0], L"First intensity", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 1 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 1 * traits_type::stride());
                Assert::AreEqual(std::int16_t(1), pos[0], L"Second position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[1], L"Second position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[2], L"Second position z", LINE_INFO());
                Assert::AreEqual(64.0f, col[0], L"Second intensity", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 2 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 2 * traits_type::stride());
                Assert::AreEqual(std::int16_t(0), pos[0], L"Third position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(1), pos[1], L"Third position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[2], L"Third position z", LINE_INFO());
                Assert::AreEqual(128.0f, col[0], L"Third intensity", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 3 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 3 * traits_type::stride());
                Assert::AreEqual(std::int16_t(0), pos[0], L"Fourth position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[1], L"Fourth position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(1), pos[2], L"Fourth position z", LINE_INFO());
                Assert::AreEqual(192.0f, col[0], L"Fourth intensity", LINE_INFO());
            }
        }

        TEST_METHOD(TestReadXyzFloatIntFloatAsXyzFloatIntFloat) {
            ::SetMmpldWorkingDirectory();   // Need to have access to the test files.

            typedef mmpld::particle_traits<mmpld::vertex_type::float_xyz, mmpld::colour_type::intensity> traits_type;
            auto particles = this->testStaticReadAs<traits_type, std::ifstream>("test_xyz_float_int_float.mmpld", 1);

            {
                auto pos = traits_type::position(particles.data() + 0 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 0 * traits_type::stride());
                Assert::AreEqual(0.0f, pos[0], L"First position x", LINE_INFO());
                Assert::AreEqual(0.0f, pos[1], L"First position y", LINE_INFO());
                Assert::AreEqual(0.0f, pos[2], L"First position z", LINE_INFO());
                Assert::AreEqual(255.0f, col[0], L"First intensity", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 1 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 1 * traits_type::stride());
                Assert::AreEqual(1.0f, pos[0], L"Second position x", LINE_INFO());
                Assert::AreEqual(0.0f, pos[1], L"Second position y", LINE_INFO());
                Assert::AreEqual(0.0f, pos[2], L"Second position z", LINE_INFO());
                Assert::AreEqual(64.0f, col[0], L"Second intensity", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 2 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 2 * traits_type::stride());
                Assert::AreEqual(0.0f, pos[0], L"Third position x", LINE_INFO());
                Assert::AreEqual(1.0f, pos[1], L"Third position y", LINE_INFO());
                Assert::AreEqual(0.0f, pos[2], L"Third position z", LINE_INFO());
                Assert::AreEqual(128.0f, col[0], L"Third intensity", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 3 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 3 * traits_type::stride());
                Assert::AreEqual(0.0f, pos[0], L"Fourth position x", LINE_INFO());
                Assert::AreEqual(0.0f, pos[1], L"Fourth position y", LINE_INFO());
                Assert::AreEqual(1.0f, pos[2], L"Fourth position z", LINE_INFO());
                Assert::AreEqual(192.0f, col[0], L"Fourth intensity", LINE_INFO());
            }
        }

        TEST_METHOD(TestStaticReadXyzFloatIntFloatAsXyzShortIntFloatBuffer1) {
            ::SetMmpldWorkingDirectory();   // Need to have access to the test files.

            typedef mmpld::particle_traits<mmpld::vertex_type::short_xyz, mmpld::colour_type::intensity> traits_type;
            auto particles = this->testStaticReadAs<traits_type, std::ifstream>("test_xyz_float_int_float.mmpld", 1);

            {
                auto pos = traits_type::position(particles.data() + 0 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 0 * traits_type::stride());
                Assert::AreEqual(std::int16_t(0), pos[0], L"First position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[1], L"First position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[2], L"First position z", LINE_INFO());
                Assert::AreEqual(255.0f, col[0], L"First intensity", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 1 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 1 * traits_type::stride());
                Assert::AreEqual(std::int16_t(1), pos[0], L"Second position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[1], L"Second position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[2], L"Second position z", LINE_INFO());
                Assert::AreEqual(64.0f, col[0], L"Second intensity", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 2 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 2 * traits_type::stride());
                Assert::AreEqual(std::int16_t(0), pos[0], L"Third position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(1), pos[1], L"Third position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[2], L"Third position z", LINE_INFO());
                Assert::AreEqual(128.0f, col[0], L"Third intensity", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 3 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 3 * traits_type::stride());
                Assert::AreEqual(std::int16_t(0), pos[0], L"Fourth position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[1], L"Fourth position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(1), pos[2], L"Fourth position z", LINE_INFO());
                Assert::AreEqual(192.0f, col[0], L"Fourth intensity", LINE_INFO());
            }
        }

        TEST_METHOD(TestStaticReadXyzFloatIntFloatAsXyzShortIntFloatBuffer2) {
            ::SetMmpldWorkingDirectory();   // Need to have access to the test files.

            typedef mmpld::particle_traits<mmpld::vertex_type::short_xyz, mmpld::colour_type::intensity> traits_type;
            auto particles = this->testStaticReadAs<traits_type, std::ifstream>("test_xyz_float_int_float.mmpld", 2);

            {
                auto pos = traits_type::position(particles.data() + 0 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 0 * traits_type::stride());
                Assert::AreEqual(std::int16_t(0), pos[0], L"First position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[1], L"First position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[2], L"First position z", LINE_INFO());
                Assert::AreEqual(255.0f, col[0], L"First intensity", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 1 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 1 * traits_type::stride());
                Assert::AreEqual(std::int16_t(1), pos[0], L"Second position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[1], L"Second position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[2], L"Second position z", LINE_INFO());
                Assert::AreEqual(64.0f, col[0], L"Second intensity", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 2 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 2 * traits_type::stride());
                Assert::AreEqual(std::int16_t(0), pos[0], L"Third position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(1), pos[1], L"Third position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[2], L"Third position z", LINE_INFO());
                Assert::AreEqual(128.0f, col[0], L"Third intensity", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 3 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 3 * traits_type::stride());
                Assert::AreEqual(std::int16_t(0), pos[0], L"Fourth position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[1], L"Fourth position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(1), pos[2], L"Fourth position z", LINE_INFO());
                Assert::AreEqual(192.0f, col[0], L"Fourth intensity", LINE_INFO());
            }
        }


        TEST_METHOD(TestStaticReadXyzFloatIntFloatAsXyzShortIntFloatBuffer3) {
            ::SetMmpldWorkingDirectory();   // Need to have access to the test files.

            typedef mmpld::particle_traits<mmpld::vertex_type::short_xyz, mmpld::colour_type::intensity> traits_type;
            auto particles = this->testStaticReadAs<traits_type, std::ifstream>("test_xyz_float_int_float.mmpld", 3);

            {
                auto pos = traits_type::position(particles.data() + 0 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 0 * traits_type::stride());
                Assert::AreEqual(std::int16_t(0), pos[0], L"First position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[1], L"First position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[2], L"First position z", LINE_INFO());
                Assert::AreEqual(255.0f, col[0], L"First intensity", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 1 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 1 * traits_type::stride());
                Assert::AreEqual(std::int16_t(1), pos[0], L"Second position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[1], L"Second position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[2], L"Second position z", LINE_INFO());
                Assert::AreEqual(64.0f, col[0], L"Second intensity", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 2 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 2 * traits_type::stride());
                Assert::AreEqual(std::int16_t(0), pos[0], L"Third position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(1), pos[1], L"Third position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[2], L"Third position z", LINE_INFO());
                Assert::AreEqual(128.0f, col[0], L"Third intensity", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 3 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 3 * traits_type::stride());
                Assert::AreEqual(std::int16_t(0), pos[0], L"Fourth position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[1], L"Fourth position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(1), pos[2], L"Fourth position z", LINE_INFO());
                Assert::AreEqual(192.0f, col[0], L"Fourth intensity", LINE_INFO());
            }
        }

        TEST_METHOD(TestStaticReadXyzFloatIntFloatAsXyzShortIntFloatBuffer4) {
            ::SetMmpldWorkingDirectory();   // Need to have access to the test files.

            typedef mmpld::particle_traits<mmpld::vertex_type::short_xyz, mmpld::colour_type::intensity> traits_type;
            auto particles = this->testStaticReadAs<traits_type, std::ifstream>("test_xyz_float_int_float.mmpld", 4);

            {
                auto pos = traits_type::position(particles.data() + 0 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 0 * traits_type::stride());
                Assert::AreEqual(std::int16_t(0), pos[0], L"First position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[1], L"First position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[2], L"First position z", LINE_INFO());
                Assert::AreEqual(255.0f, col[0], L"First intensity", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 1 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 1 * traits_type::stride());
                Assert::AreEqual(std::int16_t(1), pos[0], L"Second position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[1], L"Second position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[2], L"Second position z", LINE_INFO());
                Assert::AreEqual(64.0f, col[0], L"Second intensity", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 2 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 2 * traits_type::stride());
                Assert::AreEqual(std::int16_t(0), pos[0], L"Third position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(1), pos[1], L"Third position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[2], L"Third position z", LINE_INFO());
                Assert::AreEqual(128.0f, col[0], L"Third intensity", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 3 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 3 * traits_type::stride());
                Assert::AreEqual(std::int16_t(0), pos[0], L"Fourth position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[1], L"Fourth position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(1), pos[2], L"Fourth position z", LINE_INFO());
                Assert::AreEqual(192.0f, col[0], L"Fourth intensity", LINE_INFO());
            }
        }

        TEST_METHOD(TestStaticReadXyzFloatIntFloatAsXyzShortIntFloatBuffer5) {
            ::SetMmpldWorkingDirectory();   // Need to have access to the test files.

            typedef mmpld::particle_traits<mmpld::vertex_type::short_xyz, mmpld::colour_type::intensity> traits_type;
            auto particles = this->testStaticReadAs<traits_type, std::ifstream>("test_xyz_float_int_float.mmpld", 5);

            {
                auto pos = traits_type::position(particles.data() + 0 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 0 * traits_type::stride());
                Assert::AreEqual(std::int16_t(0), pos[0], L"First position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[1], L"First position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[2], L"First position z", LINE_INFO());
                Assert::AreEqual(255.0f, col[0], L"First intensity", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 1 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 1 * traits_type::stride());
                Assert::AreEqual(std::int16_t(1), pos[0], L"Second position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[1], L"Second position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[2], L"Second position z", LINE_INFO());
                Assert::AreEqual(64.0f, col[0], L"Second intensity", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 2 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 2 * traits_type::stride());
                Assert::AreEqual(std::int16_t(0), pos[0], L"Third position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(1), pos[1], L"Third position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[2], L"Third position z", LINE_INFO());
                Assert::AreEqual(128.0f, col[0], L"Third intensity", LINE_INFO());
            }

            {
                auto pos = traits_type::position(particles.data() + 3 * traits_type::stride());
                auto col = traits_type::colour(particles.data() + 3 * traits_type::stride());
                Assert::AreEqual(std::int16_t(0), pos[0], L"Fourth position x", LINE_INFO());
                Assert::AreEqual(std::int16_t(0), pos[1], L"Fourth position y", LINE_INFO());
                Assert::AreEqual(std::int16_t(1), pos[2], L"Fourth position z", LINE_INFO());
                Assert::AreEqual(192.0f, col[0], L"Fourth intensity", LINE_INFO());
            }
        }

        TEST_METHOD(TestFullReadFrameAs) {
            ::SetMmpldWorkingDirectory();   // Need to have access to the test files.

            mmpld::file_header fileHeader;
            mmpld::frame_header frameHeader;
            mmpld::list_header listHeader;
            mmpld::seek_table seekTable;

            // Open the file with your preferred API, in this case WIN32.
            auto hFile = ::CreateFileW(L"test_xyz_double_int_double.mmpld",
                GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING,
                FILE_ATTRIBUTE_READONLY, NULL);
            Assert::IsTrue(hFile != INVALID_HANDLE_VALUE, L"File open", LINE_INFO());

            mmpld::read_file_header(hFile, fileHeader, seekTable);
            Assert::AreNotEqual(int(mmpld::make_version(1, 1)), int(fileHeader.version), L"MMPLD version is not 1.1.", LINE_INFO());
            Assert::AreEqual(std::uint32_t(1), fileHeader.frames, L"Number of expected frames matches.", LINE_INFO());

            {
                LARGE_INTEGER offset;
                offset.QuadPart = seekTable[0];
                Assert::IsTrue(::SetFilePointerEx(hFile, offset, nullptr, FILE_BEGIN), L"Seek to frame", LINE_INFO());
            }

            mmpld::read_frame_header(hFile, fileHeader.version, frameHeader);
            Assert::AreEqual(std::int32_t(4), frameHeader.lists, L"Frame #1 holds four particle lists.", LINE_INFO());

            {
                listHeader.particles = mmpld::count<std::uint64_t>(frameHeader, fileHeader.version, hFile);
                Assert::AreEqual(std::uint64_t(4 + 5 + 5 + 5), listHeader.particles, L"Total number of particles", LINE_INFO());
            }

            listHeader.vertex_type = mmpld::vertex_type::float_xyzr;
            listHeader.colour_type = mmpld::colour_type::intensity32;
            std::vector<std::uint8_t> particles(std::size_t(listHeader.particles) * mmpld::get_stride<std::size_t>(listHeader));

            {
                auto cnt = mmpld::read_as(hFile, frameHeader, fileHeader.version, particles.data(), listHeader);
                Assert::AreEqual(std::uint64_t(4 + 5 + 5 + 5), cnt, L"All particles converted", LINE_INFO());
                Assert::AreEqual(std::uint64_t(4 + 5 + 5 + 5), listHeader.particles, L"List header updated", LINE_INFO());
            }

            {
                mmpld::particle_view<float> view(listHeader, reinterpret_cast<float *>(particles.data()));
                Assert::AreEqual(0.0f, view.position()[0], 0.0001f, L"p0.x", LINE_INFO());
                Assert::AreEqual(0.0f, view.position()[1], 0.0001f, L"p0.y", LINE_INFO());
                Assert::AreEqual(0.0f, view.position()[2], 0.0001f, L"p0.z", LINE_INFO());
                Assert::AreEqual(0.1f, view.position()[3], 0.0001f, L"p0.r", LINE_INFO());
                Assert::AreEqual(255.0f, view.colour()[0], 0.0001f, L"p0.i", LINE_INFO());

                view.advance();
                Assert::AreEqual(1.0f, view.position()[0], 0.0001f, L"p1.x", LINE_INFO());
                Assert::AreEqual(0.0f, view.position()[1], 0.0001f, L"p1.y", LINE_INFO());
                Assert::AreEqual(0.0f, view.position()[2], 0.0001f, L"p1.z", LINE_INFO());
                Assert::AreEqual(0.1f, view.position()[3], 0.0001f, L"p1.r", LINE_INFO());
                Assert::AreEqual(64.0f, view.colour()[0], 0.0001f, L"p1.i", LINE_INFO());

                view.advance();
                Assert::AreEqual(0.0f, view.position()[0], 0.0001f, L"p2.x", LINE_INFO());
                Assert::AreEqual(1.0f, view.position()[1], 0.0001f, L"p2.y", LINE_INFO());
                Assert::AreEqual(0.0f, view.position()[2], 0.0001f, L"p2.z", LINE_INFO());
                Assert::AreEqual(0.1f, view.position()[3], 0.0001f, L"p2.r", LINE_INFO());
                Assert::AreEqual(128.0f, view.colour()[0], 0.0001f, L"p2.i", LINE_INFO());

                view.advance();
                Assert::AreEqual(0.0f, view.position()[0], 0.0001f, L"p3.x", LINE_INFO());
                Assert::AreEqual(0.0f, view.position()[1], 0.0001f, L"p3.y", LINE_INFO());
                Assert::AreEqual(1.0f, view.position()[2], 0.0001f, L"p3.z", LINE_INFO());
                Assert::AreEqual(0.1f, view.position()[3], 0.0001f, L"p3.r", LINE_INFO());
                Assert::AreEqual(192.0f, view.colour()[0], 0.0001f, L"p3.i", LINE_INFO());

                view.advance();
                Assert::AreEqual(2.0f, view.position()[0], 0.0001f, L"p4.x", LINE_INFO());
                Assert::AreEqual(-2.0f, view.position()[1], 0.0001f, L"p4.y", LINE_INFO());
                Assert::AreEqual(-2.0f, view.position()[2], 0.0001f, L"p4.z", LINE_INFO());
                Assert::AreEqual(0.1f, view.position()[3], 0.0001f, L"p4.r", LINE_INFO());
                // 0.21r + 0.72g + 0.07b
                Assert::AreEqual(0.21f, view.colour()[0], 0.0001f, L"p4.i", LINE_INFO());

                view.advance();
                Assert::AreEqual(1.8f, view.position()[0], 0.0001f, L"p5.x", LINE_INFO());
                Assert::AreEqual(-2.0f, view.position()[1], 0.0001f, L"p5.y", LINE_INFO());
                Assert::AreEqual(-2.0f, view.position()[2], 0.0001f, L"p5.z", LINE_INFO());
                Assert::AreEqual(0.1f, view.position()[3], 0.0001f, L"p5.r", LINE_INFO());
                Assert::AreEqual(0.21f, view.colour()[0], 0.0001f, L"p5.i", LINE_INFO());

                view.advance();
                Assert::AreEqual(1.6f, view.position()[0], 0.0001f, L"p6.x", LINE_INFO());
                Assert::AreEqual(-2.0f, view.position()[1], 0.0001f, L"p6.y", LINE_INFO());
                Assert::AreEqual(-2.0f, view.position()[2], 0.0001f, L"p6.z", LINE_INFO());
                Assert::AreEqual(0.1f, view.position()[3], 0.0001f, L"p6.r", LINE_INFO());
                Assert::AreEqual(0.21f, view.colour()[0], 0.0001f, L"p6.i", LINE_INFO());

                view.advance();
                Assert::AreEqual(1.4f, view.position()[0], 0.0001f, L"p7.x", LINE_INFO());
                Assert::AreEqual(-2.0f, view.position()[1], 0.0001f, L"p7.y", LINE_INFO());
                Assert::AreEqual(-2.0f, view.position()[2], 0.0001f, L"p7.z", LINE_INFO());
                Assert::AreEqual(0.1f, view.position()[3], 0.0001f, L"p7.r", LINE_INFO());
                Assert::AreEqual(0.21f, view.colour()[0], 0.0001f, L"p7.i", LINE_INFO());

                view.advance();
                Assert::AreEqual(1.2f, view.position()[0], 0.0001f, L"p8.x", LINE_INFO());
                Assert::AreEqual(-2.0f, view.position()[1], 0.0001f, L"p8.y", LINE_INFO());
                Assert::AreEqual(-2.0f, view.position()[2], 0.0001f, L"p8.z", LINE_INFO());
                Assert::AreEqual(0.1f, view.position()[3], 0.0001f, L"p8.r", LINE_INFO());
                Assert::AreEqual(0.21f, view.colour()[0], 0.0001f, L"p8.i", LINE_INFO());

                view.advance();
                Assert::AreEqual(-2.0f, view.position()[0], 0.0001f, L"p9.x", LINE_INFO());
                Assert::AreEqual(2.0f, view.position()[1], 0.0001f, L"p9.y", LINE_INFO());
                Assert::AreEqual(-2.0f, view.position()[2], 0.0001f, L"p9.z", LINE_INFO());
                Assert::AreEqual(0.1f, view.position()[3], 0.0001f, L"p9.r", LINE_INFO());
                // 0.21r + 0.72g + 0.07b
                Assert::AreEqual(0.72f, view.colour()[0], 0.0001f, L"p9.i", LINE_INFO());

                view.advance();
                Assert::AreEqual(-2.0f, view.position()[0], 0.0001f, L"p10.x", LINE_INFO());
                Assert::AreEqual(1.8f, view.position()[1], 0.0001f, L"p10.y", LINE_INFO());
                Assert::AreEqual(-2.0f, view.position()[2], 0.0001f, L"p10.z", LINE_INFO());
                Assert::AreEqual(0.1f, view.position()[3], 0.0001f, L"p10.r", LINE_INFO());
                Assert::AreEqual(0.72f, view.colour()[0], 0.0001f, L"p10.i", LINE_INFO());

                view.advance();
                Assert::AreEqual(-2.0f, view.position()[0], 0.0001f, L"p11.x", LINE_INFO());
                Assert::AreEqual(1.6f, view.position()[1], 0.0001f, L"p11.y", LINE_INFO());
                Assert::AreEqual(-2.0f, view.position()[2], 0.0001f, L"p11.z", LINE_INFO());
                Assert::AreEqual(0.1f, view.position()[3], 0.0001f, L"p11.r", LINE_INFO());
                Assert::AreEqual(0.72f, view.colour()[0], 0.0001f, L"p11.i", LINE_INFO());

                view.advance();
                Assert::AreEqual(-2.0f, view.position()[0], 0.0001f, L"p12.x", LINE_INFO());
                Assert::AreEqual(1.4f, view.position()[1], 0.0001f, L"p12.y", LINE_INFO());
                Assert::AreEqual(-2.0f, view.position()[2], 0.0001f, L"p12.z", LINE_INFO());
                Assert::AreEqual(0.1f, view.position()[3], 0.0001f, L"p12.r", LINE_INFO());
                Assert::AreEqual(0.72f, view.colour()[0], 0.0001f, L"p12.i", LINE_INFO());

                view.advance();
                Assert::AreEqual(-2.0f, view.position()[0], 0.0001f, L"p13.x", LINE_INFO());
                Assert::AreEqual(1.2f, view.position()[1], 0.0001f, L"p13.y", LINE_INFO());
                Assert::AreEqual(-2.0f, view.position()[2], 0.0001f, L"p13.z", LINE_INFO());
                Assert::AreEqual(0.1f, view.position()[3], 0.0001f, L"p13.r", LINE_INFO());
                Assert::AreEqual(0.72f, view.colour()[0], 0.0001f, L"p13.i", LINE_INFO());

                view.advance();
                Assert::AreEqual(-2.0f, view.position()[0], 0.0001f, L"p14.x", LINE_INFO());
                Assert::AreEqual(-2.0f, view.position()[1], 0.0001f, L"p14.y", LINE_INFO());
                Assert::AreEqual(2.0f, view.position()[2], 0.0001f, L"p14.z", LINE_INFO());
                Assert::AreEqual(0.1f, view.position()[3], 0.0001f, L"p14.r", LINE_INFO());
                // 0.21r + 0.72g + 0.07b
                Assert::AreEqual(0.07f, view.colour()[0], 0.0001f, L"p14.i", LINE_INFO());

                view.advance();
                Assert::AreEqual(-2.0f, view.position()[0], 0.0001f, L"p15.x", LINE_INFO());
                Assert::AreEqual(-2.0f, view.position()[1], 0.0001f, L"p15.y", LINE_INFO());
                Assert::AreEqual(1.8f, view.position()[2], 0.0001f, L"p15.z", LINE_INFO());
                Assert::AreEqual(0.1f, view.position()[3], 0.0001f, L"p15.r", LINE_INFO());
                Assert::AreEqual(0.07f, view.colour()[0], 0.0001f, L"p15.i", LINE_INFO());

                view.advance();
                Assert::AreEqual(-2.0f, view.position()[0], 0.0001f, L"p16.x", LINE_INFO());
                Assert::AreEqual(-2.0f, view.position()[1], 0.0001f, L"p16.y", LINE_INFO());
                Assert::AreEqual(1.6f, view.position()[2], 0.0001f, L"p16.z", LINE_INFO());
                Assert::AreEqual(0.1f, view.position()[3], 0.0001f, L"p16.r", LINE_INFO());
                Assert::AreEqual(0.07f, view.colour()[0], 0.0001f, L"p16.i", LINE_INFO());

                view.advance();
                Assert::AreEqual(-2.0f, view.position()[0], 0.0001f, L"p17.x", LINE_INFO());
                Assert::AreEqual(-2.0f, view.position()[1], 0.0001f, L"p17.y", LINE_INFO());
                Assert::AreEqual(1.4f, view.position()[2], 0.0001f, L"p17.z", LINE_INFO());
                Assert::AreEqual(0.1f, view.position()[3], 0.0001f, L"p17.r", LINE_INFO());
                Assert::AreEqual(0.07f, view.colour()[0], 0.0001f, L"p17.i", LINE_INFO());

                view.advance();
                Assert::AreEqual(-2.0f, view.position()[0], 0.0001f, L"p18.x", LINE_INFO());
                Assert::AreEqual(-2.0f, view.position()[1], 0.0001f, L"p18.y", LINE_INFO());
                Assert::AreEqual(1.2f, view.position()[2], 0.0001f, L"p18.z", LINE_INFO());
                Assert::AreEqual(0.1f, view.position()[3], 0.0001f, L"p18.r", LINE_INFO());
                Assert::AreEqual(0.07f, view.colour()[0], 0.0001f, L"p18.i", LINE_INFO());
            }

            // Note: we cannot check the bbox union here, because our test file is MMPLD 1.2

            Assert::AreEqual(0.0f, listHeader.min_intensity, L"minimum intensity", LINE_INFO());
            Assert::AreEqual(255.0f, listHeader.max_intensity, L"maximum intensity", LINE_INFO());
        }

        TEST_METHOD(TestBufferedReadFrameAs) {
            ::SetMmpldWorkingDirectory();   // Need to have access to the test files.

            mmpld::file_header fileHeader;
            mmpld::frame_header frameHeader;
            mmpld::list_header listHeader;
            mmpld::seek_table seekTable;

            // Open the file with your preferred API, in this case WIN32.
            auto hFile = ::CreateFileW(L"test_xyz_double_int_double.mmpld",
                GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING,
                FILE_ATTRIBUTE_READONLY, NULL);
            Assert::IsTrue(hFile != INVALID_HANDLE_VALUE, L"File open", LINE_INFO());

            mmpld::read_file_header(hFile, fileHeader, seekTable);
            Assert::AreNotEqual(int(mmpld::make_version(1, 1)), int(fileHeader.version), L"MMPLD version is not 1.1.", LINE_INFO());
            Assert::AreEqual(std::uint32_t(1), fileHeader.frames, L"Number of expected frames matches.", LINE_INFO());

            {
                LARGE_INTEGER offset;
                offset.QuadPart = seekTable[0];
                Assert::IsTrue(::SetFilePointerEx(hFile, offset, nullptr, FILE_BEGIN), L"Seek to frame", LINE_INFO());
            }

            mmpld::read_frame_header(hFile, fileHeader.version, frameHeader);
            Assert::AreEqual(std::int32_t(4), frameHeader.lists, L"Frame #1 holds four particle lists.", LINE_INFO());

            {
                listHeader.particles = mmpld::count<std::uint64_t>(frameHeader, fileHeader.version, hFile);
                Assert::AreEqual(std::uint64_t(4 + 5 + 5 + 5), listHeader.particles, L"Total number of particles", LINE_INFO());
            }

            listHeader.vertex_type = mmpld::vertex_type::float_xyz;
            listHeader.colour_type = mmpld::colour_type::rgb32;
            std::vector<std::uint8_t> particles(std::size_t(listHeader.particles) * mmpld::get_stride<std::size_t>(listHeader));

            {
                auto cnt = mmpld::read_as(hFile, frameHeader, fileHeader.version, particles.data(), listHeader, 2);
                Assert::AreEqual(std::uint64_t(4 + 5 + 5 + 5), cnt, L"All particles converted", LINE_INFO());
                Assert::AreEqual(std::uint64_t(4 + 5 + 5 + 5), listHeader.particles, L"List header updated", LINE_INFO());
            }

            {
                mmpld::particle_view<float> view(listHeader, reinterpret_cast<float *>(particles.data()));
                Assert::AreEqual(0.0f, view.position()[0], 0.0001f, L"p0.x", LINE_INFO());
                Assert::AreEqual(0.0f, view.position()[1], 0.0001f, L"p0.y", LINE_INFO());
                Assert::AreEqual(0.0f, view.position()[2], 0.0001f, L"p0.z", LINE_INFO());
                Assert::AreEqual(255.0f / 255.0f, view.colour()[0], 0.0001f, L"p0.r", LINE_INFO());
                Assert::AreEqual(255.0f / 255.0f, view.colour()[1], 0.0001f, L"p0.g", LINE_INFO());
                Assert::AreEqual(255.0f / 255.0f, view.colour()[2], 0.0001f, L"p0.b", LINE_INFO());

                view.advance();
                Assert::AreEqual(1.0f, view.position()[0], 0.0001f, L"p1.x", LINE_INFO());
                Assert::AreEqual(0.0f, view.position()[1], 0.0001f, L"p1.y", LINE_INFO());
                Assert::AreEqual(0.0f, view.position()[2], 0.0001f, L"p1.z", LINE_INFO());
                Assert::AreEqual(64.0f / 255.0f, view.colour()[0], 0.0001f, L"p1.r", LINE_INFO());
                Assert::AreEqual(64.0f / 255.0f, view.colour()[1], 0.0001f, L"p1.g", LINE_INFO());
                Assert::AreEqual(64.0f / 255.0f, view.colour()[2], 0.0001f, L"p1.b", LINE_INFO());

                view.advance();
                Assert::AreEqual(0.0f, view.position()[0], 0.0001f, L"p2.x", LINE_INFO());
                Assert::AreEqual(1.0f, view.position()[1], 0.0001f, L"p2.y", LINE_INFO());
                Assert::AreEqual(0.0f, view.position()[2], 0.0001f, L"p2.z", LINE_INFO());
                Assert::AreEqual(128.0f / 255.0f, view.colour()[0], 0.0001f, L"p2.r", LINE_INFO());
                Assert::AreEqual(128.0f / 255.0f, view.colour()[1], 0.0001f, L"p2.g", LINE_INFO());
                Assert::AreEqual(128.0f / 255.0f, view.colour()[2], 0.0001f, L"p2.b", LINE_INFO());

                view.advance();
                Assert::AreEqual(0.0f, view.position()[0], 0.0001f, L"p3.x", LINE_INFO());
                Assert::AreEqual(0.0f, view.position()[1], 0.0001f, L"p3.y", LINE_INFO());
                Assert::AreEqual(1.0f, view.position()[2], 0.0001f, L"p3.z", LINE_INFO());
                Assert::AreEqual(192.0f / 255.0f, view.colour()[0], 0.0001f, L"p3.r", LINE_INFO());
                Assert::AreEqual(192.0f / 255.0f, view.colour()[1], 0.0001f, L"p3.g", LINE_INFO());
                Assert::AreEqual(192.0f / 255.0f, view.colour()[2], 0.0001f, L"p3.b", LINE_INFO());

                view.advance();
                Assert::AreEqual(2.0f, view.position()[0], 0.0001f, L"p4.x", LINE_INFO());
                Assert::AreEqual(-2.0f, view.position()[1], 0.0001f, L"p4.y", LINE_INFO());
                Assert::AreEqual(-2.0f, view.position()[2], 0.0001f, L"p4.z", LINE_INFO());
                Assert::AreEqual(1.0f, view.colour()[0], 0.0001f, L"p4.r", LINE_INFO());
                Assert::AreEqual(0.0f, view.colour()[1], 0.0001f, L"p4.g", LINE_INFO());
                Assert::AreEqual(0.0f, view.colour()[2], 0.0001f, L"p4.b", LINE_INFO());

                view.advance();
                Assert::AreEqual(1.8f, view.position()[0], 0.0001f, L"p5.x", LINE_INFO());
                Assert::AreEqual(-2.0f, view.position()[1], 0.0001f, L"p5.y", LINE_INFO());
                Assert::AreEqual(-2.0f, view.position()[2], 0.0001f, L"p5.z", LINE_INFO());
                Assert::AreEqual(1.0f, view.colour()[0], 0.0001f, L"p5.r", LINE_INFO());
                Assert::AreEqual(0.0f, view.colour()[1], 0.0001f, L"p5.g", LINE_INFO());
                Assert::AreEqual(0.0f, view.colour()[2], 0.0001f, L"p5.b", LINE_INFO());

                view.advance();
                Assert::AreEqual(1.6f, view.position()[0], 0.0001f, L"p6.x", LINE_INFO());
                Assert::AreEqual(-2.0f, view.position()[1], 0.0001f, L"p6.y", LINE_INFO());
                Assert::AreEqual(-2.0f, view.position()[2], 0.0001f, L"p6.z", LINE_INFO());
                Assert::AreEqual(1.0f, view.colour()[0], 0.0001f, L"p6.r", LINE_INFO());
                Assert::AreEqual(0.0f, view.colour()[1], 0.0001f, L"p6.g", LINE_INFO());
                Assert::AreEqual(0.0f, view.colour()[2], 0.0001f, L"p6.b", LINE_INFO());

                view.advance();
                Assert::AreEqual(1.4f, view.position()[0], 0.0001f, L"p7.x", LINE_INFO());
                Assert::AreEqual(-2.0f, view.position()[1], 0.0001f, L"p7.y", LINE_INFO());
                Assert::AreEqual(-2.0f, view.position()[2], 0.0001f, L"p7.z", LINE_INFO());
                Assert::AreEqual(1.0f, view.colour()[0], 0.0001f, L"p7.r", LINE_INFO());
                Assert::AreEqual(0.0f, view.colour()[1], 0.0001f, L"p7.g", LINE_INFO());
                Assert::AreEqual(0.0f, view.colour()[2], 0.0001f, L"p7.b", LINE_INFO());

                view.advance();
                Assert::AreEqual(1.2f, view.position()[0], 0.0001f, L"p8.x", LINE_INFO());
                Assert::AreEqual(-2.0f, view.position()[1], 0.0001f, L"p8.y", LINE_INFO());
                Assert::AreEqual(-2.0f, view.position()[2], 0.0001f, L"p8.z", LINE_INFO());
                Assert::AreEqual(1.0f, view.colour()[0], 0.0001f, L"p8.r", LINE_INFO());
                Assert::AreEqual(0.0f, view.colour()[1], 0.0001f, L"p8.g", LINE_INFO());
                Assert::AreEqual(0.0f, view.colour()[2], 0.0001f, L"p8.b", LINE_INFO());

                view.advance();
                Assert::AreEqual(-2.0f, view.position()[0], 0.0001f, L"p9.x", LINE_INFO());
                Assert::AreEqual(2.0f, view.position()[1], 0.0001f, L"p9.y", LINE_INFO());
                Assert::AreEqual(-2.0f, view.position()[2], 0.0001f, L"p9.z", LINE_INFO());
                Assert::AreEqual(0.0f, view.colour()[0], 0.0001f, L"p9.r", LINE_INFO());
                Assert::AreEqual(1.0f, view.colour()[1], 0.0001f, L"p9.g", LINE_INFO());
                Assert::AreEqual(0.0f, view.colour()[2], 0.0001f, L"p9.b", LINE_INFO());

                view.advance();
                Assert::AreEqual(-2.0f, view.position()[0], 0.0001f, L"p10.x", LINE_INFO());
                Assert::AreEqual(1.8f, view.position()[1], 0.0001f, L"p10.y", LINE_INFO());
                Assert::AreEqual(-2.0f, view.position()[2], 0.0001f, L"p10.z", LINE_INFO());
                Assert::AreEqual(0.0f, view.colour()[0], 0.0001f, L"p10.r", LINE_INFO());
                Assert::AreEqual(1.0f, view.colour()[1], 0.0001f, L"p10.g", LINE_INFO());
                Assert::AreEqual(0.0f, view.colour()[2], 0.0001f, L"p10.b", LINE_INFO());

                view.advance();
                Assert::AreEqual(-2.0f, view.position()[0], 0.0001f, L"p11.x", LINE_INFO());
                Assert::AreEqual(1.6f, view.position()[1], 0.0001f, L"p11.y", LINE_INFO());
                Assert::AreEqual(-2.0f, view.position()[2], 0.0001f, L"p11.z", LINE_INFO());
                Assert::AreEqual(0.0f, view.colour()[0], 0.0001f, L"p11.r", LINE_INFO());
                Assert::AreEqual(1.0f, view.colour()[1], 0.0001f, L"p11.g", LINE_INFO());
                Assert::AreEqual(0.0f, view.colour()[2], 0.0001f, L"p11.b", LINE_INFO());

                view.advance();
                Assert::AreEqual(-2.0f, view.position()[0], 0.0001f, L"p12.x", LINE_INFO());
                Assert::AreEqual(1.4f, view.position()[1], 0.0001f, L"p12.y", LINE_INFO());
                Assert::AreEqual(-2.0f, view.position()[2], 0.0001f, L"p12.z", LINE_INFO());
                Assert::AreEqual(0.0f, view.colour()[0], 0.0001f, L"p12.r", LINE_INFO());
                Assert::AreEqual(1.0f, view.colour()[1], 0.0001f, L"p12.g", LINE_INFO());
                Assert::AreEqual(0.0f, view.colour()[2], 0.0001f, L"p12.b", LINE_INFO());

                view.advance();
                Assert::AreEqual(-2.0f, view.position()[0], 0.0001f, L"p13.x", LINE_INFO());
                Assert::AreEqual(1.2f, view.position()[1], 0.0001f, L"p13.y", LINE_INFO());
                Assert::AreEqual(-2.0f, view.position()[2], 0.0001f, L"p13.z", LINE_INFO());
                Assert::AreEqual(0.0f, view.colour()[0], 0.0001f, L"p13.r", LINE_INFO());
                Assert::AreEqual(1.0f, view.colour()[1], 0.0001f, L"p13.g", LINE_INFO());
                Assert::AreEqual(0.0f, view.colour()[2], 0.0001f, L"p13.b", LINE_INFO());

                view.advance();
                Assert::AreEqual(-2.0f, view.position()[0], 0.0001f, L"p14.x", LINE_INFO());
                Assert::AreEqual(-2.0f, view.position()[1], 0.0001f, L"p14.y", LINE_INFO());
                Assert::AreEqual(2.0f, view.position()[2], 0.0001f, L"p14.z", LINE_INFO());
                Assert::AreEqual(0.0f, view.colour()[0], 0.0001f, L"p14.r", LINE_INFO());
                Assert::AreEqual(0.0f, view.colour()[1], 0.0001f, L"p14.g", LINE_INFO());
                Assert::AreEqual(1.0f, view.colour()[2], 0.0001f, L"p14.b", LINE_INFO());

                view.advance();
                Assert::AreEqual(-2.0f, view.position()[0], 0.0001f, L"p15.x", LINE_INFO());
                Assert::AreEqual(-2.0f, view.position()[1], 0.0001f, L"p15.y", LINE_INFO());
                Assert::AreEqual(1.8f, view.position()[2], 0.0001f, L"p15.z", LINE_INFO());
                Assert::AreEqual(0.0f, view.colour()[0], 0.0001f, L"p15.r", LINE_INFO());
                Assert::AreEqual(0.0f, view.colour()[1], 0.0001f, L"p15.g", LINE_INFO());
                Assert::AreEqual(1.0f, view.colour()[2], 0.0001f, L"p15.b", LINE_INFO());

                view.advance();
                Assert::AreEqual(-2.0f, view.position()[0], 0.0001f, L"p16.x", LINE_INFO());
                Assert::AreEqual(-2.0f, view.position()[1], 0.0001f, L"p16.y", LINE_INFO());
                Assert::AreEqual(1.6f, view.position()[2], 0.0001f, L"p16.z", LINE_INFO());
                Assert::AreEqual(0.0f, view.colour()[0], 0.0001f, L"p16.r", LINE_INFO());
                Assert::AreEqual(0.0f, view.colour()[1], 0.0001f, L"p16.g", LINE_INFO());
                Assert::AreEqual(1.0f, view.colour()[2], 0.0001f, L"p16.b", LINE_INFO());

                view.advance();
                Assert::AreEqual(-2.0f, view.position()[0], 0.0001f, L"p17.x", LINE_INFO());
                Assert::AreEqual(-2.0f, view.position()[1], 0.0001f, L"p17.y", LINE_INFO());
                Assert::AreEqual(1.4f, view.position()[2], 0.0001f, L"p17.z", LINE_INFO());
                Assert::AreEqual(0.0f, view.colour()[0], 0.0001f, L"p17.r", LINE_INFO());
                Assert::AreEqual(0.0f, view.colour()[1], 0.0001f, L"p17.g", LINE_INFO());
                Assert::AreEqual(1.0f, view.colour()[2], 0.0001f, L"p17.b", LINE_INFO());

                view.advance();
                Assert::AreEqual(-2.0f, view.position()[0], 0.0001f, L"p18.x", LINE_INFO());
                Assert::AreEqual(-2.0f, view.position()[1], 0.0001f, L"p18.y", LINE_INFO());
                Assert::AreEqual(1.2f, view.position()[2], 0.0001f, L"p18.z", LINE_INFO());
                Assert::AreEqual(0.0f, view.colour()[0], 0.0001f, L"p18.r", LINE_INFO());
                Assert::AreEqual(0.0f, view.colour()[1], 0.0001f, L"p18.g", LINE_INFO());
                Assert::AreEqual(1.0f, view.colour()[2], 0.0001f, L"p18.b", LINE_INFO());
            }

            // Note: we cannot check the bbox union here, because our test file is MMPLD 1.2

            Assert::AreEqual(0.0f, listHeader.min_intensity, L"minimum intensity", LINE_INFO());
            Assert::AreEqual(255.0f, listHeader.max_intensity, L"maximum intensity", LINE_INFO());
        }

        TEST_METHOD(TestRuntimeConvertXyzFloatIntFloatToXyzFloatIntFloat) {
            typedef mmpld::particle_traits<mmpld::vertex_type::float_xyz, mmpld::colour_type::intensity> src_view;
            typedef src_view dst_view;
            std::vector<std::uint8_t> src(2 * src_view::stride());
            std::vector<std::uint8_t> dst(2 * dst_view::stride());
            mmpld::list_header src_header;
            src_header.particles = 2;
            src_header.vertex_type = src_view::vertex_traits::value;
            src_header.colour_type = src_view::colour_traits::colour_type;
            src_header.radius = 12.0f;
            src_header.colour[0] = 0.7f;
            src_header.colour[1] = 0.8f;
            src_header.colour[2] = 0.9f;
            src_header.colour[3] = 0.5f;

            src_view::position(src.data())[0] = 1.0f;
            src_view::position(src.data())[1] = 2.0f;
            src_view::position(src.data())[2] = 3.0f;
            *src_view::colour(src.data()) = 0.5f;

            src_view::position(src.data() + src_view::stride())[0] = 4.0f;
            src_view::position(src.data() + src_view::stride())[1] = 5.0f;
            src_view::position(src.data() + src_view::stride())[2] = 6.0f;
            *src_view::colour(src.data() + src_view::stride()) = 1.0f;

            auto dst_header = src_header;
            auto cnt = mmpld::convert(src.data(), src_header, dst.data(), src_header);
            Assert::AreEqual(std::uint64_t(2), cnt, L"All particles have been converted.", LINE_INFO());

            for (size_t i = 0, end = src.size(); i < end; ++i) {
                Assert::AreEqual(src[i], dst[i], L"Particle byte has been copied.", LINE_INFO());
            }
        }

        TEST_METHOD(TestRuntimeConvertXyzFloatIntFloatToXyzShortIntFloat) {
            typedef mmpld::particle_traits<mmpld::vertex_type::float_xyz, mmpld::colour_type::intensity> src_view;
            typedef mmpld::particle_traits<mmpld::vertex_type::short_xyz, mmpld::colour_type::intensity> dst_view;
            std::vector<std::uint8_t> src(2 * src_view::stride());
            std::vector<std::uint8_t> dst(2 * dst_view::stride());
            mmpld::list_header src_header;
            src_header.particles = 2;
            src_header.vertex_type = src_view::vertex_traits::value;
            src_header.colour_type = src_view::colour_traits::colour_type;
            src_header.radius = 12.0f;
            src_header.colour[0] = 0.7f;
            src_header.colour[1] = 0.8f;
            src_header.colour[2] = 0.9f;
            src_header.colour[3] = 0.5f;

            src_view::position(src.data())[0] = 1.0f;
            src_view::position(src.data())[1] = 2.0f;
            src_view::position(src.data())[2] = 3.0f;
            *src_view::colour(src.data()) = 0.5f;

            src_view::position(src.data() + src_view::stride())[0] = 4.0f;
            src_view::position(src.data() + src_view::stride())[1] = 5.0f;
            src_view::position(src.data() + src_view::stride())[2] = 6.0f;
            *src_view::colour(src.data() + src_view::stride()) = 1.0f;

            mmpld::list_header dst_header;
            dst_header.vertex_type = dst_view::vertex_type();
            dst_header.colour_type = dst_view::colour_type();
            dst_header.particles = src_header.particles;
            auto cnt = mmpld::convert(src.data(), src_header, dst.data(), dst_header);
            Assert::AreEqual(std::uint64_t(2), cnt, L"All particles have been converted.", LINE_INFO());

            Assert::AreEqual(dst_view::vertex_value_type(1), dst_view::position(dst.data())[0], L"P1: Conversion to short at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(2), dst_view::position(dst.data())[1], L"P1: Conversion to short at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(3), dst_view::position(dst.data())[2], L"P1: Conversion to short at [2]", LINE_INFO());
            Assert::AreEqual(*src_view::colour(src.data()), *dst_view::colour(dst.data()), L"P1: Unchanged intensity", LINE_INFO());

            Assert::AreEqual(dst_view::vertex_value_type(4), dst_view::position(dst.data() + dst_view::stride())[0], L"P2: Conversion to short at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(5), dst_view::position(dst.data() + dst_view::stride())[1], L"P2: Conversion to short at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(6), dst_view::position(dst.data() + dst_view::stride())[2], L"P2: Conversion to short at [2]", LINE_INFO());
            Assert::AreEqual(*src_view::colour(src.data() + src_view::stride()), *dst_view::colour(dst.data() + dst_view::stride()), L"P2: Unchanged intensity", LINE_INFO());
        }

        TEST_METHOD(TestRuntimeConvertXyzFloatIntFloatToXyzFloatNone) {
            typedef mmpld::particle_traits<mmpld::vertex_type::float_xyz, mmpld::colour_type::intensity> src_view;
            typedef mmpld::particle_traits<mmpld::vertex_type::float_xyzr, mmpld::colour_type::none> dst_view;
            std::vector<std::uint8_t> src(2 * src_view::stride());
            std::vector<std::uint8_t> dst(2 * dst_view::stride());
            mmpld::list_header src_header;
            src_header.particles = 2;
            src_header.vertex_type = src_view::vertex_traits::value;
            src_header.colour_type = src_view::colour_traits::colour_type;
            src_header.radius = 12.0f;
            src_header.colour[0] = 0.7f;
            src_header.colour[1] = 0.8f;
            src_header.colour[2] = 0.9f;
            src_header.colour[3] = 0.5f;

            src_view::position(src.data())[0] = 1.0f;
            src_view::position(src.data())[1] = 2.0f;
            src_view::position(src.data())[2] = 3.0f;
            *src_view::colour(src.data()) = 0.5f;

            src_view::position(src.data() + src_view::stride())[0] = 4.0f;
            src_view::position(src.data() + src_view::stride())[1] = 5.0f;
            src_view::position(src.data() + src_view::stride())[2] = 6.0f;
            *src_view::colour(src.data() + src_view::stride()) = 1.0f;

            mmpld::list_header dst_header;
            dst_header.vertex_type = dst_view::vertex_type();
            dst_header.colour_type = dst_view::colour_type();
            dst_header.particles = src_header.particles;
            auto cnt = mmpld::convert(src.data(), src_header, dst.data(), dst_header);
            Assert::AreEqual(std::uint64_t(2), cnt, L"All particles have been converted.", LINE_INFO());

            Assert::AreEqual(dst_view::vertex_value_type(1), dst_view::position(dst.data())[0], L"P1: Conversion to short at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(2), dst_view::position(dst.data())[1], L"P1: Conversion to short at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(3), dst_view::position(dst.data())[2], L"P1: Conversion to short at [2]", LINE_INFO());
            Assert::AreEqual(src_header.radius, *dst_view::radius(dst.data()), L"P1: Global radius has been converted.", LINE_INFO());

            Assert::AreEqual(dst_view::vertex_value_type(4), dst_view::position(dst.data() + dst_view::stride())[0], L"P2: Conversion to short at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(5), dst_view::position(dst.data() + dst_view::stride())[1], L"P2: Conversion to short at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(6), dst_view::position(dst.data() + dst_view::stride())[2], L"P2: Conversion to short at [2]", LINE_INFO());
            Assert::AreEqual(src_header.radius, *dst_view::radius(dst.data() + dst_view::stride()), L"P2: Global radius has been converted.", LINE_INFO());
        }

        TEST_METHOD(TestRuntimeConvertXyzFloatNoneToXyzrFloatRgba32) {
            typedef mmpld::particle_traits<mmpld::vertex_type::short_xyz, mmpld::colour_type::none> src_view;
            typedef mmpld::particle_traits<mmpld::vertex_type::float_xyzr, mmpld::colour_type::rgba32> dst_view;
            std::vector<std::uint8_t> src(2 * src_view::stride());
            std::vector<std::uint8_t> dst(2 * dst_view::stride());
            mmpld::list_header src_header;
            src_header.particles = 2;
            src_header.vertex_type = src_view::vertex_traits::value;
            src_header.colour_type = src_view::colour_traits::colour_type;
            src_header.radius = 12.0f;
            src_header.colour[0] = 0.7f;
            src_header.colour[1] = 0.8f;
            src_header.colour[2] = 0.9f;
            src_header.colour[3] = 0.5f;

            src_view::position(src.data())[0] = 1;
            src_view::position(src.data())[1] = 2;
            src_view::position(src.data())[2] = 3;

            src_view::position(src.data() + src_view::stride())[0] = 4;
            src_view::position(src.data() + src_view::stride())[1] = 5;
            src_view::position(src.data() + src_view::stride())[2] = 6;

            mmpld::list_header dst_header;
            dst_header.vertex_type = dst_view::vertex_type();
            dst_header.colour_type = dst_view::colour_type();
            dst_header.particles = src_header.particles;
            auto cnt = mmpld::convert(src.data(), src_header, dst.data(), dst_header);
            Assert::AreEqual(std::uint64_t(2), cnt, L"All particles have been converted.", LINE_INFO());

            Assert::AreEqual(dst_view::vertex_value_type(1), dst_view::position(dst.data())[0], L"P1: Conversion to float at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(2), dst_view::position(dst.data())[1], L"P1: Conversion to float at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(3), dst_view::position(dst.data())[2], L"P1: Conversion to float at [2]", LINE_INFO());
            Assert::AreEqual(src_header.radius, *dst_view::radius(dst.data()), L"P1: Global radius has been converted.", LINE_INFO());
            Assert::AreEqual(src_header.colour[0], dst_view::colour(dst.data())[0], L"P1: Global colour has been copied to [0]", LINE_INFO());
            Assert::AreEqual(src_header.colour[1], dst_view::colour(dst.data())[1], L"P1: Global colour has been copied to [1]", LINE_INFO());
            Assert::AreEqual(src_header.colour[2], dst_view::colour(dst.data())[2], L"P1: Global colour has been copied to [2]", LINE_INFO());
            Assert::AreEqual(src_header.colour[3], dst_view::colour(dst.data())[3], L"P1: Global colour has been copied to [3]", LINE_INFO());

            Assert::AreEqual(dst_view::vertex_value_type(4), dst_view::position(dst.data() + dst_view::stride())[0], L"P2: Conversion to float at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(5), dst_view::position(dst.data() + dst_view::stride())[1], L"P2: Conversion to float at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(6), dst_view::position(dst.data() + dst_view::stride())[2], L"P2: Conversion to float at [2]", LINE_INFO());
            Assert::AreEqual(src_header.radius, *dst_view::radius(dst.data() + dst_view::stride()), L"P2: Global radius has been converted.", LINE_INFO());
            Assert::AreEqual(src_header.colour[0], dst_view::colour(dst.data() + dst_view::stride())[0], L"P2: Global colour has been copied to [0]", LINE_INFO());
            Assert::AreEqual(src_header.colour[1], dst_view::colour(dst.data() + dst_view::stride())[1], L"P2: Global colour has been copied to [1]", LINE_INFO());
            Assert::AreEqual(src_header.colour[2], dst_view::colour(dst.data() + dst_view::stride())[2], L"P2: Global colour has been copied to [2]", LINE_INFO());
            Assert::AreEqual(src_header.colour[3], dst_view::colour(dst.data() + dst_view::stride())[3], L"P2: Global colour has been copied to [3]", LINE_INFO());
        }

        TEST_METHOD(TestRuntimeConvertXyzShortRgb8ToXyzrFloatRgba32) {
            typedef mmpld::particle_traits<mmpld::vertex_type::short_xyz, mmpld::colour_type::rgb8> src_view;
            typedef mmpld::particle_traits<mmpld::vertex_type::float_xyzr, mmpld::colour_type::rgba32> dst_view;
            std::vector<std::uint8_t> src(2 * src_view::stride());
            std::vector<std::uint8_t> dst(2 * dst_view::stride());
            mmpld::list_header src_header;
            src_header.particles = 2;
            src_header.vertex_type = src_view::vertex_traits::value;
            src_header.colour_type = src_view::colour_traits::colour_type;
            src_header.radius = 12.0f;
            src_header.colour[0] = 0.7f;
            src_header.colour[1] = 0.8f;
            src_header.colour[2] = 0.9f;
            src_header.colour[3] = 0.5f;

            src_view::position(src.data())[0] = 1;
            src_view::position(src.data())[1] = 2;
            src_view::position(src.data())[2] = 3;
            src_view::colour(src.data())[0] = 0;
            src_view::colour(src.data())[1] = 16;
            src_view::colour(src.data())[2] = 32;

            src_view::position(src.data() + src_view::stride())[0] = 4;
            src_view::position(src.data() + src_view::stride())[1] = 5;
            src_view::position(src.data() + src_view::stride())[2] = 6;
            src_view::colour(src.data() + src_view::stride())[0] = 64;
            src_view::colour(src.data() + src_view::stride())[1] = 128;
            src_view::colour(src.data() + src_view::stride())[2] = 255;

            mmpld::list_header dst_header;
            dst_header.vertex_type = dst_view::vertex_type();
            dst_header.colour_type = dst_view::colour_type();
            dst_header.particles = src_header.particles;
            auto cnt = mmpld::convert(src.data(), src_header, dst.data(), dst_header);
            Assert::AreEqual(std::uint64_t(2), cnt, L"All particles have been converted.", LINE_INFO());

            Assert::AreEqual(dst_view::vertex_value_type(1), dst_view::position(dst.data())[0], L"P1: Conversion to float at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(2), dst_view::position(dst.data())[1], L"P1: Conversion to float at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(3), dst_view::position(dst.data())[2], L"P1: Conversion to float at [2]", LINE_INFO());
            Assert::AreEqual(src_header.radius, *dst_view::radius(dst.data()), L"P1: Global radius has been converted.", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(0.f / 255.f), dst_view::colour(dst.data())[0], L"P1: Byte to float colour conversion at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(16.f / 255.f), dst_view::colour(dst.data())[1], L"P1: Byte to float colour conversion at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(32.f / 255.f), dst_view::colour(dst.data())[2], L"P1: Byte to float colour conversion at [2]", LINE_INFO());

            Assert::AreEqual(dst_view::vertex_value_type(4), dst_view::position(dst.data() + dst_view::stride())[0], L"P2: Conversion to float at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(5), dst_view::position(dst.data() + dst_view::stride())[1], L"P2: Conversion to float at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(6), dst_view::position(dst.data() + dst_view::stride())[2], L"P2: Conversion to float at [2]", LINE_INFO());
            Assert::AreEqual(src_header.radius, *dst_view::radius(dst.data() + dst_view::stride()), L"P2: Global radius has been converted.", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(64.f / 255.f), dst_view::colour(dst.data() + dst_view::stride())[0], L"P2: Byte to float colour conversion at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(128.f / 255.f), dst_view::colour(dst.data() + dst_view::stride())[1], L"P2: Byte to float colour conversion at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(255.f / 255.f), dst_view::colour(dst.data() + dst_view::stride())[2], L"P2: Byte to float colour conversion at [2]", LINE_INFO());
        }

        TEST_METHOD(TestRuntimeConvertXyzShortRgb8ToXyzFloatRgba32) {
            typedef mmpld::particle_traits<mmpld::vertex_type::short_xyz, mmpld::colour_type::rgb8> src_view;
            typedef mmpld::particle_traits<mmpld::vertex_type::float_xyz, mmpld::colour_type::rgba8> dst_view;
            std::vector<std::uint8_t> src(2 * src_view::stride());
            std::vector<std::uint8_t> dst(2 * dst_view::stride());
            mmpld::list_header src_header;
            src_header.particles = 2;
            src_header.vertex_type = src_view::vertex_traits::value;
            src_header.colour_type = src_view::colour_traits::colour_type;
            src_header.radius = 12.0f;
            src_header.colour[0] = 0.7f;
            src_header.colour[1] = 0.8f;
            src_header.colour[2] = 0.9f;
            src_header.colour[3] = 0.5f;

            src_view::position(src.data())[0] = 1;
            src_view::position(src.data())[1] = 2;
            src_view::position(src.data())[2] = 3;
            src_view::colour(src.data())[0] = 0;
            src_view::colour(src.data())[1] = 16;
            src_view::colour(src.data())[2] = 32;

            src_view::position(src.data() + src_view::stride())[0] = 4;
            src_view::position(src.data() + src_view::stride())[1] = 5;
            src_view::position(src.data() + src_view::stride())[2] = 6;
            src_view::colour(src.data() + src_view::stride())[0] = 64;
            src_view::colour(src.data() + src_view::stride())[1] = 128;
            src_view::colour(src.data() + src_view::stride())[2] = 255;

            mmpld::list_header dst_header;
            dst_header.vertex_type = dst_view::vertex_type();
            dst_header.colour_type = dst_view::colour_type();
            dst_header.particles = src_header.particles;
            auto cnt = mmpld::convert(src.data(), src_header, dst.data(), dst_header);
            Assert::AreEqual(std::uint64_t(2), cnt, L"All particles have been converted.", LINE_INFO());

            Assert::AreEqual(dst_view::vertex_value_type(1), dst_view::position(dst.data())[0], L"P1: Conversion to float at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(2), dst_view::position(dst.data())[1], L"P1: Conversion to float at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(3), dst_view::position(dst.data())[2], L"P1: Conversion to float at [2]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(0), dst_view::colour(dst.data())[0], L"P1: Byte colour copy at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(16), dst_view::colour(dst.data())[1], L"P1: Byte colour copy at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(32), dst_view::colour(dst.data())[2], L"P1: Byte colour copy at [2]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(255), dst_view::colour(dst.data())[3], L"P1: Opaque alpha inserted at [3]", LINE_INFO());


            Assert::AreEqual(dst_view::vertex_value_type(4), dst_view::position(dst.data() + dst_view::stride())[0], L"P2: Conversion to float at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(5), dst_view::position(dst.data() + dst_view::stride())[1], L"P2: Conversion to float at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(6), dst_view::position(dst.data() + dst_view::stride())[2], L"P2: Conversion to float at [2]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(64), dst_view::colour(dst.data() + dst_view::stride())[0], L"P2: Byte colour copy at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(128), dst_view::colour(dst.data() + dst_view::stride())[1], L"P2: Byte colour copy at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(255), dst_view::colour(dst.data() + dst_view::stride())[2], L"P2: Byte colour copy at [2]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(255), dst_view::colour(dst.data() + dst_view::stride())[3], L"P2: Opaque alpha inserted at [3]", LINE_INFO());
        }

        TEST_METHOD(TestRuntimeConvertXyzShortRgb32ToXyzFloatRgba32) {
            typedef mmpld::particle_traits<mmpld::vertex_type::short_xyz, mmpld::colour_type::rgb32> src_view;
            typedef mmpld::particle_traits<mmpld::vertex_type::float_xyz, mmpld::colour_type::rgba32> dst_view;
            std::vector<std::uint8_t> src(2 * src_view::stride());
            std::vector<std::uint8_t> dst(2 * dst_view::stride());
            mmpld::list_header src_header;
            src_header.particles = 2;
            src_header.vertex_type = src_view::vertex_traits::value;
            src_header.colour_type = src_view::colour_traits::colour_type;
            src_header.radius = 12.0f;
            src_header.colour[0] = 0.7f;
            src_header.colour[1] = 0.8f;
            src_header.colour[2] = 0.9f;
            src_header.colour[3] = 0.5f;

            src_view::position(src.data())[0] = 1;
            src_view::position(src.data())[1] = 2;
            src_view::position(src.data())[2] = 3;
            src_view::colour(src.data())[0] = 0.1f;
            src_view::colour(src.data())[1] = 0.2f;
            src_view::colour(src.data())[2] = 0.3f;

            src_view::position(src.data() + src_view::stride())[0] = 4;
            src_view::position(src.data() + src_view::stride())[1] = 5;
            src_view::position(src.data() + src_view::stride())[2] = 6;
            src_view::colour(src.data() + src_view::stride())[0] = 0.4f;
            src_view::colour(src.data() + src_view::stride())[1] = 0.5f;
            src_view::colour(src.data() + src_view::stride())[2] = 0.6f;

            mmpld::list_header dst_header;
            dst_header.vertex_type = dst_view::vertex_type();
            dst_header.colour_type = dst_view::colour_type();
            dst_header.particles = src_header.particles;
            auto cnt = mmpld::convert(src.data(), src_header, dst.data(), dst_header);
            Assert::AreEqual(std::uint64_t(2), cnt, L"All particles have been converted.", LINE_INFO());

            Assert::AreEqual(dst_view::vertex_value_type(1), dst_view::position(dst.data())[0], L"P1: Conversion to float at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(2), dst_view::position(dst.data())[1], L"P1: Conversion to float at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(3), dst_view::position(dst.data())[2], L"P1: Conversion to float at [2]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(0.1), dst_view::colour(dst.data())[0], L"P1: Float colour copy at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(0.2), dst_view::colour(dst.data())[1], L"P1: Float colour copy at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(0.3), dst_view::colour(dst.data())[2], L"P1: Float colour copy at [2]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(1.0), dst_view::colour(dst.data())[3], L"P1: Opaque alpha inserted at [3]", LINE_INFO());

            Assert::AreEqual(dst_view::vertex_value_type(4), dst_view::position(dst.data() + dst_view::stride())[0], L"P2: Conversion to float at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(5), dst_view::position(dst.data() + dst_view::stride())[1], L"P2: Conversion to float at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(6), dst_view::position(dst.data() + dst_view::stride())[2], L"P2: Conversion to float at [2]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(0.4), dst_view::colour(dst.data() + dst_view::stride())[0], L"P2: Float colour copy at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(0.5), dst_view::colour(dst.data() + dst_view::stride())[1], L"P2: Float colour copy at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(0.6), dst_view::colour(dst.data() + dst_view::stride())[2], L"P2: Float colour copy at [2]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(1.0), dst_view::colour(dst.data() + dst_view::stride())[3], L"P2: Opaque alpha inserted at [3]", LINE_INFO());
        }

        TEST_METHOD(TestRuntimeConvertXyzFloatRgb32ToXyzShortRgba8) {
            typedef mmpld::particle_traits<mmpld::vertex_type::float_xyz, mmpld::colour_type::rgb32> src_view;
            typedef mmpld::particle_traits<mmpld::vertex_type::short_xyz, mmpld::colour_type::rgba8> dst_view;
            std::vector<std::uint8_t> src(2 * src_view::stride());
            std::vector<std::uint8_t> dst(2 * dst_view::stride());
            mmpld::list_header src_header;
            src_header.particles = 2;
            src_header.vertex_type = src_view::vertex_traits::value;
            src_header.colour_type = src_view::colour_traits::colour_type;
            src_header.radius = 12.0f;
            src_header.colour[0] = 0.7f;
            src_header.colour[1] = 0.8f;
            src_header.colour[2] = 0.9f;
            src_header.colour[3] = 0.5f;

            src_view::position(src.data())[0] = 1.0f;
            src_view::position(src.data())[1] = 2.0f;
            src_view::position(src.data())[2] = 3.0f;
            src_view::colour(src.data())[0] = 0.0f;
            src_view::colour(src.data())[1] = 16.0f / 255.0f;
            src_view::colour(src.data())[2] = 32.0f / 255.0f;

            src_view::position(src.data() + src_view::stride())[0] = 4.0f;
            src_view::position(src.data() + src_view::stride())[1] = 5.0f;
            src_view::position(src.data() + src_view::stride())[2] = 6.0f;
            src_view::colour(src.data() + src_view::stride())[0] = 64.0f / 255.0f;
            src_view::colour(src.data() + src_view::stride())[1] = 128.0f / 255.0f;
            src_view::colour(src.data() + src_view::stride())[2] = 255.0f / 255.0f;

            mmpld::list_header dst_header;
            dst_header.vertex_type = dst_view::vertex_type();
            dst_header.colour_type = dst_view::colour_type();
            dst_header.particles = src_header.particles;
            auto cnt = mmpld::convert(src.data(), src_header, dst.data(), dst_header);
            Assert::AreEqual(std::uint64_t(2), cnt, L"All particles have been converted.", LINE_INFO());

            Assert::AreEqual(dst_view::vertex_value_type(1), dst_view::position(dst.data())[0], L"P1: Conversion to float at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(2), dst_view::position(dst.data())[1], L"P1: Conversion to float at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(3), dst_view::position(dst.data())[2], L"P1: Conversion to float at [2]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(0), dst_view::colour(dst.data())[0], L"P1: Conversion to byte colour at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(16), dst_view::colour(dst.data())[1], L"P1: Conversion to byte colour at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(32), dst_view::colour(dst.data())[2], L"P1: Conversion to byte colour at [2]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(255), dst_view::colour(dst.data())[3], L"P1: Opaque alpha inserted at [3]", LINE_INFO());

            Assert::AreEqual(dst_view::vertex_value_type(4), dst_view::position(dst.data() + dst_view::stride())[0], L"P2: Conversion to float at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(5), dst_view::position(dst.data() + dst_view::stride())[1], L"P2: Conversion to float at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(6), dst_view::position(dst.data() + dst_view::stride())[2], L"P2: Conversion to float at [2]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(64), dst_view::colour(dst.data() + dst_view::stride())[0], L"P2: Conversion to byte colour at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(128), dst_view::colour(dst.data() + dst_view::stride())[1], L"P2: Conversion to byte colour at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(255), dst_view::colour(dst.data() + dst_view::stride())[2], L"P2: Conversion to byte colour at [2]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(255), dst_view::colour(dst.data() + dst_view::stride())[3], L"P2: Opaque alpha inserted at [3]", LINE_INFO());
        }

        TEST_METHOD(TestRuntimeConvertXyzDoubleIntDoubleToXyzFloatIntFloat) {
            typedef mmpld::particle_traits<mmpld::vertex_type::double_xyz, mmpld::colour_type::intensity64> src_view;
            typedef mmpld::particle_traits<mmpld::vertex_type::float_xyz, mmpld::colour_type::intensity32> dst_view;
            std::vector<std::uint8_t> src(2 * src_view::stride());
            std::vector<std::uint8_t> dst(2 * dst_view::stride());
            mmpld::list_header src_header;
            src_header.particles = 2;
            src_header.vertex_type = src_view::vertex_traits::value;
            src_header.colour_type = src_view::colour_traits::colour_type;
            src_header.radius = 12.0f;
            src_header.min_intensity = 0.0f;
            src_header.max_intensity = 1.0f;

            src_view::position(src.data())[0] = 1.0;
            src_view::position(src.data())[1] = 2.0;
            src_view::position(src.data())[2] = 3.0;
            src_view::colour(src.data())[0] = 0.0;

            src_view::position(src.data() + src_view::stride())[0] = 4.0;
            src_view::position(src.data() + src_view::stride())[1] = 5.0;
            src_view::position(src.data() + src_view::stride())[2] = 6.0;
            src_view::colour(src.data() + src_view::stride())[0] = 1.0;

            mmpld::list_header dst_header;
            dst_header.vertex_type = dst_view::vertex_type();
            dst_header.colour_type = dst_view::colour_type();
            dst_header.particles = src_header.particles;
            auto cnt = mmpld::convert(src.data(), src_header, dst.data(), dst_header);
            Assert::AreEqual(std::uint64_t(2), cnt, L"All particles have been converted.", LINE_INFO());

            Assert::AreEqual(dst_view::vertex_value_type(1), dst_view::position(dst.data())[0], L"P1: Conversion to float at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(2), dst_view::position(dst.data())[1], L"P1: Conversion to float at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(3), dst_view::position(dst.data())[2], L"P1: Conversion to float at [2]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(0), dst_view::colour(dst.data())[0], L"P1: Conversion to float intensity", LINE_INFO());

            Assert::AreEqual(dst_view::vertex_value_type(4), dst_view::position(dst.data() + dst_view::stride())[0], L"P2: Conversion to float at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(5), dst_view::position(dst.data() + dst_view::stride())[1], L"P2: Conversion to float at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(6), dst_view::position(dst.data() + dst_view::stride())[2], L"P2: Conversion to float at [2]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(1), dst_view::colour(dst.data() + dst_view::stride())[0], L"P2: Conversion to float intensity", LINE_INFO());
        }

        TEST_METHOD(TestRuntimeConvertXyzrFloatIntFloatToXyzFloatIntFloat) {
            typedef mmpld::particle_traits<mmpld::vertex_type::float_xyzr, mmpld::colour_type::intensity32> src_view;
            typedef mmpld::particle_traits<mmpld::vertex_type::float_xyz, mmpld::colour_type::intensity32> dst_view;
            std::vector<std::uint8_t> src(2 * src_view::stride());
            std::vector<std::uint8_t> dst(2 * dst_view::stride());
            mmpld::list_header src_header;
            src_header.particles = 2;
            src_header.vertex_type = src_view::vertex_traits::value;
            src_header.colour_type = src_view::colour_traits::colour_type;
            src_header.radius = 0.0f;
            src_header.min_intensity = 0.0f;
            src_header.max_intensity = 1.0f;

            src_view::position(src.data())[0] = 1.0f;
            src_view::position(src.data())[1] = 2.0f;
            src_view::position(src.data())[2] = 3.0f;
            src_view::position(src.data())[3] = 1.0f;
            src_view::colour(src.data())[0] = 0.0f;

            src_view::position(src.data() + src_view::stride())[0] = 4.0f;
            src_view::position(src.data() + src_view::stride())[1] = 5.0f;
            src_view::position(src.data() + src_view::stride())[2] = 6.0f;
            src_view::position(src.data() + src_view::stride())[3] = 3.0f;
            src_view::colour(src.data() + src_view::stride())[0] = 1.0f;

            mmpld::list_header dst_header;
            dst_header.vertex_type = dst_view::vertex_type();
            dst_header.colour_type = dst_view::colour_type();
            dst_header.particles = src_header.particles;
            auto cnt = mmpld::convert(src.data(), src_header, dst.data(), dst_header);
            Assert::AreEqual(std::uint64_t(2), cnt, L"All particles have been converted.", LINE_INFO());

            Assert::AreEqual(2.0f, dst_header.radius, L"Mean radius has been computed.", LINE_INFO());

            Assert::AreEqual(dst_view::vertex_value_type(1), dst_view::position(dst.data())[0], L"P1: Conversion to float at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(2), dst_view::position(dst.data())[1], L"P1: Conversion to float at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(3), dst_view::position(dst.data())[2], L"P1: Conversion to float at [2]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(0), dst_view::colour(dst.data())[0], L"P1: Conversion to float intensity", LINE_INFO());

            Assert::AreEqual(dst_view::vertex_value_type(4), dst_view::position(dst.data() + dst_view::stride())[0], L"P2: Conversion to float at [0]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(5), dst_view::position(dst.data() + dst_view::stride())[1], L"P2: Conversion to float at [1]", LINE_INFO());
            Assert::AreEqual(dst_view::vertex_value_type(6), dst_view::position(dst.data() + dst_view::stride())[2], L"P2: Conversion to float at [2]", LINE_INFO());
            Assert::AreEqual(dst_view::colour_value_type(1), dst_view::colour(dst.data() + dst_view::stride())[0], L"P2: Conversion to float intensity", LINE_INFO());
        }

    private:

        template<class F, class C>
        std::vector<std::uint8_t> testRuntimeReadAs(const C *path, mmpld::list_header& dst_header, const std::size_t buffer = 0) {
            typedef F file_type;
            typedef mmpld::detail::io_traits<F, C> io_type;

            mmpld::file_header fileHeader;
            mmpld::frame_header frameHeader;
            file_type hFile;
            mmpld::list_header listHeader;
            mmpld::seek_table seekTable;

            io_type::open_read(path, hFile);

            mmpld::read_file_header(hFile, fileHeader, seekTable);
            io_type::seek(hFile, static_cast<size_t>(seekTable[0]));
            mmpld::read_frame_header(hFile, fileHeader.version, frameHeader);
            mmpld::read_list_header(hFile, fileHeader.version, listHeader);

            dst_header.particles = listHeader.particles;
            std::vector<std::uint8_t> retval(mmpld::get_size<std::size_t>(dst_header));
            mmpld::read_as(hFile, listHeader, retval.data(), dst_header, buffer);

            io_type::close(hFile);

            return retval;
        }

        template<class T, class F, class C>
        std::vector<std::uint8_t> testStaticReadAs(const C *path, const std::size_t buffer = 0) {
            typedef F file_type;
            typedef mmpld::detail::io_traits<F, C> io_type;
            typedef T traits_type;

            mmpld::file_header fileHeader;
            mmpld::frame_header frameHeader;
            file_type hFile;
            mmpld::list_header listHeader;
            mmpld::seek_table seekTable;

            io_type::open_read(path, hFile);

            mmpld::read_file_header(hFile, fileHeader, seekTable);
            io_type::seek(hFile, static_cast<size_t>(seekTable[0]));
            mmpld::read_frame_header(hFile, fileHeader.version, frameHeader);
            mmpld::read_list_header(hFile, fileHeader.version, listHeader);

            std::vector<std::uint8_t> retval(traits_type::size(listHeader.particles));
            mmpld::read_as<traits_type>(hFile, listHeader, retval.data(),
                listHeader.particles, buffer);

            io_type::close(hFile);

            return retval;
        }

    };
}
