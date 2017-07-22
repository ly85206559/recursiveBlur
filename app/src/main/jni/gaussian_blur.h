//
// Created by Ben.li on 2017/7/11.
//

#ifndef GAUSSIAN_BLUR_H
#define GAUSSIAN_BLUR_H

#endif //GAUSSIAN_BLUR_H

/**
 * 获取权重值
 * @param x 取值从-radius到radius
 * @param radius 模糊半径
 * @return
 */
double getWeight(int x, int radius);

/**
 * 计算权重数组的权重值
 * @param weightArr
 * @param radius 模糊半径
 */
void calculateWeightMatrix(double *weightArr, int radius);

/**
 * 计算归一化的权重数组
 * @param weightArr
 * @param out
 * @param length
 */
void calculateNormalizedWeightMatrix(double *weightArr, int length);

/**
 * 水平方向处理图片高斯模糊
 * @param data
 * @param weightArr
 * @param width
 * @param height
 * @param radius
 */
void
calculateHorizonComp(unsigned char *data, double *weightArr, int width, int height, int radius);

/**
 * 垂直方向处理图片高斯模糊
 * @param data
 * @param weightArr
 * @param width
 * @param height
 * @param radius
 */
void
calculateVerticalComp(unsigned char *data, double *weightArr, int width, int height, int radius);