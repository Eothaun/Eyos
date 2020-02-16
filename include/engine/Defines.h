#pragma once
// std includes:
#include <cassert>

// Generic helper definitions for shared library support
#if defined _WIN32 || defined __CYGWIN__
#define DllImport __declspec(dllimport)
#define DllExport __declspec(dllexport)
#define EYOS_API_DLL_LOCAL
#else
#if __GNUC__ >= 4
#define DllImport __attribute__((visibility("default")))
#define DllExport __attribute__((visibility("default")))
#define EYOS_API_DLL_LOCAL __attribute__((visibility("hidden")))
#else
#define DllImport
#define DllExport
#define EYOS_API_DLL_LOCAL
#endif
#endif

#ifdef BUILD_SHARED_LIBS
#define EYOS_API DllExport
#else
#define EYOS_API DllImport
#endif

#define assertm(exp, msg) assert(((void)msg, exp))