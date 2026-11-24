/*
 * Lets the AOSP Camera2 NDK headers compile with a plain glibc toolchain.
 */
#ifndef HC2_NDK_COMPAT_H
#define HC2_NDK_COMPAT_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/cdefs.h>

/* Bionic availability annotations: no-ops outside Android. */
#ifndef __INTRODUCED_IN
#define __INTRODUCED_IN(api_level)
#endif
#ifndef __DEPRECATED_IN
#define __DEPRECATED_IN(api_level, ...)
#endif
#ifndef __REMOVED_IN
#define __REMOVED_IN(api_level, ...)
#endif
#ifndef __ANDROID_API__
#define __ANDROID_API__ 10000 /* expose every declaration */
#endif

/* Clang nullability qualifiers: no-ops for GCC. */
#if !defined(__clang__)
#ifndef _Nullable
#define _Nullable
#endif
#ifndef _Nonnull
#define _Nonnull
#endif
#ifndef _Null_unspecified
#define _Null_unspecified
#endif
#endif

#endif /* HC2_NDK_COMPAT_H */
