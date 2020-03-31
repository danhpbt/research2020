package com.xynotec.research2020.data;

import android.content.Context;

import androidx.lifecycle.LiveData;

import com.xynotec.research2020.data.remote.cryptocurrency.listting.latest.CryptocurrencyListingsLatestResponse;

import java.util.List;

import io.reactivex.Single;

public interface DataManager {

    Context getContext();

    Single<CryptocurrencyListingsLatestResponse> doCryptoCurrencyListingsLatest(CryptocurrencyListingsLatestResponse.LatestRequest request);
}
