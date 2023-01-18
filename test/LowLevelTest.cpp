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

        TEST_METHOD(TestConvert) {
            {
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

            {
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

            {
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

            {
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

            {
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

            {
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

            {
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

            {
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

            {
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

            {
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
        }

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

        TEST_METHOD(TestReadAs) {
            ::SetMmpldWorkingDirectory();   // Need to have access to the test files.

            {
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

            {
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

            {
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

            {
                typedef mmpld::particle_traits<mmpld::vertex_type::short_xyz, mmpld::colour_type::rgb32> traits_type;
                auto particles = this->testStaticReadAs<traits_type, HANDLE>("test_xyz_float_int_float.mmpld");

                {
                    auto pos = traits_type::position(particles.data() + 0 * traits_type::stride());
                    auto col = traits_type::colour(particles.data() + 0 * traits_type::stride());
                    Assert::AreEqual(std::int16_t(0), pos[0], L"First position x", LINE_INFO());
                    Assert::AreEqual(std::int16_t(0), pos[1], L"First position y", LINE_INFO());
                    Assert::AreEqual(std::int16_t(0), pos[2], L"First position z", LINE_INFO());
                    Assert::AreEqual(255.0f, col[0], L"First intensity r", LINE_INFO());
                    Assert::AreEqual(255.0f, col[1], L"First intensity g", LINE_INFO());
                    Assert::AreEqual(255.0f, col[2], L"First intensity b", LINE_INFO());
                }

                {
                    auto pos = traits_type::position(particles.data() + 1 * traits_type::stride());
                    auto col = traits_type::colour(particles.data() + 1 * traits_type::stride());
                    Assert::AreEqual(std::int16_t(1), pos[0], L"Second position x", LINE_INFO());
                    Assert::AreEqual(std::int16_t(0), pos[1], L"Second position y", LINE_INFO());
                    Assert::AreEqual(std::int16_t(0), pos[2], L"Second position z", LINE_INFO());
                    Assert::AreEqual(64.0f, col[0], L"Second intensity r", LINE_INFO());
                    Assert::AreEqual(64.0f, col[1], L"Second intensity g", LINE_INFO());
                    Assert::AreEqual(64.0f, col[2], L"Second intensity b", LINE_INFO());
                }

                {
                    auto pos = traits_type::position(particles.data() + 2 * traits_type::stride());
                    auto col = traits_type::colour(particles.data() + 2 * traits_type::stride());
                    Assert::AreEqual(std::int16_t(0), pos[0], L"Third position x", LINE_INFO());
                    Assert::AreEqual(std::int16_t(1), pos[1], L"Third position y", LINE_INFO());
                    Assert::AreEqual(std::int16_t(0), pos[2], L"Third position z", LINE_INFO());
                    Assert::AreEqual(128.0f, col[0], L"Third intensity r", LINE_INFO());
                    Assert::AreEqual(128.0f, col[1], L"Third intensity g", LINE_INFO());
                    Assert::AreEqual(128.0f, col[2], L"Third intensity b", LINE_INFO());
                }

                {
                    auto pos = traits_type::position(particles.data() + 3 * traits_type::stride());
                    auto col = traits_type::colour(particles.data() + 3 * traits_type::stride());
                    Assert::AreEqual(std::int16_t(0), pos[0], L"Fourth position x", LINE_INFO());
                    Assert::AreEqual(std::int16_t(0), pos[1], L"Fourth position y", LINE_INFO());
                    Assert::AreEqual(std::int16_t(1), pos[2], L"Fourth position z", LINE_INFO());
                    Assert::AreEqual(192.0f, col[0], L"Fourth intensity r", LINE_INFO());
                    Assert::AreEqual(192.0f, col[1], L"Fourth intensity g", LINE_INFO());
                    Assert::AreEqual(192.0f, col[2], L"Fourth intensity b", LINE_INFO());
                }
            }

            {
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

            {
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

            {
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

            {
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

            {
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

            {
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

            {
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

            {
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

            {
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

            {
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

            {
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
        }

        TEST_METHOD(ReadFrameAs) {
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

            // Full read
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
            std::vector<std::uint8_t> particles(listHeader.particles * mmpld::get_stride<std::size_t>(listHeader));

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

            // Buffered read
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
            particles.resize(listHeader.particles * mmpld::get_stride<std::size_t>(listHeader));

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
                Assert::AreEqual(255.0f, view.colour()[0], 0.0001f, L"p0.r", LINE_INFO());
                Assert::AreEqual(255.0f, view.colour()[1], 0.0001f, L"p0.g", LINE_INFO());
                Assert::AreEqual(255.0f, view.colour()[2], 0.0001f, L"p0.b", LINE_INFO());

                view.advance();
                Assert::AreEqual(1.0f, view.position()[0], 0.0001f, L"p1.x", LINE_INFO());
                Assert::AreEqual(0.0f, view.position()[1], 0.0001f, L"p1.y", LINE_INFO());
                Assert::AreEqual(0.0f, view.position()[2], 0.0001f, L"p1.z", LINE_INFO());
                Assert::AreEqual(64.0f, view.colour()[0], 0.0001f, L"p1.r", LINE_INFO());
                Assert::AreEqual(64.0f, view.colour()[1], 0.0001f, L"p1.g", LINE_INFO());
                Assert::AreEqual(64.0f, view.colour()[2], 0.0001f, L"p1.b", LINE_INFO());

                view.advance();
                Assert::AreEqual(0.0f, view.position()[0], 0.0001f, L"p2.x", LINE_INFO());
                Assert::AreEqual(1.0f, view.position()[1], 0.0001f, L"p2.y", LINE_INFO());
                Assert::AreEqual(0.0f, view.position()[2], 0.0001f, L"p2.z", LINE_INFO());
                Assert::AreEqual(128.0f, view.colour()[0], 0.0001f, L"p2.r", LINE_INFO());
                Assert::AreEqual(128.0f, view.colour()[1], 0.0001f, L"p2.g", LINE_INFO());
                Assert::AreEqual(128.0f, view.colour()[2], 0.0001f, L"p2.b", LINE_INFO());

                view.advance();
                Assert::AreEqual(0.0f, view.position()[0], 0.0001f, L"p3.x", LINE_INFO());
                Assert::AreEqual(0.0f, view.position()[1], 0.0001f, L"p3.y", LINE_INFO());
                Assert::AreEqual(1.0f, view.position()[2], 0.0001f, L"p3.z", LINE_INFO());
                Assert::AreEqual(192.0f, view.colour()[0], 0.0001f, L"p3.r", LINE_INFO());
                Assert::AreEqual(192.0f, view.colour()[1], 0.0001f, L"p3.g", LINE_INFO());
                Assert::AreEqual(192.0f, view.colour()[2], 0.0001f, L"p3.b", LINE_INFO());

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
        }

        TEST_METHOD(TestRuntimeConvert) {
            {
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

            {
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

            {
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

            {
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

            {
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

            {
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

            {
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

            {
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

            {
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

            {
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

            {
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
