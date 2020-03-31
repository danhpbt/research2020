package com.xynotec.research2020.ui.shimmer;

import android.os.Bundle;
import android.view.View;

import androidx.annotation.Nullable;
import androidx.appcompat.widget.Toolbar;
import androidx.lifecycle.ViewModelProvider;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.facebook.shimmer.ShimmerFrameLayout;
import com.xynotec.dagger.BaseActivity;
import com.xynotec.dagger.BaseViewModel;
import com.xynotec.research2020.BR;
import com.xynotec.research2020.R;
import com.xynotec.research2020.ViewModelProviderFactory;
import com.xynotec.research2020.databinding.ActivityShimmerBinding;
import com.xynotec.utils.CommonUtils;

import javax.inject.Inject;

import butterknife.BindView;

public class ShimmerActivity extends BaseActivity<ActivityShimmerBinding, ShimmerViewModel>
    implements ShimmerViewModel.ShimmerViewModelListener, ListingLatestAdapter.ListingLatestAdapterListener
{
    @Inject
    ListingLatestAdapter mListingLatestAdapter;

    @Inject
    LinearLayoutManager mLayoutManager;

    @Inject
    ViewModelProviderFactory factory;

    @BindView(R.id.rvItems)
    RecyclerView mRecyclerView;

    @BindView(R.id.shimmer_view_container)
    ShimmerFrameLayout mShimmerFrameLayout;

    private ShimmerViewModel mShimmerViewModel;

    @Override
    protected int getLayoutRes() {
        return R.layout.activity_shimmer;
    }

    @Override
    public int getBindingVariable() {
        return BR.shimmerVM;
    }

    @Override
    public ShimmerViewModel getViewModel() {
        mShimmerViewModel = new ViewModelProvider(this, factory).get(ShimmerViewModel.class);
        return mShimmerViewModel;
    }

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        Toolbar toolbar = (Toolbar)findViewById(R.id.sub_toolbar);
        if (toolbar != null) {
            setSupportActionBar(toolbar);

            getSupportActionBar().setHomeAsUpIndicator(R.drawable.ic_action_back);
            getSupportActionBar().setDisplayHomeAsUpEnabled(true);

            toolbar.setNavigationOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    onBackPressed();
                }
            });
        }

        mRecyclerView.setLayoutManager(mLayoutManager);
        mRecyclerView.setAdapter(mListingLatestAdapter);
        mListingLatestAdapter.setListener(this);

    }

    @Override
    public void onError(String msg) {
        CommonUtils.showErrorDlg(this, msg);
    }

    @Override
    public void onClickListener(int index) {
        CommonUtils.showInfoDlg(this, "Item click " + index);
    }

}