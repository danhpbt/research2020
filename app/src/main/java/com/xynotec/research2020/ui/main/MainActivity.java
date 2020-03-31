package com.xynotec.research2020.ui.main;

import android.content.ActivityNotFoundException;
import android.content.DialogInterface;
import android.content.Intent;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.provider.Settings;
import android.speech.RecognizerIntent;
import android.view.View;
import android.widget.ImageView;

import com.google.android.material.navigation.NavigationView;
import com.google.android.material.tabs.TabLayout;
import com.xynotec.dagger.BaseActivity;
import com.xynotec.research2020.BR;
import com.xynotec.research2020.R;
import com.xynotec.research2020.ViewModelProviderFactory;
import com.xynotec.research2020.databinding.ActivityMainBinding;
import com.xynotec.research2020.ui.shimmer.ShimmerActivity;

import androidx.annotation.Nullable;
import androidx.appcompat.app.ActionBarDrawerToggle;
import androidx.appcompat.app.AlertDialog;
import androidx.core.view.GravityCompat;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.ViewModelProvider;
import androidx.navigation.ui.AppBarConfiguration;
import androidx.drawerlayout.widget.DrawerLayout;
import androidx.appcompat.widget.Toolbar;
import androidx.viewpager.widget.ViewPager;

import java.util.ArrayList;

import javax.inject.Inject;

import butterknife.BindView;

public class MainActivity extends BaseActivity<ActivityMainBinding, MainViewModel> {

    private AppBarConfiguration mAppBarConfiguration;


    @Inject
    ViewModelProviderFactory factory;
    private MainViewModel mMainViewModel;
    ActivityMainBinding mActivityMainBinding;

    DrawerLayout drawer;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        getSupportActionBar().setTitle(R.string.main_activity_title);

        drawer = findViewById(R.id.drawer_layout);
        ActionBarDrawerToggle toggle = new ActionBarDrawerToggle(
                this, drawer, toolbar, R.string.navigation_drawer_open, R.string.navigation_drawer_close);
        drawer.addDrawerListener(toggle);
        toggle.syncState();

        NavigationView navigationView = findViewById(R.id.nav_view);
        navigationView.setNavigationItemSelectedListener(onNavigationItemSelectedListener);

    }

    NavigationView.OnNavigationItemSelectedListener onNavigationItemSelectedListener =
            menuItem -> {

                int id = menuItem.getItemId();

                if (id == R.id.nav_skimmer_loading) {
                    doSkimmerLoading();

                } else if (id == R.id.nav_antigrain_engine) {
                    doAntigrainEngine();
                }

                drawer.closeDrawer(GravityCompat.START);
                return true;
            };


    @Override
    protected int getLayoutRes() {
        return R.layout.activity_main;
    }

    @Override
    public MainViewModel getViewModel() {
        mMainViewModel = new ViewModelProvider(this, factory).get(MainViewModel.class);
        return mMainViewModel;
    }

    @Override
    public int getBindingVariable() {
        return BR.mainVM;
    }


    void doSkimmerLoading()
    {
        Intent intent = new Intent(this, ShimmerActivity.class);
        startActivity(intent);
    }

    private void doAntigrainEngine()
    {
    }

    private void doRateApp()
    {

    }

    private void doShareApp()
    {
    }

    private void doMoreApps()
    {
    }

    private void doRemoveAds()
    {
    }

    private void doSettings() {
//        Intent intent = new Intent(this, SettingActivity.class);
//        startActivity(intent);
    }

    void doAbout()
    {
//        Intent intent = new Intent(this, AboutActivity.class);
//        startActivity(intent);
    }


}
