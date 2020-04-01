#include <jni.h>
#include "simplecam.h"

#ifndef GRAY_FROM_RGB
	#define GRAY_FROM_RGB(r, g, b) (unsigned char)((r*29 + g*150 + b*77 + 128)/256)
#endif

#define LUMINANCE(r, g ,b) (int)(299 * r + 580 * g + 110 * b)/1000


void Java_com_xynotec_camera_CameraOverlayView_YUV2RGB(JNIEnv* env, jobject thiz, jbyteArray dataYUV, jintArray dataRGB, jint width, jint height)
{
	jbyte* outYUV = env->GetByteArrayElements(dataYUV, 0);
	jint* outRGB = env->GetIntArrayElements(dataRGB, 0);
	
	decodeYUV420SP(outRGB, (unsigned char*) outYUV, width, height);
	
	env->ReleaseByteArrayElements(dataYUV, outYUV, JNI_ABORT);
	env->ReleaseIntArrayElements(dataRGB, outRGB, 0);
}

void Java_com_xynotec_camera_CameraOverlayView_GrayScale(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height)
{
	jint* outRGB = env->GetIntArrayElements(dataRGB, 0);
	
	Grayscale(outRGB, width, height);
	
	env->ReleaseIntArrayElements(dataRGB, outRGB, 0);
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


void decodeYUV420SP(int* rgb, unsigned char* yuv420sp, int width, int height) 
{
	int frameSize = width * height;
	int i, j, yp;
	for (j = 0, yp = 0; j < height; j++) 
	{
		int uvp = frameSize + (j >> 1) * width, u = 0, v = 0;
		for (i = 0; i < width; i++, yp++) 
		{
			int y = (0xff & ((int) yuv420sp[yp])) - 16;
			if (y < 0)
				y = 0;
			if ((i & 1) == 0) 
			{
				v = (0xff & yuv420sp[uvp++]) - 128;
				u = (0xff & yuv420sp[uvp++]) - 128;
			}

			int y1192 = 1192 * y;
			int r = (y1192 + 1634 * v);
			int g = (y1192 - 833 * v - 400 * u);
			int b = (y1192 + 2066 * u);

			if (r < 0)
				r = 0;
			else if (r > 262143)
				r = 262143;
			if (g < 0)
				g = 0;
			else if (g > 262143)
				g = 262143;
			if (b < 0)
				b = 0;
			else if (b > 262143)
				b = 262143;

			rgb[yp] = 0xff000000 | ((r << 6) & 0xff0000) | ((g >> 2) & 0xff00) | ((b >> 10) & 0xff);
		}
	}
}

void Java_com_xynotec_camera_CameraOverlayView_EdgeDetector(JNIEnv* env, jobject thiz, jintArray dataRGB, jint width, jint height)
{
	jint* outRGB = env->GetIntArrayElements(dataRGB, 0);
	
	EdgeDetector(outRGB, width, height);
	
	env->ReleaseIntArrayElements(dataRGB, outRGB, 0);
}

//http://marvinproject.sourceforge.net/en/plugins/edgeDetector.html
void EdgeDetector(int *data, int width, int height)
{       
	unsigned char* image = (unsigned char*)data;
	int length = width * height;
	// Init gray matrix
	int* grayMatrix = new int[256];
	for (int i = 0; i <= 255; i++) 
		grayMatrix[i] = (i << 16) | (i << 8) | i;	
       
	int* luminance = new int[width*height];
	
	int y, x, i;
	for (i = 0; i < length; i++, image += 4)
		luminance[i] = LUMINANCE(*image, *(image + 1), *(image + 2));
	
        
	int grayX, grayY;
	int magnitude;	
	
	image = (unsigned char*)data;
	int h_1 = height-1;
	int w_1 = width-1;
	for (y = 1; y < h_1; y++) 
	{
		int val_1 = (y-1)*width;
		int val0 = val_1 + width;
		int val1 = val0 + width;

		for (x = 1; x < w_1; x++) 
		{			
			int x_1 = x - 1;
			int x1 = x + 1;
			grayX = - luminance[x_1 + val_1] + luminance[x_1 + val1]
					- 2* luminance[x + val_1] + 2* luminance[x + val1]
					- luminance[x + val_1] + luminance[x1 + val1];
			grayY = luminance[x_1 + val_1] + 2* luminance[x_1 + val0] + luminance[x_1 + val1]
					- luminance[x1 + val_1] - 2* luminance[x1 + val0] - luminance[x1 + val1];
			
			magnitude = 255 - (abs(grayX) + abs(grayY));
		  
			int grayscaleColor = grayMatrix[magnitude];

			// Apply the color into a new image
			//data[x + y*width] = data[x + y*width] | grayscaleColor;
			int offset = (x + y*width)*4;
			*(image + offset) = magnitude;
			*(image + offset + 1) = magnitude;
			*(image + offset + 2) = magnitude;
		}		
	}
         
	delete[] grayMatrix;
	delete[] luminance;
}

