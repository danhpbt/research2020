package com.xynotec.research2020.data.remote;

import com.rx2androidnetworking.Rx2AndroidNetworking;
import com.xynotec.research2020.data.remote.cryptocurrency.listting.latest.CryptocurrencyListingsLatestResponse;

import javax.inject.Inject;
import javax.inject.Singleton;

import io.reactivex.Single;

@Singleton
public class AppApiHelper implements ApiHelper {

    private ApiHeader mApiHeader;

    @Inject
    public AppApiHelper(ApiHeader apiHeader) {
        mApiHeader = apiHeader;
    }

    @Override
    public Single<CryptocurrencyListingsLatestResponse> doCryptoCurrencyListingsLatest(CryptocurrencyListingsLatestResponse.LatestRequest request) {
        return Rx2AndroidNetworking.get(ApiEndPoint.CRYPTOCURRENCY_LISTTING_LATEST)
                .addHeaders(mApiHeader.getInfoApiHeader())
                .addQueryParameter(request)
                .build()
                .getObjectSingle(CryptocurrencyListingsLatestResponse.class);
    }
}
