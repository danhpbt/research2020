package com.xynotec.research2020;

import android.content.Context;
import android.content.res.AssetManager;

import com.xynotec.research2020.di.component.AppComponent;
import com.xynotec.research2020.di.component.DaggerAppComponent;

import dagger.android.AndroidInjector;
import dagger.android.DaggerApplication;

public class MainApplication extends DaggerApplication {

    static
    {
        System.loadLibrary("simplecam");
    }

    private static Context context;
    public static Context getContext()
    {
        return context;
    }

    static native void loadAssetManager(AssetManager mgr);

    @Override
    public void onCreate() {
        super.onCreate();
        context = getApplicationContext();

        loadAssetManager(context.getAssets());
    }

    @Override
    protected AndroidInjector<? extends DaggerApplication> applicationInjector() {
        AppComponent component = DaggerAppComponent.builder().application(this).build();
        component.inject(this);

        return component;
    }
}
