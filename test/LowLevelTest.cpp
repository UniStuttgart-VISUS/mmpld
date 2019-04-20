/// <copyright file="LowLevelTest.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2018 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>

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
                src_header.vertex_type = src_view::vertex_traits::vertex_type;
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
                Assert::AreEqual(size_t(2), cnt, L"All particles have been converted.", LINE_INFO());

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
                src_header.vertex_type = src_view::vertex_traits::vertex_type;
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
                Assert::AreEqual(size_t(2), cnt, L"All particles have been converted.", LINE_INFO());

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
                src_header.vertex_type = src_view::vertex_traits::vertex_type;
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
                Assert::AreEqual(size_t(2), cnt, L"All particles have been converted.", LINE_INFO());

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
                src_header.vertex_type = src_view::vertex_traits::vertex_type;
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
                Assert::AreEqual(size_t(2), cnt, L"All particles have been converted.", LINE_INFO());

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
                src_header.vertex_type = src_view::vertex_traits::vertex_type;
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
                Assert::AreEqual(size_t(2), cnt, L"All particles have been converted.", LINE_INFO());

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
                src_header.vertex_type = src_view::vertex_traits::vertex_type;
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
                Assert::AreEqual(size_t(2), cnt, L"All particles have been converted.", LINE_INFO());

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
                src_header.vertex_type = src_view::vertex_traits::vertex_type;
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
                Assert::AreEqual(size_t(2), cnt, L"All particles have been converted.", LINE_INFO());

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
                src_header.vertex_type = src_view::vertex_traits::vertex_type;
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
                Assert::AreEqual(size_t(2), cnt, L"All particles have been converted.", LINE_INFO());

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
                src_header.vertex_type = src_view::vertex_traits::vertex_type;
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
                Assert::AreEqual(size_t(2), cnt, L"All particles have been converted.", LINE_INFO());

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
                Assert::AreEqual(src_view::position(src.data())[0], dst.position<src_view::vertex_traits::vertex_type>()[0], L"P1: View on position[0] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data())[1], dst.position<src_view::vertex_traits::vertex_type>()[1], L"P1: View on position[1] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data())[2], dst.position<src_view::vertex_traits::vertex_type>()[2], L"P1: View on position[2] correct", LINE_INFO());
                Assert::AreEqual((const void *) nullptr, dst.radius(), L"P1: View has no radius", LINE_INFO());
                Assert::AreEqual((const src_view::vertex_value_type *) nullptr, dst.radius<src_view::vertex_traits::vertex_type>(), L"P1: View has no radius", LINE_INFO());
                Assert::AreEqual(src_view::colour(src.data())[0], dst.colour<src_view::colour_traits::colour_type>()[0], L"P1: View on colour correct", LINE_INFO());

                dst.advance();
                Assert::AreEqual(src_view::position(src.data() + src_view::stride())[0], dst.position<src_view::vertex_traits::vertex_type>()[0], L"P2: View on position[0] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data() + src_view::stride())[1], dst.position<src_view::vertex_traits::vertex_type>()[1], L"P2: View on position[1] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data() + src_view::stride())[2], dst.position<src_view::vertex_traits::vertex_type>()[2], L"P2: View on position[2] correct", LINE_INFO());
                Assert::AreEqual((const void *) nullptr, dst.radius(), L"P2: View has no radius", LINE_INFO());
                Assert::AreEqual((const src_view::vertex_value_type *) nullptr, dst.radius<src_view::vertex_traits::vertex_type>(), L"P2: View has no radius", LINE_INFO());
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
                Assert::AreEqual(src_view::position(src.data())[0], dst.position<src_view::vertex_traits::vertex_type>()[0], L"P1: View on position[0] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data())[1], dst.position<src_view::vertex_traits::vertex_type>()[1], L"P1: View on position[1] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data())[2], dst.position<src_view::vertex_traits::vertex_type>()[2], L"P1: View on position[2] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data())[3], dst.position<src_view::vertex_traits::vertex_type>()[3], L"P1: View on position[3] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data())[3], *dst.radius<src_view::vertex_traits::vertex_type>(), L"P1: View on radius correct", LINE_INFO());
                Assert::AreEqual(src_view::colour(src.data())[0], dst.colour<src_view::colour_traits::colour_type>()[0], L"P2: View on colour[0] correct", LINE_INFO());
                Assert::AreEqual(src_view::colour(src.data())[1], dst.colour<src_view::colour_traits::colour_type>()[1], L"P2: View on colour[1] correct", LINE_INFO());
                Assert::AreEqual(src_view::colour(src.data())[2], dst.colour<src_view::colour_traits::colour_type>()[2], L"P2: View on colour[2] correct", LINE_INFO());

                dst.advance();
                Assert::AreEqual(src_view::position(src.data() + src_view::stride())[0], dst.position<src_view::vertex_traits::vertex_type>()[0], L"P1: View on position[0] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data() + src_view::stride())[1], dst.position<src_view::vertex_traits::vertex_type>()[1], L"P1: View on position[1] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data() + src_view::stride())[2], dst.position<src_view::vertex_traits::vertex_type>()[2], L"P1: View on position[2] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data() + src_view::stride())[3], dst.position<src_view::vertex_traits::vertex_type>()[3], L"P1: View on position[3] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data() + src_view::stride())[3], *dst.radius<src_view::vertex_traits::vertex_type>(), L"P1: View on radius correct", LINE_INFO());
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
                Assert::AreEqual(src_view::position(src.data())[0], dst.position<src_view::vertex_traits::vertex_type>()[0], L"P1: View on position[0] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data())[1], dst.position<src_view::vertex_traits::vertex_type>()[1], L"P1: View on position[1] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data())[2], dst.position<src_view::vertex_traits::vertex_type>()[2], L"P1: View on position[2] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data())[3], dst.position<src_view::vertex_traits::vertex_type>()[3], L"P1: View on position[3] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data())[3], *dst.radius<src_view::vertex_traits::vertex_type>(), L"P1: View on radius correct", LINE_INFO());
                Assert::AreEqual(src_view::colour(src.data())[0], dst.colour<src_view::colour_traits::colour_type>()[0], L"P2: View on colour[0] correct", LINE_INFO());
                Assert::AreEqual(src_view::colour(src.data())[1], dst.colour<src_view::colour_traits::colour_type>()[1], L"P2: View on colour[1] correct", LINE_INFO());
                Assert::AreEqual(src_view::colour(src.data())[2], dst.colour<src_view::colour_traits::colour_type>()[2], L"P2: View on colour[2] correct", LINE_INFO());
                Assert::AreEqual(src_view::colour(src.data())[3], dst.colour<src_view::colour_traits::colour_type>()[3], L"P2: View on colour[3] correct", LINE_INFO());

                dst.advance();
                Assert::AreEqual(src_view::position(src.data() + src_view::stride())[0], dst.position<src_view::vertex_traits::vertex_type>()[0], L"P1: View on position[0] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data() + src_view::stride())[1], dst.position<src_view::vertex_traits::vertex_type>()[1], L"P1: View on position[1] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data() + src_view::stride())[2], dst.position<src_view::vertex_traits::vertex_type>()[2], L"P1: View on position[2] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data() + src_view::stride())[3], dst.position<src_view::vertex_traits::vertex_type>()[3], L"P1: View on position[3] correct", LINE_INFO());
                Assert::AreEqual(src_view::position(src.data() + src_view::stride())[3], *dst.radius<src_view::vertex_traits::vertex_type>(), L"P1: View on radius correct", LINE_INFO());
                Assert::AreEqual(src_view::colour(src.data() + src_view::stride())[0], dst.colour<src_view::colour_traits::colour_type>()[0], L"P2: View on colour[0] correct", LINE_INFO());
                Assert::AreEqual(src_view::colour(src.data() + src_view::stride())[1], dst.colour<src_view::colour_traits::colour_type>()[1], L"P2: View on colour[1] correct", LINE_INFO());
                Assert::AreEqual(src_view::colour(src.data() + src_view::stride())[2], dst.colour<src_view::colour_traits::colour_type>()[2], L"P2: View on colour[2] correct", LINE_INFO());
                Assert::AreEqual(src_view::colour(src.data() + src_view::stride())[3], dst.colour<src_view::colour_traits::colour_type>()[3], L"P2: View on colour[3] correct", LINE_INFO());
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

            header.colour_type = mmpld::colour_type::intensity;
            header.vertex_type = mmpld::vertex_type::float_xyz;
            Assert::AreEqual(size_t(3 * sizeof(float) + sizeof(float)), mmpld::get_stride<size_t>(header), L"Stride of float_xyz + intensity", LINE_INFO());

            header.colour_type = mmpld::colour_type::intensity;
            header.vertex_type = mmpld::vertex_type::float_xyzr;
            Assert::AreEqual(size_t(4 * sizeof(float) + sizeof(float)), mmpld::get_stride<size_t>(header), L"Stride of float_xyzr + intensity", LINE_INFO());

            header.colour_type = mmpld::colour_type::intensity;
            header.vertex_type = mmpld::vertex_type::short_xyz;
            Assert::AreEqual(size_t(3 * sizeof(short) + sizeof(float)), mmpld::get_stride<size_t>(header), L"Stride of short_xyz + intensity", LINE_INFO());

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

            header.colour_type = mmpld::colour_type::rgb32;
            header.vertex_type = mmpld::vertex_type::float_xyz;
            Assert::AreEqual(size_t(3 * sizeof(float) + 3 * sizeof(float)), mmpld::get_stride<size_t>(header), L"Stride of float_xyz + rgb32", LINE_INFO());

            header.colour_type = mmpld::colour_type::rgb32;
            header.vertex_type = mmpld::vertex_type::float_xyzr;
            Assert::AreEqual(size_t(4 * sizeof(float) + 3 * sizeof(float)), mmpld::get_stride<size_t>(header), L"Stride of float_xyzr + rgb32", LINE_INFO());

            header.colour_type = mmpld::colour_type::rgb32;
            header.vertex_type = mmpld::vertex_type::short_xyz;
            Assert::AreEqual(size_t(3 * sizeof(short) + 3 * sizeof(float)), mmpld::get_stride<size_t>(header), L"Stride of short_xyz + rgb32", LINE_INFO());

            header.colour_type = mmpld::colour_type::rgba32;
            header.vertex_type = mmpld::vertex_type::float_xyz;
            Assert::AreEqual(size_t(3 * sizeof(float) + 4 * sizeof(float)), mmpld::get_stride<size_t>(header), L"Stride of float_xyz + rgba32", LINE_INFO());

            header.colour_type = mmpld::colour_type::rgba32;
            header.vertex_type = mmpld::vertex_type::float_xyzr;
            Assert::AreEqual(size_t(4 * sizeof(float) + 4 * sizeof(float)), mmpld::get_stride<size_t>(header), L"Stride of float_xyzr + rgba32", LINE_INFO());

            header.colour_type = mmpld::colour_type::rgba32;
            header.vertex_type = mmpld::vertex_type::short_xyz;
            Assert::AreEqual(size_t(3 * sizeof(short) + 4 * sizeof(float)), mmpld::get_stride<size_t>(header), L"Stride of short_xyz + rgba32", LINE_INFO());
        }

        TEST_METHOD(TestToString) {
            Assert::AreEqual("none", mmpld::to_string<char>(mmpld::colour_type::none).c_str(), L"Stringisation of colour type \"none\"", LINE_INFO());
            Assert::AreEqual("rgb8", mmpld::to_string<char>(mmpld::colour_type::rgb8).c_str(), L"Stringisation of colour type \"rgb8\"", LINE_INFO());
            Assert::AreEqual("rgba8", mmpld::to_string<char>(mmpld::colour_type::rgba8).c_str(), L"Stringisation of colour type \"rgba8\"", LINE_INFO());
            Assert::AreEqual("intensity", mmpld::to_string<char>(mmpld::colour_type::intensity).c_str(), L"Stringisation of colour type \"intensity\"", LINE_INFO());
            Assert::AreEqual("rgb32", mmpld::to_string<char>(mmpld::colour_type::rgb32).c_str(), L"Stringisation of colour type \"rgb32\"", LINE_INFO());
            Assert::AreEqual("rgba32", mmpld::to_string<char>(mmpld::colour_type::rgba32).c_str(), L"Stringisation of colour type \"rgba32\"", LINE_INFO());

            Assert::AreEqual(L"none", mmpld::to_string<wchar_t>(mmpld::colour_type::none).c_str(), L"Stringisation of colour type \"none\"", LINE_INFO());
            Assert::AreEqual(L"rgb8", mmpld::to_string<wchar_t>(mmpld::colour_type::rgb8).c_str(), L"Stringisation of colour type \"rgb8\"", LINE_INFO());
            Assert::AreEqual(L"rgba8", mmpld::to_string<wchar_t>(mmpld::colour_type::rgba8).c_str(), L"Stringisation of colour type \"rgba8\"", LINE_INFO());
            Assert::AreEqual(L"intensity", mmpld::to_string<wchar_t>(mmpld::colour_type::intensity).c_str(), L"Stringisation of colour type \"intensity\"", LINE_INFO());
            Assert::AreEqual(L"rgb32", mmpld::to_string<wchar_t>(mmpld::colour_type::rgb32).c_str(), L"Stringisation of colour type \"rgb32\"", LINE_INFO());
            Assert::AreEqual(L"rgba32", mmpld::to_string<wchar_t>(mmpld::colour_type::rgba32).c_str(), L"Stringisation of colour type \"rgba32\"", LINE_INFO());

            Assert::AreEqual("none", mmpld::to_string<char>(mmpld::vertex_type::none).c_str(), L"Stringisation of vertex type \"none\"", LINE_INFO());
            Assert::AreEqual("float_xyz", mmpld::to_string<char>(mmpld::vertex_type::float_xyz).c_str(), L"Stringisation of vertex type \"float_xyz\"", LINE_INFO());
            Assert::AreEqual("float_xyzr", mmpld::to_string<char>(mmpld::vertex_type::float_xyzr).c_str(), L"Stringisation of vertex type \"float_xyzr\"", LINE_INFO());
            Assert::AreEqual("short_xyz", mmpld::to_string<char>(mmpld::vertex_type::short_xyz).c_str(), L"Stringisation of vertex type \"short_xyz\"", LINE_INFO());

            Assert::AreEqual(L"none", mmpld::to_string<wchar_t>(mmpld::vertex_type::none).c_str(), L"Stringisation of vertex type \"none\"", LINE_INFO());
            Assert::AreEqual(L"float_xyz", mmpld::to_string<wchar_t>(mmpld::vertex_type::float_xyz).c_str(), L"Stringisation of vertex type \"float_xyz\"", LINE_INFO());
            Assert::AreEqual(L"float_xyzr", mmpld::to_string<wchar_t>(mmpld::vertex_type::float_xyzr).c_str(), L"Stringisation of vertex type \"float_xyzr\"", LINE_INFO());
            Assert::AreEqual(L"short_xyz", mmpld::to_string<wchar_t>(mmpld::vertex_type::short_xyz).c_str(), L"Stringisation of vertex type \"short_xyz\"", LINE_INFO());
        }

        TEST_METHOD(TestTraits) {
            Assert::AreEqual(size_t(0), mmpld::colour_traits<mmpld::colour_type::none>::size, L"Size of colour_type::none", LINE_INFO());
            Assert::AreEqual(size_t(3), mmpld::colour_traits<mmpld::colour_type::rgb8>::size, L"Size of colour_type::rgb8", LINE_INFO());
            Assert::AreEqual(size_t(4), mmpld::colour_traits<mmpld::colour_type::rgba8>::size, L"Size of colour_type::rgba8", LINE_INFO());
            Assert::AreEqual(size_t(4), mmpld::colour_traits<mmpld::colour_type::intensity>::size, L"Size of colour_type::intensity", LINE_INFO());
            Assert::AreEqual(size_t(12), mmpld::colour_traits<mmpld::colour_type::rgb32>::size, L"Size of colour_type::rgb32", LINE_INFO());
            Assert::AreEqual(size_t(16), mmpld::colour_traits<mmpld::colour_type::rgba32>::size, L"Size of colour_type::rgba32", LINE_INFO());

            Assert::AreEqual(size_t(0), mmpld::vertex_traits<mmpld::vertex_type::none>::size, L"Size of vertex_type::none", LINE_INFO());
            Assert::AreEqual(size_t(12), mmpld::vertex_traits<mmpld::vertex_type::float_xyz>::size, L"Size of vertex_type::float_xyz", LINE_INFO());
            Assert::AreEqual(size_t(16), mmpld::vertex_traits<mmpld::vertex_type::float_xyzr>::size, L"Size of vertex_type::float_xyzr", LINE_INFO());
            Assert::AreEqual(size_t(6), mmpld::vertex_traits<mmpld::vertex_type::short_xyz>::size, L"Size of vertex_type::short_xyz", LINE_INFO());
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
            Assert::AreEqual(std::uint32_t(1), fileHeader.frames, L"Number of expected frames matches.", LINE_INFO());
            Assert::AreEqual(seekTable.size(), size_t(fileHeader.frames), L"Number of frames and size of seek table match.", LINE_INFO());

            io_type::seek(hFile, static_cast<size_t>(seekTable[0]));
            mmpld::read_frame_header(hFile, fileHeader.version, frameHeader);
            Assert::AreEqual(std::int32_t(1), frameHeader.lists, L"Frame #1 holds one particle list.", LINE_INFO());

            mmpld::read_list_header(hFile, fileHeader.version, listHeader);
            Assert::AreEqual(std::uint64_t(4), listHeader.particles, L"List holds four particles.", LINE_INFO());

            return listHeader;
        }
    };
}
