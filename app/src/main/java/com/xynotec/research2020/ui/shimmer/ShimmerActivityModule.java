package com.xynotec.research2020.ui.shimmer;

import androidx.recyclerview.widget.LinearLayoutManager;

import com.xynotec.research2020.data.remote.cryptocurrency.listting.latest.CryptocurrencyListingsLatestResponse;

import java.util.ArrayList;

import dagger.Module;
import dagger.Provides;

@Module
public class ShimmerActivityModule {

    @Provides
    ListingLatestAdapter provideListingLatestAdapter() {
        return new ListingLatestAdapter(new ArrayList<>());
    }

    @Provides
    LinearLayoutManager provideLinearLayoutManager(ShimmerActivity activity) {
        return new LinearLayoutManager(activity);
    }

}
