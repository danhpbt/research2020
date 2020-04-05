#include <jni.h>
#include "image_util.h"
#include "libyuv.h"
#include "BasicEffect.h"




using namespace libyuv;


void Java_com_xynotec_image_ImageUtil_YUV2ARGB(JNIEnv* env, jobject thiz, jbyteArray sData, jint sFormat, jint sRotation, jint sWidth, jint sHeight,
																							jintArray dData, jint dWidth, jint dHeight)
{
	jbyte* outYUV = env->GetByteArrayElements(sData, 0);
	jint* outRGB = env->GetIntArrayElements(dData, 0);

	decodeYUV420ARGB((unsigned char*)outYUV, sFormat, sRotation, sWidth, sHeight,
							outRGB, dWidth, dHeight);

	env->ReleaseByteArrayElements(sData, outYUV, JNI_ABORT);
	env->ReleaseIntArrayElements(dData, outRGB, JNI_ABORT);
}

void Java_com_xynotec_image_ImageUtil_GrayScale(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height)
{
	jint* outRGB = env->GetIntArrayElements(dataRGB, 0);

    Grayscale((BMP_ARGB*)outRGB, width, height);

	env->ReleaseIntArrayElements(dataRGB, outRGB, 0);
}
void Java_com_xynotec_image_ImageUtil_ColorFilter(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jint filter)
{
	jint* outRGB = env->GetIntArrayElements(dataRGB, 0);

	ColorFilter((BMP_ARGB*)outRGB, width, height, (COLOR_FILTER)filter);

	env->ReleaseIntArrayElements(dataRGB, outRGB, 0);
}

void Java_com_xynotec_image_ImageUtil_Gamma(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jdouble red, jdouble green, jdouble blue)
{
	jint* outRGB = env->GetIntArrayElements(dataRGB, 0);

	Gamma((BMP_ARGB*)outRGB, width, height, red, green, blue);

	env->ReleaseIntArrayElements(dataRGB, outRGB, 0);
}

void Java_com_xynotec_image_ImageUtil_Brightness(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jint brightness)
{
	jint* outRGB = env->GetIntArrayElements(dataRGB, 0);

	Brightness((BMP_ARGB*)outRGB, width, height, brightness);

	env->ReleaseIntArrayElements(dataRGB, outRGB, 0);
}

void Java_com_xynotec_image_ImageUtil_Contrast(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jdouble contrast)
{
	jint* outRGB = env->GetIntArrayElements(dataRGB, 0);

	Contrast((BMP_ARGB*)outRGB, width, height, contrast);

	env->ReleaseIntArrayElements(dataRGB, outRGB, 0);
}

void Java_com_xynotec_image_ImageUtil_Invert(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height)
{
	jint* outRGB = env->GetIntArrayElements(dataRGB, 0);

	Invert((BMP_ARGB*)outRGB, width, height);

	env->ReleaseIntArrayElements(dataRGB, outRGB, 0);
}

void Java_com_xynotec_image_ImageUtil_Smooth(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jint, jint weight)
{
	jint* outRGB = env->GetIntArrayElements(dataRGB, 0);

	Smooth((BMP_ARGB*)outRGB, width, height, weight);

	env->ReleaseIntArrayElements(dataRGB, outRGB, 0);
}

void Java_com_xynotec_image_ImageUtil_GaussianBlur(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jint weight)
{
	jint* outRGB = env->GetIntArrayElements(dataRGB, 0);

	GaussianBlur((BMP_ARGB*)outRGB, width, height, weight);

	env->ReleaseIntArrayElements(dataRGB, outRGB, 0);
}

void Java_com_xynotec_image_ImageUtil_MeanRemoval(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jint weight)
{
	jint* outRGB = env->GetIntArrayElements(dataRGB, 0);

	MeanRemoval((BMP_ARGB*)outRGB, width, height, weight);

	env->ReleaseIntArrayElements(dataRGB, outRGB, 0);
}

void Java_com_xynotec_image_ImageUtil_Sharpen(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jint weight)
{
	jint* outRGB = env->GetIntArrayElements(dataRGB, 0);

	Sharpen((BMP_ARGB*)outRGB, width, height, weight);

	env->ReleaseIntArrayElements(dataRGB, outRGB, 0);
}

void Java_com_xynotec_image_ImageUtil_EmbossLaplacian(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height)
{
	jint* outRGB = env->GetIntArrayElements(dataRGB, 0);

	EmbossLaplacian((BMP_ARGB*)outRGB, width, height);

	env->ReleaseIntArrayElements(dataRGB, outRGB, 0);
}

void Java_com_xynotec_image_ImageUtil_EdgeDetectQuick(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height)
{
	jint* outRGB = env->GetIntArrayElements(dataRGB, 0);

	EdgeDetectQuick((BMP_ARGB*)outRGB, width, height);

	env->ReleaseIntArrayElements(dataRGB, outRGB, 0);
}

void Java_com_xynotec_image_ImageUtil_Flip(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jboolean bHorz, jboolean bVert)
{
	jint* outRGB = env->GetIntArrayElements(dataRGB, 0);

	Flip((BMP_ARGB*)outRGB, width, height, bHorz, bVert);

	env->ReleaseIntArrayElements(dataRGB, outRGB, 0);
}

