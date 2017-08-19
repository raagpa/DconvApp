package edu.osu.dconvapp;

import android.graphics.Color;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.Editable;
import android.widget.Button;
import android.widget.SeekBar;
import android.widget.TextView;
import android.view.View;
import android.widget.EditText;

import android.content.Intent;
import android.content.SharedPreferences;
import android.preference.PreferenceManager;


public class MainActivity extends AppCompatActivity {

    public static final String X_STRING = "edu.osu.dconvapp.X_STRING";
    public static final String H_STRING = "edu.osu.dconvapp.Y_STRING";

     Button runButton ;
     EditText xEdit;

     EditText hEdit ;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        /*TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());*/

        runButton = (Button)findViewById(R.id.button2);
        xEdit = (EditText) findViewById(R.id.xeditTextID);

        hEdit = (EditText)findViewById(R.id.heditText);






        runButton.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                // Code here executes on main thread after user presses button
                //callDconvAndUpdatePlots(xEdit, errorMsgText, hEdit, seekBar, grapheb, graphm, graphy);

                launchResultActivity(xEdit, hEdit);

            }
        });




    }

    public void launchResultActivity(EditText xEdit, EditText hEdit){

        Intent intent = new Intent(this, ResultsActivity.class);
        String xString = xEdit.getText().toString();
        intent.putExtra(X_STRING, xString);

        String hString = hEdit.getText().toString();
        intent.putExtra(H_STRING, hString);

        startActivity(intent);
    }


    private void loadSavedPreferences() {
        SharedPreferences sharedPreferences = PreferenceManager
                .getDefaultSharedPreferences(this);

        xEdit.setText(sharedPreferences.getString("string_x",""));
        hEdit.setText(sharedPreferences.getString("string_h",""));

    }
    private void savePreferences(String key, String value) {
        SharedPreferences sharedPreferences = PreferenceManager
                .getDefaultSharedPreferences(this);
        SharedPreferences.Editor editor = sharedPreferences.edit();
        editor.putString(key, value);
        editor.commit();
    }
    public void saveData(){
        savePreferences("string_x", xEdit.getText().toString());
        savePreferences("string_h", hEdit.getText().toString());
    }
    @Override
    public void onPause(){
        saveData();
        super.onPause();
    }

    @Override
    public void onResume(){
        loadSavedPreferences();
        super.onResume();
    }






}
