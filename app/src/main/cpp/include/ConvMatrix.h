#ifndef _CONV_MATRIX_H__
#define _CONV_MATRIX_H__

//#ifdef __cplusplus
//extern "C" {
//#endif

class ConvMatrix
{
public:
	int TopLeft, TopMid, TopRight;
	int MidLeft, Pixel, MidRight;
	int BottomLeft, BottomMid, BottomRight;
	int Factor;
	int Offset;

	ConvMatrix(void);
	~ConvMatrix(void);
	void SetAll(int nVal);

};

//#ifdef __cplusplus
//} /* closing brace for extern "C" */
//#endif


#endif //_CONV_MATRIX_H__
