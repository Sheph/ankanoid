package com.ankanoid;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.view.MotionEvent;

class AnkanoidGLSurfaceView extends GLSurfaceView
{
    public AnkanoidGLSurfaceView(Context context)
    {
        super(context);
        ankanoidRenderer = new AnkanoidRenderer();
        setRenderer(ankanoidRenderer);
    }

    public boolean onTouchEvent(final MotionEvent event)
    {
        if (event.getAction() == MotionEvent.ACTION_DOWN)
        {            
        }
        return true;
    }

    AnkanoidRenderer ankanoidRenderer;   
}
