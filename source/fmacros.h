#ifndef FMACRO_H
#define FMACRO_H

#define _BSD_SOURCE

#if defined(__linux__)
#define _GNU_SOURCE
#define _DEFAULT_SOURCE
#endif

#if defined(__linux__) || defined(__OpenBSD__)
#define _XOPEN_SOURCE 700
/*
 * On NetBSD, _XOPEN_SOURCE undefines _NETBSD_SOURCE and
 * thus hides inet_aton etc.
 */
#elif !defined(__NetBSD__)
#define _XOPEN_SOURCE
#endif

#endif
