#ifdef _WIN32
	#include <string.h>
	#include <stdlib.h>	
#endif

#include <time.h>
#include <math.h>
#include "BasicEffect.h"
#include "BokehEffect.h"
/*
#include "../ipcommon/RGBImage.h"
#include "../ipcommon/LiquidProcessor.h"

#include "../Liquid/LiquifyArgs.h"
#include "../Liquid/DisplacementMesh.h"
#include "../Liquid/LiquifyRenderer.h"
#include "../Liquid/Surface.h"
*/
#ifdef GLOBAL_BMP_MEMORY
	BMP_ARGB* src = NEW_ARRAY(BMP_ARGB, 800 * 800);
#else
	BMP_ARGB* src = NULL;	
#endif

byte* CreateGamma(double color)
{
	byte* gammaArray = NEW_ARRAY(byte, 256);
	for (int i = 0; i < 256; ++i)
	{
		gammaArray[i] = (byte)MIN(255,
			(int)((255.0 * pow(i / 255.0, 1.0 / color)) + 0.5));
	}
	return gammaArray;
}

void ColorFilter(BMP_ARGB *data, int width, int height, enum COLOR_FILTER filter)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			byte* bData = (byte*)data; 			
			
			int nPixelR = 0;
			int nPixelG = 0;
			int nPixelB = 0;
			if (filter == COLOR_RED)
			{
#ifdef INVERT_RED
				nPixelR = bData[2];
				nPixelB = bData[0] - 255;
#else
				nPixelR = bData[0];
				nPixelB = bData[2] - 255;
#endif	

				nPixelG = bData[1] - 255;
				
			}
			else if (filter == COLOR_GREEN)
			{
#ifdef INVERT_RED
				nPixelR = bData[2] - 255;				
				nPixelB = bData[0] - 255;
#else
				nPixelR = bData[0] - 255;				
				nPixelB = bData[2] - 255;
#endif

				nPixelG = bData[1];
			}
			else if (filter == COLOR_BLUE)
			{
#ifdef INVERT_RED
				nPixelR = bData[2] - 255;
				nPixelB = bData[0];
#else
				nPixelR = bData[0] - 255;
				nPixelB = bData[2];
#endif				
				nPixelG = bData[1] - 255;
			}
			nPixelR = MAX(nPixelR, 0);
			nPixelR = MIN(255, nPixelR);

			nPixelG = MAX(nPixelG, 0);
			nPixelG = MIN(255, nPixelG);

			nPixelB = MAX(nPixelB, 0);
			nPixelB = MIN(255, nPixelB);

#ifdef INVERT_RED
			bData[2] = nPixelR;			
			bData[0] = nPixelB;
#else
			bData[0] = nPixelR;			
			bData[2] = nPixelB;
#endif

			bData[1] = nPixelG;

			data++;
		}
	}
}

void Gamma(BMP_ARGB *data, int width, int height, double red, double green, double blue)
{
	byte* redGamma = CreateGamma(red);
	byte* greenGamma = CreateGamma(green);
	byte* blueGamma = CreateGamma(blue);
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			byte* bData = (byte*)data; 		
#ifdef INVERT_RED

			bData[0] = redGamma[bData[2]];	
			bData[2] = blueGamma[bData[0]];
#else
			bData[0] = redGamma[bData[0]];	
			bData[2] = blueGamma[bData[2]];
#endif

			bData[1] = greenGamma[bData[1]];
			
			data++;
		}
	}

	DELETE_ARRAY(redGamma);	
	DELETE_ARRAY(greenGamma);
	DELETE_ARRAY(blueGamma);	
}

void Brightness(BMP_ARGB *data, int width, int height, int brightness)
{
	if (brightness < -255) brightness = -255;
	if (brightness > 255) brightness = 255;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			byte* bData = (byte*)data; 		

#ifdef INVERT_RED
			int cR = bData[2] + brightness;
			int cB = bData[0] + brightness;
#else
			int cR = bData[0] + brightness;
			int cB = bData[2] + brightness;
#endif
			
			int cG = bData[1] + brightness;

			if (cR < 0) cR = 1;
			if (cR > 255) cR = 255;

			if (cG < 0) cG = 1;
			if (cG > 255) cG = 255;

			if (cB < 0) cB = 1;
			if (cB > 255) cB = 255;

#ifdef INVERT_RED
			bData[2] = cR;
			bData[0] = cB;
#else
			bData[0] = cR;
			bData[2] = cB;
#endif
			bData[1] = cG;

			data++;
		}
	}
}

void Contrast(BMP_ARGB *data, int width, int height, double contrast)
{
	if (contrast < -100) contrast = -100;
	if (contrast > 100) contrast = 100;
	contrast = (100.0 + contrast) / 100.0;
	contrast *= contrast;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			byte* bData = (byte*)data; 		

#ifdef INVERT_RED
			double pR = bData[2] / 255.0;
#else
			double pR = bData[0] / 255.0;
#endif
			pR -= 0.5;
			pR *= contrast;
			pR += 0.5;
			pR *= 255;
			if (pR < 0) pR = 0;
			if (pR > 255) pR = 255;

			double pG = bData[1] / 255.0;
			pG -= 0.5;
			pG *= contrast;
			pG += 0.5;
			pG *= 255;
			if (pG < 0) pG = 0;
			if (pG > 255) pG = 255;

#ifdef INVERT_RED
			double pB = bData[0] / 255.0;
#else
			double pB = bData[2] / 255.0;
#endif
			pB -= 0.5;
			pB *= contrast;
			pB += 0.5;
			pB *= 255;
			if (pB < 0) pB = 0;
			if (pB > 255) pB = 255;

#ifdef INVERT_RED
			bData[2] = pR;			
			bData[0] = pB;
#else
			bData[0] = pR;			
			bData[2] = pB;
#endif

			bData[1] = pG;
			
			data++;
		}
	}
}

void Grayscale(BMP_ARGB *data, int width, int height)
{
	// Cong modified
#ifndef GRAY_FROM_RGB
	#define GRAY_FROM_RGB(r, g, b) (byte)((r*29 + g*150 + b*77 + 128)/256)
#endif

	byte* image = (byte*)data;
	int length = width * height;
	byte gray = 0;
	for (int i = 0; i < length; i++, image += 4)
	{
		gray = GRAY_FROM_RGB(*image, *(image + 1), *(image + 2));
		
		*image = gray;
		*(image + 1) = gray;
		*(image + 2) = gray;
	}

	image = NULL;
}

void Invert(BMP_ARGB *data, int width, int height)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			byte* bData = (byte*)data; 	
			
			bData[0] = 255 - bData[0];
			bData[1] = 255 - bData[1];
			bData[2] = 255 - bData[2];

			data++;
		}
	}
}

void Vignette(BMP_ARGB *data, int width, int height)
{
	double ScaleX = 1;
	double ScaleY = 1;
	double alpha;
	double Amount1 = 1;
	double power = Amount1 * Amount1;
	bool bInvert = false;

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			byte* bData = (byte*)data; 	

			bData[0] = 255 - bData[0];
			bData[1] = 255 - bData[1];
			bData[2] = 255 - bData[2];

			alpha = (sin((i)*3.141592/(width)) ) * (sin((j)*3.141592/(height)) );
			double a = cos((i-width/2)*6.283*ScaleX/(width)) / 2.0;
			double b = cos((j-height/2)*6.283*ScaleY/(height)) / 2.0; 
			alpha = (a + 0.5) * (b + 0.5);
			alpha = alpha * power;
			if( bInvert )
			{
				alpha = 1 - alpha;   
			}
			//Towards transparent
			if( alpha > 1 )
			{
				alpha = 1;
			}
			// Towards black
			if( alpha <0.0)
			{
				alpha = 0.0;
			}
			bData[3] = (byte)(bData[3]* alpha);

			data++;
		}
	}
}

void Conv3x3(BMP_ARGB *data, int width, int height, ConvMatrix* m)
{
	// Avoid divide by zero errors
	if (0 == m->Factor)
		return;

	int nPixel;
	int stride = width * 4;//4 bytes per pixel
	int stride2 = stride * 2;

#ifndef GLOBAL_BMP_MEMORY
	bool bDelete = false;
	if (src == NULL)
	{
		bDelete = true;
		src = NEW_ARRAY(BMP_ARGB, width * height);
		memcpy(src, data, width*height*sizeof(BMP_ARGB));
	}
#endif
	memcpy(src, data, width*height*sizeof(BMP_ARGB));

	byte * p = (byte *)data;
	byte* pSrc = (byte*)src;

	int nWidth = width - 2;
	int nHeight = height - 2;

	for(int y=0;y < nHeight;++y)
	{
		for(int x=0; x < nWidth; ++x )
		{
			/*
			nPixel = ( ( ( (pSrc[2] * m->TopLeft) + (pSrc[5] * m->TopMid) + (pSrc[8] * m->TopRight) +
				(pSrc[2 + stride] * m->MidLeft) + (pSrc[5 + stride] * m->Pixel) + (pSrc[8 + stride] * m->MidRight) +
				(pSrc[2 + stride2] * m->BottomLeft) + (pSrc[5 + stride2] * m->BottomMid) + (pSrc[8 + stride2] * m->BottomRight)) / m->Factor) + m->Offset);

			if (nPixel < 0) nPixel = 0;
			if (nPixel > 255) nPixel = 255;

			p[5 + stride]= (byte)nPixel;

			nPixel = ( ( ( (pSrc[1] * m->TopLeft) + (pSrc[4] * m->TopMid) + (pSrc[7] * m->TopRight) +
				(pSrc[1 + stride] * m->MidLeft) + (pSrc[4 + stride] * m->Pixel) + (pSrc[7 + stride] * m->MidRight) +
				(pSrc[1 + stride2] * m->BottomLeft) + (pSrc[4 + stride2] * m->BottomMid) + (pSrc[7 + stride2] * m->BottomRight)) / m->Factor) + m->Offset);

			if (nPixel < 0) nPixel = 0;
			if (nPixel > 255) nPixel = 255;

			p[4 + stride] = (byte)nPixel;

			nPixel = ( ( ( (pSrc[0] * m->TopLeft) + (pSrc[3] * m->TopMid) + (pSrc[6] * m->TopRight) +
				(pSrc[0 + stride] * m->MidLeft) + (pSrc[3 + stride] * m->Pixel) + (pSrc[6 + stride] * m->MidRight) +
				(pSrc[0 + stride2] * m->BottomLeft) + (pSrc[3 + stride2] * m->BottomMid) + (pSrc[6 + stride2] * m->BottomRight)) / m->Factor) + m->Offset);

			if (nPixel < 0) nPixel = 0;
			if (nPixel > 255) nPixel = 255;

			p[3 + stride] = (byte)nPixel;
			*/

			nPixel = ( ( ( (pSrc[2] * m->TopLeft) + (pSrc[6] * m->TopMid) + (pSrc[10] * m->TopRight) +
				(pSrc[2 + stride] * m->MidLeft) + (pSrc[6 + stride] * m->Pixel) + (pSrc[10 + stride] * m->MidRight) +
				(pSrc[2 + stride2] * m->BottomLeft) + (pSrc[6 + stride2] * m->BottomMid) + (pSrc[10 + stride2] * m->BottomRight)) / m->Factor) + m->Offset);

			if (nPixel < 0) nPixel = 0;
			if (nPixel > 255) nPixel = 255;

			p[6 + stride]= (byte)nPixel;

			nPixel = ( ( ( (pSrc[1] * m->TopLeft) + (pSrc[5] * m->TopMid) + (pSrc[9] * m->TopRight) +
				(pSrc[1 + stride] * m->MidLeft) + (pSrc[5 + stride] * m->Pixel) + (pSrc[9 + stride] * m->MidRight) +
				(pSrc[1 + stride2] * m->BottomLeft) + (pSrc[5 + stride2] * m->BottomMid) + (pSrc[9 + stride2] * m->BottomRight)) / m->Factor) + m->Offset);

			if (nPixel < 0) nPixel = 0;
			if (nPixel > 255) nPixel = 255;

			p[5 + stride] = (byte)nPixel;

			nPixel = ( ( ( (pSrc[0] * m->TopLeft) + (pSrc[4] * m->TopMid) + (pSrc[8] * m->TopRight) +
				(pSrc[0 + stride] * m->MidLeft) + (pSrc[4 + stride] * m->Pixel) + (pSrc[8 + stride] * m->MidRight) +
				(pSrc[0 + stride2] * m->BottomLeft) + (pSrc[4 + stride2] * m->BottomMid) + (pSrc[8 + stride2] * m->BottomRight)) / m->Factor) + m->Offset);

			if (nPixel < 0) nPixel = 0;
			if (nPixel > 255) nPixel = 255;

			p[4 + stride] = (byte)nPixel;

			p += 4;
			pSrc += 4;
		}
	}

#ifndef GLOBAL_BMP_MEMORY
	if (bDelete)
		DELETE_ARRAY(src);
#endif
}

void Smooth(BMP_ARGB *data, int width, int height, int nWeight /* default to 1 */)
{
	ConvMatrix* m = new ConvMatrix();
	m->SetAll(1);
	m->Pixel = nWeight;
	m->Factor = nWeight + 8;

	Conv3x3(data, width, height, m);

	DELETE(m);	
}

void GaussianBlur(BMP_ARGB *data, int width, int height, int nWeight /* default to 4*/)
{
	ConvMatrix* m = new ConvMatrix();
	m->SetAll(1);
	m->Pixel = nWeight;
	m->TopMid = m->MidLeft = m->MidRight = m->BottomMid = 2;
	m->Factor = nWeight + 12;

	Conv3x3(data, width, height, m);

	DELETE(m);
}

void MeanRemoval(BMP_ARGB *data, int width, int height, int nWeight /* default to 9*/ )
{
	ConvMatrix* m = new ConvMatrix();
	m->SetAll(-1);
	m->Pixel = nWeight;
	m->Factor = nWeight - 8;

	Conv3x3(data, width, height, m);

	DELETE(m);
}

