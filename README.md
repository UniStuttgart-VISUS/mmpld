# mmpld
This is a C++ header-only library for loading MegaMol's MMPLD particle files.

## Usage
The library can be used without compiling anything. Just add the root directory `mmpld` of the library project to the include directories of your C++ programme and include `mmpld.h` from there.

The library contains APIs for interacting with MMPLD files at different levels of abstractions: the low-level API leaves the user most control about handling the file. The `mmpld::file` abstraction handles the file I/O and the meta-data management for you.

For the particle data itself, the library provides several methods for interpeting the content of a particle list: The `mmpld::particle_view` is a runtime-defined view for particle data. `mmpld::particle_traits` holds similar functionality, but is defined at compile-time. Note that both views do not perfom any range checks for you, but assume that you pass only valid memory holding particles to them.

If `#define MMPLD_WITH_DIRECT3D` is added before including the library header, the library provides a method to create the input layout description for a particle list. The output of the `mmpld::get_input_layout` function can be used to create an input layout that is compatible with the data of a particle list. A versions 10, 11 and 12 use the same layout for their input layout descriptions, `mmpld::get_input_layout` can be instantiated with `D3D10_INPUT_ELEMENT_DESC`, `D3D11_INPUT_ELEMENT_DESC` or `D3D12_INPUT_ELEMENT_DESC`. 

## The low-level API
The low-level API provides APIs for reading and interpreting the MMPLD file header, the frame header(s) and the list header(s). The user is responsible for seeking to the correct positions in the file. The templates in the API provide instantiations for several I/O methods: `std::ifstream`, `int` file handles obtained from POSIX `_open`, `FILE` pointers and on Windows for native `HANDLE`s. On Windows, `wchar_t` variants are also available. The following sample code illustrates how to use the low-level API:

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
        mmpld::read_list_header(hFile, listHeader);

        // Compute the number of bytes required for all particles.
        auto rem = static_cast<size_t>(listHeader.particles)
            * mmpld::get_stride<size_t>(listHeader);

        // Allocate the buffer for all particles.
        particles.resize(rem);

        // Initialise the destination pointer.
        auto ptr = particles.data();

        // Read until we have all particles in memory.
        while (rem > 0) {
            DWORD cnt = 0;
            if (!::ReadFile(file, ptr, rem, &cnt, nullptr)) { /* Handle rror. */ }
            ptr += cnt;
            rem -= cnt;
        }

        /* Do something with the content of 'particles'. */
    } /* end for (decltype(frameHeader.lists) j = 0; ... */
} /* end for (decltype(fileHeader.frames) i = 0; ... */

::CloseHandle(hFile);
```

## The mmpld::file class

The `mmpld::file` class is a stateful wrapper around the low-level API, which allows you to parse through an MMPLD file one frame after another. The `mmpld::file` class is responsible for all I/O operations and keeps track of the seek table and the file pointer for you. The following code illustrates how to iterate over all particles in a file using this abstraction layer:

```C++
#include "mmpld.h"

// Open the file and prepare the first frame.
mmpld::file<HANDLE, TCHAR> file(_T("test.mmpld"));

// Iterate over all frames in the file. Note that if you are only
// interested in the first one, you can use it right away without calling
// file.open_frame again, because the first frame is opened in the ctor.
for (mmpld::file::frame_number_type f = 0; f < file.frames; ++f) {
    file.open_frame(f);


}
```