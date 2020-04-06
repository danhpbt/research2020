package com.xynotec.research2020.ui.imagefilter;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;

import androidx.databinding.ObservableBoolean;
import androidx.databinding.ObservableField;

import com.xynotec.dagger.BaseViewModel;
import com.xynotec.image.ImageUtil;
import com.xynotec.research2020.R;
import com.xynotec.research2020.data.DataManager;

public class ImageFilterViewModel extends BaseViewModel {
    private final ObservableField<Bitmap> mBitmap = new ObservableField<>();
    private int[] mData;
    private int mWidth;
    private int mHeight;

    private final ObservableBoolean mIsLoading = new ObservableBoolean();

    ImageFilterViewModelListener mListener;

    Context context;
    public ImageFilterViewModel(DataManager dataManager) {
        super(dataManager);
        context = getDataManager().getContext();

        reload();
    }

    public ObservableBoolean getIsLoading() {
        return mIsLoading;
    }

    public void setIsLoading(boolean isLoading) {
        mIsLoading.set(isLoading);
    }

    public ObservableField<Bitmap> getBitmap()
    {
        return mBitmap;
    }

    public void setListener(ImageFilterViewModelListener listener)
    {
        this.mListener = listener;
    }

    public void reload()
    {
        setIsLoading(true);

        Bitmap bitmap = BitmapFactory.decodeResource(context.getResources(), R.drawable.effect);
        Bitmap bmpARGB = bitmap.copy(Bitmap.Config.ARGB_8888, true);

        mWidth = bmpARGB.getWidth();
        mHeight = bmpARGB.getHeight();
        mData = new int[mWidth*mHeight];
        bmpARGB.getPixels(mData, 0, mWidth, 0, 0, mWidth, mHeight);

        mBitmap.set(bitmap.copy(Bitmap.Config.ARGB_8888, true));

        bitmap.recycle();
        bmpARGB.recycle();

        setIsLoading(false);
    }

    public void antiGrain()
    {
        setIsLoading(true);

        long time = System.currentTimeMillis();

        int length = mData.length;
        int[] data = new int[length];

        System.arraycopy(mData, 0, data, 0, length);
        ImageUtil.AntiGrain(data, mWidth, mHeight);
        mBitmap.set(Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888));

        time = System.currentTimeMillis() - time;

        String msg = String.format("Grayscale image %dx%d in %d", mWidth, mHeight, time);

        if (mListener != null)
            mListener.onMessage(msg);