void Sharpen(BMP_ARGB *data, int width, int height, int nWeight /* default to 11*/ )
{
	ConvMatrix* m = new ConvMatrix();
	m->SetAll(0);
	m->Pixel = nWeight;
	m->TopMid = m->MidLeft = m->MidRight = m->BottomMid = -2;
	m->Factor = nWeight - 8;

	Conv3x3(data, width, height, m);

	DELETE(m);	
}

void EmbossLaplacian(BMP_ARGB *data, int width, int height)
{
	ConvMatrix* m = new ConvMatrix();
	m->SetAll(-1);
	m->TopMid = m->MidLeft = m->MidRight = m->BottomMid = 0;
	m->Pixel = 4;
	m->Offset = 127;

	Conv3x3(data, width, height, m);

	DELETE(m);	
}
void EdgeDetectQuick(BMP_ARGB *data, int width, int height)
{
	ConvMatrix* m = new ConvMatrix();
	m->TopLeft = m->TopMid = m->TopRight = -1;
	m->MidLeft = m->Pixel = m->MidRight = 0;
	m->BottomLeft = m->BottomMid = m->BottomRight = 1;

	m->Offset = 127;

	Conv3x3(data, width, height, m);

	DELETE(m);	
}


void OffsetFilterAbs(BMP_ARGB *data, int width, int height, IntPoint** offset)
{
	int nPixel;
	int stride = width * 4;//4 bytes per pixel
	int scanline = stride;

#ifndef GLOBAL_BMP_MEMORY
	bool bDelete = false;
	if (src == NULL)
	{
		bDelete = true;
		src = NEW_ARRAY(BMP_ARGB, width * height);
		memcpy(src, data, width*height*sizeof(BMP_ARGB));
	}
#endif
	memcpy(src, data, width*height*sizeof(BMP_ARGB));

	byte * p = (byte *)data;
	byte* pSrc = (byte*)src;

	int nWidth = width;
	int nHeight = height;

	int xOffset, yOffset;

	for(int y=0;y < nHeight;++y)
	{
		for(int x=0; x < nWidth; ++x )
		{
			xOffset = offset[x][y].X;
			yOffset = offset[x][y].Y;

			if (yOffset >= 0 && yOffset < nHeight && xOffset >= 0 && xOffset < nWidth)
			{
				p[0] = pSrc[(yOffset * scanline) + (xOffset * 4)];
				p[1] = pSrc[(yOffset * scanline) + (xOffset * 4) + 1];
				p[2] = pSrc[(yOffset * scanline) + (xOffset * 4) + 2];
			}

			p += 4;
		}
	}

#ifndef GLOBAL_BMP_MEMORY
	if (bDelete)
		DELETE_ARRAY(src);
#endif
}

void OffsetFilter(BMP_ARGB *data, int width, int height, IntPoint** offset)
{
	int nPixel;
	int stride = width * 4;//4 bytes per pixel
	int scanline = stride;

#ifndef GLOBAL_BMP_MEMORY
	bool bDelete = false;
	if (src == NULL)
	{
		bDelete = true;
		src = NEW_ARRAY(BMP_ARGB, width * height);
		memcpy(src, data, width*height*sizeof(BMP_ARGB));
	}
#endif
	memcpy(src, data, width*height*sizeof(BMP_ARGB));

	byte * p = (byte *)data;
	byte* pSrc = (byte*)src;

	int nWidth = width;
	int nHeight = height;

	int xOffset, yOffset;

	for(int y=0;y < nHeight;++y)
	{
		for(int x=0; x < nWidth; ++x )
		{
			xOffset = offset[x][y].X;
			yOffset = offset[x][y].Y;

			if (y+yOffset >= 0 && y+yOffset < nHeight && x+xOffset >= 0 && x+xOffset < nWidth)
			{
				p[0] = pSrc[((y+yOffset) * scanline) + ((x+xOffset) * 4)];
				p[1] = pSrc[((y+yOffset) * scanline) + ((x+xOffset) * 4) + 1];
				p[2] = pSrc[((y+yOffset) * scanline) + ((x+xOffset) * 4) + 2];
			}

			p += 4;
		}
	}

#ifndef GLOBAL_BMP_MEMORY
	if (bDelete)
		DELETE_ARRAY(src);
#endif
}

void OffsetFilterAntiAlias(BMP_ARGB *data, int width, int height, FloatPoint** fp)
{
	int nPixel;
	int stride = width * 4;//4 bytes per pixel
	int scanline = stride;

#ifndef GLOBAL_BMP_MEMORY
	bool bDelete = false;
	if (src == NULL)
	{
		bDelete = true;
		src = NEW_ARRAY(BMP_ARGB, width * height);
		memcpy(src, data, width*height*sizeof(BMP_ARGB));
	}
#endif
	memcpy(src, data, width*height*sizeof(BMP_ARGB));

	byte * p = (byte *)data;
	byte* pSrc = (byte*)src;

	int nWidth = width;
	int nHeight = height;

	double xOffset, yOffset;

	double fraction_x, fraction_y, one_minus_x, one_minus_y;
	int ceil_x, ceil_y, floor_x, floor_y;
	byte p1, p2;

	for(int y=0;y < nHeight;++y)
	{
		for(int x=0; x < nWidth; ++x )
		{
			xOffset = fp[x][y].X;
			yOffset = fp[x][y].Y;

			// Setup

			floor_x = (int)floor(xOffset);
			floor_y = (int)floor(yOffset);
			ceil_x = floor_x + 1;
			ceil_y = floor_y + 1;
			fraction_x = xOffset - floor_x;
			fraction_y = yOffset - floor_y;
			one_minus_x = 1.0 - fraction_x;
			one_minus_y = 1.0 - fraction_y;

			if (floor_y >= 0 && ceil_y < nHeight && floor_x >= 0 && ceil_x < nWidth)
			{
				// Blue

				p1 = (byte)(one_minus_x * (double)(pSrc[floor_y * scanline + floor_x * 4]) +
					fraction_x * (double)(pSrc[floor_y * scanline + ceil_x * 4]));

				p2 = (byte)(one_minus_x * (double)(pSrc[ceil_y * scanline + floor_x * 4]) +
					fraction_x * (double)(pSrc[ceil_y * scanline + 4 * ceil_x]));

				p[x * 4 + y*scanline] = (byte)(one_minus_y * (double)(p1) + fraction_y * (double)(p2));

				// Green

				p1 = (byte)(one_minus_x * (double)(pSrc[floor_y * scanline + floor_x * 4 + 1]) +
					fraction_x * (double)(pSrc[floor_y * scanline + ceil_x * 4 + 1]));

				p2 = (byte)(one_minus_x * (double)(pSrc[ceil_y * scanline + floor_x * 4 + 1]) +
					fraction_x * (double)(pSrc[ceil_y * scanline + 4 * ceil_x + 1]));

				p[x * 4 + y*scanline + 1] = (byte)(one_minus_y * (double)(p1) + fraction_y * (double)(p2));

				// Red

				p1 = (byte)(one_minus_x * (double)(pSrc[floor_y * scanline + floor_x * 4 + 2]) +
					fraction_x * (double)(pSrc[floor_y * scanline + ceil_x * 4 + 2]));

				p2 = (byte)(one_minus_x * (double)(pSrc[ceil_y * scanline + floor_x * 4 + 2]) +
					fraction_x * (double)(pSrc[ceil_y * scanline + 4 * ceil_x + 2]));

				p[x * 4 + y*scanline + 2] = (byte)(one_minus_y * (double)(p1) + fraction_y * (double)(p2));
			}
		}
	}

#ifndef GLOBAL_BMP_MEMORY
	if (bDelete)
		DELETE_ARRAY(src);
#endif
}

void Flip(BMP_ARGB *data, int width, int height, bool bHorz, bool bVert)
{
	IntPoint** ptFlip = new IntPoint*[width];

	for(int i = 0; i < width; i++)
		ptFlip[i] = new IntPoint[height];

	int nWidth = width;
	int nHeight = height;

	for (int x = 0; x < nWidth; ++x)
		for (int y = 0; y < nHeight; ++y)
		{
			ptFlip[x][y].X = (bHorz) ? nWidth - (x+1) : x;
			ptFlip[x][y].Y = (bVert) ? nHeight - (y + 1) : y;
		}

	OffsetFilterAbs(data, width, height, ptFlip);

	for(int i = 0; i < width; i++)
		delete[] ptFlip[i];
	delete[] ptFlip;
}

void RandomJitter(BMP_ARGB *data, int width, int height, short nDegree)
{
	IntPoint** ptRandJitter = new IntPoint*[width];

	for(int i = 0; i < width; i++)
		ptRandJitter[i] = new IntPoint[height];

	int nWidth = width;
	int nHeight = height;

	int newX, newY;

	short nHalf = (short)floor((double)nDegree/2);

	srand(time(NULL));

	for (int x = 0; x < nWidth; ++x)
		for (int y = 0; y < nHeight; ++y)
		{
			newX = rand()%nDegree - nHalf;

			if (x + newX > 0 && x + newX < nWidth)
				ptRandJitter[x][y].X = newX;
			else
				ptRandJitter[x][y].X = 0;

			newY = rand()%nDegree - nHalf;

			if (y + newY > 0 && y + newY < nWidth)
				ptRandJitter[x][y].Y = newY;
			else
				ptRandJitter[x][y].Y = 0;
		}

	OffsetFilter(data, width, height, ptRandJitter);

	for(int i = 0; i < width; i++)
		delete[] ptRandJitter[i];
	delete[] ptRandJitter;
}

void Swirl(BMP_ARGB *data, int width, int height, double fDegree, bool bSmoothing /* default fDegree to .05 */)
{
	int nWidth = width;
	int nHeight = height;

	FloatPoint** fp = new FloatPoint*[nWidth];
	IntPoint** pt = new IntPoint*[nWidth];

	for(int i = 0; i < nWidth; i++)
	{
		fp[i] = new FloatPoint[height];
		pt[i] = new IntPoint[height];
	}

	IntPoint mid;
	mid.X = nWidth/2;
	mid.Y = nHeight/2;

	double theta, radius;
	double newX, newY;

	for (int x = 0; x < nWidth; ++x)
		for (int y = 0; y < nHeight; ++y)
		{
			int trueX = x - mid.X;
			int trueY = y - mid.Y;
			theta = atan2((double)trueY,(double)trueX);

			radius = sqrt((double)(trueX*trueX + trueY*trueY));

			newX = mid.X + (radius * cos(theta + fDegree * radius));
			if (newX > 0 && newX < nWidth)
			{
				fp[x][y].X = newX;
				pt[x][y].X = (int)newX;
			}
			else
				fp[x][y].X = pt[x][y].X = x;

			newY = mid.Y + (radius * sin(theta + fDegree * radius));
			if (newY > 0 && newY < nHeight)
			{
				fp[x][y].Y = newY;
				pt[x][y].Y = (int)newY;
			}
			else
				fp[x][y].Y = pt[x][y].Y = y;
		}

	if(bSmoothing)
		OffsetFilterAntiAlias(data, width, height, fp);
	else
		OffsetFilterAbs(data, width, height, pt);

	for(int i = 0; i < nWidth; i++)
	{
		delete[] fp[i];
		delete[] pt[i];
	}
	delete[] fp;
	delete[] pt;

}

void Sphere(BMP_ARGB *data, int width, int height, bool bSmoothing)
{
	int nWidth = width;
	int nHeight = height;

	FloatPoint** fp = new FloatPoint*[nWidth];
	IntPoint** pt = new IntPoint*[nWidth];

	for(int i = 0; i < nWidth; i++)
	{
		fp[i] = new FloatPoint[height];
		pt[i] = new IntPoint[height];
	}

	IntPoint mid;
	mid.X = nWidth/2;
	mid.Y = nHeight/2;

	double theta, radius;
	double newX, newY;

	for (int x = 0; x < nWidth; ++x)
		for (int y = 0; y < nHeight; ++y)
		{
			int trueX = x - mid.X;
			int trueY = y - mid.Y;
			theta = atan2((double)trueY, (double)trueX);

			radius = sqrt((double)(trueX*trueX + trueY*trueY));

			double newRadius = radius * radius/(MAX(mid.X, mid.Y));

			newX = mid.X + (newRadius * cos(theta));

			if (newX > 0 && newX < nWidth)
			{
				fp[x][y].X = newX;
				pt[x][y].X = (int) newX;
			}
			else
			{
				fp[x][y].X = fp[x][y].Y = 0.0;
				pt[x][y].X = pt[x][y].Y = 0;
			}

			newY = mid.Y + (newRadius * sin(theta));

			if (newY > 0 && newY < nHeight && newX > 0 && newX < nWidth)
			{
				fp[x][y].Y = newY;
				pt[x][y].Y = (int) newY;
			}
			else
			{
				fp[x][y].X = fp[x][y].Y = 0.0;
				pt[x][y].X = pt[x][y].Y = 0;
			}
		}

	if(bSmoothing)
		OffsetFilterAbs(data, width, height, pt);
	else
		OffsetFilterAntiAlias(data, width, height, fp);

	for(int i = 0; i < nWidth; i++)
	{
		delete[] fp[i];
		delete[] pt[i];
	}
	delete[] fp;
	delete[] pt;

}

