package com.xynotec.utils;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Build;
import android.provider.Settings;
import android.util.Log;

import com.xynotec.research2020.R;


public class CommonUtils {

    private static final String TAG = "CommonUtils";

    public static void delay(int milisecond)
    {
        try
        {
            Thread.sleep(milisecond);
        }
        catch (Exception e)
        {
            Log.d(TAG, "delay: " + e.getLocalizedMessage());
        }
    }

    public static void showErrorDlg(Context context, String msg)
    {
        AlertDialog infoDlg = new AlertDialog.Builder(context, R.style.AlertDialogErrorStyle)
                .setIcon(R.drawable.ic_alert_error)
                .setTitle(R.string.app_name)
                .setMessage(msg)
                .setPositiveButton(R.string.str_ok, null)
                .setCancelable(false)
                .create();

        infoDlg.show();
    }

    public static void showWarningDlg(Context context, String msg)
    {
        AlertDialog infoDlg = new AlertDialog.Builder(context, R.style.AlertDialogWarningStyle)
                .setIcon(R.drawable.ic_alert_warning)
                .setTitle(R.string.app_name)
                .setMessage(msg)
                .setPositiveButton(R.string.str_ok, null)
                .setCancelable(false)
                .create();

        infoDlg.show();
    }

    public static void showInfoDlg(Context context, String msg)
    {
        AlertDialog infoDlg = new AlertDialog.Builder(context, R.style.AlertDialogInfoStyle)
                .setIcon(R.drawable.ic_alert_info)
                .setTitle(R.string.app_name)
                .setMessage(msg)
                .setPositiveButton(R.string.str_ok, null)
                .setCancelable(false)
                .create();

        infoDlg.show();
    }

    public static void showSuccessDlg(Context context, String msg)
    {
        AlertDialog infoDlg = new AlertDialog.Builder(context, R.style.AlertDialogSuccessStyle)
                .setIcon(R.drawable.ic_alert_success)
                .setTitle(R.string.app_name)
                .setMessage(msg)
                .setPositiveButton(R.string.str_ok, null)
                .setCancelable(false)
                .create();

        infoDlg.show();
    }
}
