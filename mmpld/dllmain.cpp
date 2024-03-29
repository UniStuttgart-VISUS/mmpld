// <copyright file="dllmain.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2018 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#if defined(_WIN32)
#include <Windows.h>

#include "mmpld.h"


/// <summary>
/// Entry point of the DLL.
/// </summary>
BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID reserved) {

    switch (reason) {
        case DLL_PROCESS_ATTACH:
            ::DisableThreadLibraryCalls(hModule);

        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}
#endif /* defined(_WIN32) */
