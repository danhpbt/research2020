package com.xynotec.research2020.di.module;

import android.app.Application;
import android.content.Context;

import com.xynotec.research2020.data.AppDataManager;
import com.xynotec.research2020.data.DataManager;
import com.xynotec.research2020.data.local.db.AppDbHelper;
import com.xynotec.research2020.data.local.db.DbHelper;
import com.xynotec.research2020.data.local.prefs.AppPreferencesHelper;
import com.xynotec.research2020.data.local.prefs.PreferencesHelper;
import com.xynotec.research2020.data.remote.ApiHelper;
import com.xynotec.research2020.data.remote.AppApiHelper;
import com.xynotec.research2020.di.ApiInfo;

import javax.inject.Singleton;

import dagger.Module;
import dagger.Provides;
import io.realm.Realm;
import io.realm.RealmConfiguration;

@Module
public class AppModule {
    @Provides
    @Singleton
    Context provideContext(Application application) {
        return application;
    }

    @Singleton
    @Provides
    PreferencesHelper providePreferencesHelper(AppPreferencesHelper appPreferencesHelper){
        return appPreferencesHelper;
    }

    @Singleton
    @Provides
    DbHelper provideDbHelper(AppDbHelper appDbHelper){
        return appDbHelper;
    }

    @Provides
    @Singleton
    ApiHelper provideApiHelper(AppApiHelper appApiHelper) {
        return appApiHelper;
    }

    @Provides
    @Singleton
    DataManager provideDataManager(AppDataManager appDataManager) {
        return appDataManager;
    }

    @Provides
    @Singleton
    RealmConfiguration provideRealmConfiguration(Context context) {
        Realm.init(context);
        RealmConfiguration realmConfig = new RealmConfiguration
                .Builder()
                .deleteRealmIfMigrationNeeded()
                .build();
        Realm.setDefaultConfiguration(realmConfig);
        return realmConfig;
    }

    @Provides
    @ApiInfo
    String provideApiKey() {
        return "00b7eea6-8db0-447e-912d-7f7a56761ede";
    }

}
