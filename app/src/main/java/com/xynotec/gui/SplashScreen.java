package com.xynotec.gui;



import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.util.TypedValue;

import androidx.appcompat.app.AppCompatActivity;

import com.xynotec.research2020.R;
import com.xynotec.research2020.ui.main.MainActivity;

public class SplashScreen extends AppCompatActivity
{   
	final static int SPLASH_TIME = 500;

	@Override
	protected void onCreate(Bundle savedInstanceState)
	{
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);

		setContentView(R.layout.xynotec_splash);


		new Handler().postDelayed(new Runnable() {
        	 
            /*
             * Showing splash screen with a timer. This will be useful when you
             * want to show case your app logo / company
             */
 
            @Override
            public void run() {
                // This method will be executed once the timer is over
                // Start your app main activity
            	Intent i = new Intent(SplashScreen.this, MainActivity.class);
				//Intent i = new Intent(SplashScreen.this, LoginActivity.class);
				startActivity(i);

                // close this activity
                finish();
            }
        }, SPLASH_TIME);

	}

}

