/*
 * Opens the device's libcamera2ndk.so through libhybris, resolves the NDK
 * functions listed in ndk_symbols.h, and starts a binder thread pool.
 * Runs once, the first time any forwarded function is called.
 */
#include "private.h"

#include <dlfcn.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <hybris/common/binding.h>

struct ndk_table ndk;

static pthread_once_t load_once = PTHREAD_ONCE_INIT;

static void start_binder_thread_pool(void)
{
    void *binder = android_dlopen("libbinder_ndk.so", RTLD_LAZY);

    void (*start)(void) = NULL;
    if (binder)
    {
        start = (void (*)(void))android_dlsym(binder, "ABinderProcess_startThreadPool");
    }

    if (!start) {
        fprintf(stderr, "camera2ndk-hybris: cannot start binder thread pool\n");
        return;
    }
    start();
}

static void load(void)
{
    bool debug = getenv("CAMERA2NDK_HYBRIS_DEBUG") != NULL;

    void *camera = android_dlopen("libcamera2ndk.so", RTLD_LAZY);

    if (!camera) {
        fprintf(stderr, "camera2ndk-hybris: cannot open libcamera2ndk.so: %s\n", android_dlerror());
        return;
    }

    ndk.ACameraManager_create = (__typeof__(&ACameraManager_create))android_dlsym(camera, "ACameraManager_create");
    ndk.ACameraManager_delete = (__typeof__(&ACameraManager_delete))android_dlsym(camera, "ACameraManager_delete");
    ndk.ACameraManager_getCameraIdList = (__typeof__(&ACameraManager_getCameraIdList))android_dlsym(camera, "ACameraManager_getCameraIdList");
    ndk.ACameraManager_deleteCameraIdList = (__typeof__(&ACameraManager_deleteCameraIdList))android_dlsym(camera, "ACameraManager_deleteCameraIdList");
    ndk.ACameraManager_getCameraCharacteristics = (__typeof__(&ACameraManager_getCameraCharacteristics))android_dlsym(camera, "ACameraManager_getCameraCharacteristics");
    ndk.ACameraMetadata_getConstEntry = (__typeof__(&ACameraMetadata_getConstEntry))android_dlsym(camera, "ACameraMetadata_getConstEntry");
    ndk.ACameraMetadata_free = (__typeof__(&ACameraMetadata_free))android_dlsym(camera, "ACameraMetadata_free");

    if (debug) {
        fprintf(stderr, "camera2ndk-hybris: ACameraManager_create %s\n", ndk.ACameraManager_create ? "ok" : "MISSING");
    }

    start_binder_thread_pool();
}

void ndk_ensure_loaded(void)
{
    pthread_once(&load_once, load);
}