package com.xynotec.research2020.data.remote.cryptocurrency.listting.latest;

import com.google.gson.annotations.Expose;
import com.google.gson.annotations.SerializedName;

public class Quote {
    @Expose
    @SerializedName("USD")
    private USD USD;

    public USD getUSD ()
    {
        return USD;
    }

    public void setUSD (USD USD)
    {
        this.USD = USD;
    }

    @Override
    public String toString()
    {
        return "ClassPojo [USD = "+USD+"]";
    }
}
