package edu.osu.dconvapp;

/**
 * Created by chirag on 6/11/17.
 */

public class DConvResults {
    public double[] b;
    public double [] e;
    public double [] m;
    public double i;
    public double[] y;

    public DConvResults(double[] b, double[] e, double[] m , double i , double[] y){
        this.b =b;
        this.e = e;
        this.m = m;
        this.y = y;
        this.i = i;
    }


    public DConvResults(double i ){
        this.i = i;
    }

}

