package com.xynotec.research2020.data.remote.cryptocurrency.listting.latest;

import androidx.annotation.Nullable;

import com.google.gson.annotations.Expose;
import com.google.gson.annotations.SerializedName;

class Status {
    @Expose
    @SerializedName("error_message")
    private String error_message;

    @Expose
    @SerializedName("elapsed")
    private String elapsed;

    @Expose
    @SerializedName("credit_count")
    private String credit_count;

    @Expose
    @SerializedName("error_code")
    private String error_code;

    @Expose
    @SerializedName("timestamp")
    private String timestamp;

    @Expose
    @SerializedName("notice")
    private String notice;

    @Override
    public boolean equals(@Nullable Object o) {
        if (this == o) {
            return true;
        }
        if (!(o instanceof Status)) {
            return false;
        }

        Status that = (Status) o;

        if (!error_message.equals(that.error_message)) {
            return false;
        }

        if (!elapsed.equals(that.elapsed)) {
            return false;
        }

        if (!credit_count.equals(that.credit_count)) {
            return false;
        }

        if (!error_code.equals(that.error_code)) {
            return false;
        }

        if (!timestamp.equals(that.timestamp)) {
            return false;
        }

        if (!notice.equals(that.notice)) {
            return false;
        }

        return true;
    }

    public String getError_message ()
    {
        return error_message;
    }

    public void setError_message (String error_message)
    {
        this.error_message = error_message;
    }

    public String getElapsed ()
    {
        return elapsed;
    }

    public void setElapsed (String elapsed)
    {
        this.elapsed = elapsed;
    }

    public String getCredit_count ()
    {
        return credit_count;
    }

    public void setCredit_count (String credit_count)
    {
        this.credit_count = credit_count;
    }

    public String getError_code ()
    {
        return error_code;
    }

    public void setError_code (String error_code)
    {
        this.error_code = error_code;
    }

    public String getTimestamp ()
    {
        return timestamp;
    }

    public void setTimestamp (String timestamp)
    {
        this.timestamp = timestamp;
    }

    public String getNotice ()
    {
        return notice;
    }

    public void setNotice (String notice)
    {
        this.notice = notice;
    }

    @Override
    public String toString()
    {
        return "ClassPojo [error_message = "+error_message+", elapsed = "+elapsed+", credit_count = "+credit_count+", error_code = "+error_code+", timestamp = "+timestamp+", notice = "+notice+"]";
    }
}
