#include "ndk_compat.h"
#include <camera/NdkCameraManager.h>
#include <camera/NdkCameraMetadata.h>

#include <dlfcn.h>
#include <stdio.h>
#include <hybris/common/binding.h>

/* Resolve an NDK function into a correctly typed pointer named p_<name>. */
#define LOAD(lib, name)                                                    \
    __typeof__(&name) p_##name = (__typeof__(&name))android_dlsym(lib, #name); \
    if (!p_##name) {                                                       \
        fprintf(stderr, "missing symbol %s\n", #name);                     \
        return 1;                                                          \
    }

int main(void)
{
    void *cam = android_dlopen("libcamera2ndk.so", RTLD_LAZY);
    if (!cam) {
        fprintf(stderr, "libcamera2ndk.so: %s\n", android_dlerror());
        return 1;
    }

    /* Camera callbacks and replies arrive over binder; an Android app gets
     * a thread pool from the runtime, we have to start one. */
    void *binder = android_dlopen("libbinder_ndk.so", RTLD_LAZY);
    void (*start_pool)(void) =
        binder ? (void (*)(void))android_dlsym(binder, "ABinderProcess_startThreadPool") : NULL;
    if (!start_pool) {
        fprintf(stderr, "libbinder_ndk.so: no ABinderProcess_startThreadPool\n");
        return 1;
    }
    start_pool();

    LOAD(cam, ACameraManager_create);
    LOAD(cam, ACameraManager_getCameraIdList);
    LOAD(cam, ACameraManager_getCameraCharacteristics);
    LOAD(cam, ACameraMetadata_getConstEntry);
    LOAD(cam, ACameraMetadata_free);

    ACameraManager *mgr = p_ACameraManager_create();
    ACameraIdList *ids = NULL;
    camera_status_t st = p_ACameraManager_getCameraIdList(mgr, &ids);
    if (st != ACAMERA_OK) {
        fprintf(stderr, "getCameraIdList failed: %d\n", st);
        return 1;
    }

    printf("%d camera(s)\n", ids->numCameras);
    for (int i = 0; i < ids->numCameras; i++) {
        ACameraMetadata *chars = NULL;
        if (p_ACameraManager_getCameraCharacteristics(mgr, ids->cameraIds[i], &chars) != ACAMERA_OK)
            continue;

        ACameraMetadata_const_entry facing = { 0 }, level = { 0 };
        p_ACameraMetadata_getConstEntry(chars, ACAMERA_LENS_FACING, &facing);
        p_ACameraMetadata_getConstEntry(chars, ACAMERA_INFO_SUPPORTED_HARDWARE_LEVEL, &level);

        /* raw enum values for now: facing 0=front 1=back 2=external,
         * level 0=LIMITED 1=FULL 2=LEGACY 3=LEVEL_3 4=EXTERNAL */
        printf("camera %s: facing=%d hardware_level=%d\n", ids->cameraIds[i],
               facing.count ? facing.data.u8[0] : -1, level.count ? level.data.u8[0] : -1);
        p_ACameraMetadata_free(chars);
    }
    return 0;
}