void TimeWarp(BMP_ARGB *data, int width, int height, byte factor, bool bSmoothing)
{
	int nWidth = width;
	int nHeight = height;

	FloatPoint** fp = new FloatPoint*[nWidth];
	IntPoint** pt = new IntPoint*[nWidth];

	for(int i = 0; i < nWidth; i++)
	{
		fp[i] = new FloatPoint[height];
		pt[i] = new IntPoint[height];
	}

	IntPoint mid;
	mid.X = nWidth/2;
	mid.Y = nHeight/2;

	double theta, radius;
	double newX, newY;

	for (int x = 0; x < nWidth; ++x)
		for (int y = 0; y < nHeight; ++y)
		{
			int trueX = x - mid.X;
			int trueY = y - mid.Y;
			theta = atan2((double)trueY, (double)trueX);

			radius = sqrt((double)(trueX*trueX + trueY*trueY));

			double newRadius = sqrt(radius) * factor;

			newX = mid.X + (newRadius * cos(theta));
			if (newX > 0 && newX < nWidth)
			{
				fp[x][y].X = newX;
				pt[x][y].X = (int) newX;
			}
			else
			{
				fp[x][y].X = 0.0;
				pt[x][y].X = 0;
			}

			newY = mid.Y + (newRadius * sin(theta));
			if (newY > 0 && newY < nHeight)
			{
				fp[x][y].Y = newY;
				pt[x][y].Y = (int) newY;
			}
			else
			{
				fp[x][y].Y = 0.0;
				pt[x][y].Y = 0;
			}
		}

	if(bSmoothing)
		OffsetFilterAbs(data, width, height, pt);
	else
		OffsetFilterAntiAlias(data, width, height, fp);

	for(int i = 0; i < nWidth; i++)
	{
		delete[] fp[i];
		delete[] pt[i];
	}
	delete[] fp;
	delete[] pt;
}

void Moire(BMP_ARGB *data, int width, int height, double fDegree)
{
	int nWidth = width;
	int nHeight = height;

	FloatPoint** fp = new FloatPoint*[nWidth];
	IntPoint** pt = new IntPoint*[nWidth];

	for(int i = 0; i < nWidth; i++)
	{
		fp[i] = new FloatPoint[height];
		pt[i] = new IntPoint[height];
	}

	IntPoint mid;
	mid.X = nWidth/2;
	mid.Y = nHeight/2;

	double theta, radius;
	int newX, newY;

	for (int x = 0; x < nWidth; ++x)
		for (int y = 0; y < nHeight; ++y)
		{
			int trueX = x - mid.X;
			int trueY = y - mid.Y;
			theta = atan2((double)trueX, (double)trueY);

			radius = sqrt((double)(trueX*trueX + trueY*trueY));

			newX = (int)(radius * sin(theta + fDegree * radius));
			if (newX > 0 && newX < nWidth)
			{
				pt[x][y].X = (int) newX;
			}
			else
			{
				pt[x][y].X = 0;
			}

			newY = (int)(radius * sin(theta + fDegree * radius));
			if (newY > 0 && newY < nHeight)
			{
				pt[x][y].Y = (int) newY;
			}
			else
			{
				pt[x][y].Y = 0;
			}
		}

	OffsetFilterAbs(data, width, height, pt);

	for(int i = 0; i < nWidth; i++)
	{
		delete[] fp[i];
		delete[] pt[i];
	}
	delete[] fp;
	delete[] pt;
}


void WaterLight(BMP_ARGB *data, int width, int height, short nWave, bool bSmoothing)
{
	int nCosSinLookup = (width > height ? width : height);
	int* sin_tbl = new int[nCosSinLookup];
	int* cos_tbl = new int[nCosSinLookup];
	double pi = 3.1415926;
	for (int i=0; i<nCosSinLookup; i++)
	{
		sin_tbl[i] = (floor)(0.5 + nWave * sin(2.0 * pi * i / 128.0));
		cos_tbl[i] = (floor)(0.5 + nWave * cos(2.0 * pi * i / 128.0));
	}

	int length = width * height;
	int* src = (int*)data;
	int* dst = new int[length];

	int index = 0, newX = 0, newY = 0, xo, yo;
	for (int y=0; y<height; y++)
	{
		xo = sin_tbl[y];
		for (int x = 0; x<width; x++, index++)
		{
			yo = cos_tbl[x];

			newX = x + xo;
			newY = y + yo;

			newX = (newX < 0 ? 0 : (newX >= width ? (width-1) : newX));
			newY = (newY < 0 ? 0 : (newY >= height ? (height-1) : newY));

			dst[index] = src[newY * width + newX];
		}
	}

	memccpy(data, dst, 0, length*sizeof(int));

	delete dst;
	delete sin_tbl; delete cos_tbl;
}


void Water(BMP_ARGB *data, int width, int height, short nWave, bool bSmoothing)
{
	WaterLight(data, width, height, nWave, bSmoothing);
	return;

	int nWidth = width;
	int nHeight = height;

	FloatPoint** fp = new FloatPoint*[nWidth];
	IntPoint** pt = new IntPoint*[nWidth];

	for(int i = 0; i < nWidth; i++)
	{
		fp[i] = new FloatPoint[height];
		pt[i] = new IntPoint[height];
	}

	IntPoint mid;
	mid.X = nWidth/2;
	mid.Y = nHeight/2;

	double newX, newY;
	double xo, yo;

	double pi = 3.1415926;

	int nCosSinLookup = (nWidth > nHeight ? nWidth : nHeight);
	/*double* sin_tbl = new double[nCosSinLookup];
	double* cos_tbl = new double[nCosSinLookup];*/

	// test c++ oop
	double* sin_tbl = SimpleImageProcessor::CreateBuffer(nCosSinLookup * sizeof(double));
	double* cos_tbl = SimpleImageProcessor::CreateBuffer(nCosSinLookup * sizeof(double));

	for (int i=0; i<nCosSinLookup; i++)
	{
		sin_tbl[i] = nWave * sin(2.0 * pi * i / 128.0);
		cos_tbl[i] = nWave * cos(2.0 * pi * i / 128.0);
	}

	

	for (int x = 0; x < nWidth; ++x)
		for (int y = 0; y < nHeight; ++y)
		{
			xo = sin_tbl[y];
				//((double)nWave * sin(2.0 * 3.1415 * (float)y / 128.0));
			yo = cos_tbl[x]; 
				//((double)nWave * cos(2.0 * 3.1415 * (float)x / 128.0));

			newX = (x + xo);
			newY = (y + yo);

			if (newX > 0 && newX < nWidth)
			{
				fp[x][y].X = newX;
				pt[x][y].X = (int) newX;
			}
			else
			{
				fp[x][y].X = 0.0;
				pt[x][y].X = 0;
			}


			if (newY > 0 && newY < nHeight)
			{
				fp[x][y].Y = newY;
				pt[x][y].Y = (int) newY;
			}
			else
			{
				fp[x][y].Y = 0.0;
				pt[x][y].Y = 0;
			}
		}

	delete sin_tbl; delete cos_tbl;

	if(bSmoothing)
		OffsetFilterAbs(data, width, height, pt);
	else
		OffsetFilterAntiAlias(data, width, height, fp);

	for(int i = 0; i < nWidth; i++)
	{
		delete[] fp[i];
		delete[] pt[i];
	}

	delete[] fp;
	delete[] pt;
}

void Pixelate(BMP_ARGB *data, int width, int height, short pixel, bool bGrid)
{
	int nWidth = width;
	int nHeight = height;

	IntPoint** pt = new IntPoint*[nWidth];

	for(int i = 0; i < nWidth; i++)
		pt[i] = new IntPoint[height];

	int newX, newY;

	for (int x = 0; x < nWidth; ++x)
		for (int y = 0; y < nHeight; ++y)
		{
			newX = pixel - x%pixel;

			if (bGrid && newX == pixel)
				pt[x][y].X = -x;
			else if (x + newX > 0 && x +newX < nWidth)
				pt[x][y].X = newX;
			else
				pt[x][y].X = 0;

			newY = pixel - y%pixel;

			if (bGrid && newY == pixel)
				pt[x][y].Y = -y;
			else if (y + newY > 0 && y + newY < nHeight)
				pt[x][y].Y = newY;
			else
				pt[x][y].Y = 0;
		}

	OffsetFilter(data, width, height, pt);

	for(int i = 0; i < nWidth; i++)
		delete[] pt[i];
	delete[] pt;
}

void FishEye(BMP_ARGB *data, int width, int height, double m_iCurvature, bool m_bInverse, bool bSmoothing)
{
	FloatPoint** fp = new FloatPoint*[width];
	IntPoint** pt = new IntPoint*[width];

	for(int i = 0; i < width; i++)
	{
		fp[i] = new FloatPoint[height];
		pt[i] = new IntPoint[height];
	}

	int			 i, j;								// cartesian coordinates
	int			 x, y;								// converted cartesian coordinates

	double		 r, a;								// polar coordinates (radius, angle)

	double		 m_width = width;
	double		 m_height = height;
	unsigned int R  = (MIN(m_width, m_height)) / 2; // maxium radius of polar coordinates

	double		 w = m_iCurvature;					// curvature [0.001,0.1]
	//   m_iCurvature will return [1,100]
	double		 s = R / log(w*R+1);				// transformation coefficient
	//   set according to largest radius
	//   and curvature w

	int w2 = m_width  / 2;
	int h2 = m_height / 2;

	//enum background {leave, white, black};
	//int  backgroundtype = dlg.m_iBackground;
	bool inverse = m_bInverse;

	// for loops with origin in center of image
	// [i,j] in terms of filtered image

	for (i = -1*h2; i < ((int)m_height-h2); i++)
	{
		for (j = -1*w2; j < ((int)m_width-w2); j++)
		{
			// convert to polar
			r = sqrt((double)(i*i + j*j));
			a = atan2((float)i, j);		// calculates arctan(i/j)

			// if we're inside R (i.e. inside the circle) do...
			if (r <= R)
			{
				// make transformation using Basu and Licardie model [DEVE01]
				if (!inverse)
					r = (exp(r/s)-1)/w;
				else
					r = s * log(1+w*r);

				// convert back to cartesian
				x = int  (r * cos(a));
				y = int  (r * sin(a));

				// move origin back to bottom left
				x += w2;
				y += h2;

				fp[j + w2][i + h2].X = x;
				fp[j + w2][i + h2].Y = y;

				pt[j + w2][i + h2].X = x;
				pt[j + w2][i + h2].Y = y;
			}

			// if we're outside R, do not curve
			else
			{
				fp[j + w2][i + h2].X = j + w2;
				fp[j + w2][i + h2].Y = i + h2;

				pt[j + w2][i + h2].X = j + w2;
				pt[j + w2][i + h2].Y = i + h2;

			}
		}
	}

	if(bSmoothing)
		OffsetFilterAbs(data, width, height, pt);
	else
		OffsetFilterAntiAlias(data, width, height, fp);

	for(int i = 0; i < width; i++)
	{
		delete[] fp[i];
		delete[] pt[i];
	}
	delete[] fp;
	delete[] pt;
}

void Tube(BMP_ARGB *data, int width, int height, double m_iCurvature, bool m_bInverse, bool bSmoothing)
{
	FloatPoint** fp = new FloatPoint*[width];
	IntPoint** pt = new IntPoint*[width];

	for(int i = 0; i < width; i++)
	{
		fp[i] = new FloatPoint[height];
		pt[i] = new IntPoint[height];
	}

	int Amount1=0;  //[-500,500]Horizontal cylinder factor
	int Amount2=32;  //[-500,500]Vertical cylinder factor

	float RadiusY =-(float)Amount1 / 100.0f;
	float RadiusX =(float)Amount2 / 100.0f;
	float Distort = 2.0f;

	long SizeX = (long)(width);
	long SizeY = (long)(height);
	long CenterX = (long)((SizeX / 2.0f));
	long CenterY = (long)((SizeY / 2.0f));

	for(int y = 0; y < SizeY; y++)
	{
		float AngleY = (float)asin(Distort *(float)(y - CenterY)/(float)SizeY);
		float srcXd = (float)(cos(AngleY) * RadiusY * CenterY);
		for (int x = 0; x < SizeX; x++)
		{
			//CurrentPixel = src.GetBilinearSample(x, y); // Get the current pixel 
			int srcX = ((int)srcXd + x)%SizeX;//(int)Math.IEEERemainder((int)srcXd + x,SizeX);
			if (srcX < 0) srcX+=(int)SizeX;
			if (srcX >= SizeX) srcX-=(int)SizeX;

			float AngleX = (float)acos(Distort *(float)(x - CenterX)/(float)SizeX);
			float srcYd = (float)(sin(AngleX)* RadiusX * CenterX);
			int srcY = ((int)srcYd + y)%SizeY;//(int)Math.IEEERemainder((int)srcYd + y,SizeY);
			if (srcY < 0) srcY+=(int)SizeY;
			if (srcY >= SizeY) srcY-=(int)SizeY;

			//CurrentPixel = src.GetBilinearSample(srcX, srcY);
			//dst[x,y] = CurrentPixel;
			fp[x][y].X = srcX;
			fp[x][y].Y = srcY;

			pt[x][y].X = srcX;
			pt[x][y].Y = srcY;
		}
	}

	if(bSmoothing)
		OffsetFilterAbs(data, width, height, pt);
	else
		OffsetFilterAntiAlias(data, width, height, fp);
	

	for(int i = 0; i < width; i++)
	{
		delete[] fp[i];
		delete[] pt[i];
	}
	delete[] fp;
	delete[] pt;
}

