package com.xynotec.utils;

public class MathUtils {

    public static float roundFloat(float value, int decimal)
    {
        double pow = Math.pow(10, decimal);
        return (float)(Math.round(value*pow)/pow);
    }

    public static double roundDouble(double value, int decimal)
    {
        double pow = Math.pow(10, decimal);
        return Math.round(value*pow)/pow;
    }

}
