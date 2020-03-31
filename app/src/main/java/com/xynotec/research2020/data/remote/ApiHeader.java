package com.xynotec.research2020.data.remote;

import com.google.gson.annotations.Expose;
import com.google.gson.annotations.SerializedName;
import com.xynotec.research2020.di.ApiInfo;

import javax.inject.Inject;
import javax.inject.Singleton;

@Singleton
public class ApiHeader {
    private InfoApiHeader mInfoApiHeader;

    @Inject
    public ApiHeader(InfoApiHeader mInfoApiHeader) {
        this.mInfoApiHeader = mInfoApiHeader;
    }

    public InfoApiHeader getInfoApiHeader() {
        return mInfoApiHeader;
    }

    public static final class InfoApiHeader {
        @Expose
        @SerializedName("X-CMC_PRO_API_KEY")
        private String mApiKey;

        @Inject
        public InfoApiHeader(@ApiInfo String apiKey) {
            this.mApiKey = apiKey;
        }

        public String getApiKey() {
            return mApiKey;
        }

        public void setApiKey(String apiKey) {
            mApiKey = apiKey;
        }
    }
}