void MyTube(BMP_ARGB *data, int width, int height, double m_iCurvature, bool m_bInverse, bool bSmoothing)
{
	FloatPoint** fp = new FloatPoint*[width];
	IntPoint** pt = new IntPoint*[width];

	for(int i = 0; i < width; i++)
	{
		fp[i] = new FloatPoint[height];
		pt[i] = new IntPoint[height];
	}

	int w2 = width  / 2;
	int h2 = height / 2;

	bool bWidth = true;

	double radius;
	double ratio = 2.0f;
	double delta;
	double thetra;

	if (bWidth)
	{
		radius = ratio * w2;
		delta = sqrt(radius*radius - w2*w2);		
	}
	else
	{
		radius = ratio * h2;
		delta = sqrt(radius*radius - h2*h2);		
	}
	
	if (bWidth)
	{
		for (int x = 0; x < w2; ++x)
		{
			thetra = atan2(w2 - x, delta);
			double srcX = w2 - radius*sin(thetra);
			for (int y = 0; y < height; ++y)
			{	
				fp[x][y].X = (int)srcX;
				fp[width - x - 1][y].X = (int)(width - srcX);
				pt[x][y].X = (int)srcX;
				pt[width - x - 1][y].X = (int)(width - srcX);
				
				double srcY = y + radius*cos(thetra) - delta;
				if (srcY >= height) srcY-=height;

				fp[x][y].Y = (int)srcY;
				fp[width - x - 1][y].Y = (int)srcY;
				pt[x][y].Y = (int)srcY;
				pt[width - x - 1][y].Y = (int)srcY;
			}
		}
	}
	else
	{

	}

	if(bSmoothing)
		OffsetFilterAbs(data, width, height, pt);
	else
		OffsetFilterAntiAlias(data, width, height, fp);


	for(int i = 0; i < width; i++)
	{
		delete[] fp[i];
		delete[] pt[i];
	}
	delete[] fp;
	delete[] pt;
}

/*
void LiquidTest(BMP_ARGB *data, int width, int height, byte* surface)
{
	RGBImage* image = new RGBImage((int*)data, width, height, false);

	//photo_engine_ipcore::LiquidProcessor::ApplyEffect(image, surface);
	photo_engine_ipcore::LiquidProcessor::TestLiquid(image);

	DELETE(image);
}

void Agg2DImageOnImage(BMP_ARGB *bkData, int bkWidth, int bkHeight, 
				  BMP_ARGB *overlayData, int overlayWidth, int overlayHeight)
{
	RGBImage* bkImage = new RGBImage((int*)bkData, bkWidth, bkHeight, false);
	RGBImage* overlayImage = new RGBImage((int*)overlayData, overlayWidth, overlayHeight, false);

	photo_engine_ipcore::LiquidProcessor::TestOverLayImage(bkImage, overlayImage);

	DELETE(bkImage);
	DELETE(overlayImage);

}
*/
void InkSketch(BMP_ARGB *data, int width, int height, int inkOutline, int coloring)
{
#ifndef GLOBAL_BMP_MEMORY
	bool bDelete = false;
	if (src == NULL)
	{
		bDelete = true;
		src = NEW_ARRAY(BMP_ARGB, width * height);
		memcpy(src, data, width*height*sizeof(BMP_ARGB));
	}
#endif
	memcpy(src, data, width*height*sizeof(BMP_ARGB));

	GlowEffect_PDN(data, width, height, 6, (coloring - 50) * 2, (coloring - 50) * 2);

	const int size = 5; // odd number

	//play around with the matrix for interesting effects.
	const int conv [size][size] = {
			                       {-1,  -1,  -1,  -1, -1},
			                       {-1,  -1,  -1,  -1, -1},
			                       {-1,  -1,  30,  -1, -1},
			                       {-1,  -1,  -1,  -1, -1},
			                       {-1,  -1,  -5,  -1, -1},
    				              };

	//const int conv [size][size] = {
	//	                       { 1,   1,   1,   1,  1},
	//	                       { 1,   1,   1,   1,  1},
	//	                       { 1,   1,   24,   1,  1},
	//	                       { 1,   1,   1,   1,  1},
	//	                       { 1,   1,   1,   1,  1},
	//			              };

    int radius = (size-1)/2;
	
	for (int y = 0; y < height; ++y)
    {
        int top = y - radius;
        int bottom = y + radius + 1;

        if (top < 0)
        {
            top = 0;
        }

        if (bottom > height)
        {
            bottom = height;
        }

        BMP_ARGB* srcPtr = src + y*width;
		BMP_ARGB* dstPtr = data + y*width;

        for (int x = 0; x < width; ++x)
        {
            int left = x - radius;
            int right = x + radius + 1;

            if (left < 0)
            {
                left = 0;
            }

            if (right > width)
            {
                right = width;
            }

            int r = 0;
            int g = 0;
            int b = 0;

            for (int v = top; v < bottom; v++)
            {
                BMP_ARGB* pRow = src + v*width;				
                int j = v - y + radius;

                for (int u = left; u < right; u++)
                {
                    int i1 = u - x + radius;
                    int w = conv[j][i1];

                    BMP_ARGB* pRef = pRow + u;

					byte* pRef8 = (byte*)pRef;
#ifdef INVERT_RED
                    r += pRef8[2] * w;
                    g += pRef8[1] * w;
                    b += pRef8[1] * w;
#else
					r += pRef8[0] * w;
                    g += pRef8[1] * w;
                    b += pRef8[2] * w;
#endif 
                }
            }

            BMP_ARGB topLayer = ClampToByte(b) | (ClampToByte(g) << 8) | (ClampToByte(r) << 16) | 0xFF000000;				

            // Desaturate 
            topLayer = DesaturateOp_Apply(topLayer);
			
			byte* topLayer8 = (byte*)&topLayer;
#ifdef INVERT_RED
            byte topLayerR = topLayer8[2];
			byte topLayerA = topLayer8[3];
            
#else
			byte topLayerR = topLayer8[0];
			byte topLayerA = topLayer8[3];
#endif 
			

            // Adjust Brightness and Contrast 
            if (topLayerR > (inkOutline * 255 / 100))
            {
                topLayer = 0xFFFFFF | (topLayer & 0xFF000000);
            }
            else
            {
                topLayer = 0 |(topLayer & 0xFF000000);
            }

            // Change Blend Mode to Darken 
            BMP_ARGB myPixel = DarkenBlendOp_Apply(topLayer, *dstPtr);
            *dstPtr = myPixel;

            ++srcPtr;
            ++dstPtr;
        }
    }
	
#ifndef GLOBAL_BMP_MEMORY
	if (bDelete)
		DELETE_ARRAY(src);
#endif
	
}

