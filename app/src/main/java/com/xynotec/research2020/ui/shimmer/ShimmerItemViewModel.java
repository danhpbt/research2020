package com.xynotec.research2020.ui.shimmer;

import androidx.databinding.ObservableField;
import androidx.databinding.ObservableInt;

import com.xynotec.research2020.data.remote.cryptocurrency.listting.latest.Data;
import com.xynotec.utils.MathUtils;

public class ShimmerItemViewModel {
    final ObservableInt mIndex = new ObservableInt();

    final Data mData;

    private ShimmerItemViewModelListener mListener;

    public ShimmerItemViewModel(int index, Data data) {
        this.mIndex.set(index + 1);
        this.mData = data;
    }

    public String getIndex()
    {
        return mIndex.get() + "";
    }

    public String getSymbolImg()
    {
        String img_url = String.format("https://s2.coinmarketcap.com/static/img/coins/64x64/%s.png",
                mData.getId());

        return img_url;
    }

    public String getName()
    {
        return mData.getName();
    }

    public String getSymbol()
    {
        return mData.getSymbol();
    }

    public boolean getUpDownChange24h()
    {
        String str_change_24h = mData.getQuote().getUSD().getPercent_change_24h();
        float change_24h = Float.parseFloat(str_change_24h);
        boolean bUp = change_24h < 0 ? false : true;

        return bUp;
    }

    public String getPercentChange24h()
    {
        String str_change_24h = mData.getQuote().getUSD().getPercent_change_24h();
        float change_24h = Float.parseFloat(str_change_24h);
        if (change_24h < 0)
            str_change_24h = String.format(" \u25BC %.2f%%", change_24h);
        else
            str_change_24h = String.format(" \u25B2 %.2f%%", change_24h);

        return str_change_24h;
    }

    public String getPrice()
    {
        String str_price = mData.getQuote().getUSD().getPrice();
        float price = Float.parseFloat(str_price);
        if (price < 1)
            str_price = String.format("$%.6f", price);
        else
            str_price = String.format("$%.2f", price);
        return str_price;
    }

    public String getMarketCap()
    {
        final double THOUSAND = 1000;
        final double MILLION = THOUSAND*THOUSAND;
        final double BILLION = MILLION*THOUSAND;

        double market_cap = Double.parseDouble(mData.getQuote().getUSD().getMarket_cap());

        String str_market_cap;
        if (market_cap > BILLION)
        {
            market_cap = MathUtils.roundDouble(market_cap/BILLION, 2);
            str_market_cap = String.format("MCap $%.2f Bn", market_cap);
        }
        else if (market_cap > MILLION)
        {
            market_cap = MathUtils.roundDouble(market_cap/MILLION, 2);
            str_market_cap = String.format("MCap $%.2f M", market_cap);
        }
        else if (market_cap > THOUSAND)
        {
            market_cap = MathUtils.roundDouble(market_cap/THOUSAND, 2);
            str_market_cap = String.format("MCap $%.2f K", market_cap);
        }
        else
        {
            str_market_cap = String.format("MCap $%.2f", market_cap);
        }

        return str_market_cap;
    }

    public void setListener(ShimmerItemViewModelListener listener)
    {
        mListener = listener;
    }

    public void onItemClick()
    {
        if (mListener != null)
            mListener.onClick(mIndex.get());
    }

    public interface ShimmerItemViewModelListener
    {
        void onClick(int index);
    }

}
