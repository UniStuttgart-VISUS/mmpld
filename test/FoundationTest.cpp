// <copyright file="FoundationTest.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "stdafx.h"
#include "CppUnitTest.h"

#include "util.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace test {

    TEST_CLASS(FoundationTest) {

    public:

        TEST_METHOD(TestConversionTable) {
            {
                typedef std::underlying_type<mmpld::vertex_type>::type value_type;
                auto table = mmpld::detail::make_conversion_table3<mmpld::vertex_type, mmpld::vertex_traits>(mmpld::detail::vertex_dispatch_list{});

                Assert::AreEqual(value_type(mmpld::vertex_type::none), value_type(std::get<(0 * 5) + 0>(table).first.first), L"Conversion target is vertex_type::none", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::none), value_type(std::get<(0 * 5) + 1>(table).first.first), L"Conversion target is vertex_type::none", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::none), value_type(std::get<(0 * 5) + 2>(table).first.first), L"Conversion target is vertex_type::none", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::none), value_type(std::get<(0 * 5) + 3>(table).first.first), L"Conversion target is vertex_type::none", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::none), value_type(std::get<(0 * 5) + 4>(table).first.first), L"Conversion target is vertex_type::none", LINE_INFO());

                Assert::AreEqual(value_type(mmpld::vertex_type::float_xyz), value_type(std::get<(1 * 5) + 0>(table).first.first), L"Conversion target is vertex_type::float_xyz", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::float_xyz), value_type(std::get<(1 * 5) + 1>(table).first.first), L"Conversion target is vertex_type::float_xyz", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::float_xyz), value_type(std::get<(1 * 5) + 2>(table).first.first), L"Conversion target is vertex_type::float_xyz", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::float_xyz), value_type(std::get<(1 * 5) + 3>(table).first.first), L"Conversion target is vertex_type::float_xyz", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::float_xyz), value_type(std::get<(1 * 5) + 4>(table).first.first), L"Conversion target is vertex_type::float_xyz", LINE_INFO());

                Assert::AreEqual(value_type(mmpld::vertex_type::float_xyzr), value_type(std::get<(2 * 5) + 0>(table).first.first), L"Conversion target is vertex_type::float_xyzr", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::float_xyzr), value_type(std::get<(2 * 5) + 1>(table).first.first), L"Conversion target is vertex_type::float_xyzr", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::float_xyzr), value_type(std::get<(2 * 5) + 2>(table).first.first), L"Conversion target is vertex_type::float_xyzr", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::float_xyzr), value_type(std::get<(2 * 5) + 3>(table).first.first), L"Conversion target is vertex_type::float_xyzr", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::float_xyzr), value_type(std::get<(2 * 5) + 4>(table).first.first), L"Conversion target is vertex_type::float_xyzr", LINE_INFO());

                Assert::AreEqual(value_type(mmpld::vertex_type::short_xyz), value_type(std::get<(3 * 5) + 0>(table).first.first), L"Conversion target is vertex_type::short_xyz", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::short_xyz), value_type(std::get<(3 * 5) + 1>(table).first.first), L"Conversion target is vertex_type::short_xyz", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::short_xyz), value_type(std::get<(3 * 5) + 2>(table).first.first), L"Conversion target is vertex_type::short_xyz", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::short_xyz), value_type(std::get<(3 * 5) + 3>(table).first.first), L"Conversion target is vertex_type::short_xyz", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::short_xyz), value_type(std::get<(3 * 5) + 4>(table).first.first), L"Conversion target is vertex_type::short_xyz", LINE_INFO());

                Assert::AreEqual(value_type(mmpld::vertex_type::double_xyz), value_type(std::get<(4 * 5) + 0>(table).first.first), L"Conversion target is vertex_type::double_xyz", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::double_xyz), value_type(std::get<(4 * 5) + 1>(table).first.first), L"Conversion target is vertex_type::double_xyz", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::double_xyz), value_type(std::get<(4 * 5) + 2>(table).first.first), L"Conversion target is vertex_type::double_xyz", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::double_xyz), value_type(std::get<(4 * 5) + 3>(table).first.first), L"Conversion target is vertex_type::double_xyz", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::double_xyz), value_type(std::get<(4 * 5) + 4>(table).first.first), L"Conversion target is vertex_type::double_xyz", LINE_INFO());

                Assert::AreEqual(value_type(mmpld::vertex_type::none), value_type(std::get<(0 * 5) + 0>(table).first.second), L"Conversion target is vertex_type::none", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::none), value_type(std::get<(1 * 5) + 0>(table).first.second), L"Conversion target is vertex_type::none", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::none), value_type(std::get<(2 * 5) + 0>(table).first.second), L"Conversion target is vertex_type::none", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::none), value_type(std::get<(3 * 5) + 0>(table).first.second), L"Conversion target is vertex_type::none", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::none), value_type(std::get<(4 * 5) + 0>(table).first.second), L"Conversion target is vertex_type::none", LINE_INFO());

                Assert::AreEqual(value_type(mmpld::vertex_type::float_xyz), value_type(std::get<(0 * 5) + 1>(table).first.second), L"Conversion source is vertex_type::float_xyz", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::float_xyz), value_type(std::get<(1 * 5) + 1>(table).first.second), L"Conversion source is vertex_type::float_xyz", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::float_xyz), value_type(std::get<(2 * 5) + 1>(table).first.second), L"Conversion source is vertex_type::float_xyz", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::float_xyz), value_type(std::get<(3 * 5) + 1>(table).first.second), L"Conversion source is vertex_type::float_xyz", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::float_xyz), value_type(std::get<(4 * 5) + 1>(table).first.second), L"Conversion source is vertex_type::float_xyz", LINE_INFO());

                Assert::AreEqual(value_type(mmpld::vertex_type::float_xyzr), value_type(std::get<(0 * 5) + 2>(table).first.second), L"Conversion source is vertex_type::float_xyzr", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::float_xyzr), value_type(std::get<(1 * 5) + 2>(table).first.second), L"Conversion source is vertex_type::float_xyzr", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::float_xyzr), value_type(std::get<(2 * 5) + 2>(table).first.second), L"Conversion source is vertex_type::float_xyzr", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::float_xyzr), value_type(std::get<(3 * 5) + 2>(table).first.second), L"Conversion source is vertex_type::float_xyzr", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::float_xyzr), value_type(std::get<(4 * 5) + 2>(table).first.second), L"Conversion source is vertex_type::float_xyzr", LINE_INFO());

                Assert::AreEqual(value_type(mmpld::vertex_type::short_xyz), value_type(std::get<(0 * 5) + 3>(table).first.second), L"Conversion source is vertex_type::short_xyz", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::short_xyz), value_type(std::get<(1 * 5) + 3>(table).first.second), L"Conversion source is vertex_type::short_xyz", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::short_xyz), value_type(std::get<(2 * 5) + 3>(table).first.second), L"Conversion source is vertex_type::short_xyz", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::short_xyz), value_type(std::get<(3 * 5) + 3>(table).first.second), L"Conversion source is vertex_type::short_xyz", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::short_xyz), value_type(std::get<(4 * 5) + 3>(table).first.second), L"Conversion source is vertex_type::short_xyz", LINE_INFO());

                Assert::AreEqual(value_type(mmpld::vertex_type::double_xyz), value_type(std::get<(0 * 5) + 4>(table).first.second), L"Conversion source is vertex_type::double_xyz", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::double_xyz), value_type(std::get<(1 * 5) + 4>(table).first.second), L"Conversion source is vertex_type::double_xyz", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::double_xyz), value_type(std::get<(2 * 5) + 4>(table).first.second), L"Conversion source is vertex_type::double_xyz", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::double_xyz), value_type(std::get<(3 * 5) + 4>(table).first.second), L"Conversion source is vertex_type::double_xyz", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::double_xyz), value_type(std::get<(4 * 5) + 4>(table).first.second), L"Conversion source is vertex_type::double_xyz", LINE_INFO());
            }

            {
                typedef std::underlying_type<mmpld::vertex_type>::type value_type;
                auto table = mmpld::detail::make_vertex_conversion_table();

                Assert::AreEqual((void *)mmpld::detail::runtime_converter<mmpld::vertex_type, mmpld::vertex_type::none, mmpld::vertex_type::none>::convert,
                    (void *)table[std::make_pair(mmpld::vertex_type::none, mmpld::vertex_type::none)], L"Conversion from vertex_type::none to vertex_type::none", LINE_INFO());
            }

            {
                typedef std::underlying_type<mmpld::colour_type>::type value_type;
                auto table = mmpld::detail::make_colour_conversion_table();

                Assert::AreEqual((void *)mmpld::detail::runtime_converter<mmpld::colour_type, mmpld::colour_type::none, mmpld::colour_type::none>::convert,
                    (void *)table[std::make_pair(mmpld::colour_type::none, mmpld::colour_type::none)], L"Conversion from colour_type::none to colour_type::none", LINE_INFO());
            }
        }

        TEST_METHOD(TestDispatchListToArray) {
            {
                typedef std::underlying_type<mmpld::vertex_type>::type value_type;
                auto a = mmpld::detail::make_dispatch_array(mmpld::detail::vertex_dispatch_list { });
                Assert::AreEqual(value_type(mmpld::vertex_type::none), value_type(std::get<0>(a)), L"Enum member vertex_type::none", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::float_xyz), value_type(std::get<1>(a)), L"Enum member vertex_type::float_xyz", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::float_xyzr), value_type(std::get<2>(a)), L"Enum member vertex_type::float_xyzr", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::short_xyz), value_type(std::get<3>(a)), L"Enum member vertex_type::short_xyz", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::double_xyz), value_type(std::get<4>(a)), L"Enum member vertex_type::double_xyz", LINE_INFO());
            }

            {
                typedef std::underlying_type<mmpld::colour_type>::type value_type;
                auto a = mmpld::detail::make_dispatch_array(mmpld::detail::colour_dispatch_list { });
                Assert::AreEqual(value_type(mmpld::colour_type::none), value_type(std::get<0>(a)), L"Enum member colour_type::none", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::colour_type::rgb8), value_type(std::get<1>(a)), L"Enum member colour_type::rgb8", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::colour_type::rgba8), value_type(std::get<2>(a)), L"Enum member colour_type::rgba8", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::colour_type::intensity), value_type(std::get<3>(a)), L"Enum member colour_type::intensity", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::colour_type::rgb32), value_type(std::get<4>(a)), L"Enum member colour_type::rgb32", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::colour_type::rgba32), value_type(std::get<5>(a)), L"Enum member colour_type::rgba32", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::colour_type::rgba16), value_type(std::get<6>(a)), L"Enum member colour_type::rgba16", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::colour_type::intensity64), value_type(std::get<7>(a)), L"Enum member colour_type::intensity64", LINE_INFO());
            }
        }

        TEST_METHOD(TestDispatchListToTuple) {
            {
                typedef std::underlying_type<mmpld::vertex_type>::type value_type;
                auto tuple = mmpld::detail::make_dispatch_tuple(mmpld::detail::vertex_dispatch_list { });
                Assert::AreEqual(value_type(mmpld::vertex_type::none), value_type(std::get<0>(tuple)), L"Enum member vertex_type::none", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::float_xyz), value_type(std::get<1>(tuple)), L"Enum member vertex_type::float_xyz", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::float_xyzr), value_type(std::get<2>(tuple)), L"Enum member vertex_type::float_xyzr", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::short_xyz), value_type(std::get<3>(tuple)), L"Enum member vertex_type::short_xyz", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_type::double_xyz), value_type(std::get<4>(tuple)), L"Enum member vertex_type::double_xyz", LINE_INFO());
            }

            {
                typedef std::underlying_type<mmpld::colour_type>::type value_type;
                auto tuple = mmpld::detail::make_dispatch_tuple(mmpld::detail::colour_dispatch_list { });
                Assert::AreEqual(value_type(mmpld::colour_type::none), value_type(std::get<0>(tuple)), L"Enum member colour_type::none", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::colour_type::rgb8), value_type(std::get<1>(tuple)), L"Enum member colour_type::rgb8", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::colour_type::rgba8), value_type(std::get<2>(tuple)), L"Enum member colour_type::rgba8", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::colour_type::intensity), value_type(std::get<3>(tuple)), L"Enum member colour_type::intensity", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::colour_type::rgb32), value_type(std::get<4>(tuple)), L"Enum member colour_type::rgb32", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::colour_type::rgba32), value_type(std::get<5>(tuple)), L"Enum member colour_type::rgba32", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::colour_type::rgba16), value_type(std::get<6>(tuple)), L"Enum member colour_type::rgba16", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::colour_type::intensity64), value_type(std::get<7>(tuple)), L"Enum member colour_type::intensity64", LINE_INFO());
            }
        }

        TEST_METHOD(TestIncrementalMean) {
            {
                float mean = 0.0f;
                std::size_t count = 0;

                mmpld::detail::incremental_mean(mean, count, 0.0f);
                Assert::AreEqual(0.0f, mean, L"mean is 0.0f", LINE_INFO());
                Assert::AreEqual(std::size_t(1), count, L"count is 1", LINE_INFO());

                mmpld::detail::incremental_mean(mean, count, 1.0f);
                Assert::AreEqual(0.5f, mean, L"mean is 0.5f", LINE_INFO());
                Assert::AreEqual(std::size_t(2), count, L"count is 2", LINE_INFO());

                mmpld::detail::incremental_mean(mean, count, 2.0f);
                Assert::AreEqual(1.0f, mean, L"mean is 1.0f", LINE_INFO());
                Assert::AreEqual(std::size_t(3), count, L"count is 3", LINE_INFO());
            }
        }

        TEST_METHOD(TestLegacyValues) {
            {
                typedef std::underlying_type<mmpld::vertex_type>::type value_type;
                Assert::AreEqual(value_type(mmpld::vertex_traits<mmpld::vertex_type::none>::value), value_type(mmpld::vertex_traits<mmpld::vertex_type::none>::vertex_type), L"Legacy vertex_type::none", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_traits<mmpld::vertex_type::float_xyz>::value), value_type(mmpld::vertex_traits<mmpld::vertex_type::float_xyz>::vertex_type), L"Legacy vertex_type::float_xyz", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_traits<mmpld::vertex_type::float_xyzr>::value), value_type(mmpld::vertex_traits<mmpld::vertex_type::float_xyzr>::vertex_type), L"Legacy vertex_type::float_xyzr", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_traits<mmpld::vertex_type::short_xyz>::value), value_type(mmpld::vertex_traits<mmpld::vertex_type::short_xyz>::vertex_type), L"Legacy vertex_type::short_xyz", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::vertex_traits<mmpld::vertex_type::double_xyz>::value), value_type(mmpld::vertex_traits<mmpld::vertex_type::double_xyz>::vertex_type), L"Legacy vertex_type::double_xyz", LINE_INFO());
            }

            {
                typedef std::underlying_type<mmpld::colour_type>::type value_type;
                Assert::AreEqual(value_type(mmpld::colour_traits<mmpld::colour_type::none>::value), value_type(mmpld::colour_traits<mmpld::colour_type::none>::colour_type), L"Legacy colour_type::none", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::colour_traits<mmpld::colour_type::rgb8>::value), value_type(mmpld::colour_traits<mmpld::colour_type::rgb8>::colour_type), L"Legacy colour_type::rgb8", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::colour_traits<mmpld::colour_type::rgba8>::value), value_type(mmpld::colour_traits<mmpld::colour_type::rgba8>::colour_type), L"Legacy colour_type::rgba8", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::colour_traits<mmpld::colour_type::intensity>::value), value_type(mmpld::colour_traits<mmpld::colour_type::intensity>::colour_type), L"Legacy colour_type::intensity", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::colour_traits<mmpld::colour_type::rgb32>::value), value_type(mmpld::colour_traits<mmpld::colour_type::rgb32>::colour_type), L"Legacy colour_type::rgb32", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::colour_traits<mmpld::colour_type::rgba32>::value), value_type(mmpld::colour_traits<mmpld::colour_type::rgba32>::colour_type), L"Legacy colour_type::rgba32", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::colour_traits<mmpld::colour_type::rgba16>::value), value_type(mmpld::colour_traits<mmpld::colour_type::rgba16>::colour_type), L"Legacy colour_type::rgba16", LINE_INFO());
                Assert::AreEqual(value_type(mmpld::colour_traits<mmpld::colour_type::intensity64>::value), value_type(mmpld::colour_traits<mmpld::colour_type::intensity64>::colour_type), L"Legacy colour_type::intensity64", LINE_INFO());
            }
        }
    };
}
