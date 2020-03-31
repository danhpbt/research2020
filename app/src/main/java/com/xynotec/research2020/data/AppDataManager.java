package com.xynotec.research2020.data;

import android.content.Context;

import androidx.lifecycle.LiveData;

import com.xynotec.research2020.data.local.db.DbHelper;
import com.xynotec.research2020.data.local.prefs.PreferencesHelper;
import com.xynotec.research2020.data.remote.ApiHelper;
import com.xynotec.research2020.data.remote.cryptocurrency.listting.latest.CryptocurrencyListingsLatestResponse;

import java.util.List;

import javax.inject.Inject;
import javax.inject.Singleton;

import io.reactivex.Single;

@Singleton
public class AppDataManager implements DataManager {
    private static final String TAG = "AppDataManager";

    private final Context mContext;

    private final DbHelper mDbHelper;

    private final ApiHelper mApiHelper;

    private final PreferencesHelper mPreferencesHelper;

    @Inject
    public AppDataManager(Context mContext, DbHelper mDbHelper,
                          PreferencesHelper mPreferencesHelper,
                          ApiHelper apiHelper) {
        this.mContext = mContext;
        this.mDbHelper = mDbHelper;
        this.mPreferencesHelper = mPreferencesHelper;
        this.mApiHelper = apiHelper;
    }

    @Override
    public Context getContext() {
        return mContext;
    }

    @Override
    public Single<CryptocurrencyListingsLatestResponse> doCryptoCurrencyListingsLatest(CryptocurrencyListingsLatestResponse.LatestRequest request) {
        return mApiHelper.doCryptoCurrencyListingsLatest(request);
    }
}
