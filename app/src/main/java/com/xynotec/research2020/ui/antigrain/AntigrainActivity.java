package com.xynotec.research2020.ui.antigrain;

import android.Manifest;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.graphics.SurfaceTexture;
import android.hardware.Camera;
import android.hardware.camera2.CameraCharacteristics;
import android.hardware.camera2.CameraManager;
import android.hardware.camera2.params.StreamConfigurationMap;
import android.os.Bundle;
import android.util.Log;
import android.util.Size;
import android.util.SparseIntArray;
import android.view.Surface;
import android.view.SurfaceView;
import android.view.TextureView;
import android.widget.FrameLayout;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import com.xynotec.camera.CameraCallback;
import com.xynotec.camera.CameraOverlayView;
import com.xynotec.camera.CameraSurface;
import com.xynotec.research2020.R;

import butterknife.BindView;
import butterknife.ButterKnife;

public class AntigrainActivity extends AppCompatActivity implements CameraCallback {

    private static final String TAG = "AntigrainActivity";

    private static final int REQUEST_CAMERA_PERMISSION = 200;

    @BindView(R.id.cameraHolder)
    FrameLayout mCameraHolder;

    CameraSurface mCameraSurface;
    CameraOverlayView mCameraOverlayView;

    private boolean overlayPreview = true;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_antigrain);

        ButterKnife.bind(this);

        openCamera();
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        if (requestCode == REQUEST_CAMERA_PERMISSION) {
            if (grantResults[0] == PackageManager.PERMISSION_DENIED) {
                // close the app
                Toast.makeText(AntigrainActivity.this, "Sorry!!!, you can't use this app without granting permission", Toast.LENGTH_LONG).show();
                finish();
            }
            else if (grantResults[0] == PackageManager.PERMISSION_GRANTED)
            {
                setupPictureMode();
            }
        }
    }

    @Override
    public void onPreviewFrame(byte[] data, int rotation, Camera camera) {

        if (overlayPreview == true)
        {
            mCameraOverlayView.CreateBitmapOverlay(data, mCameraSurface.getPostRotate(), camera);
            mCameraOverlayView.invalidate();
        }
    }


    private void setupPictureMode(){

        if (overlayPreview == false)
        {
            mCameraSurface = new CameraSurface(this);
            mCameraHolder.addView(mCameraSurface, new FrameLayout.LayoutParams(FrameLayout.LayoutParams.MATCH_PARENT, FrameLayout.LayoutParams.MATCH_PARENT));
            mCameraSurface.setCallback(this);
        }
        else
        {
            mCameraSurface = new CameraSurface(this);
            mCameraOverlayView  = new CameraOverlayView(this);

            mCameraHolder.addView(mCameraSurface, new FrameLayout.LayoutParams(FrameLayout.LayoutParams.MATCH_PARENT, FrameLayout.LayoutParams.MATCH_PARENT));
            mCameraHolder.addView(mCameraOverlayView, new FrameLayout.LayoutParams(FrameLayout.LayoutParams.MATCH_PARENT, FrameLayout.LayoutParams.MATCH_PARENT));
            mCameraSurface.setCallback(this);
        }
    }

    private void openCamera()
    {
        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.CAMERA) != PackageManager.PERMISSION_GRANTED &&
                ActivityCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(AntigrainActivity.this, new String[]{Manifest.permission.CAMERA, Manifest.permission.WRITE_EXTERNAL_STORAGE}, REQUEST_CAMERA_PERMISSION);
            return;
        }

        setupPictureMode();
    }
}
