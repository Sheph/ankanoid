package com.ankanoid;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.view.MotionEvent;

class AnkanoidGLSurfaceView extends GLSurfaceView
{
    public AnkanoidGLSurfaceView(Context context)
    {
        super(context);
        ankanoidRenderer = new AnkanoidRenderer(context);
        setRenderer(ankanoidRenderer);
    }

    public boolean onTouchEvent(final MotionEvent event)
    {   
    	AnkanoidJNILib.input(
			(int)event.getRawX(),
			(int)event.getRawY(),
			(event.getAction() == MotionEvent.ACTION_UP) );    	     
        return true;
    }

    AnkanoidRenderer ankanoidRenderer;   
}
