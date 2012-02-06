package com.ankanoid;

import android.app.Activity;
import android.os.Bundle;

public class AnkanoidActivity extends Activity
{      
    private AnkanoidGLSurfaceView glView;
    
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        glView = new AnkanoidGLSurfaceView(this);
        setContentView(glView);
    }
    
    @Override
    protected void onPause()
    {
        super.onPause();
        glView.onPause();
    }

    @Override
    protected void onResume()
    {
        super.onResume();
        glView.onResume();
    }    
}
