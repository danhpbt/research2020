package com.xynotec.camera;

import android.content.Context;
import android.graphics.ImageFormat;
import android.graphics.PixelFormat;
import android.hardware.Camera;
import android.util.AttributeSet;
import android.view.Display;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.WindowManager;

import java.io.IOException;
import java.util.List;

import static android.content.Context.WINDOW_SERVICE;

public class CameraSurface extends SurfaceView implements SurfaceHolder.Callback {

    private Camera camera = null;
    private SurfaceHolder holder = null;
    private CameraCallback callback = null;
    private boolean isStarted = false;

    private Context mContext;
    private int mPostRotate;

	public CameraSurface(Context context) {
            super(context);

            initialize(context);
        }


    public void setCallback(CameraCallback callback){
        this.callback = callback;
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
        if(null != camera && isStarted)
            camera.stopPreview();

            setupCamera(width, height);
            startPreviewCamera();
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        camera = Camera.open();

        try {
            camera.setPreviewDisplay(holder);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        isStarted = false;

        camera.stopPreview();
        camera.setPreviewCallback(null);
        camera.release();

        camera = null;
    }

    private void initialize(Context context) {
        mContext = context;
        holder = getHolder();
        holder.addCallback(this);
    }

    private void setupCamera(int width, int height)
    {
        mPostRotate = 0;
        Display display = ((WindowManager)mContext.getSystemService(WINDOW_SERVICE)).getDefaultDisplay();

        if(display.getRotation() == Surface.ROTATION_0) {
            mPostRotate = 90;
        }
        else if(display.getRotation() == Surface.ROTATION_90) {
            mPostRotate = 0;
        }
        else if(display.getRotation() == Surface.ROTATION_180) {
            mPostRotate = 270;
        }
        else if(display.getRotation() == Surface.ROTATION_270) {
            mPostRotate = 180;
        }

        camera.setDisplayOrientation(mPostRotate);
    }

    void startPreviewCamera()
    {
        camera.startPreview();
        camera.setPreviewCallback((data, cam) -> {
            if (callback !=null)
                callback.onPreviewFrame(data, cam);
        });

        isStarted = true;
    }

    public int getPostRotate()
    {
        return mPostRotate;
    }
}