package com.xynotec.research2020.di.component;

import android.app.Application;

import com.xynotec.research2020.MainApplication;
import com.xynotec.research2020.di.module.ActivityBuilder;
import com.xynotec.research2020.di.module.AppModule;

import javax.inject.Singleton;

import dagger.BindsInstance;
import dagger.Component;
import dagger.android.AndroidInjector;
import dagger.android.support.AndroidSupportInjectionModule;

@Singleton
@Component(modules = {AndroidSupportInjectionModule.class, ActivityBuilder.class, AppModule.class})
public interface AppComponent extends AndroidInjector<MainApplication> {
    void inject(MainApplication application);

    @Component.Builder
    interface Builder {
        @BindsInstance
        Builder application(Application application);

        AppComponent build();
    }
}
