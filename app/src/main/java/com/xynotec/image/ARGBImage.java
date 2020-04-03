package com.xynotec.image;

import android.graphics.Bitmap;
import android.graphics.Camera;
import android.graphics.ImageFormat;
import android.graphics.PixelFormat;

public class ARGBImage {
    private int[] mData;
    private Bitmap mBitmap;
    private int mWidth;
    private int mHeight;

    public Bitmap getBitmap()
    {
        return mBitmap;
    }
    public int getWidth()
    {
        return mWidth;
    }

    public int getHeight()
    {
        return mHeight;
    }

    public void fromYUV(byte[] data, int format, int rotation, int width, int height)
    {
        int nWidth = 0;
        int nHeight = 0;
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

        if ((nWidth != this.mWidth) || (nHeight != this.mHeight))
        {
            if (mBitmap != null)
                mBitmap.recycle();

            mWidth = mWidth;
            mHeight = nHeight;
            mBitmap = Bitmap.createBitmap(mWidth, mHeight, Bitmap.Config.ARGB_8888);
            mData = new int[mWidth*mHeight];
        }

        mBitmap.getPixels(mData, 0, mWidth, 0, 0, mWidth, mHeight);
        ImageUtil.YUV2ARGB(data, format, rotation, width, height,
                mData, mWidth, mHeight);
        mBitmap.setPixels(mData, 0, mWidth, 0, 0, mWidth, mHeight);
    }

}