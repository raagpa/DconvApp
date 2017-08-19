package edu.osu.dconvapp;

import android.content.Intent;
import android.graphics.Color;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.widget.EditText;
import android.widget.SeekBar;
import android.widget.TextView;

import com.jjoe64.graphview.GraphView;
import com.jjoe64.graphview.GridLabelRenderer;
import com.jjoe64.graphview.LegendRenderer;
import com.jjoe64.graphview.series.DataPoint;
import com.jjoe64.graphview.series.PointsGraphSeries;

import java.util.Arrays;

public class ResultsActivity extends AppCompatActivity {


    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_results);


        final SeekBar seekBar = (SeekBar) findViewById(R.id.seekBarID);


        final GraphView grapheb = (GraphView) findViewById(R.id.grapheb);
        final GraphView graphm = (GraphView) findViewById(R.id.graphm);
        final GraphView graphy = (GraphView) findViewById(R.id.graphy);

        graphm.setTitle("m");
        graphy.setTitle("y");

        /*GridLabelRenderer gridLabelm = graphm.getGridLabelRenderer();
        gridLabelm.setVerticalAxisTitle("m");*/


        /*GridLabelRenderer gridLabely = graphy.getGridLabelRenderer();
        gridLabely.setVerticalAxisTitle("y");*/


        // Get the Intent that started this activity and extract the string
        Intent intent = getIntent();
        final String xString = intent.getStringExtra(MainActivity.X_STRING);
        final String hString = intent.getStringExtra(MainActivity.H_STRING);


        if (!xString.isEmpty() || !hString.isEmpty()) {

            String[] x = xString.split(" ");
            String[] h = hString.split(" ");
            seekBar.setMax(x.length + h.length);
        } else {
            seekBar.setMax(0);
        }


        callDconvAndUpdatePlots(xString, hString, seekBar, grapheb, graphm, graphy);


        seekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                // TODO Auto-generated method stub
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
                // TODO Auto-generated method stub
            }

            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                callDconvAndUpdatePlots(xString, hString, seekBar, grapheb, graphm, graphy);


            }
        });
    }


    private void callDconvAndUpdatePlots(String xValue, String hValue, SeekBar seekBar, GraphView grapheb, GraphView graphm, GraphView graphy) {

        double [] x = createDoubleArray(xValue.trim());

        double [] h = createDoubleArray(hValue.trim());

        double s = seekBar.getProgress();

        System.out.println("s : " + s);
        double[] i_ ={0};


        if(x[0] != -1 && h[0] != -1) {
            int len_x = x.length;
            int len_h = h.length;

            int len_e = 2 * len_h + len_x;
            int len_b = 2 * len_h + len_x;
            int len_m = 2 * len_h + len_x;
            int len_y = 2 * len_h + len_x - 1;
            double b[] = new double[len_b];
            double e[] = new double[len_e];
            double m[] = new double[len_m];
            double y[] = new double[len_y];



            dconvolution(x, h, s, b, e, m, y, i_);

            System.out.println("X");

            for (int k = 0; k < x.length; k++) {
                System.out.println(x[k]);

            }

            System.out.println("H");

            for (int k = 0; k < h.length; k++) {
                System.out.println(h[k]);

            }

            System.out.println("E");

            for (int k = 0; k < e.length; k++) {
                System.out.println(e[k]);

            }

            System.out.println("M");
            for (int k = 0; k < m.length; k++) {
                System.out.println(m[k]);

            }
            System.out.println("B");
            for (int k = 0; k < b.length; k++) {
                System.out.println(b[k]);

            }

            System.out.println("Y");
            for (int k = 0; k < y.length; k++) {
                System.out.println(y[k]);

            }


            System.out.println(i_[0]);
            ploteb(b, e, grapheb);

            plotmy(m,y, graphm, graphy);

        }
    }

    private void ploteb(double[] b, double[] e, GraphView grapheb) {
        DataPoint e_val[] = new DataPoint[e.length] ;
        for(int i=0; i<e.length; i++) {
            e_val[i] = new DataPoint(i+1, e[i]);
        }

        PointsGraphSeries<DataPoint> e_series = new PointsGraphSeries<DataPoint>( e_val );
        e_series.setTitle("e");

        grapheb.removeAllSeries();
        grapheb.addSeries(e_series);

        GridLabelRenderer gridLabele = grapheb.getGridLabelRenderer();
        //gridLabele.setVerticalAxisTitle("b,e");


        DataPoint b_val[] = new DataPoint[b.length] ;
        for(int i=0; i<e.length; i++) {
            b_val[i] = new DataPoint(i+1, b[i]);
        }

        PointsGraphSeries<DataPoint> b_series = new PointsGraphSeries<>(b_val);
        b_series.setColor(Color.GREEN);
        b_series.setTitle("b");

        // graphb.removeAllSeries();
        grapheb.addSeries(b_series);

        grapheb.getLegendRenderer().setVisible(true);
        grapheb.getLegendRenderer().setAlign(LegendRenderer.LegendAlign.TOP);
        grapheb.getViewport().setMaxX(e.length);

        Arrays.sort(e);
        double maxe = e[e.length - 1];

        Arrays.sort(b);
        double maxb = b[b.length - 1];

        double max = 0;
        if(maxb >maxe){
            max = maxb;

        }else{
            max = maxe;
        }

        grapheb.getViewport().setMaxY(max);

        grapheb.getViewport().setYAxisBoundsManual(true);
        grapheb.getViewport().setXAxisBoundsManual(true);
    }


    private void plotmy(double[] m, double[] y, GraphView graphm, GraphView graphy) {
        DataPoint m_val[] = new DataPoint[m.length] ;
        for(int i=0; i<m.length; i++) {
            m_val[i] = new DataPoint(i+1, m[i]);
        }

        PointsGraphSeries<DataPoint> m_series = new PointsGraphSeries<DataPoint>( m_val );

        graphm.removeAllSeries();
        graphm.addSeries(m_series);



        graphm.getViewport().setMaxX(m.length);

        Arrays.sort(m);
        double maxm = m[m.length - 1];

        graphm.getViewport().setMaxY(maxm);
        System.out.print( "Max m : " + maxm);

        graphm.getViewport().setYAxisBoundsManual(true);
        graphm.getViewport().setXAxisBoundsManual(true);


        DataPoint y_val[] = new DataPoint[y.length] ;
        for(int i=0; i<y.length; i++) {
            y_val[i] = new DataPoint(i+1, y[i]);
        }

        PointsGraphSeries<DataPoint> y_series = new PointsGraphSeries<DataPoint>(y_val);


        graphy.removeAllSeries();
        graphy.addSeries(y_series);

        graphy.getViewport().setMaxX(y.length);

        Arrays.sort(y);
        double maxy = y[y.length - 1];

        graphm.getViewport().setMaxY(maxy);
        System.out.print( "Max y : " + maxy);

        graphy.getViewport().setYAxisBoundsManual(true);
        graphy.getViewport().setXAxisBoundsManual(true);


    }

    private double[] createDoubleArray(String value) {
        if (value != null || !value.isEmpty()){
            try {
                String[] array = value.split(" ");
                double mlArray[] = new double[array.length];
                for (int i = 0; i < array.length; i++) {
                    mlArray[i] = Double.parseDouble(array[i]);
                }

                // call FromApp Method
                System.out.println();
                for (int i = 0; i < array.length; i++) {
                    System.out.println(mlArray[i]);
                }

                return mlArray;
            }catch(Exception e){
                // errorMsgText.setText("Incorrect Values Entered");
            }
        }else{
            // errorMsgText.setText("Incorrect Values Entered");
        }

        return new double[]{-1};
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */

    public native void dconvolution(double[] x, double[] h , double s, double[] b, double[] e, double[] m, double[] y, double i[]);



}

