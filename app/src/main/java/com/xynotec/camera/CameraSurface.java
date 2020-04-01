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

    private Camera.Size cameraPreviewSize;
    private Context mContext;

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
            camera.setPreviewCallback((data, cam) -> {
                if (callback !=null)
                    callback.onPreviewFrame(data, cam);
            });

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
        Camera.Parameters parameters = camera.getParameters();
        Display display = ((WindowManager)mContext.getSystemService(WINDOW_SERVICE)).getDefaultDisplay();

        if(display.getRotation() == Surface.ROTATION_0) {
            parameters.setPreviewSize(height, width);
            camera.setDisplayOrientation(90);
        }
        else if(display.getRotation() == Surface.ROTATION_90) {
            parameters.setPreviewSize(width, height);
            camera.setDisplayOrientation(0);
        }
        else  if(display.getRotation() == Surface.ROTATION_180) {
            parameters.setPreviewSize(height, width);
            camera.setDisplayOrientation(270);
        }
        else if(display.getRotation() == Surface.ROTATION_270) {
            parameters.setPreviewSize(width, height);
            camera.setDisplayOrientation(180);
        }

        camera.setParameters(parameters);
    }

    void startPreviewCamera()
    {
        Camera.Parameters parameters = camera.getParameters();
        cameraPreviewSize = parameters.getPreviewSize();

        camera.startPreview();
        isStarted = true;
    }

    public int GetPreviewWidth()
    {
        return cameraPreviewSize.width;
    }

    public int GetPreviewHeight()
    {
        return cameraPreviewSize.height;
    }
}