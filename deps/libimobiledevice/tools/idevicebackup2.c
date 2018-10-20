/*
 * idevicebackup2.c
 * Command line interface to use the device's backup and restore service
 *
 * Copyright (c) 2009-2010 Martin Szulecki All Rights Reserved.
 * Copyright (c) 2010      Nikias Bassen All Rights Reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#ifndef _MSC_VER
#include <unistd.h>
#include <libgen.h>
#else 
//#include "msc_config.h"
#endif

#include <ctype.h>
#include <time.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include <libimobiledevice/libimobiledevice.h>
#include <libimobiledevice/lockdown.h>
#include <libimobiledevice/mobilebackup2.h>
#include <libimobiledevice/notification_proxy.h>
#include <libimobiledevice/afc.h>
#include <libimobiledevice/installation_proxy.h>
#include <libimobiledevice/sbservices.h>
#include "common/utils.h"

#include <endianness.h>

#define LOCK_ATTEMPTS 50
#define LOCK_WAIT 200000

#ifdef WIN32
#include <windows.h>
#include <conio.h>
#define sleep(x) Sleep(x*1000)
#define __func__ __FUNCTION__
#else
#include <termios.h>
#include <sys/statvfs.h>
#endif
#include <sys/stat.h>
#include "usbmuxd.h"
int strncasecmp(const char* s1, const char* s2, size_t c)
{
    return _strnicmp(s1, s2, c);
}

int strcasecmp(const char* s1, const char* s2)
{
    return _stricmp(s1, s2);
}

int vasprintf(char **PTR, const char *TEMPLATE, va_list AP)
{
    int res;
    char buf[16];
    res = vsnprintf(buf, 16, TEMPLATE, AP);
    if (res > 0)
    {
        *PTR = (char*)malloc(res + 1);
        res = vsnprintf(*PTR, res + 1, TEMPLATE, AP);
    }
    return res;
}

int asprintf(char **PTR, const char *TEMPLATE, ...)
{
    int res;
    va_list AP;
    va_start(AP, TEMPLATE);
    res = vasprintf(PTR, TEMPLATE, AP);
    va_end(AP);
    return res;
}


/*
char *stpncpy(char *dest, const char *src, size_t len)
{
    size_t n = strlen(src);
    if (n > len)
        n = len;
    return strncpy(dest, src, len) + n;
    //return ptr + n;
}

char* stpncpy(char *dst, const char *src, size_t len)
{
    size_t n = strlen(src);
    if (n > len)
        n = len;
    return strncpy(dst, src, len) + n;
}
*/
int vsnprintf(char *outBuf, size_t size, const char *format, va_list ap)
{
    int count = -1;

    if (size != 0)
        count = _vsnprintf_s(outBuf, size, _TRUNCATE, format, ap);
    if (count == -1)
        count = _vscprintf(format, ap);

    return count;
}

int snprintf(char *outBuf, size_t size, const char *format, ...)
{
    int count;
    va_list ap;

    va_start(ap, format);
    count = vsnprintf(outBuf, size, format, ap);
    va_end(ap);

    return count;
}


#define CODE_SUCCESS 0x00
#define CODE_ERROR_LOCAL 0x06
#define CODE_ERROR_REMOTE 0x0b
#define CODE_FILE_DATA 0x0c

static int verbose = 1;
static int quit_flag = 0;

#define PRINT_VERBOSE(min_level, ...) if (verbose >= min_level) { printf(__VA_ARGS__); };

static void print_usage(int argc, char **argv)
{
    char *name = NULL;

    name = strrchr(argv[0], '/');
    printf("Usage: %s [OPTIONS]\n", (name ? name + 1 : argv[0]));
    printf("Shows information about what devices are connected.\n\n");
    printf("  -d, --debug\t\tenable communication debugging\n");
    printf("  -u, --usb\t\tshow usb connected devices\n");
    printf("  -w, --wifi\t\tshow wifi connected devices\n");
    printf("  -p, --pretty\t\toutput in human readable\n");
    printf("  -h, --help\t\tprints usage information\n");
    printf("\n");
    printf("Homepage: <" PACKAGE_URL ">\n");
}

int main(int argc, char** argv)
{
    printf("Welcome!");
    idevice_t device = NULL;
    idevice_error_t ret = IDEVICE_E_UNKNOWN_ERROR;
    int i;

    int show_usb_connected_devices = 0;
    int show_wifi_connected_devices = 0;

    /* parse cmdline args */
    for (i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "-d") || !strcmp(argv[i], "--debug"))
        {
            idevice_set_debug_level(1);
            continue;
        }
        if (!strcmp(argv[i], "-u") || !strcmp(argv[i], "--usb"))
        {
            show_usb_connected_devices = 1;
            continue;
        }
        if (!strcmp(argv[i], "-w") || !strcmp(argv[i], "--wifi"))
        {
            show_wifi_connected_devices = 1;
            continue;
        }
        else if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help"))
        {
            print_usage(argc, argv);
            return 0;
        }
        else
        {
            print_usage(argc, argv);
            return 0;
        }
    }

    if (show_usb_connected_devices == 0 && show_wifi_connected_devices == 0)
    {
        show_usb_connected_devices = 1;
        show_wifi_connected_devices = 1;
    }

    usbmuxd_device_info_t *dev_list = NULL;

    ret = usbmuxd_get_device_list(&dev_list);
    if (ret < 0)
    {
        printf("%s: couldn't get device list from usbmuxd (%d)\n", __func__, ret);
        return -1;
    }
        for (i = 0; dev_list[i].handle > 0; i++)
        {
            printf("%s -> %s\n", dev_list[i].conn_type == CONNECTION_TYPE_NETWORK ? "Network" : "USB", dev_list[i].udid);
        }
    
    
    idevice_free(device);
    free(dev_list);

    return 0;
}