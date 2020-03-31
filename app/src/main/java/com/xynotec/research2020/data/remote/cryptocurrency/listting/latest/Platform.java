package com.xynotec.research2020.data.remote.cryptocurrency.listting.latest;

import com.google.gson.annotations.Expose;
import com.google.gson.annotations.SerializedName;

class Platform {

    @Expose
    @SerializedName("symbol")
    private String symbol;

    @Expose
    @SerializedName("name")
    private String name;

    @Expose
    @SerializedName("token_address")
    private String token_address;

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

    public String getName ()
    {
        return name;
    }

    public void setName (String name)
    {
        this.name = name;
    }

    public String getToken_address ()
    {
        return token_address;
    }

    public void setToken_address (String token_address)
    {
        this.token_address = token_address;
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
        return "ClassPojo [symbol = "+symbol+", name = "+name+", token_address = "+token_address+", id = "+id+", slug = "+slug+"]";
    }
}