void EdgeDetector(BMP_ARGB *data, int width, int height)
{
	unsigned char* image = (unsigned char*)data;
	int length = width * height;
	// Init gray matrix
	int* grayMatrix = NEW_ARRAY(int, 256);
	for (int i = 0; i <= 255; i++) 
		grayMatrix[i] = (i << 16) | (i << 8) | i;	
       
	int* luminance = NEW_ARRAY(int, width*height);
	
	int y, x, i;
	for (i = 0; i < length; i++, image += 4)
		luminance[i] = LUMINANCE(*image, *(image + 1), *(image + 2));
	
        
	int grayX, grayY;
	int magnitude;	
	
	image = (unsigned char*)data;
	for (y = 1; y < height-1; y++) 
	{
		for (x = 1; x < width-1; x++) 
		{			
			grayX = - luminance[x - 1 + (y-1)*width] + luminance[x - 1 + (y+1)*width]
					- 2* luminance[x + (y-1)*width] + 2* luminance[x + (y+1)*width]
					- luminance[x + (y-1)*width] + luminance[x + 1 + (y+1)*width];
			grayY = luminance[x -1 + (y-1)*width] + 2* luminance[x-1 + y*width] + luminance[x - 1 + (y+1)*width]
					- luminance[x + 1 + (y-1)*width] - 2* luminance[x+1 + y*width] - luminance[x + 1 + (y+1)*width];
			
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
         
	DELETE_ARRAY(grayMatrix);
	DELETE_ARRAY(luminance);
}

BMP_ARGB DifferenceBlendOp_Apply(BMP_ARGB lhs, BMP_ARGB rhs)
{
	int lhsA; 
	lhsA = lhs >> 24;  
	
	int rhsA; 
	rhsA = rhs >> 24; 

    int y = (lhsA * (0xff - rhsA)) + 0x80;
    y = ((y >> 8) + y) >> 8;
    int totalA = y + rhsA;
    if (totalA == 0)
    {        
        return 0;
    }

	int rhsB, rhsG, rhsR;
	rhsB = rhs & 0xFF;
	rhsG = (rhs & 0xFF00) >> 8;
	rhsR = (rhs & 0xFF0000) >> 16;

	int lhsB, lhsG, lhsR;
	lhsB = lhs & 0xFF;
	lhsG = (lhs & 0xFF00) >> 8;
	lhsR = (lhs & 0xFF0000) >> 16;
    
	int fB = abs((int) (rhsB - lhsB));
    int fG = abs((int) (rhsG - lhsG));
    int fR = abs((int) (rhsR - lhsR));

    int x = (lhsA * rhsA) + 0x80;
    x = ((x >> 8) + x) >> 8;
    int z = rhsA - x;
    int masIndex = totalA * 3;
    
	BMP_ARGB taM = masTable[masIndex];
	BMP_ARGB taA = masTable[masIndex + 1];

#if _WIN32
	BMP_ARGB taS = masTable[masIndex + 2];
#else
	BMP_ARGB taS = masTable[masIndex + 2] % 32;
#endif

	BMP_ARGB test = (((((lhsB * y) + (rhsB * z)) + (fB * x)) * taM) + taA);
	BMP_ARGB val = test >> taS;

    BMP_ARGB b = (BMP_ARGB) ((((((lhsB * y) + (rhsB * z)) + (fB * x)) * taM) + taA) >> taS);
    BMP_ARGB g = (BMP_ARGB) ((((((lhsG * y) + (rhsG * z)) + (fG * x)) * taM) + taA) >> taS);
    BMP_ARGB r = (BMP_ARGB) ((((((lhsR * y) + (rhsR * z)) + (fR * x)) * taM) + taA) >> taS);
    int a = (lhsA * (0xff - rhsA)) + 0x80;
    a = ((a >> 8) + a) >> 8;
    a += rhsA;

	BMP_ARGB ret = ((b | (g << 8)) | (r << 0x10)) | ((BMP_ARGB) (a << 0x18));	
	//BMP_ARGB ret = b + (g << 8) + (r << 16) + ((BMP_ARGB)a << 24); 
    return ret;
	

	/*
	int lhsA; 
	lhsA = lhs >> 24; 
	int rhsA; 
	rhsA = rhs >> 24;
	
	int y; 
	y = ((lhsA) * (255 - rhsA) + 0x80); 
	y = ((((y) >> 8) + (y)) >> 8);

	int totalA = y + rhsA; 
	
	BMP_ARGB ret; 
	if (totalA == 0) 
	{ 
		ret = 0; 
	} 
	else 
	{ 
		int rhsB, rhsG, rhsR;
		rhsB = rhs & 0xFF;
		rhsG = (rhs & 0xFF00) >> 8;
		rhsR = (rhs & 0xFF0000) >> 16;

		int lhsB, lhsG, lhsR;
		lhsB = lhs & 0xFF;
		lhsG = (lhs & 0xFF00) >> 8;
		lhsR = (lhs & 0xFF0000) >> 16;

		int fB; int fG; int fR; 
		fB = abs((rhsB) - (lhsB));
		fG = abs((rhsG) - (lhsG));
		fR = abs((rhsR) - (lhsR));
		
		int x; 
		x = ((lhsA) * (rhsA) + 0x80); 
		x = ((((x) >> 8) + (x)) >> 8);
		
		int z = rhsA - x; 
		int masIndex = totalA * 3; 
		
		BMP_ARGB taM = masTable[masIndex]; 
		BMP_ARGB taA = masTable[masIndex + 1]; 
		BMP_ARGB taS = masTable[masIndex + 2]; 
		
		BMP_ARGB b = (BMP_ARGB)(((((long)(((lhsB * y) + (rhsB * z) + (fB * x)))) * taM) + taA) >> (int)taS); 
		BMP_ARGB g = (BMP_ARGB)(((((long)(((lhsG * y) + (rhsG * z) + (fG * x)))) * taM) + taA) >> (int)taS); 
		BMP_ARGB r = (BMP_ARGB)(((((long)(((lhsR * y) + (rhsR * z) + (fR * x)))) * taM) + taA) >> (int)taS); 
		
		int a; { { a = ((lhsA) * (255 - (rhsA)) + 0x80); 
		a = ((((a) >> 8) + (a)) >> 8); 
		a += (rhsA); 
		ret = b + (g << 8) + (r << 16) + ((BMP_ARGB)a << 24); 
	}
	return ret; 
	*/
}

static BMP_ARGB DarkenBlendOp_Apply(BMP_ARGB lhs, BMP_ARGB rhs)
{
	BMP_ARGB ret;
    int lhsA = lhs >> 24;
    int rhsA = rhs >> 24;
    int y = (lhsA * (0xff - rhsA)) + 0x80;
    y = ((y >> 8) + y) >> 8;
    int totalA = y + rhsA;
    if (totalA == 0)
    {
        ret = 0;
        return ret;
    }
	int rhsB, rhsG, rhsR;
	rhsB = rhs & 0xFF;
	rhsG = (rhs & 0xFF00) >> 8;
	rhsR = (rhs & 0xFF0000) >> 16;

	int lhsB, lhsG, lhsR;
	lhsB = lhs & 0xFF;
	lhsG = (lhs & 0xFF00) >> 8;
	lhsR = (lhs & 0xFF0000) >> 16;

    int fB = MIN(lhsB, rhsB);
    int fG = MIN(lhsG, rhsG);
    int fR = MIN(lhsR, rhsR);
    int x = (lhsA * rhsA) + 0x80;
    x = ((x >> 8) + x) >> 8;
    int z = rhsA - x;
    int masIndex = totalA * 3;
    BMP_ARGB taM = masTable[masIndex];
    BMP_ARGB taA = masTable[masIndex + 1];
#if _WIN32
	BMP_ARGB taS = masTable[masIndex + 2];
#else
	BMP_ARGB taS = masTable[masIndex + 2] % 32;
#endif
    BMP_ARGB b = (BMP_ARGB) ((((((lhsB * y) + (rhsB * z)) + (fB * x)) * taM) + taA) >> taS);
    BMP_ARGB g = (BMP_ARGB) ((((((lhsG * y) + (rhsG * z)) + (fG * x)) * taM) + taA) >> taS);
    BMP_ARGB r = (BMP_ARGB) ((((((lhsR * y) + (rhsR * z)) + (fR * x)) * taM) + taA) >> taS);
    int a = (lhsA * (0xff - rhsA)) + 0x80;
    a = ((a >> 8) + a) >> 8;
    a += rhsA;
    ret = ((b | (g << 8)) | (r << 0x10)) | ((BMP_ARGB) (a << 0x18));
    return ret;
}

static BMP_ARGB ScreenBlendOp_Apply(BMP_ARGB lhs, BMP_ARGB rhs)
{
    BMP_ARGB ret;
    int lhsA = lhs>>24;
    int rhsA = rhs>>24;
    int y = (lhsA * (0xff - rhsA)) + 0x80;
    y = ((y >> 8) + y) >> 8;
    int totalA = y + rhsA;
    if (totalA == 0)
    {
        ret = 0;
        return ret;
    }
	
	int rhsB, rhsG, rhsR;
	rhsB = rhs & 0xFF;
	rhsG = (rhs & 0xFF00) >> 8;
	rhsR = (rhs & 0xFF0000) >> 16;

	int lhsB, lhsG, lhsR;
	lhsB = lhs & 0xFF;
	lhsG = (lhs & 0xFF00) >> 8;
	lhsR = (lhs & 0xFF0000) >> 16;

    int fB = (rhsB * lhsB) + 0x80;
    fB = ((fB >> 8) + fB) >> 8;
    fB = (rhsB + lhsB) - fB;
    int fG = (rhsG * lhsG) + 0x80;
    fG = ((fG >> 8) + fG) >> 8;
    fG = (rhsG + lhsG) - fG;
    int fR = (rhsR * lhsR) + 0x80;
    fR = ((fR >> 8) + fR) >> 8;
    fR = (rhsR + lhsR) - fR;
    int x = (lhsA * rhsA) + 0x80;
    x = ((x >> 8) + x) >> 8;
    int z = rhsA - x;
    int masIndex = totalA * 3;
    BMP_ARGB taM = masTable[masIndex];
    BMP_ARGB taA = masTable[masIndex + 1];
#if _WIN32
	BMP_ARGB taS = masTable[masIndex + 2];
#else
	BMP_ARGB taS = masTable[masIndex + 2] % 32;
#endif
    BMP_ARGB b = (BMP_ARGB) ((((((lhsB * y) + (rhsB * z)) + (fB * x)) * taM) + taA) >> taS);
    BMP_ARGB g = (BMP_ARGB) ((((((lhsG * y) + (rhsG * z)) + (fG * x)) * taM) + taA) >> taS);
    BMP_ARGB r = (BMP_ARGB) ((((((lhsR * y) + (rhsR * z)) + (fR * x)) * taM) + taA) >> taS);
    int a = (lhsA * (0xff - rhsA)) + 0x80;
    a = ((a >> 8) + a) >> 8;
    a += rhsA;
    ret = ((b | (g << 8)) | (r << 0x10)) | ((BMP_ARGB) (a << 0x18));
    return ret;
}

BMP_ARGB DesaturateOp_Apply(BMP_ARGB color)
{
	byte i = GetIntensityByte(color);
	//return ColorBgra.FromBgra(i, i, i, color.A);
	return (i | (i << 8) | (i << 16) | (color & 0xFF000000));

}

unsigned char ClampToByte(int x)
{
    if (x > 255)
    {
        return 255;
    }
    else if (x < 0)
    {
        return 0;
    }
    else
    {
        return (unsigned char)x;
    }

}


void EdgeMaster(BMP_ARGB *data, int width, int height, int color, int amount)
{
	//Rectangle boundsInt = base.get_EnvironmentParameters().GetSelection(src.get_Bounds()).GetBoundsInt();
#ifndef GLOBAL_BMP_MEMORY
	bool bDelete = false;
	if (src == NULL)
	{
		bDelete = true;
		src = NEW_ARRAY(BMP_ARGB, width * height);
		memcpy(src, data, width*height*sizeof(BMP_ARGB));
	}
#endif
	memcpy(src, data, width*height*sizeof(BMP_ARGB));

	byte* color8 = (byte*)&color;
#ifdef INVERT_RED
	byte sr8 = color8[2];
	byte sg8 = color8[1];
	byte sb8 = color8[0];
#else
	byte sr8 = color8[0];
	byte sg8 = color8[1];
	byte sb8 = color8[2];
#endif

    for (int i = 0; i < height; i++)
    {
        int top = i - 1;
        if (top < 0)
        {
            top = 0;
        }
        int num3 = i + 1;
        if (num3 > height - 1)
        {
            num3 = height - 1;
        }
        for (int j = 0; j < width; j++)
        {
            int left = j - 1;
            if (left < 0)
            {
                left = 0;
            }
            int num6 = j + 1;
            if (num6 > (width - 1))
            {
                num6 = width - 1;
            }

            BMP_ARGB bgra = src[j + i*width];
            BMP_ARGB bgra2 = DifferenceBlendOp_Apply(bgra, src[left + top*width]);
            BMP_ARGB bgra3 = DifferenceBlendOp_Apply(bgra, src[num6 + num3*width]);
            BMP_ARGB bgra4 = DifferenceBlendOp_Apply(bgra, src[left + num3*width]);
            BMP_ARGB bgra5 = DifferenceBlendOp_Apply(bgra, src[num6 + top*width]);

			int bgra2_R = (bgra2 & 0xFF0000) >> 16;
			int bgra3_R = (bgra3 & 0xFF0000) >> 16;
			int bgra4_R = (bgra4 & 0xFF0000) >> 16;
			int bgra5_R = (bgra5 & 0xFF0000) >> 16;

			int bgra2_G = (bgra2 & 0xFF00) >> 8;
			int bgra3_G = (bgra3 & 0xFF00) >> 8;
			int bgra4_G = (bgra4 & 0xFF00) >> 8;
			int bgra5_G = (bgra5 & 0xFF00) >> 8;

			int bgra2_B = (bgra2 & 0xFF);
			int bgra3_B = (bgra3 & 0xFF);
			int bgra4_B = (bgra4 & 0xFF);
			int bgra5_B = (bgra5 & 0xFF);

			int num7 = (((bgra2_R + bgra3_R) + bgra4_R) + bgra5_R) / 4;
            int num8 = (((bgra2_G + bgra3_G) + bgra4_G) + bgra5_G) / 4;
            int num9 = (((bgra2_B + bgra3_B) + bgra4_B) + bgra5_B) / 4;

            int alpha = ((num7 + num8) + num9) / 3;
            alpha = ClampToByte(alpha * amount);
//#ifdef _WIN32
//			data[j + i*width] = color | (alpha << 24);
//#else
			byte rb = (byte)((sb8 - 0xFF)*alpha/255 + 0xFF);
			byte rg = (byte)((sg8 - 0xFF)*alpha/255 + 0xFF);
			byte rr = (byte)((sr8 - 0xFF)*alpha/255 + 0xFF);
			
			data[j + i*width] = rb | (rg << 8) | (rr << 16) | 0xFF000000;            
//#endif 
        }
    }
	
#ifndef GLOBAL_BMP_MEMORY
	if (bDelete)
		DELETE_ARRAY(src);
#endif
	/*
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
	for (y = 1; y < height-1; y++) 
	{
		for (x = 1; x < width-1; x++) 
		{			
			grayX = - luminance[x - 1 + (y-1)*width] + luminance[x - 1 + (y+1)*width]
					- 2* luminance[x + (y-1)*width] + 2* luminance[x + (y+1)*width]
					- luminance[x + (y-1)*width] + luminance[x + 1 + (y+1)*width];
			grayY = luminance[x -1 + (y-1)*width] + 2* luminance[x-1 + y*width] + luminance[x - 1 + (y+1)*width]
					- luminance[x + 1 + (y-1)*width] - 2* luminance[x+1 + y*width] - luminance[x + 1 + (y+1)*width];
			
			magnitude = 255 - (abs(grayX) + abs(grayY));
		  
			int grayscaleColor = grayMatrix[magnitude];

			// Apply the color into a new image
			data[x + y*width] = color;

			int num10 = ClampToByte(255 - magnitude* amount);
			int offset = (x + y*width)*4;
			*(image + offset + 3) = num10;			
		}		
	}
         
	delete[] grayMatrix;
	delete[] luminance;
	*/
	
}

//http://forums.getpaint.net/index.php?/topic/1671-toon-filter/
void ToonEffect(BMP_ARGB *data, int width, int height)
{
	// filter kernel
	const int size = 5; // odd number

	//play around with the matrix for interesting effects.
	const int conv [size][size] = {
			                       {-1,  -1,  -1,  -1, -1},
			                       {-1,  -1,  -1,  -1, -1},
			                       {-1,  -1,  30,  -1, -1},
			                       {-1,  -1,  -1,  -1, -1},
			                       {-1,  -1,  -5,  -1, -1},
    				              };

    int radius = (size-1)/2;

#ifndef GLOBAL_BMP_MEMORY
	bool bDelete = false;
	if (src == NULL)
	{
		bDelete = true;
		src = NEW_ARRAY(BMP_ARGB, width * height);
		memcpy(src, data, width*height*sizeof(BMP_ARGB));
	}
#endif
	memcpy(src, data, width*height*sizeof(BMP_ARGB));

    for(int y = 0; y < height; y++)
    {
        int top = y - radius;
		int bottom = y + radius;
		
        if (top < 0) 
			top = 0;
        
		if (bottom >= height) 
			bottom = height - 1;

        for (int x = 0; x < width; x++)
        {
            int left = x - radius;
			int right = x + radius;
            int c = 0, s = 0, r = 0, g = 0, b = 0;
            
			if (left < 0) 
				left = 0;
            
			if (right >= width) 
				right = width - 1;

            for (int v = top; v <= bottom; v++)
            {
                //ColorBgra *pRow = src.GetRowAddressUnchecked(v);
                BMP_ARGB *pRow = src + v*width;
				
				int j = v - y + radius;                
                for (int u = left; u <= right; u++)
                {
                    int i = u - x + radius;
                    int w = conv[i][j];
                    //ColorBgra *pRef = pRow + u;
					BMP_ARGB* pRef = pRow + u;
					unsigned char* pRef8 = (unsigned char*)pRef;
                    b += (*pRef8) * w;
                    g += (*(pRef8 + 1)) * w;
                    r += (*(pRef8 + 2)) * w;					
                    s += w;
                    c++;
                }
            }
            data[x + y*width] = ClampToByte(b) | (ClampToByte(g) << 8) | (ClampToByte(r) << 16) | 0xFF000000;
        }		
    }

#ifndef GLOBAL_BMP_MEMORY
	if (bDelete)
		DELETE_ARRAY(src);
#endif
}

byte GetIntensityByte(BMP_ARGB rgba)
{
	byte* rgba8 = (byte*)&rgba;

#ifdef INVERT_RED
    return (byte)((7471 * (*(rgba8)) + 38470 * (*(rgba8 + 1)) + 19595 * (*(rgba8 + 2))) >> 16);
#else
	return (byte)((7471 * (*(rgba8 + 2)) + 38470 * (*(rgba8 + 1)) + 19595 * (*(rgba8))) >> 16);
	//return (byte)((7471 * B + 38470 * G + 19595 * R) >> 16);
#endif	
}

static byte FastScaleByteByByte(byte a, byte b)
{
    int r1 = a * b + 0x80;
    int r2 = ((r1 >> 8) + r1) >> 8;
    return (byte)r2;
}


void OilEffect(BMP_ARGB *data, int width, int height, int range, int levels)
{
	/*
	int index = 0;
	int* rHistogram = new int[levels];
	int* gHistogram = new int[levels];
	int* bHistogram = new int[levels];
	int* rTotal = new int[levels];
	int* gTotal = new int[levels];
	int* bTotal = new int[levels];
	BMP_ARGB* outPixels = new BMP_ARGB[width * height];
	memcpy(outPixels, data, width*height*4);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			for (int i = 0; i < levels; i++)
				rHistogram[i] = gHistogram[i] = bHistogram[i] = rTotal[i] = gTotal[i] = bTotal[i] = 0;

			for (int row = -range; row <= range; row++) {
				int iy = y+row;
				int ioffset;
				if (0 <= iy && iy < height) {
					ioffset = iy*width;
					for (int col = -range; col <= range; col++) {
						int ix = x+col;
						if (0 <= ix && ix < width) {
							int rgb = outPixels[ioffset+ix];
							int r = (rgb >> 16) & 0xff;
							int g = (rgb >> 8) & 0xff;
							int b = rgb & 0xff;
							int ri = r*levels/256;
							int gi = g*levels/256;
							int bi = b*levels/256;
							rTotal[ri] += r;
							gTotal[gi] += g;
							bTotal[bi] += b;
							rHistogram[ri]++;
							gHistogram[gi]++;
							bHistogram[bi]++;
						}
					}
				}
			}
			
			int r = 0, g = 0, b = 0;
			for (int i = 1; i < levels; i++) {
				if (rHistogram[i] > rHistogram[r])
					r = i;
				if (gHistogram[i] > gHistogram[g])
					g = i;
				if (bHistogram[i] > bHistogram[b])
					b = i;
			}
			r = rTotal[r] / rHistogram[r];
			g = gTotal[g] / gHistogram[g];
			b = bTotal[b] / bHistogram[b];
			data[index] = (outPixels[index] & 0xff000000) | ( r << 16 ) | ( g << 8 ) | b;
			index++;
		}
	}

	delete[] rHistogram;
	delete[] gHistogram;
	delete[] bHistogram;
	delete[] rTotal;
	delete[] gTotal;
	delete[] bTotal;
	delete[] outPixels;
	*/

#ifndef GLOBAL_BMP_MEMORY
	bool bDelete = false;
	if (src == NULL)
	{
		bDelete = true;
		src = NEW_ARRAY(BMP_ARGB, width * height);
		memcpy(src, data, width*height*sizeof(BMP_ARGB));
	}
#endif
	memcpy(src, data, width*height*sizeof(BMP_ARGB));

	int coarseness = levels;
	int brushSize = range;

    //Surface src = SrcArgs.Surface;
    //Surface dst = DstArgs.Surface;
    //int width = src.Width;
    //int height = src.Height;

    int arrayLens = 1 + coarseness;

    int localStoreSize = arrayLens * 5 * sizeof(int);

    byte* localStore = NEW_ARRAY(byte, localStoreSize);
    byte* p = localStore;

    int* intensityCount = (int*)p;
    p += arrayLens * sizeof(int);

    BMP_ARGB* avgRed = (BMP_ARGB*)p;
    p += arrayLens * sizeof(BMP_ARGB);

    BMP_ARGB* avgGreen = (BMP_ARGB*)p;
    p += arrayLens * sizeof(BMP_ARGB);

    BMP_ARGB* avgBlue = (BMP_ARGB*)p;
    p += arrayLens * sizeof(BMP_ARGB);

    BMP_ARGB* avgAlpha = (BMP_ARGB*)p;
    p += arrayLens * sizeof(BMP_ARGB);

    byte maxIntensity = coarseness;

    for (int y = 0; y < height; ++y)
    {
        BMP_ARGB *dstPtr = data + y*width;

        int top = y - brushSize;
        int bottom = y + brushSize + 1;

        if (top < 0)
        {
            top = 0;
        }

        if (bottom > height)
        {
            bottom = height;
        }

        for (int x = 0; x < width; ++x)
        {
            memset(localStore, 0, localStoreSize);

            int left = x - brushSize;
            int right = x + brushSize + 1;

            if (left < 0)
            {
                left = 0;
            }

            if (right > width)
            {
                right = width;
            }

            int numInt = 0;

            for (int j = top; j < bottom; ++j)
            {
                BMP_ARGB *srcPtr = src + left + j*width;

                for (int i = left; i < right; ++i)
                {
#ifndef OPTIMIZE_SPEED_BY_MACRO
					byte getIntensityByte = GetIntensityByte(*srcPtr);
                    byte intensity = FastScaleByteByByte(getIntensityByte, maxIntensity);
#else
					byte getIntensityByte;
					GET_INTENSITY_BYTE(*srcPtr, getIntensityByte);
                    byte intensity;
					FAST_SCALE_BYTE_BY_BYTE(getIntensityByte, maxIntensity, intensity);
#endif
                    ++intensityCount[intensity];
                    ++numInt;

					byte* srcPtr8 = (byte*)srcPtr;
#ifdef INVERT_RED
                    avgRed[intensity] += *(srcPtr8 + 2);
                    avgGreen[intensity] += *(srcPtr8 + 1);
                    avgBlue[intensity] += *srcPtr8;
                    avgAlpha[intensity] += *(srcPtr8 + 3);
#else
					avgRed[intensity] += *srcPtr8;
                    avgGreen[intensity] += *(srcPtr8 + 1);
                    avgBlue[intensity] += *(srcPtr8 + 2);
                    avgAlpha[intensity] += *(srcPtr8 + 3);
#endif

                    ++srcPtr;
                }
            }

            byte chosenIntensity = 0;
            int maxInstance = 0;

            for (int i = 0; i <= maxIntensity; ++i)
            {
                if (intensityCount[i] > maxInstance)
                {
                    chosenIntensity = (byte)i;
                    maxInstance = intensityCount[i];
                }
            }

            // TODO: correct handling of alpha values?

            byte R = (byte)(avgRed[chosenIntensity] / maxInstance);
            byte G = (byte)(avgGreen[chosenIntensity] / maxInstance);
            byte B = (byte)(avgBlue[chosenIntensity] / maxInstance);
            byte A = (byte)(avgAlpha[chosenIntensity] / maxInstance);

            *dstPtr = (A << 24) | ( R << 16 ) | ( G << 8 ) | B; 			
            ++dstPtr;
        }
    }
	
#ifndef GLOBAL_BMP_MEMORY
	if (bDelete)
		DELETE_ARRAY(src);
#endif

	DELETE_ARRAY(localStore);
}

double AngleConstrain(double MyAngle)
{
    if (MyAngle >= 360.0)
    {
        MyAngle -= floor((double) (MyAngle / 360.0)) * 360.0;
    }
    if (MyAngle < 0.0)
    {
        MyAngle += 360.0;
    }
    return MyAngle;
}

double EvanMax3(double x, double y, double z)
{
    if (x <= y)
    {
        if (y <= z)
        {
            return z;
        }
        return y;
    }
    if (x <= z)
    {
        return z;
    }
    return x;
}

double EvanMin3(double x, double y, double z)
{
    if (x >= y)
    {
        if (y >= z)
        {
            return z;
        }
        return y;
    }
    if (x >= z)
    {
        return z;
    }
    return x;
}

static void EvanRGBtoHSV(int R, int G, int B, double &outH, double &outS, double &outV)
{
	double x = ((double) R) / 255.0;
    double y = ((double) G) / 255.0;
    double z = ((double) B) / 255.0;
    double num4 = EvanMax3(x, y, z);
    double num5 = EvanMin3(x, y, z);
    double num6 = num4 - num5;
    outV = num4;
    if (num4 == 0.0)
    {
        outH = -999.0;
        outS = 0.0;
    }
    else
    {
        outS = num6 / num4;
        if (num4 == num5)
        {
            outH = -999.0;
        }
        else
        {
            if (x == num4)
            {
                outH = ((y - z) / num6) * 60.0;
            }
            else if (y == num4)
            {
                outH = (2.0 + ((z - x) / num6)) * 60.0;
            }
            else
            {
                outH = (4.0 + ((x - y) / num6)) * 60.0;
            }
            if (outH < 0.0)
            {
                outH += 360.0;
            }
        }
    }

}

static void EvanHSVtoRGB(double H, double S, double V, byte &bR, byte &bG, byte &bB)
{
	if ((S == 0.0) || (H == -999.0))
    {
        byte num = (byte) ((int) (V * 255.0));
        bR = num;
        bG = num;
        bB = num;
    }
    else
    {
        if (H >= 360.0)
        {
            H = AngleConstrain(H);
        }
        double num2 = V;
        double num3 = V;
        double num4 = V;
        //double num5 = floor((double) (H / 60.0));
		int num5 = (int)floor((double) (H / 60.0));
        double num6 = (H / 60.0) - num5;
        double num7 = V * (1.0 - S);
        double num8 = V * (1.0 - (num6 * S));
        double num9 = V * (1.0 - ((1.0 - num6) * S));
        switch (num5)
        {
            case 0:
                num2 = V;
                num3 = num9;
                num4 = num7;
                break;

            case 1:
                num2 = num8;
                num3 = V;
                num4 = num7;
                break;

            case 2:
                num2 = num7;
                num3 = V;
                num4 = num9;
                break;

            case 3:
                num2 = num7;
                num3 = num8;
                num4 = V;
                break;

            case 4:
                num2 = num9;
                num3 = num7;
                num4 = V;
                break;

            case 5:
                num2 = V;
                num3 = num7;
                num4 = num8;
                break;
        }
        int num10 = (int) (num2 * 255.0);
        int num11 = (int) (num3 * 255.0);
        int num12 = (int) (num4 * 255.0);
        bR = (byte) num10;
        bG = (byte) num11;
        bB = (byte) num12;
    }
}

void PastelEffect(BMP_ARGB *data, int width, int height, int range, int levels)
{
	OilEffect(data, width, height, range, levels);

	double outH = 0.0;
    double outS = 0.0;
    double outV = 0.0;
    double num4 = 36.0;
    double num5 = 1.0;
    double num6 = 30.0;
    double num7 = 360.0 / num4;

	for (int i = 0; i < height; i++)
    {
        BMP_ARGB* pointAddressUnchecked = data + i*width;
        for (int j = 0; j < width; j++)
        {
            //BMP_ARGB bgra = pointAddressUnchecked[0];
			byte* bgra8 = (byte*)pointAddressUnchecked;
#ifdef INVERT_RED
	#ifndef OPTIMIZE_SPEED_BY_MACRO
				EvanRGBtoHSV(*(bgra8 + 2), *(bgra8 + 1), *bgra8, outH, outS, outV);
	#else
				EVAN_RGB_TO_HSV(*(bgra8 + 2), *(bgra8 + 1), *bgra8, outH, outS, outV);
	#endif 
#else
	#ifndef OPTIMIZE_SPEED_BY_MACRO
			EvanRGBtoHSV(*bgra8, *(bgra8 + 1), *(bgra8 + 2), outH, outS, outV);
	#else
			EVAN_RGB_TO_HSV(*bgra8, *(bgra8 + 1), *(bgra8 + 2), outH, outS, outV);
	#endif
#endif
            outH = num7 * (int)(outH / num7);
            outS /= num5;
            outV *= 100.0;
            outV /= num6 * 10.0;
            outV += (1.0 - (num6 / 100.0)) + 0.1;
            if (outV > 1.0)
            {
                outV = 1.0;
            }
            byte r, g, b;

#ifndef OPTIMIZE_SPEED_BY_MACRO
			EvanHSVtoRGB(outH, outS, outV, r, g, b);			
#else
			EVAN_HSV_TO_RGB(outH, outS, outV, r, g, b);			
#endif

            *pointAddressUnchecked = 0xFF000000 | (r << 16) | (g << 8) | b;
            pointAddressUnchecked++;
        }
    }
}

void DreamEffect(BMP_ARGB *data, int width, int height, int focus)
{
#ifndef GLOBAL_BMP_MEMORY
	bool bDelete = false;
	if (src == NULL)
	{
		bDelete = true;
		src = NEW_ARRAY(BMP_ARGB, width * height);
		memcpy(src, data, width*height*sizeof(BMP_ARGB));
	}
#endif
	memcpy(src, data, width*height*sizeof(BMP_ARGB));

	GaussianBlur_PDN(data, width, height, focus);

	for (int i = 0; i < height; i++)
    {
        BMP_ARGB* pointAddressUnchecked = src + i*width;		
        BMP_ARGB* bgraPtr2 =  data + i*width;
        for (int j = 0; j < width; j++)
        {
            *bgraPtr2 = DarkenBlendOp_Apply(*pointAddressUnchecked, *bgraPtr2);
            pointAddressUnchecked++;
            bgraPtr2++;
        }
    }

#ifndef GLOBAL_BMP_MEMORY
	if (bDelete)
		DELETE_ARRAY(src);
#endif
}
//static int lerp(float t, int a, int b)
inline int lerp(float t, int a, int b)
{
	return (int)(a + t * (b - a));
}
static int mixColors(float t, int rgb1, int rgb2)
{
	int a1 = (rgb1 >> 24) & 0xff;
	int r1 = (rgb1 >> 16) & 0xff;
	int g1 = (rgb1 >> 8) & 0xff;
	int b1 = rgb1 & 0xff;
	int a2 = (rgb2 >> 24) & 0xff;
	int r2 = (rgb2 >> 16) & 0xff;
	int g2 = (rgb2 >> 8) & 0xff;
	int b2 = rgb2 & 0xff;
	a1 = lerp(t, a1, a2);
	r1 = lerp(t, r1, r2);
	g1 = lerp(t, g1, g2);
	b1 = lerp(t, b1, b2);
	return (a1 << 24) | (r1 << 16) | (g1 << 8) | b1;
}

void SmearEffect(BMP_ARGB *data, int width, int height)
{
	//param
	float angle = 0;
	float density = 0.5f;
	float scatter = 0.0f;
	int distance = 8;
	//Random randomGenerator;
	long seed = 567;
	//#define CROSSES		0
	//#define LINES			1
	//#define CIRCLES		2
	//#define SQUARES		3
	int shape = LINES;
	float mix = 0.5f;
	bool background = false;

	////
	BMP_ARGB* outPixels = NEW_ARRAY(BMP_ARGB,width * height);
	BMP_ARGB* inPixels = data;

	//randomGenerator.setSeed(seed);
	srand(seed);
	float sinAngle = (float)sin(angle);
	float cosAngle = (float)cos(angle);

	int i = 0;
	int numShapes;

	//for (int y = 0; y < height; y++)
	//	for (int x = 0; x < width; x++) {
	//		outPixels[i] = background ? 0xffffffff : inPixels[i];
	//		i++;
	//	}
	if (background)
		memset(outPixels, 0xFF, width*height*sizeof(BMP_ARGB));
	else
		memcpy(outPixels, data, width*height*sizeof(BMP_ARGB));

	switch (shape) {
	case CROSSES:
		//Crosses
		numShapes = (int)(2*density*width * height / (distance + 1));
		for (i = 0; i < numShapes; i++) {
			//int x = (randomGenerator.nextInt() & 0x7fffffff) % width;
			//int y = (randomGenerator.nextInt() & 0x7fffffff) % height;
			//int length = randomGenerator.nextInt() % distance + 1;
			int x = (rand() & 0x7fffffff) % width;
			int y = (rand() & 0x7fffffff) % height;
			int length = rand() % distance + 1;
			int rgb = inPixels[y*width+x];
			for (int x1 = x - length; x1 < x + length + 1; x1++) {
				if (x1 >= 0 && x1 < width) {
					int rgb2 = background ? 0xffffffff : outPixels[y*width+x1];
					outPixels[y*width+x1] = mixColors(mix, rgb2, rgb);
				}
			}
			for (int y1 = y - length; y1 < y + length + 1; y1++) {
				if (y1 >= 0 && y1 < height) {
					int rgb2 = background ? 0xffffffff : outPixels[y1*width+x];
					outPixels[y1*width+x] = mixColors(mix, rgb2, rgb);
				}
			}
		}
		break;
	case LINES:
		numShapes = (int)(2*density*width * height / 2);

		for (i = 0; i < numShapes; i++) {
			int sx = (rand() & 0x7fffffff) % width;
			int sy = (rand() & 0x7fffffff) % height;
			int rgb = inPixels[sy*width+sx];
			int length = (rand() & 0x7fffffff) % distance;
			int dx = (int)(length*cosAngle);
			int dy = (int)(length*sinAngle);

			int x0 = sx-dx;
			int y0 = sy-dy;
			int x1 = sx+dx;
			int y1 = sy+dy;
			int x, y, d, incrE, incrNE, ddx, ddy;
			
			if (x1 < x0)
				ddx = -1;
			else
				ddx = 1;
			if (y1 < y0)
				ddy = -1;
			else
				ddy = 1;
			dx = x1-x0;
			dy = y1-y0;
			dx = abs(dx);
			dy = abs(dy);
			x = x0;
			y = y0;

			if (x < width && x >= 0 && y < height && y >= 0) {
				int rgb2 = background ? 0xffffffff : outPixels[y*width+x];
				outPixels[y*width+x] = mixColors(mix, rgb2, rgb);
			}
			if (abs(dx) > abs(dy)) {
				d = 2*dy-dx;
				incrE = 2*dy;
				incrNE = 2*(dy-dx);

				while (x != x1) {
					if (d <= 0)
						d += incrE;
					else {
						d += incrNE;
						y += ddy;
					}
					x += ddx;
					if (x < width && x >= 0 && y < height && y >= 0) {
						int rgb2 = background ? 0xffffffff : outPixels[y*width+x];
						outPixels[y*width+x] = mixColors(mix, rgb2, rgb);
					}
				}
			} else {
				d = 2*dx-dy;
				incrE = 2*dx;
				incrNE = 2*(dx-dy);

				while (y != y1) {
					if (d <= 0)
						d += incrE;
					else {
						d += incrNE;
						x += ddx;
					}
					y += ddy;
					if (x < width && x >= 0 && y < height && y >= 0) {
						int rgb2 = background ? 0xffffffff : outPixels[y*width+x];
						outPixels[y*width+x] = mixColors(mix, rgb2, rgb);
					}
				}
			}
		}
		break;
	case SQUARES:
	case CIRCLES:
		int radius = distance+1;
		int radius2 = radius * radius;
		numShapes = (int)(2*density*width * height / radius);
		for (i = 0; i < numShapes; i++) {
			int sx = (rand() & 0x7fffffff) % width;
			int sy = (rand() & 0x7fffffff) % height;
			int rgb = inPixels[sy*width+sx];
			for (int x = sx - radius; x < sx + radius + 1; x++) {
				for (int y = sy - radius; y < sy + radius + 1; y++) {
					int f;
					if (shape == CIRCLES)
						f = (x - sx) * (x - sx) + (y - sy) * (y - sy);
					else
						f = 0;
					if (x >= 0 && x < width && y >= 0 && y < height && f <= radius2) {
						int rgb2 = background ? 0xffffffff : outPixels[y*width+x];
						outPixels[y*width+x] = mixColors(mix, rgb2, rgb);
					}
				}
			}
		}
	}

	memcpy(data, outPixels, width*height*sizeof(BMP_ARGB));

	DELETE_ARRAY(outPixels);
}

void SmearEffect(BMP_ARGB *data, int width, int height, int shape, float angle, float density,
							float scatter, int distance, float mix, bool background)
{
	long seed = 567;
	////
	BMP_ARGB* outPixels = NEW_ARRAY(BMP_ARGB,width * height);
	BMP_ARGB* inPixels = data;

	srand(seed);
	float sinAngle = (float)sin(angle);
	float cosAngle = (float)cos(angle);

	int i = 0;
	int numShapes;

	if (background)
		memset(outPixels, 0xFF, width*height*sizeof(BMP_ARGB));
	else
		memcpy(outPixels, data, width*height*sizeof(BMP_ARGB));

	switch (shape) {
	case CROSSES:
		//Crosses
		numShapes = (int)(2*density*width * height / (distance + 1));
		for (i = 0; i < numShapes; i++) {
			int x = (rand() & 0x7fffffff) % width;
			int y = (rand() & 0x7fffffff) % height;
			int length = rand() % distance + 1;
			int rgb = inPixels[y*width+x];
			for (int x1 = x - length; x1 < x + length + 1; x1++) 
			{
				if (x1 >= 0 && x1 < width) 
				{
					int rgb2 = background ? 0xffffffff : outPixels[y*width+x1];
					outPixels[y*width+x1] = mixColors(mix, rgb2, rgb);
				}
			}
			for (int y1 = y - length; y1 < y + length + 1; y1++) 
			{
				if (y1 >= 0 && y1 < height) 
				{
					int rgb2 = background ? 0xffffffff : outPixels[y1*width+x];
					outPixels[y1*width+x] = mixColors(mix, rgb2, rgb);
				}
			}
		}
		break;
	case LINES:
		numShapes = (int)(2*density*width * height / 2);

		for (i = 0; i < numShapes; i++) 
		{
			int sx = (rand() & 0x7fffffff) % width;
			int sy = (rand() & 0x7fffffff) % height;
			int rgb = inPixels[sy*width+sx];
			int length = (rand() & 0x7fffffff) % distance;
			int dx = (int)(length*cosAngle);
			int dy = (int)(length*sinAngle);

			int x0 = sx-dx;
			int y0 = sy-dy;
			int x1 = sx+dx;
			int y1 = sy+dy;
			int x, y, d, incrE, incrNE, ddx, ddy;

			if (x1 < x0)
				ddx = -1;
			else
				ddx = 1;
			if (y1 < y0)
				ddy = -1;
			else
				ddy = 1;
			dx = x1-x0;
			dy = y1-y0;
			dx = abs(dx);
			dy = abs(dy);
			x = x0;
			y = y0;

			if (x < width && x >= 0 && y < height && y >= 0) 
			{
				int rgb2 = background ? 0xffffffff : outPixels[y*width+x];
				outPixels[y*width+x] = mixColors(mix, rgb2, rgb);
			}
			if (abs(dx) > abs(dy)) 
			{
				d = 2*dy-dx;
				incrE = 2*dy;
				incrNE = 2*(dy-dx);

				while (x != x1) 
				{
					if (d <= 0)
						d += incrE;
					else 
					{
						d += incrNE;
						y += ddy;
					}
					x += ddx;
					if (x < width && x >= 0 && y < height && y >= 0) 
					{
						int rgb2 = background ? 0xffffffff : outPixels[y*width+x];
						outPixels[y*width+x] = mixColors(mix, rgb2, rgb);
					}
				}
			}
			else 
			{
				d = 2*dx-dy;
				incrE = 2*dx;
				incrNE = 2*(dx-dy);

				while (y != y1) 
				{
					if (d <= 0)
						d += incrE;
					else 
					{
						d += incrNE;
						x += ddx;
					}
					y += ddy;
					if (x < width && x >= 0 && y < height && y >= 0) 
					{
						int rgb2 = background ? 0xffffffff : outPixels[y*width+x];
						outPixels[y*width+x] = mixColors(mix, rgb2, rgb);
					}
				}
			}
		}
		break;
	case SQUARES:
	case CIRCLES:
		int radius = distance+1;
		int radius2 = radius * radius;
		numShapes = (int)(2*density*width * height / radius);
		for (i = 0; i < numShapes; i++) 
		{
			int sx = (rand() & 0x7fffffff) % width;
			int sy = (rand() & 0x7fffffff) % height;
			int rgb = inPixels[sy*width+sx];
			for (int x = sx - radius; x < sx + radius + 1; x++) 
			{
				for (int y = sy - radius; y < sy + radius + 1; y++) 
				{
					int f;
					if (shape == CIRCLES)
						f = (x - sx) * (x - sx) + (y - sy) * (y - sy);
					else
						f = 0;
					if (x >= 0 && x < width && y >= 0 && y < height && f <= radius2) 
					{
						int rgb2 = background ? 0xffffffff : outPixels[y*width+x];
						outPixels[y*width+x] = mixColors(mix, rgb2, rgb);
					}
				}
			}
		}
	}

	memcpy(data, outPixels, width*height*sizeof(BMP_ARGB));

	DELETE_ARRAY(outPixels);
}


int* CreateGaussianBlurRow(int amount, int &size)
{
	size = 1 + (amount * 2);
	int* weights = new int[size];

	for (int i = 0; i <= amount; ++i)
	{
		// 1 + aa - aa + 2ai - ii
		weights[i] = 16 * (i + 1);
		weights[size - i - 1] = weights[i];
	}
	
	return weights;
}

int** CreateGaussianBlurMatrix(int amount, int &size)
{
	size = 1 + (amount * 2);
    int center = size / 2;
    int** weights = new int*[size];

    for (int i = 0; i < size; ++i)
    {
        weights[i] = new int[size];

        for (int j = 0; j < size; ++j)
        {
            weights[i][j] = (int)(16 * sqrt((double)((j - center) * (j - center) + (i - center) * (i - center))));			
        }
    }

    int max = 0;
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (weights[i][j] > max)
            {
                max = weights[i][j];
            }
        }
    }

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            weights[i][j] = max - weights[i][j];
        }
    }

    return weights;
}

