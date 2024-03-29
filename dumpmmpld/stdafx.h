// <copyright file="stdafx.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2018 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "targetver.h"

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include <tchar.h>
#include <Windows.h>

#include "mmpld.h"

#if (defined(UNICODE) || defined(_UNICODE))
#define tcout wcout
#define tcerr wcerr
#else /* (defined(UNICODE) || defined(_UNICODE)) */
#define tcout cout
#define tcerr cerr
#endif /* (defined(UNICODE) || defined(_UNICODE)) */
