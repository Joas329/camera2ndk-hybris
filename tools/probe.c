#include "ndk_compat.h"
#include <camera/NdkCameraManager.h>
#include <camera/NdkCameraMetadata.h>

#include <stdio.h>

int main(void)
{
    ACameraManager *mgr = ACameraManager_create();
    if (!mgr) {
        fprintf(stderr, "ACameraManager_create failed (run with CAMERA2NDK_HYBRIS_DEBUG=1)\n");
        return 1;
    }

    ACameraIdList *ids = NULL;
    camera_status_t st = ACameraManager_getCameraIdList(mgr, &ids);
    if (st != ACAMERA_OK) {
        fprintf(stderr, "getCameraIdList failed: %d\n", st);
        return 1;
    }

    printf("%d camera(s)\n", ids->numCameras);
    for (int i = 0; i < ids->numCameras; i++) {
        ACameraMetadata *chars = NULL;
        if (ACameraManager_getCameraCharacteristics(mgr, ids->cameraIds[i], &chars) != ACAMERA_OK)
            continue;

        ACameraMetadata_const_entry facing = { 0 }, level = { 0 };
        ACameraMetadata_getConstEntry(chars, ACAMERA_LENS_FACING, &facing);
        ACameraMetadata_getConstEntry(chars, ACAMERA_INFO_SUPPORTED_HARDWARE_LEVEL, &level);

        /* raw values until names are added:
         * facing 0=front 1=back 2=external
         * level  0=LIMITED 1=FULL 2=LEGACY 3=LEVEL_3 4=EXTERNAL */
        printf("camera %s: facing=%d hardware_level=%d\n", ids->cameraIds[i], facing.count ? facing.data.u8[0] : -1, level.count ? level.data.u8[0] : -1);
        ACameraMetadata_free(chars);
    }

    ACameraManager_deleteCameraIdList(ids);
    ACameraManager_delete(mgr);
    return 0;
}
