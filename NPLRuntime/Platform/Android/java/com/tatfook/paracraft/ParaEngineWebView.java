package com.tatfook.paracraft;

import android.annotation.SuppressLint;
import android.content.Context;
import android.util.Log;
import android.view.Gravity;
import android.webkit.WebChromeClient;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.FrameLayout;
import android.graphics.Bitmap;
import android.view.KeyEvent; 

import java.lang.reflect.Method;
import java.net.URI;
import java.util.concurrent.CountDownLatch;

class ShouldStartLoadingWorker implements Runnable {
    private CountDownLatch mLatch;
    private boolean[] mResult;
    private final int mViewTag;
    private final String mUrlString;

    ShouldStartLoadingWorker(CountDownLatch latch, boolean[] result, int viewTag, String urlString) {
        this.mLatch = latch;
        this.mResult = result;
        this.mViewTag = viewTag;
        this.mUrlString = urlString;
    }

    @Override
    public void run() {
        this.mResult[0] = ParaEngineWebViewHelper._shouldStartLoading(mViewTag, mUrlString);
        this.mLatch.countDown(); // notify that result is ready
    }
}


public class ParaEngineWebView extends WebView {
	
	private static final String TAG = "ParaEngine";

	private int mViewTag;
    private String mJSScheme;

	public ParaEngineWebView(Context context) {
        this(context, -1);
    }

	public int getViewTag() {
		return mViewTag;
	}

	@Override    
    public boolean onKeyUp(int keyCode, KeyEvent event) {    
        if ((keyCode == KeyEvent.KEYCODE_BACK)) {   
			Log.i("ParaEngine", "ParaEngineWebView::onKeyDown");

			ParaEngineWebViewHelper._onCloseView(this);
            return false; 
		}
        else {    
            return super.onKeyDown(keyCode, event);    
        }    
	}

	@SuppressLint("SetJavaScriptEnabled")
    public ParaEngineWebView(Context context, int viewTag) {
		super(context);

		this.setFocusable(true);
        this.setFocusableInTouchMode(true);

        this.getSettings().setSupportZoom(false);

        this.getSettings().setDomStorageEnabled(true);
        this.getSettings().setJavaScriptEnabled(true);

		//this.setAlpha(0.5f);

        // `searchBoxJavaBridge_` has big security risk. http://jvn.jp/en/jp/JVN53768697
        try {
            Method method = this.getClass().getMethod("removeJavascriptInterface", new Class[]{String.class});
            method.invoke(this, "searchBoxJavaBridge_");
        } catch (Exception e) {
            Log.d(TAG, "This API level do not support `removeJavascriptInterface`");
        }

        this.setWebViewClient(new ParaEngineWebViewClient());
        this.setWebChromeClient(new WebChromeClient());
	}

	class ParaEngineWebViewClient extends WebViewClient {
        @Override
        public boolean shouldOverrideUrlLoading(WebView view, final String urlString) {

			//view.loadUrl(urlString); 
			//return true;

            AppActivity activity = (AppActivity)getContext();
		
            try {
                URI uri = URI.create(urlString);
                if (uri != null && uri.getScheme().equals(mJSScheme)) {
	                activity.runOnGLThread(new Runnable() {
                        @Override
                        public void run() {
                            ParaEngineWebViewHelper._onJsCallback(mViewTag, urlString);
                        }
                    });
                    return true;
                }
            } catch (Exception e) {
                Log.d(TAG, "Failed to create URI from url");
            }

            boolean[] result = new boolean[] { true };
            CountDownLatch latch = new CountDownLatch(1);
            // run worker on gl thread
            activity.runOnGLThread(new ShouldStartLoadingWorker(latch, result, mViewTag, urlString));
            // wait for result from gl thread
            try {
                latch.await();
            } catch (InterruptedException ex) {
                Log.d(TAG, "'shouldOverrideUrlLoading' failed");
            }

			//if (result[0])
			//	view.loadUrl(urlString);

            return result[0];
			
        }


        @Override
        public void onPageFinished(WebView view, final String url) {

            super.onPageFinished(view, url);
            AppActivity activity = (AppActivity)getContext();
            activity.runOnGLThread(new Runnable() {
                @Override
                public void run() {
                    ParaEngineWebViewHelper._didFinishLoading(mViewTag, url);
                }
            });
        }

        @Override
        public void onReceivedError(WebView view, int errorCode, String description, final String failingUrl) {

            super.onReceivedError(view, errorCode, description, failingUrl);
            AppActivity activity = (AppActivity)getContext();
            activity.runOnGLThread(new Runnable() {
                @Override
                public void run() {
                    ParaEngineWebViewHelper._didFailLoading(mViewTag, failingUrl);
                }
            });
        }
    }

	public void setJavascriptInterfaceScheme(String scheme) {
        this.mJSScheme = scheme != null ? scheme : "";
    }


	public void setWebViewRect(int left, int top, int maxWidth, int maxHeight) {
        FrameLayout.LayoutParams layoutParams = new FrameLayout.LayoutParams(FrameLayout.LayoutParams.WRAP_CONTENT,
                FrameLayout.LayoutParams.WRAP_CONTENT);
        layoutParams.leftMargin = left;
        layoutParams.topMargin = top;
        layoutParams.width = maxWidth;
        layoutParams.height = maxHeight;
        layoutParams.gravity = Gravity.TOP | Gravity.LEFT;
        this.setLayoutParams(layoutParams);
    }

	public void setScalesPageToFit(boolean scalesPageToFit) {
        this.getSettings().setSupportZoom(scalesPageToFit);
    }

}