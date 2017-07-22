//
// Created by Ben on 2017/7/19.
//

#ifndef GAUSSIANBLUR_RECURSIVE_BLUR_H
#define GAUSSIANBLUR_RECURSIVE_BLUR_H

#endif //GAUSSIANBLUR_RECURSIVE_BLUR_H

typedef struct {
    float sigma;
    double B;
    double b[4];
} GaussRecursive;

/**
 * 计算递归模型参数
 * @param gr
 * @param sigma
 */
void computeGaussRecursive(GaussRecursive *gr, float sigma);

/**
 * 计算递归高斯数据
 * @param in
 * @param out
 * @param size
 * @param rowStride
 * @param gr
 */
void
gaussSmooth(float *in, float *out, int size, int rowStride, GaussRecursive *gr);