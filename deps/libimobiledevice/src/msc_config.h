#pragma once
#ifdef _MSC_VER
#define inline __inline
#define WIN32_LEAN_AND_MEAN
#define _CRT_NONSTDC_NO_DEPRECATE
#define __func__ __FUNCTION__
#define strncasecmp _strnicmp
#define strcasecmp _stricmp
#ifndef PACKAGE_STRING
#define PACKAGE_STRING "libimobiledevice 1.1.0"
#endif
#include <windows.h>
#endif
