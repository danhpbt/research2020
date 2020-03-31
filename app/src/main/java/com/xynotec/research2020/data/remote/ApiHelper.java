package com.xynotec.research2020.data.remote;

import com.xynotec.research2020.data.remote.cryptocurrency.listting.latest.CryptocurrencyListingsLatestResponse;

import io.reactivex.Single;

public interface ApiHelper {

    Single<CryptocurrencyListingsLatestResponse> doCryptoCurrencyListingsLatest(
            CryptocurrencyListingsLatestResponse.LatestRequest request);
}
