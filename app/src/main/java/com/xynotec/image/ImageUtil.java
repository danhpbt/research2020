package com.xynotec.image;

public class ImageUtil {

    static native void GrayScale(int[] dataRGB, int width, int height);
    static native void YUV2ARGB(byte[] sData, int sFormat, int sRotation, int sWidth, int sHeight,
                                int[] dData, int dWidth, int dHeight);

}
