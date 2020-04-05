#include <time.h>

#include "BasicEffect.h"
#include "BokehEffect.h"


BokehEffect::BokehEffect(BMP_ARGB *data, int width, int height)
{
	srand(time(NULL));
	_data = data;
	int stride = width*sizeof(BMP_ARGB);
	_width = width;
	_height = height;
	_size = MIN(_width, _height);

	_outputG.attach((unsigned char*)data, width, height, stride);
	_outputG.viewport(0, 0, width, height,
		0, 0, width, height, Agg2D::XMidYMid);

	_layerData = NEW_ARRAY(BMP_ARGB, width*height);
	_layerImg.attach((unsigned char*)_layerData, width, height, stride);
	_layerG.attach(_layerImg);

	_bgData = NEW_ARRAY(BMP_ARGB, width*height);
	_bgImg.attach((unsigned char*)_bgData, width, height, stride);
	_bgG.attach(_bgImg);
}

BokehEffect::~BokehEffect()
{
	DELETE_ARRAY(_layerData);
	DELETE_ARRAY(_bgData);	
}


void BokehEffect::DrawVignette()
{
	float centerX = _width/2;
	float centerY = _height/2;
	float rX = centerX;
	float rY = centerY;
	float r = MAX(rX, rY);

	_outputG.noLine();
	_outputG.fillRadialGradient(centerX, centerY, 2.5*r, Agg2D::Color(0,0,0,0), Agg2D::Color(0,0,0,255), 0.25);
	//_outputG.ellipse(centerX, centerY, rX, rY);
	_outputG.rectangle(0, 0, _width, _height);
	
}
void BokehEffect::DrawSmt()
{
	/*
	//g->blendMode(Agg2D::BlendMode::BlendColorDodge);
	g->noLine();
	//g->lineColor(255, 0, 0);
	//g->lineWidth(5);
	//g->fillColor(255, 255, 255, 0x7f);
	g->fillLinearGradient(0, 0, 200, 200, Agg2D::Color(255, 0, 255, 0xff), Agg2D::Color(0, 255, 255, 0xff));

	
	//g->ellipse(100, 100, 100, 100);
	g->rectangle(0, 0, 200, 200);
	*/
	/*
	g->noLine();
	
	g->fillColor(255, 0, 0);
	g->rectangle(0,0, 100, 100);

	g->fillColor(0, 255, 0);
	g->rectangle(0, 100, 100, 200);

	g->fillColor(0, 0, 255);
	g->rectangle(0, 200, 100, 300);
	*/

	/*
	g->blendMode(Agg2D::BlendMode::BlendColorDodge);
	g->noLine();
	g->fillLinearGradient(0, 0, _width, _height, Agg2D::Color(255, 0, 255, 0xff), Agg2D::Color(0, 255, 255, 0xff));
	g->rectangle(0, 0, _width, _height);
	*/
}

void BokehEffect::DrawRandomCircle(int num, int radiusPercent)
{
	/*
	g->noLine();
	//g->fillColor(0, 0, 0);
	//g->rectangle(0, 0, _width, _height);
	g->fillLinearGradient(0, 0, _width, _height, Agg2D::Color(255, 0, 255, 0xff), Agg2D::Color(0, 255, 255, 0xff));
	g->rectangle(0, 0, _width, _height);

	return;
	*/

	//g->blendMode(Agg2D::BlendMode::BlendSrc);
	//g->blendMode(Agg2D::BlendMode::BlendDst);

	/*
	g->noLine();
	g->fillColor(0, 0, 0);
	g->rectangle(0, 0, _width, _height);

	int size = MIN(_width, _height);
	
	srand(time(NULL));
	for(int i = 0; i < num; i++)
	{
		double radius = radiusPercent*size/100.0f;
		double radiusOffset = 0.5*radius;

		double lineWidth = radius / 20.0f;
		double realRadius = radius - radiusOffset + rand()%((int)(2*radiusOffset));

		g->lineColor(255, 255, 255, 201 + rand()%50);
		g->lineWidth(lineWidth);

		int alphaOffset = 32;
		int alpha = (64 - alphaOffset) + rand()% (2*alphaOffset);

		g->fillColor(255, 255, 255, 127);


		int x = rand()%_width;
		int y = rand()%_height;

		g->ellipse(x, y, realRadius, realRadius);
	}
	*/
}


