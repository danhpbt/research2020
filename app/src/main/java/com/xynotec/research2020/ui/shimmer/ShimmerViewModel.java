package com.xynotec.research2020.ui.shimmer;

import androidx.databinding.ObservableArrayList;
import androidx.databinding.ObservableBoolean;
import androidx.databinding.ObservableList;
import androidx.lifecycle.LiveData;
import androidx.lifecycle.MutableLiveData;

import com.xynotec.dagger.BaseViewModel;
import com.xynotec.research2020.data.DataManager;
import com.xynotec.research2020.data.remote.cryptocurrency.listting.latest.CryptocurrencyListingsLatestResponse;
import com.xynotec.research2020.data.remote.cryptocurrency.listting.latest.Data;
import com.xynotec.utils.CommonUtils;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.TimeUnit;

import io.reactivex.android.schedulers.AndroidSchedulers;
import io.reactivex.schedulers.Schedulers;

public class ShimmerViewModel extends BaseViewModel {
    private final ObservableList<Data> listingLatestList = new ObservableArrayList<>();
    private final ObservableBoolean mIsLoading = new ObservableBoolean();

    ShimmerViewModelListener mListener;

    public ShimmerViewModel(DataManager dataManager) {
        super(dataManager);
        refreshListData();
    }

    public ObservableBoolean getIsLoading() {
        return mIsLoading;
    }

    public void setIsLoading(boolean isLoading) {
        mIsLoading.set(isLoading);
    }

    public ObservableList<Data> getListingLatestList()
    {
        return listingLatestList;
    }


    public void refreshListData()
    {
        setIsLoading(true);

        getCompositeDisposable().add(getDataManager()
                .doCryptoCurrencyListingsLatest(
                        new CryptocurrencyListingsLatestResponse.LatestRequest(1, 100, "USD"))
                .delay(3, TimeUnit.SECONDS) //delay to view shimmer
                .subscribeOn(Schedulers.io())
                .observeOn(AndroidSchedulers.mainThread())
                .subscribe(listingLatestResponse -> {
                    if (listingLatestResponse != null && listingLatestResponse.getData() != null) {
                        listingLatestList.clear();
                        listingLatestList.addAll(listingLatestResponse.getData());
                    }
                    setIsLoading(false);
                }, throwable -> {
                    setIsLoading(false);
                    if (mListener != null)
                        mListener.onError(throwable.getLocalizedMessage());
                }));
    }

    public void setListener(ShimmerViewModelListener listener)
    {
        mListener = listener;
    }

    interface ShimmerViewModelListener{
        void onError(String msg);
    }
}
