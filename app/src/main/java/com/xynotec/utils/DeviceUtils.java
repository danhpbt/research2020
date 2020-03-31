package com.xynotec.utils;

import android.app.Activity;
import android.content.Context;
import android.content.res.Resources;
import android.graphics.Point;
import android.view.Display;
import android.view.View;
import android.view.WindowManager;
import android.view.inputmethod.InputMethodManager;

public class DeviceUtils
{
	public static float dp2px(Resources resources, float dp) {
		final float scale = resources.getDisplayMetrics().density;
		return  dp * scale + 0.5f;
	}

	public static float sp2px(Resources resources, float sp){
		final float scale = resources.getDisplayMetrics().scaledDensity;
		return sp * scale;
	}

	public static Point getDisplaySize(Context context)
	{
		Display display = ((WindowManager) context.getSystemService(Context.WINDOW_SERVICE)).getDefaultDisplay();
		Point size = new Point();
		display.getSize(size);
		return size;
	}

	public static void hideEmulatorKeyboard(Activity activity)
	{
		if (activity != null) {
			View view = activity.getCurrentFocus();
			if (view != null) {
				InputMethodManager imm = (InputMethodManager)activity.getSystemService(Context.INPUT_METHOD_SERVICE);
				imm.hideSoftInputFromWindow(view.getWindowToken(), 0);
			}
		}
	}

}
