//
// Created by 10206278 on 2017/7/18.
//

#ifndef GAUSSIANBLUR_BLUR_H
#define GAUSSIANBLUR_BLUR_H

#endif //GAUSSIANBLUR_BLUR_H

/**
 * 高斯模糊
 * @param bmp
 * @param width
 * @param height
 * @param radius
 */
void gaussBlurBmp(unsigned char *bmp, int width, int height, int radius);

/**
 * 递归高斯模糊算法
 * @param bmp
 * @param width
 * @param height
 * @param radius
 */
void recursiveBlurBmp(unsigned char *bmp, int width, int height, int radius);