#pragma once
#ifdef _MSC_VER
#define inline __inline
#define WIN32_LEAN_AND_MEAN
#define _CRT_NONSTDC_NO_DEPRECATE
#define __func__ __FUNCTION__
#define strncasecmp _strnicmp
#define strcasecmp _stricmp
#define PACKAGE_STRING "libusbmuxd 1.1.0"
#endif
