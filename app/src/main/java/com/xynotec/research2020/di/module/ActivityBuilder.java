package com.xynotec.research2020.di.module;

import com.xynotec.research2020.ui.imagefilter.ImageFilterActivity;
import com.xynotec.research2020.ui.main.MainActivity;
import com.xynotec.research2020.ui.main.MainActivityModule;
import com.xynotec.research2020.ui.shimmer.ShimmerActivity;
import com.xynotec.research2020.ui.shimmer.ShimmerActivityModule;

import dagger.Module;
import dagger.android.ContributesAndroidInjector;

@Module
public abstract class ActivityBuilder {
    @ContributesAndroidInjector(modules = {
            MainActivityModule.class,
    })
    abstract MainActivity bindMainActivity();

    @ContributesAndroidInjector(modules = {
            ShimmerActivityModule.class,
    })
    abstract ShimmerActivity bindShimmerActivity();

    @ContributesAndroidInjector(modules = {

    })
    abstract ImageFilterActivity bindImageFilterActivity();
}
