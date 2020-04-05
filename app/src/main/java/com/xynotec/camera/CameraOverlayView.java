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

import com.xynotec.image.ARGBImage;

import java.io.ByteArrayOutputStream;

public class CameraOverlayView extends View {

    private ARGBImage overlayPreview;
    private String debugTime = "Debug Info";

    Paint mPaint;

    public CameraOverlayView(Context context) {
        super(context);

        overlayPreview = new ARGBImage();

        mPaint = new Paint();
        mPaint.setStyle(Paint.Style.FILL);
        mPaint.setColor(Color.MAGENTA);

        mPaint.setTextAlign(Paint.Align.CENTER);
        mPaint.setTextSize(80.0f);
    }

    @Override
    protected void onDraw(Canvas canvas) {
        // TODO Auto-generated method stub
        if (overlayPreview.getBitmap() != null)
        {
            int imgW = overlayPreview.getWidth();
            int imgH = overlayPreview.getHeight();

            canvas.drawBitmap(overlayPreview.getBitmap(), new Rect(0, 0, imgW, imgH),
                    new Rect(0, 0, this.getWidth(), this.getHeight()), mPaint);

            canvas.drawText(debugTime, getWidth()/2, getHeight()/2, mPaint);
        }
    }

    public void CreateBitmapOverlay(byte[] dataYUV, int postRotate, Camera camera)
    {
        long time = System.currentTimeMillis();

        Camera.Parameters parameters = camera.getParameters();
        int format = parameters.getPreviewFormat();
        int width = parameters.getPreviewSize().width;
        int height = parameters.getPreviewSize().height;

        overlayPreview.fromYUV(dataYUV, format, postRotate, width, height);
        overlayPreview.toGrayScale();
        overlayPreview.invalidate();

        time = System.currentTimeMillis() - time;
        debugTime = String.format("GrayScale: %dx%d in %sms", width, height, time);
        this.invalidate();
    }


}
