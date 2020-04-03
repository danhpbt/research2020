package com.xynotec.image;

public class ImageUtil {

    static native void YUV2ARGB(byte[] sData, int sFormat, int sRotation, int sWidth, int sHeight,
                                int[] dData, int dWidth, int dHeight);

//    public static void ConvertYUV2ARGB(byte[] sData, int sFormat,  int sRotation, int sWidth, int sHeight,
//                                                  int[] dData, int dWidth, int dHeight)
//    {
//        YUV2ARGB(sData, sFormat, sRotation, sWidth, sHeight, dData, dWidth, dHeight);
//    }
}
