#include <jni.h>
#include <android/log.h>
#include <stdlib.h>

#ifdef __cplusplus

void decodeYUV420SP(int* rgb, unsigned char* yuv420sp, int width, int height);
void EdgeDetector(int *data, int width, int height);
void Grayscale(int *data, int width, int height);

extern "C"
{
#endif
JNIEXPORT void JNICALL Java_com_xynotec_camera_CameraOverlayView_YUV2RGB(JNIEnv* env, jobject thiz, jbyteArray dataYUV, jintArray dataRGB, jint width, jint height);
JNIEXPORT void JNICALL Java_com_xynotec_camera_CameraOverlayView_GrayScale(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height);
JNIEXPORT void JNICALL Java_com_xynotec_camera_CameraOverlayView_EdgeDetector(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height);
 
#ifdef __cplusplus
}
#endif