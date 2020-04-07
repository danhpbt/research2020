package com.xynotec.image;

public class ImageUtil {

    public static native void YUV2ARGB(byte[] sData, int sFormat, int sRotation, int sWidth, int sHeight,
                                int[] dData, int dWidth, int dHeight);
    public static native void AntiGrain(int[] dataRGB, int width, int height);
    public static native void GrayScale(int[] dataRGB, int width, int height);
    public static native void ColorFilter(int[] dataRGB, int width, int height, int filter);
    public static native void Gamma(int[] dataRGB, int width, int height, double red, double green, double blue);
    public static native void Brightness(int[] dataRGB, int width, int height, int brightness);
    public static native void Contrast(int[] dataRGB, int width, int height, double contrast);
    public static native void Invert(int[] dataRGB, int width, int height);
    public static native void Smooth(int[] dataRGB, int width, int height, int weight);
    public static native void GaussianBlur(int[] dataRGB, int width, int height, int weight);
    public static native void MeanRemoval(int[] dataRGB, int width, int height, int weight);
    public static native void Sharpen(int[] dataRGB, int width, int height, int weight);
    public static native void EmbossLaplacian(int[] dataRGB, int width, int height);
    public static native void EdgeDetectQuick(int[] dataRGB, int width, int height);
    public static native void Flip(int[] dataRGB, int width, int height, boolean bHorz, boolean bVert);
    public static native void RandomJitter(int[] dataRGB, int width, int height, short degree);
    public static native void Swirl(int[] dataRGB, int width, int height, double degree, boolean bSmoothing);
    public static native void Sphere(int[] dataRGB, int width, int height, boolean bSmoothing);
    public static native void TimeWarp(int[] dataRGB, int width, int height, byte factor, boolean bSmoothing);
    public static native void Moire(int[] dataRGB, int width, int height, double degree);
    public static native void Water(int[] dataRGB, int width, int height, short nWave, boolean bSmoothing);
    public static native void Pixelate(int[] dataRGB, int width, int height, short pixel, boolean  bGrid);
    public static native void FishEye(int[] dataRGB, int width, int height, double iCurvature, boolean bInverse, boolean bSmoothing);
//void LiquidRender(byte* surface);
//void Agg2DOverlayImage(System::Drawing::Bitmap^ overlayImg);
    public static native void BokehEffects(int[] dataRGB, int width, int height);
    
    public static native void Tube(int[] dataRGB, int width, int height, double m_iCurvature, boolean m_bInverse, boolean bSmoothing);
    public static native void MyTube(int[] dataRGB, int width, int height, double m_iCurvature, boolean m_bInverse, boolean bSmoothing);
    public static native void InkSketch(int[] dataRGB, int width, int height, int inkOutline, int coloring);
    public static native void EdgeDetector(int[] dataRGB, int width, int height);
    public static native void EdgeMaster(int[] dataRGB, int width, int height, int color, int amount);
    public static native void ToonEffect(int[] dataRGB, int width, int height);
    public static native void OilEffect(int[] dataRGB, int width, int height, int range, int levels);//java
    public static native void PastelEffect(int[] dataRGB, int width, int height, int range, int levels);//paint.net
    public static native void DreamEffect(int[] dataRGB, int width, int height, int focus);//paint.net
    public static native void SmearEffect(int[] dataRGB, int width, int height);
    public static native void SmearEffectPDN(int[] dataRGB, int width, int height, int shape, float angle, float density,
                                                                            float scatter, int distance, float mix, boolean background);
    public static native void GaussianBlurPDN(int[] dataRGB, int width, int height, int radius);
    public static native void GlowEffectPDN(int[] dataRGB, int width, int height, int radius, int brightness, int contrast);
    public static native void JitterEffectPDN(int[] dataRGB, int width, int height,
                                                                             int maxDistance, int minDistance, int Width, int spacing,
                                                                             int angleDeg, int edge);
    public static native void StichEffectPDN(int[] dataRGB, int width, int height,
                                           int distance, int nWidth, int angle1, int angle2, boolean Wrap);



}
