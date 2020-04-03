package com.xynotec.camera;

import android.hardware.Camera;

public interface CameraCallback {
    void onPreviewFrame(byte[] data, int rotation, Camera camera);
}
