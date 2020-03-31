package com.xynotec.research2020;

import android.content.Context;

import com.xynotec.research2020.di.component.AppComponent;
import com.xynotec.research2020.di.component.DaggerAppComponent;

import dagger.android.AndroidInjector;
import dagger.android.DaggerApplication;

public class MainApplication extends DaggerApplication {

    static
    {
        System.loadLibrary("dictdroid");
    }

    private static Context context;
    public static Context getContext()
    {
        return context;
    }

    @Override
    public void onCreate() {
        super.onCreate();
        context = getApplicationContext();
    }

    @Override
    protected AndroidInjector<? extends DaggerApplication> applicationInjector() {
        AppComponent component = DaggerAppComponent.builder().application(this).build();
        component.inject(this);

        return component;
    }
}
