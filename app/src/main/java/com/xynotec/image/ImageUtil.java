package com.xynotec.image;

public class ImageUtil {

    static
    {
        System.loadLibrary("simplecam");
    }

    public static native void YUV2ARGB(byte[] sData, int sFormat, int sRotation, int sWidth, int sHeight,
                                int[] dData, int dWidth, int dHeight);
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



}
