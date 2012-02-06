package com.ankanoid;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.opengl.GLSurfaceView;

class AnkanoidRenderer implements GLSurfaceView.Renderer
{
    public void onSurfaceCreated(GL10 gl, EGLConfig config)
    {
    	AnkanoidJNILib.init();        
    }

    public void onSurfaceChanged(GL10 gl, int w, int h)
    {
    	AnkanoidJNILib.resize(w, h);
    }

    public void onDrawFrame(GL10 gl)
    {
        AnkanoidJNILib.render();
    }   
}
