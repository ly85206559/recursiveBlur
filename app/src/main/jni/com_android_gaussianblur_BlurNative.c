#include "com_android_gaussianblur_BlurNative.h"
#include <android/bitmap.h>
#include "blur.h"

JNIEXPORT void JNICALL
Java_com_android_gaussianblur_BlurNative_blurPixels(JNIEnv *env, jclass type, jintArray img_,
                                                    jint w, jint h, jint r) {
    jint *img = (*env)->GetIntArrayElements(env, img_, NULL);

    // TODO

    (*env)->ReleaseIntArrayElements(env, img_, img, 0);
}

JNIEXPORT void JNICALL
Java_com_android_gaussianblur_BlurNative_gaussBlurBitmap(JNIEnv *env, jclass type, jobject bitmap,
                                                         jint r) {
    AndroidBitmapInfo bitmapInfo;
    if (AndroidBitmap_getInfo(env, bitmap, &bitmapInfo) < 0) {
        return;
    }

    unsigned char *data = NULL;
    AndroidBitmap_lockPixels(env, bitmap, &data);

    gaussBlurBmp(data, bitmapInfo.width, bitmapInfo.height, r);

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

    unsigned char *data = NULL;
    AndroidBitmap_lockPixels(env, bitmap, &data);

    recursiveBlurBmp(data, bitmapInfo.width, bitmapInfo.height, r);

    AndroidBitmap_unlockPixels(env, bitmap);
}