#include <jni.h>
#include "simplecam.h"
#include "libyuv.h"

namespace libyuv;

void Java_com_xynotec_image_ImageUtil_YUV2ARGB(JNIEnv* env, jobject thiz, jbyteArray sData, jint sFormat, jint sRotation, jint sWidth, jint sHeight,
																							jintArray dData, jint dWidth, jint dHeight);
{
	jbyte* outYUV = env->GetByteArrayElements(sData, 0);
	jint* outRGB = env->GetIntArrayElements(dData, 0);
	
	decodeYUV420ARGB(outYUV, sFormat, sRotation, sWidth, sHeight,
							outRGB, dWidth, dHeight);
	
	env->ReleaseByteArrayElements(sData, outYUV, JNI_ABORT);
	env->ReleaseIntArrayElements(dData, outRGB, JNI_ABORT);
}

void Java_com_xynotec_image_ImageUtil_GrayScale(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height)
{
	jint* outRGB = env->GetIntArrayElements(dataRGB, 0);
	
	Grayscale(outRGB, width, height);
	
	env->ReleaseIntArrayElements(dataRGB, outRGB, 0);
}

void decodeYUV420ARGB(unsigned char* sData, int sFormat, int sRotation, int sWidth, int sHeight, int* dData, int& dWidth, int& dHeight)
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
		fourcc = libyuv::FourCC::FOURCC_NV21;
	else if (sFormat == ANDROID_IMAGEFROMAT_YV12)
		fourcc = libyuv::FourCC::FOURCC_I420;
	else
		return;// incorrect format

	int res = libyuv::ConvertToARGB(/*const uint8_t * yuv420sp*/ sData,
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
			/*uint32_t fourcc*/libyuv::FourCC::FOURCC_NV21);
}

void Grayscale(int *data, int width, int height)
{
	unsigned char* image = (unsigned char*)data;
	int length = width * height;
	unsigned char gray = 0;
	int i;
	for (i = 0; i < length; i++, image += 4)
	{
		gray = GRAY_FROM_RGB(*image, *(image + 1), *(image + 2));
		
		*image = gray;
		*(image + 1) = gray;
		*(image + 2) = gray;
	}

	image = 0;
}