void Java_com_xynotec_image_ImageUtil_RandomJitter(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jshort degree)
{
	jint* outRGB = env->GetIntArrayElements(dataRGB, 0);

	RandomJitter((BMP_ARGB*)outRGB, width, height, degree);

	env->ReleaseIntArrayElements(dataRGB, outRGB, 0);
}

void Java_com_xynotec_image_ImageUtil_Swirl(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jdouble degree, jboolean bSmoothing)
{
	jint* outRGB = env->GetIntArrayElements(dataRGB, 0);

	Swirl((BMP_ARGB*)outRGB, width, height, degree, bSmoothing);

	env->ReleaseIntArrayElements(dataRGB, outRGB, 0);
}

void Java_com_xynotec_image_ImageUtil_Sphere(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jboolean bSmoothing)
{
	jint* outRGB = env->GetIntArrayElements(dataRGB, 0);

	Sphere((BMP_ARGB*)outRGB, width, height, bSmoothing);

	env->ReleaseIntArrayElements(dataRGB, outRGB, 0);
}

void Java_com_xynotec_image_ImageUtil_TimeWarp(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jbyte factor, jboolean bSmoothing)
{
	jint* outRGB = env->GetIntArrayElements(dataRGB, 0);

	TimeWarp((BMP_ARGB*)outRGB, width, height, factor, bSmoothing);

	env->ReleaseIntArrayElements(dataRGB, outRGB, 0);
}

void Java_com_xynotec_image_ImageUtil_Moire(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jdouble degree)
{
	jint* outRGB = env->GetIntArrayElements(dataRGB, 0);

	Moire((BMP_ARGB*)outRGB, width, height, degree);

	env->ReleaseIntArrayElements(dataRGB, outRGB, 0);

}

void Java_com_xynotec_image_ImageUtil_Water(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jshort nWave, jboolean bSmoothing)
{
	jint* outRGB = env->GetIntArrayElements(dataRGB, 0);

	Water((BMP_ARGB*)outRGB, width, height, nWave, bSmoothing);

	env->ReleaseIntArrayElements(dataRGB, outRGB, 0);
}

void Java_com_xynotec_image_ImageUtil_Pixelate(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jshort pixel, jboolean  bGrid)
{
	jint* outRGB = env->GetIntArrayElements(dataRGB, 0);

	Pixelate((BMP_ARGB*)outRGB, width, height, pixel, bGrid);

	env->ReleaseIntArrayElements(dataRGB, outRGB, 0);
}

void Java_com_xynotec_image_ImageUtil_FishEye(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height, jdouble iCurvature, jboolean bInverse, jboolean bSmoothing)
{
	jint* outRGB = env->GetIntArrayElements(dataRGB, 0);

	FishEye((BMP_ARGB*)outRGB, width, height, iCurvature, bInverse, bSmoothing);

	env->ReleaseIntArrayElements(dataRGB, outRGB, 0);
}

//void LiquidRender(byte* surface);
//void Agg2DOverlayImage(System::Drawing::Bitmap^ overlayImg);
void Java_com_xynotec_image_ImageUtil_BokehEffects(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height)
{
	jint* outRGB = env->GetIntArrayElements(dataRGB, 0);

	BokehEffect_Test((BMP_ARGB*)outRGB, width, height);

	env->ReleaseIntArrayElements(dataRGB, outRGB, 0);
}

/////////////////////////////////////////////////////////
void decodeYUV420ARGB(unsigned char* sData, int sFormat, int sRotation, int sWidth, int sHeight,
		int* dData, int& dWidth, int& dHeight)
{
	RotationMode rotation = RotationMode::kRotate0;

	if (sRotation == 0)
	{
		dWidth = sWidth;
		dHeight = sHeight;
		rotation = RotationMode::kRotate0;
	}
	else if (sRotation == 90)
	{
		dWidth = sHeight;
		dHeight = sWidth;
		rotation = RotationMode::kRotate90;
	}
	else if (sRotation == 180)
	{
		dWidth = sWidth;
		dHeight = sHeight;
		rotation = RotationMode::kRotate180;
	}
	else if (sRotation == 270)
	{
		dWidth = sHeight;
		dHeight = sWidth;
		rotation = RotationMode::kRotate270;
	}

	uint32_t fourcc;
	if (sFormat == ANDROID_IMAGEFROMAT_NV21)
		fourcc = FourCC::FOURCC_NV21;
	else if (sFormat == ANDROID_IMAGEFROMAT_YV12)
		fourcc = FourCC::FOURCC_I420;
	else
		return;// incorrect format

	int res = ConvertToARGB(/*const uint8_t * yuv420sp*/ sData,
			/*size_t sample_size*/ sWidth*sHeight,
			/*uint8_t * dst_argb*/ (uint8_t *)dData,
			/*int dst_stride_argb*/ dWidth*4,
			/*int crop_x*/ 0,
			/*int crop_y*/ 0,
			/*int src_width*/ sWidth,
			/*int src_height*/ sHeight,
			/*int crop_width*/ sWidth,
			/*int crop_height*/ sHeight,
			/*enum RotationMode rotation*/ rotation,
			/*uint32_t fourcc*/FourCC::FOURCC_NV21);
}