void BokehEffect::DrawImage(Agg2D::Image image, Agg2D::BlendMode blendMode)
{
	/*
	g->blendMode(blendMode);	
	g->blendImage(image, 0, 0);
	*/
}

double* BokehEffect::CreatePolygonBokeh(double x, double y, double radius, int numShapePoint, double startAngle)
{
	double* polygon = new double[numShapePoint*2];
	double angleStep = PI*2/numShapePoint;
	double angleStart = startAngle*PI/180;
	for(int i = 0; i < numShapePoint; i++)
	{
		polygon[2*i] = x + radius*cos(i*angleStep + angleStart);
		polygon[2*i + 1] = y + radius*sin(i*angleStep + angleStart);
	}

	return polygon;
}


void BokehEffect::DrawPolygonBoken(int numShape, int numShapePoint, double sizePercent)
{
	memset(_layerData, 0, sizeof(BMP_ARGB)*_width*_height);	
	
	double radiusSize = sizePercent*_size*0.5f;
	_layerG.noLine();
	for(int i = 0; i < numShape; i++)
	{
		double radiusReal = radiusSize*0.5f + rand()%((int)radiusSize);
		//double lineWidth = radiusReal/20;

		//_layerG.lineColor(255, 255, 255, 201 + rand()%50);

		double lineWidth = radiusReal/20;

		_layerG.lineColor(255, 255, 255, 150 + rand()%50);
		_layerG.lineWidth(lineWidth);
		
		int alphaOffset = 32;
		int alpha = (64 - alphaOffset) + rand()% (2*alphaOffset);

		_layerG.fillColor(255, 255, 255, alpha);				

		double* shape = CreatePolygonBokeh(rand()%_width, rand()%_height,
										  radiusReal, numShapePoint, -90);

		_layerG.polygon(shape, numShapePoint);

		DELETE_ARRAY(shape);
				
		//_layerG.ellipse(rand()%_width, rand()%_height, radiusReal, radiusReal);
	}
}

double* BokehEffect::CreateShapeBoken(double* pts, int numPoint, double x, double y, double radius, double startAngle)
{
	double* polygon = new double[numPoint*2];	
	double angleStart = startAngle*PI/180;
	for(int i = 0; i < numPoint; i++)
	{
		double r = sqrt(pts[2*i]*pts[2*i] + pts[2*i + 1]*pts[2*i + 1]);
		double angle = atan2(pts[2*i + 1], pts[2*i]);

		polygon[2*i] = x + radius*r*cos(angle + angleStart);
		polygon[2*i + 1] = y + radius*r*sin(angle + angleStart);
	}

	return polygon;
}

void BokehEffect::DrawShapeBoken(double* pts, int numPoint, int numShape, double sizePercent)
{
	memset(_layerData, 0, sizeof(BMP_ARGB)*_width*_height);	

	double radiusSize = sizePercent*_size*0.5f;
	_layerG.noLine();
	for(int i = 0; i < numShape; i++)
	{
		double radiusReal = radiusSize*0.5f + rand()%((int)radiusSize);
		//double lineWidth = radiusReal/20;

		//_layerG.lineColor(255, 255, 255, 201 + rand()%50);

		double lineWidth = radiusReal/20;

		_layerG.lineColor(255, 255, 255, 150 + rand()%50);
		_layerG.lineWidth(lineWidth);

		int alphaOffset = 32;
		int alpha = (64 - alphaOffset) + rand()% (2*alphaOffset);

		_layerG.fillColor(255, 255, 255, alpha);				

		double* shape = CreateShapeBoken(pts, numPoint, rand()%_width, rand()%_height,
			radiusReal, 10);

		_layerG.polygon(shape, numPoint);

		DELETE_ARRAY(shape);

		//_layerG.ellipse(rand()%_width, rand()%_height, radiusReal, radiusReal);
	}

}


