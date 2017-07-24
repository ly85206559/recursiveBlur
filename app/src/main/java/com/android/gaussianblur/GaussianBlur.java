package com.android.gaussianblur;

import android.graphics.Bitmap;

/**
 * Created by Ben.li on 2017/7/13.
 */

public class GaussianBlur extends BlurNative {

    private static Bitmap buildBitmap(Bitmap bitmap, boolean canReuseInBitmap) {
        // If can reuse in bitmap return this or copy
        Bitmap rBitmap;
        if (canReuseInBitmap) {
            rBitmap = bitmap;
        } else {
            rBitmap = bitmap.copy(bitmap.getConfig(), true);
        }
        return (rBitmap);
    }

    /**
     * Blur By Jni Bitmap
     *
     * @param original         Original Image
     * @param radius           Blur radius
     * @param canReuseInBitmap Can reuse In original Bitmap
     * @return Image Bitmap
     */
    public static Bitmap gaussBlurNatively(Bitmap original, int radius, boolean canReuseInBitmap) {
        if (radius < 1) {
            return null;
        }

        Bitmap bitmap = buildBitmap(original, canReuseInBitmap);

        // Return this none blur
        if (radius == 1) {
            return bitmap;
        }

        //Jni BitMap Blur
        gaussBlurBitmap(bitmap, radius);

        return (bitmap);
    }

    /**
     * Blur By Jni Bitmap
     *
     * @param original         Original Image
     * @param radius           Blur radius
     * @param canReuseInBitmap Can reuse In original Bitmap
     * @return Image Bitmap
     */
    public static Bitmap recursiveBlurNatively(Bitmap original, int radius, boolean canReuseInBitmap) {
        if (radius < 1) {
            return null;
        }

        Bitmap bitmap = buildBitmap(original, canReuseInBitmap);

        // Return this none blur
        if (radius == 1) {
            return bitmap;
        }

        //Jni BitMap Blur
        recursiveBlurBitmap(bitmap, radius);

        return (bitmap);
    }
}
