// <copyright file="convertmmpld.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 - 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "stdafx.h"


/// <summary>
/// Tests two strings for equality (case-insensitively).
/// </summary>
template<class T>
bool Equals(const std::basic_string<T>& lhs, const std::basic_string<T>& rhs) {
    return ((lhs.length() == rhs.length())
        && std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), [](T l, T r) {
            return (std::tolower(l) == std::tolower(r)); 
        }));
}

/// <summary>
/// Find (case-insensitively) the given switch in the given range.
/// </summary>
template<class I, class T> I FindSwitch(I begin, I end, const T *name) {
    std::basic_string<T> n(name);
    return std::find_if(begin, end, [&n](const std::basic_string<T>& s) {
        return Equals(s, n);
    });
}

/// <summary>
/// Find (case-insensitively) the given switch and return its argument.
/// </summary>
template<class I, class T> I FindArgument(I begin, I end, const T *name) {
    auto retval = ::FindSwitch(begin, end, name);
    return (retval != end) ? ++retval : retval;
}

/// <summary>
/// Parse the given string as enumeration member of <typeparamref name="E" />.
/// </summary>
template<class E, E... Vs>
E ParseEnum(mmpld::detail::enum_dispatch_list<E, Vs...>&& dispatch,
        const std::string& value) {
    typedef std::decay<decltype(value)>::type::value_type char_type;
    static const auto VALUES = mmpld::detail::make_dispatch_array(dispatch);
    for (auto v : VALUES) {
        if (Equals(mmpld::to_string<char_type>(v), value)) {
            return v;
        }
    }

    throw std::invalid_argument("The specified enumeration value could not be "
        "parsed.");
}


