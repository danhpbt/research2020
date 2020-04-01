package com.xynotec.camera;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.graphics.Rect;
import android.graphics.YuvImage;
import android.hardware.Camera;
import android.view.View;

import java.io.ByteArrayOutputStream;

public class CameraOverlayView extends View {

    static
    {
        System.loadLibrary("simplecam");
    }

    private Bitmap overlayPreviewBmp = null;
    private int[] dataRGB = null;
    private int previewW;
    private int previewH;
    private String debugTime;

    Paint mPaint;

    static native void YUV2RGB(byte[] dataYUV, int[] dataRGB, int width, int height);
    static native void GrayScale(int[] dataRGB, int width, int height);
    static native void EdgeDetector(int[] dataRGB, int width, int height);

    public CameraOverlayView(Context context) {
        super(context);

        mPaint = new Paint();
        mPaint.setStyle(Paint.Style.FILL);
        mPaint.setColor(Color.MAGENTA);

        mPaint.setTextAlign(Paint.Align.CENTER);
        mPaint.setTextSize(80.0f);
    }

    @Override
    protected void onDraw(Canvas canvas) {
        // TODO Auto-generated method stub

        if (overlayPreviewBmp != null)
        {
            canvas.drawBitmap(overlayPreviewBmp, 0 , 0, mPaint);
//            canvas.drawBitmap(overlayPreviewBmp, new Rect(0, 0, previewW, previewH),
//                    new Rect(0, 0, this.getWidth(), this.getHeight()), mPaint);

            //canvas.drawText(debugTime, getWidth()/2, getHeight()/2, mPaint);
        }


        super.onDraw(canvas);
    }

    public void CreateBitmapOverlay(byte[] dataYUV, int width, int height)
    {
        if ((dataYUV != null) && (width != 0) && (height != 0))
        {
            long time = System.currentTimeMillis();
            if (dataRGB == null)
                dataRGB = new int[width*height];

            YUV2RGB(dataYUV, dataRGB, width, height);
            GrayScale(dataRGB, width, height);

            if (overlayPreviewBmp == null)
                overlayPreviewBmp = Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888);

            overlayPreviewBmp.setPixels(dataRGB, 0, width, 0, 0, width, height);

            previewW = width;
            previewH = height;

            time = System.currentTimeMillis() - time;

            debugTime = String.format("Process: %dx%d in %sms", width, height, time);
            this.invalidate();
        }

    }

    public void CreatePreviewBitmap(byte[] dataYUV, Camera camera)
    {
        Camera.Parameters parameters = camera.getParameters();
        int width = parameters.getPreviewSize().width;
        int height = parameters.getPreviewSize().height;

        YuvImage yuv = new YuvImage(dataYUV, parameters.getPreviewFormat(), width, height, null);

        ByteArrayOutputStream out = new ByteArrayOutputStream();
        yuv.compressToJpeg(new Rect(0, 0, width, height), 50, out);

        byte[] bytes = out.toByteArray();
        overlayPreviewBmp  = BitmapFactory.decodeByteArray(bytes, 0, bytes.length);

        //rotate test
        Matrix mat = new Matrix();
        mat.postRotate(90);
        overlayPreviewBmp = Bitmap.createBitmap(overlayPreviewBmp, 0, 0, overlayPreviewBmp.getWidth(), overlayPreviewBmp.getHeight(), mat, true);

    }

}
