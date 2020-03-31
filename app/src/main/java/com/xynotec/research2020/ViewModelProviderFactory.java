package com.xynotec.research2020;

import androidx.annotation.NonNull;
import androidx.lifecycle.ViewModel;
import androidx.lifecycle.ViewModelProvider;

import com.xynotec.research2020.data.DataManager;
import com.xynotec.research2020.ui.main.MainViewModel;
import com.xynotec.research2020.ui.shimmer.ShimmerViewModel;

import javax.inject.Inject;
import javax.inject.Singleton;

@Singleton
public class ViewModelProviderFactory implements ViewModelProvider.Factory {

    private final DataManager mDataManager;

    @Inject
    public ViewModelProviderFactory(DataManager dataManager) {
        mDataManager = dataManager;
    }

    @NonNull
    @Override
    public <T extends ViewModel> T create(@NonNull Class<T> modelClass) {
        if (modelClass.isAssignableFrom(MainViewModel.class)) {
            return (T) new MainViewModel(mDataManager);
        }
        else if (modelClass.isAssignableFrom(ShimmerViewModel.class)) {
            return (T) new ShimmerViewModel(mDataManager);
        }
        //noinspection unchecked
        throw new IllegalArgumentException("Unknown ViewModel class");
    }

}
