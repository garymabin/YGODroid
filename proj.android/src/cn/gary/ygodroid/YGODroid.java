/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package cn.gary.ygodroid;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.os.Bundle;
import android.os.PowerManager;
import android.os.PowerManager.WakeLock;
import android.util.Log;

public class YGODroid extends Cocos2dxActivity{
	private static final String TAG = "YGODroid";
	private PowerManager mPM;
	private WakeLock mLock;
	
    protected void onCreate(Bundle savedInstanceState){
    	Log.i(TAG, "onCreate, E:");
		super.onCreate(savedInstanceState);	
		mPM = (PowerManager) getSystemService(POWER_SERVICE);
		mLock = mPM.newWakeLock(PowerManager.SCREEN_DIM_WAKE_LOCK, TAG);
	}

    public Cocos2dxGLSurfaceView onCreateView() {
    	Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
    	// YGODroid should create stencil buffer
    	glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
    	
    	return glSurfaceView;
    }
    
    @Override
    protected void onStart() {
    	Log.i(TAG, "onStart, E:");
    	super.onStart();
    	mLock.acquire(); 
    }
    
    @Override
    protected void onPause() {
    	// TODO Auto-generated method stub
    	Log.i(TAG, "onPause, E:");
    	super.onPause();
    }
    
    @Override
    protected void onResume() {
    	// TODO Auto-generated method stub
    	Log.i(TAG, "onResume, E:");
    	super.onResume();
    }
    
    @Override
    protected void onStop() {
    	Log.i(TAG, "onStop, E:");
    	super.onStop();
    	mLock.release();
    }

    static {
        System.loadLibrary("cocos2dcpp");
    }     
}
