package com.android.gaussianblur;

import android.graphics.Bitmap;

/**
 * Created by Ben.li on 2017/7/13.
 */

public class BlurNative {

    /**
     * Load blur jni file
     */
    static {
        System.loadLibrary("fast_blur");
    }

    /**
     * Blur Image By Bitmap
     *
     * @param bitmap Img Bitmap
     * @param r      Blur radius
     */
    protected static native void recursiveBlurBitmap(Bitmap bitmap, int r);

    /**
     * @param bitmap
     * @param r
     */
    protected static native void gaussBlurBitmap(Bitmap bitmap, int r);
}