void BokehEffect::DrawHexgonBokeh()
{
	_bgG.noLine();
	_bgG.fillColor(0, 0, 0);
	_bgG.rectangle(0, 0, _width, _height);

	DrawPolygonBoken(10, 6, 0.2f);
	int radiusBlur = 12;//(int)(0.1f*_size);
	GaussianBlur_PDN(_layerData, _width, _height, radiusBlur);     		
	_bgG.blendImage(_layerImg, 0, 0);


	DrawPolygonBoken(40, 6, 0.08f);
	radiusBlur = 8;//(int)(0.03f*_size);
	GaussianBlur_PDN(_bgData, _width, _height, radiusBlur);     
	_bgG.blendImage(_layerImg, 0, 0);


	DrawPolygonBoken(200, 6, 0.03f);
	radiusBlur = 4;//(int)(0.01f*_size);	
	GaussianBlur_PDN(_bgData, _width, _height, radiusBlur);     
	_bgG.blendImage(_layerImg, 0, 0);
	

	_outputG.blendMode(Agg2D::BlendMode::BlendColorDodge);
	_outputG.blendImage(_bgImg, 0, 0);
}

void BokehEffect::DrawPentagonBokeh()
{
	_bgG.noLine();
	_bgG.fillColor(0, 0, 0);
	_bgG.rectangle(0, 0, _width, _height);

	DrawPolygonBoken(20, 5, 0.2f);
	int radiusBlur = 12;//(int)(0.1f*_size);
	GaussianBlur_PDN(_layerData, _width, _height, radiusBlur);     		
	_bgG.blendImage(_layerImg, 0, 0);


	DrawPolygonBoken(40, 5, 0.08f);
	radiusBlur = 8;//(int)(0.03f*_size);
	GaussianBlur_PDN(_bgData, _width, _height, radiusBlur);     
	_bgG.blendImage(_layerImg, 0, 0);


	DrawPolygonBoken(200, 5, 0.03f);
	radiusBlur = 4;//(int)(0.01f*_size);	
	GaussianBlur_PDN(_bgData, _width, _height, radiusBlur);     
	_bgG.blendImage(_layerImg, 0, 0);
	

	_outputG.blendMode(Agg2D::BlendMode::BlendColorDodge);
	_outputG.blendImage(_bgImg, 0, 0);
}

