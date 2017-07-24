//
// Created by 10206278 on 2017/7/18.
//

#ifndef GAUSSIANBLUR_BLUR_H
#define GAUSSIANBLUR_BLUR_H

#endif //GAUSSIANBLUR_BLUR_H

/**
 * 高斯模糊 RGBA_8888
 * @param bmp
 * @param width
 * @param height
 * @param radius
 */
void gaussBlurBmp(unsigned char *bmp, int width, int height, int radius);

/**
 * 高斯模糊 RGB_565
 * @param bmp
 * @param width
 * @param height
 * @param radius
 */
void gaussBlurBmp565(unsigned short *bmp, int width, int height, int radius);

/**
 * 递归高斯模糊算法 RGBA_8888
 * @param bmp
 * @param width
 * @param height
 * @param radius
 */
void recursiveBlurBmp(unsigned char *bmp, int width, int height, int radius);

/**
 * 递归高斯模糊算法 RGB_565
 * @param bmp
 * @param width
 * @param height
 * @param radius
 */
void recursiveBlurBmp565(unsigned short *bmp, int width, int height, int radius);