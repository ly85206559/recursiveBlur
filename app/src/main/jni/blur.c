//
// Created by 10206278 on 2017/7/18.
//

#include <stdlib.h>
#include "blur.h"
#include "gaussian_blur.h"
#include "recursive_blur.h"

/**
 * 加载RGB分量
 * @param bmp
 * @param rComp
 * @param gComp
 * @param bComp
 */
void
loadRGBComp(unsigned char *bmp, unsigned char *rComp, unsigned char *gComp, unsigned char *bComp);

/**
 * 将计算好的RGB分量重置回原BMP数组
 * @param bmp
 * @param rComp
 * @param gComp
 * @param bComp
 */
void
setBmpComp(unsigned char *bmp, unsigned char *rComp, unsigned char *gComp, unsigned char *bComp);

static int width;
static int height;

void gaussBlurBmp(unsigned char *bmp, int w, int h, int r) {
    unsigned char *rComp, *gComp, *bComp;
    double *weightArr;

    width = w;
    height = h;

    rComp = malloc(sizeof(unsigned char) * w * h);
    gComp = malloc(sizeof(unsigned char) * w * h);
    bComp = malloc(sizeof(unsigned char) * w * h);

    loadRGBComp(bmp, rComp, gComp, bComp);

    weightArr = malloc(sizeof(double) * (2 * r + 1));
    calculateWeightMatrix(weightArr, r);
    calculateNormalizedWeightMatrix(weightArr, r * 2 + 1);

    calculateHorizonComp(rComp, weightArr, w, h, r);
    calculateHorizonComp(gComp, weightArr, w, h, r);
    calculateHorizonComp(bComp, weightArr, w, h, r);

    calculateVerticalComp(rComp, weightArr, w, h, r);
    calculateVerticalComp(gComp, weightArr, w, h, r);
    calculateVerticalComp(bComp, weightArr, w, h, r);

    setBmpComp(bmp, rComp, gComp, bComp);

    free(rComp);
    free(gComp);
    free(bComp);
    free(weightArr);
}

void recursiveBlurBmp(unsigned char *bmp, int width, int height, int radius) {
    float *in, *out;
    GaussRecursive gaussRecursive;
    int channel, bytes = 4;
    int row, col, pos;
    int channelSize = width * height;

    in = (float *) malloc(sizeof(float) * width * height);
    out = (float *) malloc(sizeof(float) * width * height);
    computeGaussRecursive(&gaussRecursive, radius);
    for (channel = 0; channel < 3; channel++) {
        for (int i = 0, pos = channel; i < channelSize; i++, pos += bytes) {
            /* 0-255 => 1-256 */
            in[i] = (float) (bmp[pos] + 1.0);
        }

        /*
           *  Filtering (smoothing) Gaussian recursive.
           *
           *  Filter rows first
           */
        for (row = 0; row < height; row++) {
            pos = row * width;
            gaussSmooth(in + pos, out + pos, width, 1, &gaussRecursive);
        }

//        memcpy(in, out, sizeof(float) * channelSize);
//        memset(out, 0, sizeof(float) * channelSize);

        /*
         *  Filtering (smoothing) Gaussian recursive.
         *
         *  Second columns
         */
        for (col = 0; col < width; col++) {
            pos = col;
            gaussSmooth(out + pos, in + pos, height, width, &gaussRecursive);
        }

        for (int i = 0, pos = channel; i < channelSize; i++, pos += bytes) {
            bmp[pos] = in[i] - 1;
        }
    }

    free(in);
    free(out);
}

void
loadRGBComp(unsigned char *bmp, unsigned char *rComp, unsigned char *gComp, unsigned char *bComp) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width * 4; j += 4) {
            *rComp = *(bmp + i * width * 4 + j);
            *gComp = *(bmp + i * width * 4 + j + 1);
            *bComp = *(bmp + i * width * 4 + j + 2);
            rComp++;
            gComp++;
            bComp++;
        }
    }
}

void
setBmpComp(unsigned char *bmp, unsigned char *rComp, unsigned char *gComp, unsigned char *bComp) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width * 4; j += 4) {
            *(bmp + i * (width * 4) + j) = *rComp;
            *(bmp + i * (width * 4) + j + 1) = *gComp;
            *(bmp + i * (width * 4) + j + 2) = *bComp;
            bComp++;
            gComp++;
            rComp++;
        }
    }
}