void BokehEffect::DrawArrowBokeh()
{	
	
	double pts[252] = {
				-0.596, -0.663, 
				-0.393, -0.663, 
				-0.371, -0.64, 
				-0.326, -0.64, 
				-0.303, -0.618, 
				-0.281, -0.618, 
				-0.258, -0.596, 
				-0.236, -0.596, 
				-0.079, -0.438, 
				-0.079, -0.416, 
				-0.034, -0.371, 
				-0.034, -0.348, 
				-0.011, -0.326, 
				0.011, -0.326, 
				0.034, -0.348, 
				0.034, -0.371, 
				0.079, -0.416, 
				0.079, -0.438, 
				0.213, -0.573, 
				0.236, -0.573, 
				0.258, -0.596, 
				0.281, -0.596, 
				0.303, -0.618, 
				0.326, -0.618, 
				0.348, -0.64, 
				0.416, -0.64, 
				0.438, -0.663, 
				0.573, -0.663, 
				0.596, -0.64, 
				0.64, -0.64, 
				0.663, -0.618, 
				0.685, -0.618, 
				0.708, -0.596, 
				0.73, -0.596, 
				0.753, -0.573, 
				0.775, -0.573, 
				0.865, -0.483, 
				0.865, -0.461, 
				0.91, -0.416, 
				0.91, -0.393, 
				0.933, -0.371, 
				0.933, -0.348, 
				0.955, -0.326, 
				0.955, -0.258, 
				0.978, -0.236, 
				0.978, -0.124, 
				1, -0.101, 
				1, -0.034, 
				0.978, -0.011, 
				0.978, 0.101, 
				0.955, 0.124, 
				0.955, 0.146, 
				0.933, 0.169, 
				0.933, 0.191, 
				0.91, 0.213, 
				0.91, 0.236, 
				0.73, 0.416, 
				0.708, 0.416, 
				0.663, 0.461, 
				0.64, 0.461, 
				0.596, 0.506, 
				0.573, 0.506, 
				0.528, 0.551, 
				0.506, 0.551, 
				0.461, 0.596, 
				0.438, 0.596, 
				0.393, 0.64, 
				0.371, 0.64, 
				0.258, 0.753, 
				0.236, 0.753, 
				0.124, 0.865, 
				0.124, 0.888, 
				0.034, 0.978, 
				0.034, 1, 
				0.011, 1.022, 
				0.011, 1.045, 
				-0.011, 1.045, 
				-0.011, 1.022, 
				-0.034, 1, 
				-0.034, 0.978, 
				-0.101, 0.91, 
				-0.101, 0.888, 
				-0.258, 0.73, 
				-0.281, 0.73, 
				-0.348, 0.663, 
				-0.371, 0.663, 
				-0.438, 0.596, 
				-0.461, 0.596, 
				-0.483, 0.573, 
				-0.506, 0.573, 
				-0.551, 0.528, 
				-0.573, 0.528, 
				-0.618, 0.483, 
				-0.64, 0.483, 
				-0.663, 0.461, 
				-0.685, 0.461, 
				-0.775, 0.371, 
				-0.798, 0.371, 
				-0.865, 0.303, 
				-0.865, 0.281, 
				-0.91, 0.236, 
				-0.91, 0.213, 
				-0.933, 0.191, 
				-0.933, 0.169, 
				-0.955, 0.146, 
				-0.955, 0.124, 
				-0.978, 0.101, 
				-0.978, -0.011, 
				-1, -0.034, 
				-1, -0.079, 
				-0.978, -0.101, 
				-0.978, -0.236, 
				-0.955, -0.258, 
				-0.955, -0.326, 
				-0.933, -0.348, 
				-0.933, -0.371, 
				-0.91, -0.393, 
				-0.91, -0.416, 
				-0.888, -0.438, 
				-0.888, -0.461, 
				-0.753, -0.596, 
				-0.73, -0.596, 
				-0.708, -0.618, 
				-0.685, -0.618, 
				-0.663, -0.64, 
				-0.618, -0.64, 
				};

		int numPts = 252/2;
		
/*
	double pts[238] = {
		0.949, -0.519, 
		0.975, -0.519, 
		0.975, -0.392, 
		0.949, -0.367, 
		0.949, 0.063, 
		0.975, 0.089, 
		0.975, 0.139, 
		1, 0.165, 
		1, 0.215, 
		0.975, 0.241, 
		0.949, 0.241, 
		0.924, 0.266, 
		0.899, 0.266, 
		0.873, 0.291, 
		0.848, 0.291, 
		0.772, 0.367, 
		0.747, 0.367, 
		0.342, 0.772, 
		0.342, 0.797, 
		0.215, 0.924, 
		0.215, 0.949, 
		0.114, 1.051, 
		0.114, 1.076, 
		0.063, 1.127, 
		0.063, 1.152, 
		-0.013, 1.228, 
		-0.013, 1.253, 
		-0.063, 1.304, 
		-0.063, 1.329, 
		-0.089, 1.354, 
		-0.089, 1.38, 
		-0.139, 1.43, 
		-0.316, 1.253, 
		-0.316, 1.228, 
		-0.418, 1.127, 
		-0.443, 1.127, 
		-0.62, 0.949, 
		-0.646, 0.949, 
		-0.696, 0.899, 
		-0.722, 0.899, 
		-0.797, 0.823, 
		-0.823, 0.823, 
		-0.848, 0.797, 
		-0.873, 0.797, 
		-0.924, 0.747, 
		-0.975, 0.747, 
		-1, 0.722, 
		-0.975, 0.696, 
		-0.949, 0.696, 
		-0.899, 0.646, 
		-0.873, 0.646, 
		-0.848, 0.62, 
		-0.823, 0.62, 
		-0.772, 0.57, 
		-0.747, 0.57, 
		-0.696, 0.519, 
		-0.671, 0.519, 
		-0.646, 0.494, 
		-0.62, 0.494, 
		-0.57, 0.443, 
		-0.544, 0.443, 
		-0.519, 0.418, 
		-0.494, 0.418, 
		-0.468, 0.392, 
		-0.443, 0.392, 
		-0.418, 0.418, 
		-0.418, 0.443, 
		-0.392, 0.468, 
		-0.392, 0.494, 
		-0.367, 0.519, 
		-0.367, 0.544, 
		-0.342, 0.57, 
		-0.342, 0.595, 
		-0.316, 0.62, 
		-0.316, 0.646, 
		-0.291, 0.671, 
		-0.291, 0.696, 
		-0.266, 0.722, 
		-0.266, 0.747, 
		-0.241, 0.772, 
		-0.241, 0.797, 
		-0.215, 0.823, 
		-0.215, 0.848, 
		-0.19, 0.873, 
		-0.165, 0.873, 
		-0.139, 0.848, 
		-0.139, 0.823, 
		-0.114, 0.797, 
		-0.114, 0.772, 
		-0.089, 0.747, 
		-0.089, 0.722, 
		-0.063, 0.696, 
		-0.063, 0.671, 
		-0.038, 0.646, 
		-0.038, 0.62, 
		-0.013, 0.595, 
		-0.013, 0.57, 
		0.038, 0.519, 
		0.038, 0.494, 
		0.063, 0.468, 
		0.063, 0.443, 
		0.089, 0.418, 
		0.089, 0.392, 
		0.139, 0.342, 
		0.139, 0.316, 
		0.19, 0.266, 
		0.19, 0.241, 
		0.241, 0.19, 
		0.241, 0.165, 
		0.291, 0.114, 
		0.291, 0.089, 
		0.392, -0.013, 
		0.392, -0.038, 
		0.722, -0.367, 
		0.747, -0.367, 
		0.823, -0.443, 
		0.848, -0.443, 
		0.899, -0.494, 
		0.924, -0.494, 
		};

	int numPts = 238/2;
*/
	/*
	double pts[14] = {
		0.091,	-0.909,
		1.0,	0.0,
		0.091,	0.909,
		0.091,	0.364,
		-1.0,	0.364,
		-1.0,	-0.364,
		0.091,	-0.364,		
		};

	int numPts = 7;
	*/
	
	
	//double pts[8] = {1.0, 1.0, 
	//				  -1.0, 1.0, 
	//				  -1.0, -1.0,
	//				  1.0, -1.0};
	//int numPts = 4;
	
	
	_bgG.noLine();
	_bgG.fillColor(0, 0, 0);
	_bgG.rectangle(0, 0, _width, _height);

	DrawShapeBoken(pts, numPts, 20, 0.2f);
	int radiusBlur = 12;//(int)(0.1f*_size);
	GaussianBlur_PDN(_layerData, _width, _height, radiusBlur);     		
	_bgG.blendImage(_layerImg, 0, 0);


	DrawShapeBoken(pts, numPts, 40, 0.08f);
	radiusBlur = 8;//(int)(0.03f*_size);
	GaussianBlur_PDN(_bgData, _width, _height, radiusBlur);     
	_bgG.blendImage(_layerImg, 0, 0);


	DrawShapeBoken(pts, numPts, 200, 0.03f);
	radiusBlur = 4;//(int)(0.01f*_size);	
	GaussianBlur_PDN(_bgData, _width, _height, radiusBlur);     
	_bgG.blendImage(_layerImg, 0, 0);	

	_outputG.blendMode(Agg2D::BlendMode::BlendColorDodge);
	_outputG.blendImage(_bgImg, 0, 0);
}




