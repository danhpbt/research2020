package com.xynotec.research2020.data.remote.cryptocurrency.listting.latest;

import com.google.gson.annotations.Expose;
import com.google.gson.annotations.SerializedName;

import okhttp3.internal.platform.Platform;

public class Data
{
    @Expose
    @SerializedName("symbol")
    private String symbol;

    @Expose
    @SerializedName("circulating_supply")
    private String circulating_supply;

    @Expose
    @SerializedName("last_updated")
    private String last_updated;

    @Expose
    @SerializedName("total_supply")
    private String total_supply;

    @Expose
    @SerializedName("cmc_rank")
    private String cmc_rank;

    @Expose
    @SerializedName("platform")
    private Platform platform;

    @Expose
    @SerializedName("tags")
    private String[] tags;

    @Expose
    @SerializedName("date_added")
    private String date_added;

    @Expose
    @SerializedName("quote")
    private Quote quote;

    @Expose
    @SerializedName("num_market_pairs")
    private String num_market_pairs;

    @Expose
    @SerializedName("name")
    private String name;

    @Expose
    @SerializedName("max_supply")
    private String max_supply;

    @Expose
    @SerializedName("id")
    private String id;

    @Expose
    @SerializedName("slug")
    private String slug;

    public String getSymbol ()
    {
        return symbol;
    }

    public void setSymbol (String symbol)
    {
        this.symbol = symbol;
    }

    public String getCirculating_supply ()
    {
        return circulating_supply;
    }

    public void setCirculating_supply (String circulating_supply)
    {
        this.circulating_supply = circulating_supply;
    }

    public String getLast_updated ()
    {
        return last_updated;
    }

    public void setLast_updated (String last_updated)
    {
        this.last_updated = last_updated;
    }

    public String getTotal_supply ()
    {
        return total_supply;
    }

    public void setTotal_supply (String total_supply)
    {
        this.total_supply = total_supply;
    }

    public String getCmc_rank ()
    {
        return cmc_rank;
    }

    public void setCmc_rank (String cmc_rank)
    {
        this.cmc_rank = cmc_rank;
    }

    public Platform getPlatform ()
{
    return platform;
}

    public void setPlatform (Platform platform)
    {
        this.platform = platform;
    }

    public String[] getTags ()
    {
        return tags;
    }

    public void setTags (String[] tags)
    {
        this.tags = tags;
    }

    public String getDate_added ()
    {
        return date_added;
    }

    public void setDate_added (String date_added)
    {
        this.date_added = date_added;
    }

    public Quote getQuote ()
    {
        return quote;
    }

    public void setQuote (Quote quote)
    {
        this.quote = quote;
    }

    public String getNum_market_pairs ()
    {
        return num_market_pairs;
    }

    public void setNum_market_pairs (String num_market_pairs)
    {
        this.num_market_pairs = num_market_pairs;
    }

    public String getName ()
    {
        return name;
    }

    public void setName (String name)
    {
        this.name = name;
    }

    public String getMax_supply ()
    {
        return max_supply;
    }

    public void setMax_supply (String max_supply)
    {
        this.max_supply = max_supply;
    }

    public String getId ()
    {
        return id;
    }

    public void setId (String id)
    {
        this.id = id;
    }

    public String getSlug ()
    {
        return slug;
    }

    public void setSlug (String slug)
    {
        this.slug = slug;
    }

    @Override
    public String toString()
    {
        return "ClassPojo [symbol = "+symbol+", circulating_supply = "+circulating_supply+", last_updated = "+last_updated+", total_supply = "+total_supply+", cmc_rank = "+cmc_rank+", platform = "+platform+", tags = "+tags+", date_added = "+date_added+", quote = "+quote+", num_market_pairs = "+num_market_pairs+", name = "+name+", max_supply = "+max_supply+", id = "+id+", slug = "+slug+"]";
    }
}