void GaussianBlur_PDN(BMP_ARGB *data, int width, int height, int radius)
{
	//Surface dst = DstArgs.Surface;
    //Surface src = SrcArgs.Surface;

	int r = radius;
	int wlen;
    int* w = CreateGaussianBlurRow(r, wlen);
    
    int localStoreSize = wlen * 6 * sizeof(long);
    byte* localStore = NEW_ARRAY(byte, localStoreSize);
    byte* p = localStore;

    long* waSums = (long*)p;
    p += wlen * sizeof(long);

    long* wcSums = (long*)p;
    p += wlen * sizeof(long);

    long* aSums = (long*)p;
    p += wlen * sizeof(long);

    long* bSums = (long*)p;
    p += wlen * sizeof(long);

    long* gSums = (long*)p;
    p += wlen * sizeof(long);

    long* rSums = (long*)p;
    p += wlen * sizeof(long);
    
    for (int y = 0; y < height; ++y)
    {
        memset(localStore, 0, localStoreSize);

        long waSum = 0;
        long wcSum = 0;
        long aSum = 0;
        long bSum = 0;
        long gSum = 0;
        long rSum = 0;

        BMP_ARGB* dstPtr = data +  y*width;

        for (int wx = 0; wx < wlen; ++wx)
        {
            int srcX = wx - r;
            waSums[wx] = 0;
            wcSums[wx] = 0;
            aSums[wx] = 0;
            bSums[wx] = 0;
            gSums[wx] = 0;
            rSums[wx] = 0;

            if (srcX >= 0 && srcX < width)
            {
                for (int wy = 0; wy < wlen; ++wy)
                {
                    int srcY = y + wy - r;

                    if (srcY >= 0 && srcY < height)
                    {
                        BMP_ARGB c = *(data + srcX +  srcY*width);
						byte* c8 = (byte*)&c;
#ifdef INVERT_RED
						byte cR = *(c8 + 2);
						byte cG = *(c8 + 1);
						byte cB = *c8;
						byte cA = *(c8 + 3);
#else
						byte cR = *c8;
						byte cG = *(c8 + 1);
						byte cB = *(c8 + 2);
						byte cA = *(c8 + 3);
#endif
							
                        int wp = w[wy];

                        waSums[wx] += wp;
                        wp *= cA + (cA >> 7);
                        wcSums[wx] += wp;
                        wp >>= 8;

                        aSums[wx] += wp * cA;
                        bSums[wx] += wp * cB;
                        gSums[wx] += wp * cG;
                        rSums[wx] += wp * cR;
                    }
                }

                int wwx = w[wx];
                waSum += wwx * waSums[wx];
                wcSum += wwx * wcSums[wx];
                aSum += wwx * aSums[wx];
                bSum += wwx * bSums[wx];
                gSum += wwx * gSums[wx];
                rSum += wwx * rSums[wx];
            }
        }

        wcSum >>= 8;

        if (waSum == 0 || wcSum == 0)
        {
            *dstPtr = 0;
        }
        else
        {
            int alpha = (int)(aSum / waSum);
            int blue = (int)(bSum / wcSum);
            int green = (int)(gSum / wcSum);
            int red = (int)(rSum / wcSum);

            *dstPtr = (alpha << 24) | (red << 16) | (green << 8) | blue;				
        }

        ++dstPtr;

        for (int x = 1; x < width; ++x)
        {
            for (int i = 0; i < wlen - 1; ++i)
            {
                waSums[i] = waSums[i + 1];
                wcSums[i] = wcSums[i + 1];
                aSums[i] = aSums[i + 1];
                bSums[i] = bSums[i + 1];
                gSums[i] = gSums[i + 1];
                rSums[i] = rSums[i + 1];
            }

            waSum = 0;
            wcSum = 0;
            aSum = 0;
            bSum = 0;
            gSum = 0;
            rSum = 0;

            int wx;
            for (wx = 0; wx < wlen - 1; ++wx)
            {
                long wwx = (long)w[wx];
                waSum += wwx * waSums[wx];
                wcSum += wwx * wcSums[wx];
                aSum += wwx * aSums[wx];
                bSum += wwx * bSums[wx];
                gSum += wwx * gSums[wx];
                rSum += wwx * rSums[wx];
            }

            wx = wlen - 1;

            waSums[wx] = 0;
            wcSums[wx] = 0;
            aSums[wx] = 0;
            bSums[wx] = 0;
            gSums[wx] = 0;
            rSums[wx] = 0;

            int srcX = x + wx - r;

            if (srcX >= 0 && srcX < width)
            {
                for (int wy = 0; wy < wlen; ++wy)
                {
                    int srcY = y + wy - r;

                    if (srcY >= 0 && srcY < height)
                    {
                        BMP_ARGB c = *(data + srcX + srcY * width);
						byte* c8 = (byte*)&c;

#ifdef INVERT_RED
						byte cR = *(c8 + 2);
						byte cG = *(c8 + 1);
						byte cB = *c8;
						byte cA = *(c8 + 3);
#else
						byte cR = *c8;
						byte cG = *(c8 + 1);
						byte cB = *(c8 + 2);
						byte cA = *(c8 + 3);
#endif


                        int wp = w[wy];

                        waSums[wx] += wp;
                        wp *= cA + (cA >> 7);
                        wcSums[wx] += wp;
                        wp >>= 8;

                        aSums[wx] += wp * (long)cA;
                        bSums[wx] += wp * (long)cB;
                        gSums[wx] += wp * (long)cG;
                        rSums[wx] += wp * (long)cR;
                    }
                }

                int wr = w[wx];
                waSum += (long)wr * waSums[wx];
                wcSum += (long)wr * wcSums[wx];
                aSum += (long)wr * aSums[wx];
                bSum += (long)wr * bSums[wx];
                gSum += (long)wr * gSums[wx];
                rSum += (long)wr * rSums[wx];
            }

            wcSum >>= 8;

            if (waSum == 0 || wcSum == 0)
            {
                *dstPtr = 0;
            }
            else
            {
                int alpha = (int)(aSum / waSum);
                int blue = (int)(bSum / wcSum);
                int green = (int)(gSum / wcSum);
                int red = (int)(rSum / wcSum);

                *dstPtr = (alpha << 24) | (red << 16) | (green << 8) | blue;
            }

            ++dstPtr;
        }
    }

	////
	DELETE_ARRAY(localStore);
}

