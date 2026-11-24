/*
 * The exported NDK functions. Each one loads the device libraries if
 * needed, then calls the real function, or returns an error if the
 * device does not have it.
 */
#include "private.h"

EXPORT ACameraManager *ACameraManager_create(void)
{
    ndk_ensure_loaded();
    if (ndk.ACameraManager_create)
    {
        return ndk.ACameraManager_create();
    }
    else
    {
        return NULL;
    }
}

EXPORT void ACameraManager_delete(ACameraManager *manager)
{
    ndk_ensure_loaded();

    if (ndk.ACameraManager_delete)
        ndk.ACameraManager_delete(manager);
}

EXPORT camera_status_t ACameraManager_getCameraIdList(ACameraManager *manager, ACameraIdList **list)
{
    ndk_ensure_loaded();

    if (ndk.ACameraManager_getCameraIdList != NULL)
    {
        return ndk.ACameraManager_getCameraIdList(manager, list);
    }
    else
    {
        return ACAMERA_ERROR_UNSUPPORTED_OPERATION;
    }
}

EXPORT void ACameraManager_deleteCameraIdList(ACameraIdList *list)
{
    ndk_ensure_loaded();

    if (ndk.ACameraManager_deleteCameraIdList)
        ndk.ACameraManager_deleteCameraIdList(list);
}

EXPORT camera_status_t ACameraManager_getCameraCharacteristics(ACameraManager *manager, const char *camera_id, ACameraMetadata **characteristics)
{
    ndk_ensure_loaded();

    if (ndk.ACameraManager_getCameraCharacteristics)
    {
        ndk.ACameraManager_getCameraCharacteristics(manager, camera_id, characteristics);
    }
    else
    {
        ACAMERA_ERROR_UNSUPPORTED_OPERATION;
    }
}

EXPORT camera_status_t ACameraMetadata_getConstEntry(const ACameraMetadata *metadata, uint32_t tag, ACameraMetadata_const_entry *entry)
{
    ndk_ensure_loaded();

    if (ndk.ACameraMetadata_getConstEntry)
    {
        return ndk.ACameraMetadata_getConstEntry(metadata, tag, entry);
    }
    else 
    {
        return ACAMERA_ERROR_UNSUPPORTED_OPERATION;
    }
}

EXPORT void ACameraMetadata_free(ACameraMetadata *metadata)
{
    ndk_ensure_loaded();
    if (ndk.ACameraMetadata_free)
        ndk.ACameraMetadata_free(metadata);
}