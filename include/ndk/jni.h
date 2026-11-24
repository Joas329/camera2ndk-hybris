/*
 * Minimal JNI type stub. Only ACameraMetadata_fromCameraMetadata() uses JNI
 * and it is not available outside an Android runtime.
 */
#ifndef HC2_JNI_STUB_H
#define HC2_JNI_STUB_H

typedef struct _hc2_jobject *jobject;
#ifdef __cplusplus
struct _JNIEnv;
typedef _JNIEnv JNIEnv;
#else
struct JNINativeInterface;
typedef const struct JNINativeInterface *JNIEnv;
#endif

#endif /* HC2_JNI_STUB_H */
