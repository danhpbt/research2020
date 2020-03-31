package com.xynotec.research2020.data.remote.cryptocurrency.listting.latest;

import androidx.annotation.Nullable;

import com.google.gson.annotations.Expose;
import com.google.gson.annotations.SerializedName;

import java.util.List;

import javax.inject.Inject;

public class CryptocurrencyListingsLatestResponse {

    @Expose
    @SerializedName("data")
    private List<Data> data;

    @Expose
    @SerializedName("status")
    private Status status;

    public List<Data>  getData ()
    {
        return data;
    }


    @Override
    public boolean equals(@Nullable Object o) {
        if (this == o) {
            return true;
        }
        if (!(o instanceof CryptocurrencyListingsLatestResponse)) {
            return false;
        }

        CryptocurrencyListingsLatestResponse that = (CryptocurrencyListingsLatestResponse) o;

        if (!status.equals(that.status)) {
            return false;
        }

        return data.equals(that.data);
    }

    public void setData (List<Data> datas)
    {
        this.data = datas;
    }

    public Status getStatus ()
    {
        return status;
    }

    public void setStatus (Status status)
    {
        this.status = status;
    }

    @Override
    public String toString()
    {
        return "ClassPojo [data = "+ data +", status = "+status+"]";
    }

    public static class LatestRequest {

        @Expose
        @SerializedName("start")
        private String start;

        @Expose
        @SerializedName("limit")
        private String limit;

        @Expose
        @SerializedName("convert")
        private String convert;

        @Inject
        public LatestRequest(int start, int limit, String convert) {
            this.start = start + "";
            this.limit = limit + "";
            this.convert = convert;
        }
    }
}