void GlowEffect_PDN(BMP_ARGB *data, int width, int height, int radius, int brightness, int contrast)
{
#ifndef GLOBAL_BMP_MEMORY
	bool bDelete = false;
	if (src == NULL)
	{
		bDelete = true;
		src = NEW_ARRAY(BMP_ARGB, width * height);
		memcpy(src, data, width*height*sizeof(BMP_ARGB));
	}
#endif
	memcpy(src, data, width*height*sizeof(BMP_ARGB));

	GaussianBlur_PDN(data, width, height, radius);
	BrightnessAndContrastAdjustment_PDN(data, width, height, brightness, contrast);

	for (int y = 0; y < height; ++y)
    {
		for (int x = 0; x < width; x++)
        {
			BMP_ARGB dstPtr = data[x + y*width];
			BMP_ARGB srcPtr = src[x + y*width];
			
			data[x + y*width] = ScreenBlendOp_Apply(srcPtr, dstPtr);
		}
    }

#ifndef GLOBAL_BMP_MEMORY
	if (bDelete)
		DELETE_ARRAY(src);
#endif
	
}

void BrightnessAndContrastAdjustment_PDN(BMP_ARGB *data, int width, int height, int brightness, int contrast)
{
	int multiply, divide;

	byte* rgbTable = NULL;
	if (contrast < 0)
    {
        multiply = contrast + 100;
        divide = 100;
    }
    else if (contrast > 0)
    {
        multiply = 100;
        divide = 100 - contrast;
    }
    else
    {
        multiply = 1;
        divide = 1;
    }

    if (rgbTable == NULL)
    {
        rgbTable = NEW_ARRAY(byte, 65536);
    }

    if (divide == 0)
    {
        for (int intensity = 0; intensity < 256; ++intensity)
        {
            if (intensity + brightness < 128)
            {
                rgbTable[intensity] = 0;
            }
            else
            {
                rgbTable[intensity] = 255;
            }
        }
    }
    else if (divide == 100)
    {
        for (int intensity = 0; intensity < 256; ++intensity)
        {
            int shift = (intensity - 127) * multiply / divide + 127 - intensity + brightness;

            for (int col = 0; col < 256; ++col)
            {
                int index = (intensity * 256) + col;
                rgbTable[index] = ClampToByte(col + shift);
            }
        }
    }
    else
    {
        for (int intensity = 0; intensity < 256; ++intensity)
        {
            int shift = (intensity - 127 + brightness) * multiply / divide + 127 - intensity;

            for (int col = 0; col < 256; ++col)
            {
                int index = (intensity * 256) + col;
                rgbTable[index] = ClampToByte(col + shift);
            }
        }
    }

	/////////////////////////////////////////////////////
#ifndef GLOBAL_BMP_MEMORY
	bool bDelete = false;
	if (src == NULL)
	{
		bDelete = true;
		src = NEW_ARRAY(BMP_ARGB, width * height);
		memcpy(src, data, width*height*sizeof(BMP_ARGB));
	}
#endif
	memcpy(src, data, width*height*sizeof(BMP_ARGB));

	for (int y = 0; y < height; ++y)
    {
        BMP_ARGB* srcRowPtr = src +  y*width;
        BMP_ARGB* dstRowPtr = data +  y*width;
        BMP_ARGB *dstRowEndPtr = dstRowPtr + width;

        if (divide == 0)
        {
            while (dstRowPtr < dstRowEndPtr)
            {
                BMP_ARGB col = *srcRowPtr;
                byte i = GetIntensityByte(col);
                byte c = rgbTable[i];
                *dstRowPtr = (col & 0xff000000) | c | (c << 8) | (c << 16);

                ++dstRowPtr;
                ++srcRowPtr;
            }
        }
        else
        {
            while (dstRowPtr < dstRowEndPtr)
            {
                BMP_ARGB col = *srcRowPtr;
				byte* col8 = (byte*)&col;

                byte i = GetIntensityByte(col);
                int shiftIndex = i * 256;
#ifdef INVERT_RED
                col8[2] = rgbTable[shiftIndex + col8[2]];
                col8[1] = rgbTable[shiftIndex + col8[1]];
                col8[0] = rgbTable[shiftIndex + col8[0]];
#else
				col8[0] = rgbTable[shiftIndex + col8[0]];
                col8[1] = rgbTable[shiftIndex + col8[1]];
                col8[2] = rgbTable[shiftIndex + col8[2]];
#endif

                *dstRowPtr = col;
                ++dstRowPtr;
                ++srcRowPtr;
            }
        }
    }

#ifndef GLOBAL_BMP_MEMORY
	if (bDelete)
		DELETE_ARRAY(src);
#endif
	/////////////////////////////////////////////////////

	DELETE_ARRAY(rgbTable);
}