        setIsLoading(false);
    }

    public void grayScale()
    {
        setIsLoading(true);

        long time = System.currentTimeMillis();

        int length = mData.length;
        int[] data = new int[length];

        System.arraycopy(mData, 0, data, 0, length);
        ImageUtil.GrayScale(data, mWidth, mHeight);
        mBitmap.set(Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888));

        time = System.currentTimeMillis() - time;

        String msg = String.format("Grayscale image %dx%d in %d", mWidth, mHeight, time);

        if (mListener != null)
            mListener.onMessage(msg);

        setIsLoading(false);
    }

    public void colorFilter()
    {
        setIsLoading(true);

        long time = System.currentTimeMillis();

        int length = mData.length;
        int[] data = new int[length];

        System.arraycopy(mData, 0, data, 0, length);
        ImageUtil.ColorFilter(data, mWidth, mHeight, 0); //
        mBitmap.set(Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888));

        time = System.currentTimeMillis() - time;

        String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time);

        if (mListener != null)
        mListener.onMessage(msg);

        setIsLoading(false);
    }

    public void gamma()
    {
        setIsLoading(true);

        long time = System.currentTimeMillis();

        int length = mData.length;
        int[] data = new int[length];

        System.arraycopy(mData, 0, data, 0, length);
        ImageUtil.Gamma(data, mWidth, mHeight, 0.5, 0.5, 0.5);//value 0->1
        mBitmap.set(Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888));

        time = System.currentTimeMillis() - time;

        String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time);

        if (mListener != null)
        mListener.onMessage(msg);

        setIsLoading(false);
    }

    public void brightness()
    {
        setIsLoading(true);

        long time = System.currentTimeMillis();

        int length = mData.length;
        int[] data = new int[length];

        System.arraycopy(mData, 0, data, 0, length);
        ImageUtil.Brightness(data, mWidth, mHeight, -100); //value -255->255
        mBitmap.set(Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888));

        time = System.currentTimeMillis() - time;

        String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time);

        if (mListener != null)
        mListener.onMessage(msg);

        setIsLoading(false);
    }

    public void contrast()
    {
        setIsLoading(true);

        long time = System.currentTimeMillis();

        int length = mData.length;
        int[] data = new int[length];

        System.arraycopy(mData, 0, data, 0, length);
        ImageUtil.Contrast(data, mWidth, mHeight, -50); //value -100->100
        mBitmap.set(Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888));

        time = System.currentTimeMillis() - time;

        String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time);

        if (mListener != null)
        mListener.onMessage(msg);

        setIsLoading(false);
    }

    public void invert()
    {
        setIsLoading(true);

        long time = System.currentTimeMillis();

        int length = mData.length;
        int[] data = new int[length];

        System.arraycopy(mData, 0, data, 0, length);
        ImageUtil.Invert(data, mWidth, mHeight); //
        mBitmap.set(Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888));

        time = System.currentTimeMillis() - time;

        String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time);

        if (mListener != null)
        mListener.onMessage(msg);

        setIsLoading(false);
    }

    public void smooth()
    {
        setIsLoading(true);

        long time = System.currentTimeMillis();

        int length = mData.length;
        int[] data = new int[length];

        System.arraycopy(mData, 0, data, 0, length);
        ImageUtil.Smooth(data, mWidth, mHeight, 1); //default to 1
        mBitmap.set(Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888));

        time = System.currentTimeMillis() - time;

        String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time);

        if (mListener != null)
        mListener.onMessage(msg);

        setIsLoading(false);
    }

    public void gaussianBlur()
    {
        setIsLoading(true);

        long time = System.currentTimeMillis();

        int length = mData.length;
        int[] data = new int[length];

        System.arraycopy(mData, 0, data, 0, length);
        ImageUtil.GaussianBlur(data, mWidth, mHeight, 20); //
        mBitmap.set(Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888));

        time = System.currentTimeMillis() - time;

        String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time);

        if (mListener != null)
        mListener.onMessage(msg);

        setIsLoading(false);
    }

    public void meanRemoval()
    {
        setIsLoading(true);

        long time = System.currentTimeMillis();

        int length = mData.length;
        int[] data = new int[length];

        System.arraycopy(mData, 0, data, 0, length);
        ImageUtil.MeanRemoval(data, mWidth, mHeight, 9); //
        mBitmap.set(Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888));

        time = System.currentTimeMillis() - time;

        String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time);

        if (mListener != null)
        mListener.onMessage(msg);

        setIsLoading(false);
    }

    public void sharpen()
    {
        setIsLoading(true);

        long time = System.currentTimeMillis();

        int length = mData.length;
        int[] data = new int[length];

        System.arraycopy(mData, 0, data, 0, length);
        ImageUtil.Sharpen(data, mWidth, mHeight, 11); //
        mBitmap.set(Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888));

        time = System.currentTimeMillis() - time;

        String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time);

        if (mListener != null)
        mListener.onMessage(msg);

        setIsLoading(false);
    }

    public void embossLaplacian()
    {
        setIsLoading(true);

        long time = System.currentTimeMillis();

        int length = mData.length;
        int[] data = new int[length];

        System.arraycopy(mData, 0, data, 0, length);
        ImageUtil.EmbossLaplacian(data, mWidth, mHeight); //
        mBitmap.set(Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888));

        time = System.currentTimeMillis() - time;

        String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time);

        if (mListener != null)
        mListener.onMessage(msg);

        setIsLoading(false);
    }

    public void edgeDetect()
    {
        setIsLoading(true);

        long time = System.currentTimeMillis();

        int length = mData.length;
        int[] data = new int[length];

        System.arraycopy(mData, 0, data, 0, length);
        ImageUtil.EdgeDetectQuick(data, mWidth, mHeight); //
        mBitmap.set(Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888));

        time = System.currentTimeMillis() - time;

        String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time);

        if (mListener != null)
        mListener.onMessage(msg);

        setIsLoading(false);
    }

    public void flip()
    {
        setIsLoading(true);

        long time = System.currentTimeMillis();

        int length = mData.length;
        int[] data = new int[length];

        System.arraycopy(mData, 0, data, 0, length);
        ImageUtil.Flip(data, mWidth, mHeight, true, true); //
        mBitmap.set(Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888));

        time = System.currentTimeMillis() - time;

        String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time);

        if (mListener != null)
        mListener.onMessage(msg);

        setIsLoading(false);
    }

    public void randomJitter()
    {
        setIsLoading(true);

        long time = System.currentTimeMillis();

        int length = mData.length;
        int[] data = new int[length];

        System.arraycopy(mData, 0, data, 0, length);
        ImageUtil.RandomJitter(data, mWidth, mHeight, (short)5); //
        mBitmap.set(Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888));

        time = System.currentTimeMillis() - time;

        String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time);

        if (mListener != null)
        mListener.onMessage(msg);

        setIsLoading(false);
    }

    public void swirl()
    {
        setIsLoading(true);

        long time = System.currentTimeMillis();

        int length = mData.length;
        int[] data = new int[length];

        System.arraycopy(mData, 0, data, 0, length);
        ImageUtil.Swirl(data, mWidth, mHeight, 0.4, true); //
        mBitmap.set(Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888));

        time = System.currentTimeMillis() - time;

        String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time);

        if (mListener != null)
        mListener.onMessage(msg);

        setIsLoading(false);
    }

    public void sphere()
    {
        setIsLoading(true);

        long time = System.currentTimeMillis();

        int length = mData.length;
        int[] data = new int[length];

        System.arraycopy(mData, 0, data, 0, length);
        ImageUtil.Sphere(data, mWidth, mHeight, false); //
        mBitmap.set(Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888));

        time = System.currentTimeMillis() - time;

        String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time);

        if (mListener != null)
        mListener.onMessage(msg);

        setIsLoading(false);
    }

    public void timeWarp()
    {
        setIsLoading(true);

        long time = System.currentTimeMillis();

        int length = mData.length;
        int[] data = new int[length];

        System.arraycopy(mData, 0, data, 0, length);
        ImageUtil.TimeWarp(data, mWidth, mHeight, (byte)15, false); //
        mBitmap.set(Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888));

        time = System.currentTimeMillis() - time;

        String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time);

        if (mListener != null)
        mListener.onMessage(msg);

        setIsLoading(false);
    }

    public void moire()
    {
        setIsLoading(true);

        long time = System.currentTimeMillis();

        int length = mData.length;
        int[] data = new int[length];

        System.arraycopy(mData, 0, data, 0, length);
        ImageUtil.Moire(data, mWidth, mHeight, 3); //
        mBitmap.set(Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888));

        time = System.currentTimeMillis() - time;

        String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time);

        if (mListener != null)
        mListener.onMessage(msg);

        setIsLoading(false);
    }

    public void water()
    {
        setIsLoading(true);

        long time = System.currentTimeMillis();

        int length = mData.length;
        int[] data = new int[length];

        System.arraycopy(mData, 0, data, 0, length);
        ImageUtil.Water(data, mWidth, mHeight, (short)15, false); //
        mBitmap.set(Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888));

        time = System.currentTimeMillis() - time;

        String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time);

        if (mListener != null)
        mListener.onMessage(msg);

        setIsLoading(false);
    }

    public void pixelate()
    {
        setIsLoading(true);

        long time = System.currentTimeMillis();

        int length = mData.length;
        int[] data = new int[length];

        System.arraycopy(mData, 0, data, 0, length);
        ImageUtil.Pixelate(data, mWidth, mHeight, (short)15, false); //
        mBitmap.set(Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888));

        time = System.currentTimeMillis() - time;

        String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time);

        if (mListener != null)
        mListener.onMessage(msg);

        setIsLoading(false);
    }

    public void fishEye()
    {
        setIsLoading(true);

        long time = System.currentTimeMillis();

        int length = mData.length;
        int[] data = new int[length];

        System.arraycopy(mData, 0, data, 0, length);
        ImageUtil.FishEye(data, mWidth, mHeight, 0.03, false, false); //
        mBitmap.set(Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888));

        time = System.currentTimeMillis() - time;

        String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time);

        if (mListener != null)
        mListener.onMessage(msg);

        setIsLoading(false);
    }

//void LiquidRender(byte* surface);
//void Agg2DOverlayImage(System::Drawing::Bitmap^ overlayImg);
    public void bokehEffects()
    {
        setIsLoading(true);

        long time = System.currentTimeMillis();

        int length = mData.length;
        int[] data = new int[length];

        System.arraycopy(mData, 0, data, 0, length);
        ImageUtil.BokehEffects(data, mWidth, mHeight); //
        mBitmap.set(Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888));

        time = System.currentTimeMillis() - time;

        String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time);

        if (mListener != null)
        mListener.onMessage(msg);

        setIsLoading(false);
    }


    interface ImageFilterViewModelListener{
        void onMessage(String msg);
    }
}
