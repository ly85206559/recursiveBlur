#include "com_android_gaussianblur_BlurNative.h"
#include <android/bitmap.h>
#include "blur.h"

JNIEXPORT void JNICALL
Java_com_android_gaussianblur_BlurNative_gaussBlurBitmap(JNIEnv *env, jclass type, jobject bitmap,
                                                         jint r) {
    AndroidBitmapInfo bitmapInfo;
    if (AndroidBitmap_getInfo(env, bitmap, &bitmapInfo) < 0) {
        return;
    }

    void *data = NULL;

    if (ANDROID_BITMAP_FORMAT_RGBA_8888 == bitmapInfo.format) {
        AndroidBitmap_lockPixels(env, bitmap, (unsigned char *) &data);
        gaussBlurBmp(data, bitmapInfo.width, bitmapInfo.height, r);
    } else if (ANDROID_BITMAP_FORMAT_RGB_565 == bitmapInfo.format) {
        AndroidBitmap_lockPixels(env, bitmap, (unsigned short *) &data);
        gaussBlurBmp565(data, bitmapInfo.width, bitmapInfo.height, r);
    }

    AndroidBitmap_unlockPixels(env, bitmap);
}

JNIEXPORT void JNICALL
Java_com_android_gaussianblur_BlurNative_recursiveBlurBitmap(JNIEnv *env, jclass type,
                                                             jobject bitmap,
                                                             jint r) {
    AndroidBitmapInfo bitmapInfo;
    if (AndroidBitmap_getInfo(env, bitmap, &bitmapInfo) < 0) {
        return;
    }

    void *data = NULL;

    if (ANDROID_BITMAP_FORMAT_RGBA_8888 == bitmapInfo.format) {
        AndroidBitmap_lockPixels(env, bitmap, (unsigned char *) &data);
        recursiveBlurBmp(data, bitmapInfo.width, bitmapInfo.height, r);
    } else if (ANDROID_BITMAP_FORMAT_RGB_565 == bitmapInfo.format) {
        AndroidBitmap_lockPixels(env, bitmap, (unsigned short *) &data);
        recursiveBlurBmp565(data, bitmapInfo.width, bitmapInfo.height, r);
    }

    AndroidBitmap_unlockPixels(env, bitmap);
}