//
// Created by Ben on 2017/7/19.
//

#include <math.h>
#include <malloc.h>
#include "recursive_blur.h"

void computeGaussRecursive(GaussRecursive *gr, float sigma) {
/*
   * Papers:  "Recursive Implementation of the gaussian filter.",
   *          Ian T. Young , Lucas J. Van Vliet, Signal Processing 44, Elsevier 1995.
   * formula: 11b       computation of q
   *          8c        computation of b0..b1
   *          10        alpha is normalization constant B
   */
    double q, q2, q3;

    if (sigma >= 2.5) {
        q = 0.98711 * sigma - 0.96330;
    } else if ((sigma >= 0.5) && (sigma < 2.5)) {
        q = 3.97156 - 4.14554 * sqrt(1 - 0.26891 * sigma);
    } else {
        q = 0.1147705018520355224609375;
    }

    q2 = q * q;
    q3 = q * q2;
    gr->b[0] = (1.57825 + (2.44413 * q) + (1.4281 * q2) + (0.422205 * q3));
    gr->b[1] = ((2.44413 * q) + (2.85619 * q2) + (1.26661 * q3));
    gr->b[2] = (-((1.4281 * q2) + (1.26661 * q3)));
    gr->b[3] = ((0.422205 * q3));
    gr->B = 1.0 - ((gr->b[1] + gr->b[2] + gr->b[3]) / gr->b[0]);

    gr->b[1] = gr->b[1] / gr->b[0];
    gr->b[2] = gr->b[2] / gr->b[0];
    gr->b[3] = gr->b[3] / gr->b[0];
    gr->sigma = sigma;
}

void
gaussSmooth(float *in, float *out, int size, int rowStride, GaussRecursive *gr) {
    /*
     * Papers:  "Recursive Implementation of the gaussian filter.",
     *          Ian T. Young , Lucas J. Van Vliet, Signal Processing 44, Elsevier 1995.
     * formula: 9a        forward filter
     *          9b        backward filter
     *          fig7      algorithm
     */
    int i, n, bufsize;
    float *w1, *w2;

    /* forward pass */
    bufsize = size + 3;
    size -= 1;
    w1 = (float *) malloc(bufsize * sizeof(float));
    w2 = (float *) malloc(bufsize * sizeof(float));
    w1[0] = in[0];
    w1[1] = in[0];
    w1[2] = in[0];
    for (i = 0, n = 3; i <= size; i++, n++) {
        w1[n] = (float) (gr->B * in[i * rowStride] +
                         (gr->b[1] * w1[n - 1] +
                          gr->b[2] * w1[n - 2] +
                          gr->b[3] * w1[n - 3]));
    }

    /* backward pass */
    w2[size + 1] = w1[size + 3];
    w2[size + 2] = w1[size + 3];
    w2[size + 3] = w1[size + 3];
    for (i = size, n = i; i >= 0; i--, n--) {
        w2[n] = out[i * rowStride] = (float) (gr->B * w1[n] +
                                              (gr->b[1] * w2[n + 1] +
                                               gr->b[2] * w2[n + 2] +
                                               gr->b[3] * w2[n + 3]));
    }

    /**
     * 防止图片整体向右下角偏移
     */
    for (int i = 0; i <= size - 3; i++) {
        out[i * rowStride] = out[(i + 3) * rowStride];
    }

    free(w1);
    free(w2);
}