#include "ConvMatrix.h"

ConvMatrix::ConvMatrix(void)
{
	TopLeft = 0;	TopMid = 0;		TopRight = 0;
	MidLeft = 0;	Pixel = 1;		MidRight = 0;			
	BottomLeft = 0; BottomMid = 0;	BottomRight = 0;
	Factor = 1;
	Offset = 0;
}

ConvMatrix::~ConvMatrix(void)
{

}

void ConvMatrix::SetAll(int nVal)
{
	TopLeft = TopMid = TopRight = MidLeft = Pixel = MidRight = BottomLeft = BottomMid = BottomRight = nVal;
}
