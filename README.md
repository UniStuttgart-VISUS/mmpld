# mmpld

[![Build Status](https://visualisierungsinstitut.visualstudio.com/mmpld/_apis/build/status/UniStuttgart-VISUS.mmpld?branchName=master)](https://visualisierungsinstitut.visualstudio.com/mmpld/_build/latest?definitionId=1&branchName=master)
[![MMPLD Version](https://buildstats.info/nuget/mmpld)](https://www.nuget.org/packages/mmpld)

This is a C++ header-only library for loading MegaMol's MMPLD particle files.

## Usage
The library can be used without compiling anything. Just add the root directory `mmpld` of the library project to the include directories of your C++ programme and include `mmpld.h` from there.

The library contains APIs for interacting with MMPLD files at different levels of abstractions: the low-level API leaves the user most control about handling the file. The `mmpld::file` abstraction handles the file I/O and the meta-data management for you.

For the particle data themselves, the library provides several methods for interpeting the content of a particle list: The `mmpld::particle_view` is a runtime-defined view for particle data, which can be wrapped around a pointer to particles. `mmpld::particle_traits` holds similar functionality, but is defined at compile-time. Note that both views do not perfom any range checks for you, but assume that you pass only valid memory holding particles to them. As a last method, you can obtain the necessary information to interpret raw particle data from the `mmpld::list_header` of each particle list. Functions like `mmpld::get_offsets` and `mmpld::get_stride` allow for extracting the offsets to do pointer arithmetics on particles. The `get_properties` function allows you to create a bitmask describing the contents of a particle list as a whole. For instance, this bitmask allows you to find out whether there are per-particle radius or colour information or whether the colours are given in floating point formats.

The library also provides functions for converting particle lists to different formats, e.g. to convert global radii to per-particle data. Two different implementations for that are available, one that allows you to convert any type of particle list to a compile-time defined format described by a `mmpld::particle_traits` and one to perform arbitrary conversions at runtime.

If `#define MMPLD_WITH_DIRECT3D` is added before including the library header, the library provides a method to create Direct3D input layout descriptions for a particle list. The output of the `mmpld::get_input_layout` function can be used to create an input layout for the raw data of the particle list. As versions 10, 11 and 12 of Direct3D use the same layout for their input layout descriptions, `mmpld::get_input_layout` can be instantiated with `D3D10_INPUT_ELEMENT_DESC`, `D3D11_INPUT_ELEMENT_DESC` or `D3D12_INPUT_ELEMENT_DESC`. 

## The low-level API
The low-level API provides APIs for reading and interpreting the MMPLD file header, the frame header(s) and the list header(s). The user is responsible for seeking to the correct positions in the file. The templates in the API provide instantiations for several I/O methods: `std::ifstream`, `int` file handles obtained from POSIX `_open`, `FILE` pointers and on Windows for native `HANDLE`s. On Windows, `wchar_t` variants are also available.

### Reading a file
The following sample code illustrates how to use the low-level API:

```C++
#include "mmpld.h"

mmpld::file_header fileHeader;
mmpld::frame_header frameHeader;
mmpld::list_header listHeader;
std::vector<std::uint8_t> particles;
mmpld::seek_table seekTable;


// Open the file with your preferred API, in this case WIN32.
auto hFile = ::CreateFile(_T("test.mmpld"), GENERIC_READ, FILE_SHARE_READ,
    nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);
if (hFile == INVALID_HANDLE_VALUE) { /* Handle error. */ }

// Read the file header to obtain information about the frames in the file.
mmpld::read_file_header(hFile, fileHeader, seekTable);

// Read the frame header of each frame in the file.
for (decltype(fileHeader.frames) i = 0; i < fileHeader.frames; ++i) {
    LARGE_INTEGER offset;
    offset.QuadPart = seekTable[i];

    // Seek to the begin of the frame using the offset from 'seekTable'.
    if (!::SetFilePointerEx(hFile, offset, nullptr, FILE_BEGIN)) { /* Handle error. */ }

    // Read the frame header.
    mmpld::read_frame_header(hFile, fileHeader.version, frameHeader);

    // Process all particle lists which are located directly after the frame
    // header. Each particle list has its own header which allows for finding
    // out about its format and size.
    for (decltype(frameHeader.lists) j = 0; j < frameHeader.lists; ++j) {
        mmpld::read_list_header(hFile, fileHeader.version, listHeader);

        // Compute the number of bytes required for all particles.
        auto rem = mmpld::get_size<size_t>(listHeader);

        // Allocate the buffer for all particles.
        particles.resize(rem);

        // Initialise the destination pointer.
        auto ptr = particles.data();

        // Read until we have all particles in memory.
        while (rem > 0) {
            DWORD cnt = 0;
            if (!::ReadFile(file, ptr, rem, &cnt, nullptr)) { /* Handle error. */ }
            ptr += cnt;
            rem -= cnt;
        }

        // In MMPLD 1.1, a block of cluster information follows here. We need to
        // skip this, because otherwise, the next list would be bogus.
        if (fileHeader.version == mmpld::make_version(1, 1)) {
            mmpld::skip_cluster_info(hFile);
        }

        /* Do something with the content of 'particles'. */
    } /* end for (decltype(frameHeader.lists) j = 0; ... */
} /* end for (decltype(fileHeader.frames) i = 0; ... */

::CloseHandle(hFile);
```

### Writing a file
Starting with release 1.3 of the library, the low-level API also includes support for writing certain parts of an MMPLD file, which is illustrated by the following sample:

```C++
#include "mmpld.h"

std::ofstream file("out.mmpld", std::ios::binary | std::ios::trunc);

/* Describe the file and write its header. */
mmpld::file_header fileHeader;
mmpld::seek_table seekTable;
// Fill the file header and the seek table. If you do not know the size of the
// particle lists in advance, there is another variant of write_file_header
// that writes only the header. You need to reserve the size of the seek table
// (number of frames * sizeof(seek_table::value_type)) after the header though
// and write it at the end.

mmpld::write_file_header(fileHeader, seekTable, file);

/* Prepare each frame and write it to the file. */
for (std::size_t f = 0; f < seekTable.size(); ++f) {
    mmpld::frame_header frameHeader;
    // Fill the frame header.
    
    file.seekp(seekTable[f], std::ios::beg);
    mmpld::write_frame_header(frameHeader, fileHeader.version, file);
    
    /* Write all particle lists of the frame. */
    for (decltype(frameHeader.lists) l = 0; l < frameHeader.lists; ++l) {
         mmpld::list_header listHeader;
         // Fill the list header.
                    
         mmpld::write_list_header(listHeader, fileHeader.version, file);
         // Append the actual particles here.
    }
}

file.close();
```


## The mmpld::file class

The `mmpld::file` class is a stateful wrapper around the low-level API, which allows you parsing through an MMPLD file one frame after another. The `mmpld::file` class is responsible for all I/O operations and keeps track of the seek table and the file pointer for you.

### Reading a file
The following code, which does roughly the same as the low-level API sample above, illustrates how to iterate over all particles in a file using this abstraction layer:

```C++
#include "mmpld.h"

// Open the file and prepare the first frame.
mmpld::file<HANDLE, TCHAR> file(_T("test.mmpld"));

// Iterate over all frames in the file. Note that if you are only
// interested in the first one, you can use it right away without calling
// file.open_frame again, because the first frame is opened in the ctor.
for (mmpld::file::frame_number_type f = 0; f < file.frames(); ++f) {
    file.open_frame(f);

    for (auto l = 0; l < file.frame_header().lists; ++l) {
        mmpld::list_header listHeader;
        auto particles = file.read_particles(listHeader);

        /* Do something with the content of 'particles'. */
    }
}
```

### Read the list headers only
Beside the one-shot `read_particles` method illustrated above, `mmpld::file` provides two other methods with user-provided output buffers. These methods must be used carefully, because a whole particle list must be consumed before the next list header can be read. Otherwise, subsequent reads will return corrupt data. The methods are mainly intended for two use cases: (i) if only the list headers should be read and the actual data are irrelevant and (ii) for reading directly into mapped GPU memory. The following sample illustrates the first application case in that it creates Direct3D 11 input layouts for all particle lists in the first frame of a file:

```C++
#include "mmpld.h"

// Open the file and prepare the first frame.
mmpld::file<HANDLE, TCHAR> file(_T("test.mmpld"));

// Iterate over all particle lists in the first frame.
for (auto l = 0; l < file.frame_header().lists; ++l)
    mmpld::list_header listHeader;

    // Read the list header and skip the data (and potential cluster info).
    file.read_particles(true, listHeader, nullptr, 0);

    // Get the input elements for the list.
    auto desc = mmpld::get_input_layout<D3D11_INPUT_ELEMENT_DESC>(header);

    // Note: device creation and shader byte code ommitted.
    ID3D11InputLayout *layout = nullptr;
    device->CreateInputLayout(desc.data(), static_cast<UINT>(desc.size()),
        shaderBytes, cntShaderBytes, &layout);
}
```

### Read into user-provided memory
The second application case, writing into mapped memory, looks roughly like this:

```C++
#include "mmpld.h"

// Open the file and prepare the first frame.
mmpld::file<HANDLE, TCHAR> file(_T("test.mmpld"));

// Retrieve the header of the first list and determine the size of the particles.
mmpld::list_header listHeader;
file.read_particles(false, listHeader, nullptr, 0);
auto listSize = mmpld::get_size<UINT>(listHeader);

// We assume that the GPU buffer is large enough to hold the particles and is
// mapped to 'map'. Now read the actual particles using the continuation
// variant of read_particles.
file.read_particles(listHeader, map.pData, listSize);

// As we read manually, we need to skip cluster infos now. It is safe to call
// this method on all file versions. It has no effect if the file is not
// MMPLD 1.1. Please note that this method must not be called if the particle
// list has not been completely consumed!
file.skip_cluster_info();
```

## test

This project holds unit tests for Visual Studio's C++ unit test framework. It runs on Visual Studio 2019 atm.


## dumpmmpld

This is a simple test application for dumping meta data from an MMPLD file. It serves as demo and test bed for the `mmpld::file` API. The following command dumps the metadata of an MMMPLD file:

```posh
.\dumpmmpld /path .\test.mmpld
```

### Command line arguments of dumpmmpld

| Name                               | Description |
|---                                 |--- |
| `/path <path>`                     | Specifies the path the MMPLD file to be dumped. |
| `/samples <number>`                | Instructs the tool to print the `<number>` first particles in each particle list. |
| `/nologo`                          | Supresses the output of the version of the tool. |

## Nuget package

The project contains a nuspec to create a Nuget package using the tools from https://www.nuget.org/downloads with the following command line:

```posh
nuget.exe pack mmpld.nuspec -properties version=x.x.x
```

Replace `x.x.x` with the current version and do not forget to update the release notes in the nuspec.

## Breaking changes
### Version 1.5
* The constant `vertex_traits::vertex_type` has been renamed to `vertex_traits::value` to allow for a unified implementation of at-runtime data conversion. It is recommended to adapt all client code to this change. However, if your application heavily relies on the presence of this constant, you can enable an alias via `#define MMPLD_WITH_DEPRECATED_VERTEX_TYPE_CONSTANT` before `#include "mmpld.h"`.
* The constant `colour_traits::colour_type` has been renamed to `colour_traits::value` to allow for a unified implementation of at-runtime data conversion. It is recommended to adapt all client code to this change. However, if your application heavily relies on the presence of this constant, you can enable an alias via `#define MMPLD_WITH_DEPRECATED_COLOUR_TYPE_CONSTANT` before `#include "mmpld.h"`.
