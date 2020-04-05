#ifndef _BOKEH_EFFECT_H__
#define _BOKEH_EFFECT_H__

#include "Typedef.h"
#include "Agg2D.h"

class BokehEffect
{
private: 
	Agg2D _outputG;
	BMP_ARGB* _data;

	BMP_ARGB* _layerData;
	Agg2D _layerG;
	Agg2D::Image _layerImg;

	BMP_ARGB* _bgData;
	Agg2D _bgG;
	Agg2D::Image _bgImg;

	int _width;
	int _height;
	int _size;

public:
	BokehEffect(BMP_ARGB *data, int width, int height);	
	~BokehEffect();

public:
	void DrawSmt();
	void DrawRandomCircle(int num, int radiusPercent);
	void DrawImage(Agg2D::Image image, Agg2D::BlendMode blendMode);
	void DrawHexgonBokeh();	
	void DrawPentagonBokeh();	
	void DrawArrowBokeh();
	void DrawVignette();

private:
	void DrawPolygonBoken(int numShape, int numShapePoint, double sizePercent); //size percent with min(width, height)
	double* CreatePolygonBokeh(double x, double y, double radius, int numShapePoint, double startAngle);
	
	double* CreateShapeBoken(double* pts, int numPoint, double x, double y, double radius, double startAngle);
	void DrawShapeBoken(double* pts, int numPoint, int numShape, double sizePercent);
	
};

#endif //_BOKEH_EFFECT_H__