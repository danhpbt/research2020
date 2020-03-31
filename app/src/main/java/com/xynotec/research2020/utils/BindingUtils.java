package com.xynotec.research2020.utils;


import android.content.Context;
import android.widget.ImageView;

import androidx.databinding.BindingAdapter;
import androidx.recyclerview.widget.RecyclerView;

import com.bumptech.glide.Glide;
import com.xynotec.research2020.data.remote.cryptocurrency.listting.latest.Data;
import com.xynotec.research2020.ui.shimmer.ListingLatestAdapter;

import java.util.List;

public final class BindingUtils {

    @BindingAdapter({"adapterRV"})
    public static void addListingLatestItems(RecyclerView recyclerView, List<Data> datas) {
        ListingLatestAdapter adapter = (ListingLatestAdapter) recyclerView.getAdapter();
        if (adapter != null) {
            adapter.clearItems();
            adapter.addItems(datas);
        }
    }

    @BindingAdapter("imageUrl")
    public static void setImageUrl(ImageView imageView, String url) {
        Context context = imageView.getContext();
        Glide.with(context).load(url).into(imageView);
    }
	
}
