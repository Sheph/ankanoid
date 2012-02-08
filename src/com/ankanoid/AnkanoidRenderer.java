package com.ankanoid;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.content.Context;
import android.content.pm.PackageManager.NameNotFoundException;
import android.opengl.GLSurfaceView;

class AnkanoidRenderer implements GLSurfaceView.Renderer
{
	private Context context;
	
	public AnkanoidRenderer(Context context)
	{
		this.context = context;
	}
	
    public void onSurfaceCreated(GL10 gl, EGLConfig config)
    {    	    							
		try
		{			
			AnkanoidJNILib.init(
				context.getPackageManager().getApplicationInfo("com.ankanoid", 0).sourceDir );
	    }
		catch (NameNotFoundException e)
		{
		    throw new RuntimeException("Unable to locate assets, aborting...");
	    }					
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
