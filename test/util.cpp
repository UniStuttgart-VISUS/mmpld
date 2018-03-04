/// <copyright file="util.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
/// Copyright © 2018 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
/// </copyright>
/// <author>Christoph Müller</author>

#include "stdafx.h"
#include "util.h"


void SetMmpldWorkingDirectory(void) {
    // https://social.msdn.microsoft.com/Forums/vstudio/en-US/cc60ce12-f0aa-4f7d-88ab-8f17efbc6853/cppunittestframework-find-path-to-solutiondir-from-test-method?forum=vcgeneral
    static TCHAR c;
    HMODULE hModule;
    TCHAR path[_MAX_PATH + 1];
    ::GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, &c, &hModule);
    ::GetModuleFileName(hModule, path, sizeof(path) / sizeof(*path));
    *::_tcsrchr(path, '\\') = 0;
    ::SetCurrentDirectory(path);
}