/// <summary>
/// Entry point of convertmmpld.
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int main(const int argc, const char **argv) {
    const std::vector<std::string> CMD_LINE(argv, argv + argc);

    {
        auto it = ::FindSwitch(CMD_LINE.begin(), CMD_LINE.end(), "--no-logo");
        if (it == CMD_LINE.end()) {
            std::cout << "convertmmpld " << MMPLD_ABI_MAJOR << "."
                << MMPLD_ABI_MINOR << std::endl;
            std::cout << "Copyright (C) 2022 - 2025 Visualisierungsinstitut "
                "der Universität Stuttgart." << std::endl;
            std::cout << "Alle Rechte vorbehalten." << std::endl;
            std::cout << std::endl;
        }
    }

    try {
        std::size_t batchSize = 0;          // # of particles to read at once.
        std::vector<char> buffer;           // Buffer for conversion.
        mmpld::colour_type colourType;      // Output colour type.
        int frame = -1;                     // Limit to single frame.
        mmpld::file_header fileHeader;      // MMPLD file header.
        std::ifstream input;                // Input stream.
        std::string inputPath, outputPath;  // Path to the streams.
        mmpld::seek_table inputSeekTable;   // Seek table for input.
        std::ofstream output;               // Output stream.
        mmpld::vertex_type vertexType;      // Output vertex type.

        {
            auto it = ::FindArgument(CMD_LINE.begin(), CMD_LINE.end(),
                "--input");
            if (it != CMD_LINE.end()) {
                inputPath = *it;
            } else {
                throw std::runtime_error("The mandatory command line argument "
                    "--input is missing.");
            }
        }

        {
            auto it = ::FindArgument(CMD_LINE.begin(), CMD_LINE.end(),
                "--output");
            if (it != CMD_LINE.end()) {
                outputPath = *it;
            } else {
                throw std::runtime_error("The mandatory command line argument "
                    "--output is missing.");
            }
        }

        {
            auto it = ::FindArgument(CMD_LINE.begin(), CMD_LINE.end(),
                "--vertex-type");
            if (it != CMD_LINE.end()) {
                vertexType = ParseEnum(mmpld::detail::vertex_dispatch_list {},
                    *it);
            } else {
                throw std::runtime_error("The mandatory command line argument "
                    "--vertex-type is missing.");
            }
        }

        {
            auto it = ::FindArgument(CMD_LINE.begin(), CMD_LINE.end(),
                "--colour-type");
            if (it != CMD_LINE.end()) {
                colourType  = ParseEnum(mmpld::detail::colour_dispatch_list {},
                    *it);
            } else {
                throw std::runtime_error("The mandatory command line argument "
                    "--vertex-type is missing.");
            }
        }

        {
            auto it = ::FindArgument(CMD_LINE.begin(), CMD_LINE.end(),
                "--batch-size");
            if (it != CMD_LINE.end()) {
                batchSize = ::atoi(it->c_str());
            }
        }

        {
            auto it = ::FindArgument(CMD_LINE.begin(), CMD_LINE.end(),
                "--frame");
            if (it != CMD_LINE.end()) {
                frame = ::atoi(it->c_str());
            }
        }

        // Make ifstream/ofstream throw on error.
        input.exceptions(input.exceptions()
            | std::ios_base::failbit | std::ios_base::badbit);
        output.exceptions(output.exceptions()
            | std::ios_base::failbit | std::ios_base::badbit);

        // Open the streams in binary mode, truncating any previous output.
        input.open(inputPath, std::ios::binary);
        output.open(outputPath, std::ios::binary | std::ios::trunc);

        // Read the file header and the seek table of the input.
        mmpld::read_file_header(input, fileHeader, inputSeekTable);

        // Allocate the seek table for the output and initialise all positions
        // with zero, because we do not yet know the correct offsets.
        mmpld::seek_table outputSeekTable(inputSeekTable.size(), 0);

        // Write the file hader and the empty input table to the output file.
        // This way, 'input' and 'output' are not at the same position, which
        // is the frame header for the first frame.
        mmpld::write_file_header(fileHeader, outputSeekTable, output);

        for (decltype(mmpld::file_header::frames) f = 0; f < fileHeader.frames;
                ++f) {
            input.seekg(inputSeekTable[f]);

            // Copy the frame header.
            mmpld::frame_header frameHeader;
            mmpld::read_frame_header(input, fileHeader.version, frameHeader);
            outputSeekTable[f] = output.tellp();
            mmpld::write_frame_header(frameHeader, fileHeader.version, output);

            for (decltype(mmpld::frame_header::lists) l = 0;
                    l < frameHeader.lists; ++l) {
                mmpld::list_header inputHeader;
                mmpld::read_list_header(input, fileHeader.version, inputHeader);

                // Prepare and write the output header.
                auto outputHeader = inputHeader;
                outputHeader.vertex_type = vertexType;
                outputHeader.colour_type = colourType;
                const auto headerOffset = output.tellp();
                mmpld::write_list_header(outputHeader, fileHeader.version,
                    output);

                if (batchSize < 1) {
                    // No batching was requested, so do it at once.
                    auto bufferSize = mmpld::get_size<std::size_t>(
                        outputHeader);
                    buffer.resize(bufferSize);
                    const auto cntRead = mmpld::read_as(input, inputHeader,
                        buffer.data(), outputHeader);
                    assert(cntRead == outputHeader.particles);
                    bufferSize = static_cast<std::size_t>(cntRead)
                        * mmpld::get_stride<std::size_t>(outputHeader);
                    output.write(buffer.data(), bufferSize);

                } else {
                    // Convert in batches.
                    auto convHeader = outputHeader;
                    convHeader.particles = batchSize;

                    auto bufferSize = mmpld::get_size<std::size_t>(convHeader);
                    buffer.resize(bufferSize);

                    decltype(mmpld::list_header::particles) cntConverted = 0;

                    while (cntConverted < outputHeader.particles) {
                        const auto cntRead = mmpld::read_as(input, inputHeader,
                            buffer.data(), convHeader);
                        bufferSize = static_cast<std::size_t>(cntRead)
                            * mmpld::get_stride<std::size_t>(outputHeader);
                        output.write(buffer.data(), bufferSize);
                        cntConverted += cntRead;
                        inputHeader.particles -= cntRead;
                    }
                }

                // If the per-particle radius was dropped and a new mean global
                // radius was set, we need to patch the list header to reflect
                // this change.
                if (inputHeader.radius != outputHeader.radius) {
                    auto pos = output.tellp();
                    output.seekp(headerOffset);
                    mmpld::write_list_header(outputHeader, fileHeader.version,
                        output);
                    output.seekp(pos);
                }

                // In MMPLD 1.1, a block of cluster information follows here.
                // Skip this block and ignore it for output.
                if (fileHeader.version == mmpld::make_version(1, 1)) {
                    mmpld::skip_cluster_info(input);
                }
            } /* end for (decltype(mmpld::frame_header::lists) l = 0; ... */
        } /* end for (decltype(mmpld::file_header::frames) f = 0; ...*/

        // At this point, we need to write the seek table again with the updated
        // information.
        output.seekp(sizeof(mmpld::file_header));
        output.write(reinterpret_cast<const char *>(outputSeekTable.data()),
            outputSeekTable.size() * sizeof(mmpld::seek_table::value_type));

        return 0;
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return -1;
    }
}
