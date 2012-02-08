package com.ankanoid;

public class AnkanoidJNILib
{
     static
     {
         System.loadLibrary("ankanoidjni");
     }
       
     public static native void init(String apkPath);
     public static native void resize(int w, int h);
     public static native void render();
}
