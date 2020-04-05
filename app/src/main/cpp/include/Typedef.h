#ifndef _TYPEDEF_H__
#define _TYPEDEF_H__

#ifndef _WIN32

#include <android/log.h>

#endif

//#define OBJECTIVE_C_IOS

#define INVERT_RED

#include <stdlib.h>


//////////////////////////////////////////////////////////////////////////
// At first, bitmap data is 32bits with format ARGB
//					byte 0 | byte 1 | byte 2 | byte 3
//Windows format	   B	   G	     R	     A	
//////////////////////////////////////////////////////////////////////////
typedef unsigned int BMP_ARGB;

typedef unsigned char byte;


#define MAX(a,b)    (((a) > (b)) ? (a) : (b))
#define MIN(a,b)    (((a) < (b)) ? (a) : (b))
#define ABS(a)		((a > 0) ? a : -a)
#define PI 3.14159265358979323846

enum COLOR_FILTER
{
	COLOR_RED = 0,
	COLOR_GREEN,
	COLOR_BLUE
};

typedef struct tag_FloatPoint
{
	double X;
	double Y;

}FloatPoint;


typedef struct tag_IntPoint
{
	int X;
	int Y;

}IntPoint;

typedef struct tag_IntSize
{
	int width;
	int height;
}IntSize;

typedef struct tag_IntRectangle
{
	int x;
	int y;
	int width;
	int height;
}IntRectangle;

typedef struct tag_FloatRectangle
{
	float x;
	float y;
	float width;
	float height;
}FloatRectangle;

#ifdef OBJECTIVE_C_IOS

#else

	#define NEW_ARRAY(type, size)	new type[size]

	#define DELETE_ARRAY(var)		\
	{								\
		if (var)					\
			delete[] var;			\
		var = NULL;					\
	}								\

	#define DELETE(var)				\
	{								\
		if (var)					\
			delete var;				\
		var = NULL;					\
	}								\

#endif



#ifdef _WIN32	

	#define EXPORT_DLL __declspec(dllexport)
#else
	#define EXPORT_DLL	

#endif


#endif //_TYPEDEF_H__
