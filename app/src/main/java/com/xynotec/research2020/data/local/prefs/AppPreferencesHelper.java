package com.xynotec.research2020.data.local.prefs;

import android.content.Context;
import android.content.SharedPreferences;
import android.graphics.Point;

import com.xynotec.utils.DeviceUtils;

import javax.inject.Inject;

public class AppPreferencesHelper implements PreferencesHelper{
    final static String PREF_NAME = "AppPrefCache";

    private final SharedPreferences mPrefs;
    private final Context mContext;

    @Inject
    public AppPreferencesHelper(Context context) {
        mContext = context;
        mPrefs = mContext.getSharedPreferences(PREF_NAME, Context.MODE_PRIVATE);
    }

}
