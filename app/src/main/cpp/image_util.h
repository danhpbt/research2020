#include <jni.h>
#include <android/log.h>
#include <stdlib.h>

#ifdef __cplusplus

#define ANDROID_IMAGEFROMAT_NV21			17
#define ANDROID_IMAGEFROMAT_YV12			842094169

void decodeYUV420ARGB(unsigned char* sData, int sFormat, int sRotation, int sWidth, int sHeight, int* dData, int& dWidth, int& dHeight);

extern "C"
{
#endif
JNIEXPORT void JNICALL Java_com_xynotec_image_ImageUtil_YUV2ARGB(JNIEnv* env, jobject thiz, jbyteArray sData, jint sFormat, jint sRotation, jint sWidth, jint sHeight,
																							jintArray dData, jint dWidth, jint dHeight);
 
#ifdef __cplusplus
}
#endif