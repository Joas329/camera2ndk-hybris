/*
 * The NDK functions this library forwards, one line each:
 *   NDK_SYMBOL(library, function)
 */

NDK_SYMBOL(camera, ACameraManager_create)
NDK_SYMBOL(camera, ACameraManager_delete)
NDK_SYMBOL(camera, ACameraManager_getCameraIdList)
NDK_SYMBOL(camera, ACameraManager_deleteCameraIdList)
NDK_SYMBOL(camera, ACameraManager_getCameraCharacteristics)
NDK_SYMBOL(camera, ACameraMetadata_getConstEntry)
NDK_SYMBOL(camera, ACameraMetadata_free)