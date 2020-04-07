#include <jni.h>
#include <android/log.h>
#include <stdlib.h>
#include "Typedef.h"

#define ANDROID_IMAGEFROMAT_NV21			17
#define ANDROID_IMAGEFROMAT_YV12			842094169

#ifdef __cplusplus

void decodeYUV420ARGB(unsigned char* sData, int sFormat, int sRotation, int sWidth, int sHeight,
		int* dData, int& dWidth, int& dHeight);
extern "C"
{
#endif

JNIEXPORT void JNICALL Java_com_xynotec_research2020_MainApplication_loadAssetManager(JNIEnv *env, jobject thiz, jobject assetManager);
JNIEXPORT void JNICALL Java_com_xynotec_image_ImageUtil_YUV2ARGB(JNIEnv* env, jobject thiz, jbyteArray sData, jint sFormat, jint sRotation, jint sWidth, jint sHeight,
																							jintArray dData, jint dWidth, jint dHeight);
JNIEXPORT void JNICALL Java_com_xynotec_image_ImageUtil_AntiGrain(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height);
JNIEXPORT void JNICALL Java_com_xynotec_image_ImageUtil_GrayScale(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height);
JNIEXPORT void JNICALL Java_com_xynotec_image_ImageUtil_ColorFilter(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jint filter);
JNIEXPORT void JNICALL Java_com_xynotec_image_ImageUtil_Gamma(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jdouble red, jdouble green, jdouble blue);
JNIEXPORT void JNICALL Java_com_xynotec_image_ImageUtil_Brightness(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jint brightness);
JNIEXPORT void JNICALL Java_com_xynotec_image_ImageUtil_Contrast(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jdouble contrast);
JNIEXPORT void JNICALL Java_com_xynotec_image_ImageUtil_Invert(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height);
JNIEXPORT void JNICALL Java_com_xynotec_image_ImageUtil_Smooth(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jint, jint weight);
JNIEXPORT void JNICALL Java_com_xynotec_image_ImageUtil_GaussianBlur(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jint weight);
JNIEXPORT void JNICALL Java_com_xynotec_image_ImageUtil_MeanRemoval(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jint weight);
JNIEXPORT void JNICALL Java_com_xynotec_image_ImageUtil_Sharpen(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jint weight);
JNIEXPORT void JNICALL Java_com_xynotec_image_ImageUtil_EmbossLaplacian(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height);
JNIEXPORT void JNICALL Java_com_xynotec_image_ImageUtil_EdgeDetectQuick(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height);
JNIEXPORT void JNICALL Java_com_xynotec_image_ImageUtil_Flip(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jboolean bHorz, jboolean bVert);
JNIEXPORT void JNICALL Java_com_xynotec_image_ImageUtil_RandomJitter(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jshort degree);
JNIEXPORT void JNICALL Java_com_xynotec_image_ImageUtil_Swirl(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jdouble degree, jboolean bSmoothing);
JNIEXPORT void JNICALL Java_com_xynotec_image_ImageUtil_Sphere(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jboolean bSmoothing);
JNIEXPORT void JNICALL Java_com_xynotec_image_ImageUtil_TimeWarp(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jbyte factor, jboolean bSmoothing);
JNIEXPORT void JNICALL Java_com_xynotec_image_ImageUtil_Moire(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jdouble degree);
JNIEXPORT void JNICALL Java_com_xynotec_image_ImageUtil_Water(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jshort nWave, jboolean bSmoothing);
JNIEXPORT void JNICALL Java_com_xynotec_image_ImageUtil_Pixelate(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jshort pixel, jboolean  bGrid);
JNIEXPORT void JNICALL Java_com_xynotec_image_ImageUtil_FishEye(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jdouble iCurvature, jboolean bInverse, jboolean bSmoothing);
//void LiquidRender(byte* surface);
//void Agg2DOverlayImage(System::Drawing::Bitmap^ overlayImg);
JNIEXPORT void JNICALL Java_com_xynotec_image_ImageUtil_BokehEffects(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height);

JNIEXPORT void JNICALL Java_com_xynotec_image_ImageUtil_Tube(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jdouble m_iCurvature, jboolean m_bInverse, jboolean bSmoothing);
JNIEXPORT void JNICALL Java_com_xynotec_image_ImageUtil_MyTube(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jdouble m_iCurvature, jboolean m_bInverse, jboolean bSmoothing);
JNIEXPORT void JNICALL Java_com_xynotec_image_ImageUtil_InkSketch(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jint inkOutline, jint coloring);
JNIEXPORT void JNICALL Java_com_xynotec_image_ImageUtil_EdgeDetector(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height);
JNIEXPORT void JNICALL Java_com_xynotec_image_ImageUtil_EdgeMaster(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jint color, jint amount);
JNIEXPORT void JNICALL Java_com_xynotec_image_ImageUtil_ToonEffect(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height);
JNIEXPORT void JNICALL Java_com_xynotec_image_ImageUtil_OilEffect(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jint range, jint levels);//java
JNIEXPORT void JNICALL Java_com_xynotec_image_ImageUtil_PastelEffect(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jint range, jint levels);//paint.net
JNIEXPORT void JNICALL Java_com_xynotec_image_ImageUtil_DreamEffect(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jint focus);//paint.net
JNIEXPORT void JNICALL Java_com_xynotec_image_ImageUtil_SmearEffect(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height);
JNIEXPORT void JNICALL Java_com_xynotec_image_ImageUtil_SmearEffectPDN(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jint shape, jfloat angle, jfloat density,
							jfloat scatter, jint distance, jfloat mix, jboolean background);
JNIEXPORT void JNICALL Java_com_xynotec_image_ImageUtil_GaussianBlurPDN(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jint radius);
JNIEXPORT void JNICALL Java_com_xynotec_image_ImageUtil_GlowEffectPDN(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jint radius, jint brightness, jint contrast);
JNIEXPORT void JNICALL Java_com_xynotec_image_ImageUtil_JitterEffectPDN(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height,
                                                                         jint maxDistance, jint minDistance, jint Width, jint spacing,
                                                                         jint angleDeg, jint edge);
JNIEXPORT void JNICALL Java_com_xynotec_image_ImageUtil_StichEffectPDN(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height,
                                jint distance, jint nWidth, jint angle1, jint angle2, jboolean Wrap);

#ifdef __cplusplus
}
#endif