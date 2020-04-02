package com.xynotec.image;

import android.graphics.Bitmap;

public class ARGBImage {
    private int[] mData;
    private int mWidth;
    private int mHeight;

    public ARGBImage(int width, int height)
    {
        mWidth = width;
        mHeight = height;
        mData = new int[mWidth * mHeight];
    }

    public int getWidth()
    {
        return mWidth;
    }

    public int getHeight()
    {
        return mHeight;
    }

    public  int[] getPixels()
    {
        return mData;
    }

    public static ARGBImage fromNV21(byte[] data, int width, int height, int rotation)
    {
        int nWidth;
        int nHeight;
        if (rotation == 0)
        {
            nWidth = width;
            nHeight = height;
        }
        else if (rotation == 90)
        {
            nWidth = height;
            nHeight = width;
        }
        else if (rotation == 180)
        {
            nWidth = width;
            nHeight = height;
        }
        else if (rotation == 270)
        {
            nWidth = height;
            nHeight = width;
        }
        else
            return null;

        ARGBImage img = new ARGBImage(nWidth, nHeight);
        return img;
    }

    public Bitmap toBitmap()
    {
        int stride = mWidth;
        return Bitmap.createBitmap(mData, 0, stride,
                mWidth, mHeight, Bitmap.Config.ARGB_8888);
    }
}