void TestSpeed(int count)
{
	int a;
	for(int i = 0; i < count; i++)
		a = lerp(0.1f, i, i + 1);
		//a = LERP(0.1f, i, i + 1);
}

void ColorFilterEx(BMP_ARGB *data, int width, int height, int color)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			byte* bData = (byte*)data; 			

			int nPixelR = 0;
			int nPixelG = 0;
			int nPixelB = 0;
			if (color == COLOR_RED)
			{
#ifdef INVERT_RED
				nPixelR = bData[2];
				nPixelB = bData[0] - 255;
#else
				nPixelR = bData[0];
				nPixelB = bData[2] - 255;
#endif	

				nPixelG = bData[1] - 255;

			}
			else if (color == COLOR_GREEN)
			{
#ifdef INVERT_RED
				nPixelR = bData[2] - 255;				
				nPixelB = bData[0] - 255;
#else
				nPixelR = bData[0] - 255;				
				nPixelB = bData[2] - 255;
#endif

				nPixelG = bData[1];
			}
			else if (color == COLOR_BLUE)
			{
#ifdef INVERT_RED
				nPixelR = bData[2] - 255;
				nPixelB = bData[0];
#else
				nPixelR = bData[0] - 255;
				nPixelB = bData[2];
#endif				
				nPixelG = bData[1] - 255;
			}
			nPixelR = MAX(nPixelR, 0);
			nPixelR = MIN(255, nPixelR);

			nPixelG = MAX(nPixelG, 0);
			nPixelG = MIN(255, nPixelG);

			nPixelB = MAX(nPixelB, 0);
			nPixelB = MIN(255, nPixelB);

#ifdef INVERT_RED
			bData[2] = nPixelR;			
			bData[0] = nPixelB;
#else
			bData[0] = nPixelR;			
			bData[2] = nPixelB;
#endif

			bData[1] = nPixelG;

			data++;
		}
	}
}

int Sign(int val)
{
	if (val < 0)
		return -1;
	else if (val > 0)
		return 1;
	else 
		return 0;
}

void JitterEffect_PDN(BMP_ARGB *data, int width, int height, 
					 int MaxDistance, int MinDistance, int Width, int Spacing,
					 int AngleDeg, int Edge)	
{
	double AngleRad = AngleDeg*PI/180;
	if ((AngleDeg % 90) != 0)
		MaxDistance++;

	 byte instanceSeed = (byte)(clock()%255);
	 byte Seed = instanceSeed;

	 srand(Seed);
	 int DistanceTable_Length = MAX(height, width);
	 int* DistanceTable = NEW_ARRAY(int, DistanceTable_Length);

	for (int i = 0; i < DistanceTable_Length; i += (Width + Spacing))
	{
		int range = MaxDistance - MinDistance;
		int num3 = (rand() % (2*range + 1)) - range;
		num3 += MinDistance * Sign(num3);
		for (int j = 0; (j < (Width + Spacing)) && ((i + j) < DistanceTable_Length); j++)
		{
			if (j < Width)
			{
				DistanceTable[i + j] = num3;
			}
		}
	}
	
	////////////
	//Surface surface = base.get_DstArgs().Surface;
    //Surface surface2 = base.get_SrcArgs().Surface;
	BMP_ARGB* surface2 = NEW_ARRAY(BMP_ARGB, width * height);
	memcpy(surface2, data, width*height*sizeof(BMP_ARGB));
    for (int i = 0; i < height; i++)
    {
        BMP_ARGB* pointAddressUnchecked = data + i*width;
        for (int j = 0; j < width; j++)
        {
            int num;
            BMP_ARGB bgra;
            double num8;
            BMP_ARGB bgra2;
            BMP_ARGB* bgraArray;
            if ((abs(AngleDeg) > 45) && (abs(AngleDeg) < 135))
            {
                num = (int) (abs((int) ((tan((90 - AngleDeg) * PI/180) * i) + j)) % (DistanceTable_Length));
            }
            else
            {
                num = (int) (abs((int) ((tan(AngleRad) * j) + i)) % (DistanceTable_Length));
            }
            double d = cos(-AngleRad) * DistanceTable[num] + j;
            double num5 = sin(-AngleRad)*DistanceTable[num] + i;
            int x = (int)d;
            int y = (int)num5;
            if ((x >=0) && (x < width) && (y >=0) && (y < height))
            {
                bgra = surface2[x + y * width];
            }
            else
            {
				int xx, yy;
                switch (Edge)
                {
                    case JITTER_EDGE_WRAP:
						xx = abs((int) ((x + ((x < width) ? width : 0)) % width));
						yy = abs((int) ((y + ((y < height) ? height : 0)) % height));
                        bgra = surface2[xx + yy * width];
                        break;

                    case JITTER_EDGE_REFLECT:
						xx = abs((int) ((width - 1) - abs((int) (x - (width - 1)))));
						yy = abs((int) ((height - 1) - abs((int) (y - (height - 1)))));
                        bgra = surface2[xx + yy * width];
                        break;

                    case JITTER_EDGE_PRIMARY:
                        bgra = 0xFF000000;
                        break;

                    case JITTER_EDGE_SECONDARY:
                        bgra = 0xFFFFFFFF;
                        break;

					default:
						bgra = 0xFFFFFFFF;
						break;
                }
                
            }
        
            *pointAddressUnchecked = bgra;
            
            pointAddressUnchecked++;
        }
    }

	///////////
	DELETE_ARRAY(surface2);
	DELETE_ARRAY(DistanceTable);
}

void StichEffect_PDN(BMP_ARGB *data, int width, int height, 
					int Distance, int Width, int Angle1, int Angle2, bool Wrap)
{
    srand((unsigned int)clock());
    int a = 90 - Angle1;
    int num2 = Angle2;
    int distance = Distance;
    if (((a % 90) != 0) || ((num2 % 90) != 0))
    {
        distance++;
    }

	int numArray_Length = MAX(height, width);
    int* numArray = NEW_ARRAY(int, numArray_Length);
    for (int i = 0; i < numArray_Length; i += Width)
    {
		int num5 = rand()%(2*distance + 1) - distance;
        for (int k = i; (k < (i + Width)) && (k < numArray_Length); k++)
        {
            numArray[k] = num5;
        }
    }
	BMP_ARGB* src = NEW_ARRAY(BMP_ARGB, width * height);
	memcpy(src, data, width*height*sizeof(BMP_ARGB));
    for (int j = 0; j < height; j++)
    {
        for (int m = 0; m < width; m++)
        {
            int index = abs((int)((tan((double)a) * j) + m) % numArray_Length);
            int x = m + ((int) (cos((double)a) * numArray[index]));
            index = abs((int)((tan((double)num2) * m) + j) % numArray_Length);
            int y = j + ((int) (cos((double)num2) * numArray[index]));
            if ((x >=0) && (x < width) && (y >=0) && (y < height))
            {
                data[m + j *width] = src[x + y * width];
            }
            else if (Wrap)
            {
				int xx = abs((int) ((x + ((x < width) ? width : 0)) % width));
				int yy = abs((int) ((y + ((y < height) ? height : 0)) % height));
                data[m + j *width] = src[xx + yy*width];
            }
            else
            {                
                data[m + j *width] = 0xFFFFFFFF;
            }
        }
    }

	DELETE_ARRAY(src);
	DELETE_ARRAY(numArray);
}

void EXPORT_DLL BokehEffect_Test(BMP_ARGB *data, int width, int height)
{

	BokehEffect* bEffect = new BokehEffect(data, width, height);	
	//bEffect->DrawHexgonBokeh();
	//bEffect->DrawPentagonBokeh();
	bEffect->DrawArrowBokeh();
	//bEffect->DrawVignette();
	DELETE(bEffect);
}