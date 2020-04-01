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
    private String debugTime = "Debug Info";

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
            int imgW = overlayPreviewBmp.getWidth();
            int imgH = overlayPreviewBmp.getHeight();

            canvas.drawBitmap(overlayPreviewBmp, new Rect(0, 0, imgW, imgH),
                    new Rect(0, 0, this.getWidth(), this.getHeight()), mPaint);

            canvas.drawText(debugTime, getWidth()/2, getHeight()/2, mPaint);
        }
    }

    public void CreateBitmapOverlay(byte[] dataYUV, int postRotate, Camera camera)
    {
        long time = System.currentTimeMillis();

        Bitmap bitmap = CreatePreviewBitmap(dataYUV, postRotate, camera);
        overlayPreviewBmp = bitmap.copy(Bitmap.Config.ARGB_8888, true);
        bitmap.recycle();

        int width = overlayPreviewBmp.getWidth();
        int height = overlayPreviewBmp.getHeight();
        int stride = width;

        if (dataRGB == null)
            dataRGB = new int[width * height];

        overlayPreviewBmp.getPixels(dataRGB, 0, stride, 0, 0, width, height);

        GrayScale(dataRGB, width, height);
        //EdgeDetector(dataRGB, width, height);

        overlayPreviewBmp.setPixels(dataRGB, 0, stride, 0, 0, width, height);

        time = System.currentTimeMillis() - time;
        debugTime = String.format("GrayScale: %dx%d in %sms", width, height, time);
        this.invalidate();
    }

    private Bitmap CreatePreviewBitmap(byte[] dataYUV, int postRotate, Camera camera)
    {
        Camera.Parameters parameters = camera.getParameters();
        int format = parameters.getPreviewFormat();
        int width = parameters.getPreviewSize().width;
        int height = parameters.getPreviewSize().height;

        YuvImage yuv = new YuvImage(dataYUV, format, width, height, null);

        ByteArrayOutputStream out = new ByteArrayOutputStream();
        yuv.compressToJpeg(new Rect(0, 0, width, height), 50, out);

        byte[] bytes = out.toByteArray();
        Bitmap bitmap  = BitmapFactory.decodeByteArray(bytes, 0, bytes.length);

        Matrix mat = new Matrix();
        mat.postRotate(postRotate);
        bitmap = Bitmap.createBitmap(bitmap, 0, 0, bitmap.getWidth(), bitmap.getHeight(), mat, true);

        return bitmap;
    }


}
