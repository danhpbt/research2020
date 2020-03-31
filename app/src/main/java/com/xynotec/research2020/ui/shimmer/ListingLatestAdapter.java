package com.xynotec.research2020.ui.shimmer;

import android.view.LayoutInflater;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.xynotec.dagger.BaseViewHolder;
import com.xynotec.research2020.data.remote.cryptocurrency.listting.latest.Data;
import com.xynotec.research2020.databinding.ListingLatestListItemBinding;

import java.util.List;

public class ListingLatestAdapter extends RecyclerView.Adapter<BaseViewHolder> {

    ListingLatestAdapterListener mListener;

    List<Data> listingLatestList;

    public ListingLatestAdapter(List<Data> listingLatestList) {
        this.listingLatestList = listingLatestList;
    }

    @NonNull
    @Override
    public BaseViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        ListingLatestListItemBinding listingLatestListItemBinding =
                ListingLatestListItemBinding.inflate(LayoutInflater.from(parent.getContext()),
                        parent, false);
        return new ListingLatestViewHolder(listingLatestListItemBinding);
    }

    @Override
    public void onBindViewHolder(@NonNull BaseViewHolder holder, int position) {
        holder.onBind(position);
    }

    @Override
    public int getItemViewType(int position) {
        return 0;
    }

    @Override
    public int getItemCount() {
        if (listingLatestList != null && listingLatestList.size() > 0) {
            return listingLatestList.size();
        } else {
            return 0;
        }
    }

    public void clearItems() {
        listingLatestList.clear();
    }

    public void addItems(List<Data> data) {
        listingLatestList.addAll(data);
        notifyDataSetChanged();
    }

    public void setListener(ListingLatestAdapterListener listener)
    {
        mListener = listener;
    }

    public interface ListingLatestAdapterListener
    {
        void onClickListener(int index);
    }

    public class ListingLatestViewHolder extends BaseViewHolder
        implements ShimmerItemViewModel.ShimmerItemViewModelListener
    {
        ListingLatestListItemBinding mBinding;
        ShimmerItemViewModel mShimmerItemViewModel;

        public ListingLatestViewHolder(ListingLatestListItemBinding binding) {
            super(binding.getRoot());
            this.mBinding = binding;
        }

        @Override
        public void onBind(int position) {
            final Data data = listingLatestList.get(position);
            mShimmerItemViewModel = new ShimmerItemViewModel(position, data);
            mShimmerItemViewModel.setListener(this);
            mBinding.setViewModel(mShimmerItemViewModel);

            // Immediate Binding
            // When a variable or observable changes, the binding will be scheduled to change before
            // the next frame. There are times, however, when binding must be executed immediately.
            // To force execution, use the executePendingBindings() method.
            mBinding.executePendingBindings();
        }

        @Override
        public void onClick(int index) {
            mListener.onClickListener(index);
        }
    }
}
