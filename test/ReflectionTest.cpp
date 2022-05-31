// <copyright file="ReflectionTest.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2018 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace test {

    TEST_CLASS(ReflectionTest) {

public:

        TEST_METHOD(TestColour) {
            {
                mmpld::colour_properties props;

                auto isValid = mmpld::get_properties(mmpld::colour_type::none, props);
                Assert::IsFalse(isValid, L"colour_type::none has no colour.", LINE_INFO());

                Assert::AreEqual(props.channels, std::size_t(0), L"colour_type::none has no channels.", LINE_INFO());
                Assert::IsFalse(props.is_float, L"colour_type::none is not using floating-point values.", LINE_INFO());
                Assert::AreEqual(props.size, std::size_t(0), L"colour_type::none has no size.", LINE_INFO());
            }

            {
                mmpld::colour_properties props;

                auto isValid = mmpld::get_properties(mmpld::colour_type::rgb8, props);
                Assert::IsTrue(isValid, L"colour_type::rgb8 contains valid colour information.", LINE_INFO());

                Assert::AreEqual(props.channels, std::size_t(3), L"colour_type::rgb8 has 3 channels.", LINE_INFO());
                Assert::IsFalse(props.is_float, L"colour_type::rgb8 is not using floating-point values.", LINE_INFO());
                Assert::AreEqual(props.size, std::size_t(3), L"colour_type::rgb8 has size 3.", LINE_INFO());
            }

            {
                mmpld::colour_properties props;

                auto isValid = mmpld::get_properties(mmpld::colour_type::rgba8, props);
                Assert::IsTrue(isValid, L"colour_type::rgba8 contains valid colour information.", LINE_INFO());

                Assert::AreEqual(props.channels, std::size_t(4), L"colour_type::rgba8 has 4 channels.", LINE_INFO());
                Assert::IsFalse(props.is_float, L"colour_type::rgba8 is not using floating-point values.", LINE_INFO());
                Assert::AreEqual(props.size, std::size_t(4), L"colour_type::rgba8 has size 4.", LINE_INFO());
            }

            {
                mmpld::colour_properties props;

                auto isValid = mmpld::get_properties(mmpld::colour_type::intensity, props);
                Assert::IsTrue(isValid, L"colour_type::intensity contains valid colour information.", LINE_INFO());

                Assert::AreEqual(props.channels, std::size_t(1), L"colour_type::intensity has 1 channel.", LINE_INFO());
                Assert::IsTrue(props.is_float, L"colour_type::intensity is using floating-point values.", LINE_INFO());
                Assert::AreEqual(props.size, std::size_t(4), L"colour_type::intensity has size 4.", LINE_INFO());
            }

            {
                mmpld::colour_properties props;

                auto isValid = mmpld::get_properties(mmpld::colour_type::rgb32, props);
                Assert::IsTrue(isValid, L"colour_type::rgb32 contains valid colour information.", LINE_INFO());

                Assert::AreEqual(props.channels, std::size_t(3), L"colour_type::rgb32 has 3 channels.", LINE_INFO());
                Assert::IsTrue(props.is_float, L"colour_type::rgb32 is using floating-point values.", LINE_INFO());
                Assert::AreEqual(props.size, std::size_t(12), L"colour_type::rgb32 has size 12.", LINE_INFO());
            }

            {
                mmpld::colour_properties props;

                auto isValid = mmpld::get_properties(mmpld::colour_type::rgba32, props);
                Assert::IsTrue(isValid, L"colour_type::rgba32 contains valid colour information.", LINE_INFO());

                Assert::AreEqual(props.channels, std::size_t(4), L"colour_type::rgba32 has 4 channels.", LINE_INFO());
                Assert::IsTrue(props.is_float, L"colour_type::rgba32 is using floating-point values.", LINE_INFO());
                Assert::AreEqual(props.size, std::size_t(16), L"colour_type::rgba32 has size 16.", LINE_INFO());
            }

            {
                mmpld::colour_properties props;

                auto isValid = mmpld::get_properties(mmpld::colour_type::rgba16, props);
                Assert::IsTrue(isValid, L"colour_type::rgba16 contains valid colour information.", LINE_INFO());

                Assert::AreEqual(props.channels, std::size_t(4), L"colour_type::rgba16 has 4 channels.", LINE_INFO());
                Assert::IsFalse(props.is_float, L"colour_type::rgba16 is not using floating-point values.", LINE_INFO());
                Assert::AreEqual(props.size, std::size_t(8), L"colour_type::rgba16 has size 8.", LINE_INFO());
            }

            {
                mmpld::colour_properties props;

                auto isValid = mmpld::get_properties(mmpld::colour_type::intensity64, props);
                Assert::IsTrue(isValid, L"colour_type::intensity64 contains valid colour information.", LINE_INFO());

                Assert::AreEqual(props.channels, std::size_t(1), L"colour_type::intensity64 has 1 channel.", LINE_INFO());
                Assert::IsTrue(props.is_float, L"colour_type::intensity64 is using floating-point values.", LINE_INFO());
                Assert::AreEqual(props.size, std::size_t(8), L"colour_type::intensity64 has size 8.", LINE_INFO());
            }
        }

        TEST_METHOD(TestVertex) {
            {
                mmpld::vertex_properties props;

                auto isValid = mmpld::get_properties(mmpld::vertex_type::none, props);
                Assert::IsFalse(isValid, L"vertex_type::none has no position.", LINE_INFO());

                Assert::IsFalse(props.has_radius, L"vertex_type::none has no per-vertex radius.", LINE_INFO());
                Assert::AreEqual(props.size, std::size_t(0), L"vertex_type::none has no size.", LINE_INFO());
            }

            {
                mmpld::vertex_properties props;

                auto isValid = mmpld::get_properties(mmpld::vertex_type::float_xyz, props);
                Assert::IsTrue(isValid, L"float_xyz::float_xyz has a position.", LINE_INFO());

                Assert::IsFalse(props.has_radius, L"vertex_type::float_xyz has no per-vertex radius.", LINE_INFO());
                Assert::AreEqual(props.size, std::size_t(12), L"vertex_type::float_xyz has size 12.", LINE_INFO());
            }

            {
                mmpld::vertex_properties props;

                auto isValid = mmpld::get_properties(mmpld::vertex_type::float_xyzr, props);
                Assert::IsTrue(isValid, L"float_xyz::float_xyzr has a position.", LINE_INFO());

                Assert::IsTrue(props.has_radius, L"vertex_type::float_xyzr has a per-vertex radius.", LINE_INFO());
                Assert::AreEqual(props.size, std::size_t(16), L"vertex_type::float_xyzr has size 16.", LINE_INFO());
            }

            {
                mmpld::vertex_properties props;

                auto isValid = mmpld::get_properties(mmpld::vertex_type::short_xyz, props);
                Assert::IsTrue(isValid, L"float_xyz::short_xyz has a position.", LINE_INFO());

                Assert::IsFalse(props.has_radius, L"vertex_type::short_xyz has no per-vertex radius.", LINE_INFO());
                Assert::AreEqual(props.size, std::size_t(6), L"vertex_type::short_xyz has size 6.", LINE_INFO());
            }

            {
                mmpld::vertex_properties props;

                auto isValid = mmpld::get_properties(mmpld::vertex_type::double_xyz, props);
                Assert::IsTrue(isValid, L"float_xyz::double_xyz has a position.", LINE_INFO());

                Assert::IsFalse(props.has_radius, L"vertex_type::double_xyz has no per-vertex radius.", LINE_INFO());
                Assert::AreEqual(props.size, std::size_t(24), L"vertex_type::double_xyz has size 24.", LINE_INFO());
            }
        }

        TEST_METHOD(TestListHeader) {
            {
                mmpld::list_header header = { 0 };
                header.vertex_type = mmpld::vertex_type::none;
                header.colour_type = mmpld::colour_type::none;

                int offPos, offRad, offCol;
                auto invalid = mmpld::get_offsets(header, offPos, offRad, offCol);

                Assert::AreEqual(offPos, invalid, L"No position.", LINE_INFO());
                Assert::AreEqual(offRad, invalid, L"No radius.", LINE_INFO());
                Assert::AreEqual(offCol, invalid, L"No colour.", LINE_INFO());

                auto stride = mmpld::get_stride<int>(header);
                Assert::AreEqual(stride, 0, L"Stride is 0.", LINE_INFO());

                auto props = mmpld::get_properties<int>(header);
                Assert::AreEqual(props, int(mmpld::particle_properties::none), L"No special properties.", LINE_INFO());
            }

            {
                mmpld::list_header header = { 0 };
                header.vertex_type = mmpld::vertex_type::float_xyz;
                header.colour_type = mmpld::colour_type::none;

                int offPos, offRad, offCol;
                auto invalid = mmpld::get_offsets(header, offPos, offRad, offCol);

                Assert::AreEqual(offPos, 0, L"Position is at 0.", LINE_INFO());
                Assert::AreEqual(offRad, invalid, L"No radius.", LINE_INFO());
                Assert::AreEqual(offCol, invalid, L"No colour.", LINE_INFO());

                auto stride = mmpld::get_stride<int>(header);
                Assert::AreEqual(stride, 12, L"Stride is 12.", LINE_INFO());

                auto props = mmpld::get_properties<int>(header);
                Assert::AreEqual(props, int(mmpld::particle_properties::none), L"No special properties.", LINE_INFO());
            }

            {
                mmpld::list_header header = { 0 };
                header.vertex_type = mmpld::vertex_type::float_xyzr;
                header.colour_type = mmpld::colour_type::none;

                int offPos, offRad, offCol;
                auto invalid = mmpld::get_offsets(header, offPos, offRad, offCol);

                Assert::AreEqual(offPos, 0, L"Position is at 0.", LINE_INFO());
                Assert::AreEqual(offRad, 12, L"Radius is at 12.", LINE_INFO());
                Assert::AreEqual(offCol, invalid, L"No colour.", LINE_INFO());

                auto stride = mmpld::get_stride<int>(header);
                Assert::AreEqual(stride, 16, L"Stride is 16.", LINE_INFO());

                auto props = mmpld::get_properties<int>(header);
                Assert::AreEqual(props, int(mmpld::particle_properties::per_particle_radius), L"Per-particle radius flag set.", LINE_INFO());
            }

            {
                mmpld::list_header header = { 0 };
                header.vertex_type = mmpld::vertex_type::float_xyzr;
                header.colour_type = mmpld::colour_type::intensity32;

                int offPos, offRad, offCol;
                auto invalid = mmpld::get_offsets(header, offPos, offRad, offCol);

                Assert::AreEqual(offPos, 0, L"Position is at 0.", LINE_INFO());
                Assert::AreEqual(offRad, 12, L"Radius is at 12.", LINE_INFO());
                Assert::AreEqual(offCol, 16, L"Intensity is at 16.", LINE_INFO());

                auto stride = mmpld::get_stride<int>(header);
                Assert::AreEqual(stride, 20, L"Stride is 20.", LINE_INFO());

                auto props = mmpld::get_properties<int>(header);
                auto expected = static_cast<int>(mmpld::particle_properties::per_particle_radius
                    | mmpld::particle_properties::per_particle_intensity
                    | mmpld::particle_properties::float_colour);
                Assert::AreEqual(props, expected, L"Flags are set.", LINE_INFO());
            }

            {
                mmpld::list_header header = { 0 };
                header.vertex_type = mmpld::vertex_type::float_xyzr;
                header.colour_type = mmpld::colour_type::rgb8;

                int offPos, offRad, offCol;
                auto invalid = mmpld::get_offsets(header, offPos, offRad, offCol);

                Assert::AreEqual(offPos, 0, L"Position is at 0.", LINE_INFO());
                Assert::AreEqual(offRad, 12, L"Radius is at 12.", LINE_INFO());
                Assert::AreEqual(offCol, 16, L"Colour is at 16.", LINE_INFO());

                auto stride = mmpld::get_stride<int>(header);
                Assert::AreEqual(stride, 19, L"Stride is 19.", LINE_INFO());

                auto props = mmpld::get_properties<int>(header);
                auto expected = static_cast<int>(mmpld::particle_properties::per_particle_radius
                    | mmpld::particle_properties::per_particle_colour);
                Assert::AreEqual(props, expected, L"Flags are set.", LINE_INFO());
            }

            {
                mmpld::list_header header = { 0 };
                header.vertex_type = mmpld::vertex_type::float_xyzr;
                header.colour_type = mmpld::colour_type::intensity64;

                int offPos, offRad, offCol;
                auto invalid = mmpld::get_offsets(header, offPos, offRad, offCol);

                Assert::AreEqual(offPos, 0, L"Position is at 0.", LINE_INFO());
                Assert::AreEqual(offRad, 12, L"Radius is at 12.", LINE_INFO());
                Assert::AreEqual(offCol, 16, L"Intensity is at 16.", LINE_INFO());

                auto stride = mmpld::get_stride<int>(header);
                Assert::AreEqual(stride, 24, L"Stride is 24.", LINE_INFO());

                auto props = mmpld::get_properties<int>(header);
                auto expected = static_cast<int>(mmpld::particle_properties::per_particle_radius
                    | mmpld::particle_properties::per_particle_intensity
                    | mmpld::particle_properties::float_colour);
                Assert::AreEqual(props, expected, L"Flags are set.", LINE_INFO());
            }

            {
                mmpld::list_header header = { 0 };
                header.vertex_type = mmpld::vertex_type::double_xyz;
                header.colour_type = mmpld::colour_type::intensity64;

                int offPos, offRad, offCol;
                auto invalid = mmpld::get_offsets(header, offPos, offRad, offCol);

                Assert::AreEqual(offPos, 0, L"Position is at 0.", LINE_INFO());
                Assert::AreEqual(offRad, invalid, L"No radius.", LINE_INFO());
                Assert::AreEqual(offCol, 24, L"Intensity is at 16.", LINE_INFO());

                auto stride = mmpld::get_stride<int>(header);
                Assert::AreEqual(stride, 32, L"Stride is 32.", LINE_INFO());

                auto props = mmpld::get_properties<int>(header);
                auto expected = static_cast<int>(mmpld::particle_properties::per_particle_intensity
                    | mmpld::particle_properties::float_colour);
                Assert::AreEqual(props, expected, L"Flags are set.", LINE_INFO());
            }
        }
    };
}
