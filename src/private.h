#ifndef PRIVATE_H
#define PRIVATE_H

#include "ndk_compat.h"
#include <camera/NdkCameraManager.h>
#include <camera/NdkCameraMetadata.h>

#define EXPORT __attribute__((visibility("default"))) // Only EXPORT visible

/* One function pointer per NDK function, named after it and typed from
 * the NDK header's declaration. Filled by loader.c. NULL if the device
 * does not provide that function. */
struct ndk_table {
#define NDK_SYMBOL(lib, name) __typeof__(&name) name;
#include "ndk_symbols.h"
#undef NDK_SYMBOL
};

extern struct ndk_table ndk;

/* Loads the device libraries once, on first use.*/
void ndk_ensure_loaded(void);

#endif /* PRIVATE_H */